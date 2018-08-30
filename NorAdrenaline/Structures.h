#include "ValveSDK\common\interface.h"
#include "ValveSDK\common\wrect.h"
#include "ValveSDK\common\cl_dll.h"
#include "ValveSDK\engine\cdll_int.h"
#include "ValveSDK\common\r_studioint.h"
#include "ValveSDK\common\com_model.h"
#include "ValveSDK\common\cl_entity.h"
#include "ValveSDK\common\ref_params.h"
#include "ValveSDK\pm_shared\pm_defs.h"
#include "ValveSDK\pm_shared\pm_movevars.h"
#include "ValveSDK\engine\studio.h"
#include "ValveSDK\parsemsg.h"
#include "ValveSDK\common\cvardef.h"
#include "ValveSDK\common\triangleapi.h"
#include "ValveSDK\common\pmtrace.h"
#include "ValveSDK\common\event_api.h"
#include "ValveSDK\common\r_efx.h"
#include "ValveSDK\common\entity_types.h"
#include "ValveSDK\common\screenfade.h"
#include "ValveSDK\common\net_api.h"

#include "ValveSDK\VGUI\VGUI_Frame.h"
#include "ValveSDK\VGUI\VGUI_Panel.h"
#include "ValveSDK\GameUI\IVGuiModuleLoader.h"
#include "ValveSDK\GameUI\IRunGameEngine.h"
#include "ValveSDK\GameUI\IGameUI.h"
#include "ValveSDK\GameUI\IGameConsole.h"
#include "ValveSDK\VGUI2\IHTML.h"
#include "ValveSDK\VGUI2\IPanel.h"
#include "ValveSDK\VGUI2\ISurface.h"
#include "ValveSDK\VGUI2\IEngineVGui.h"

#include <gl\GL.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "vgui.lib")

using namespace std;

typedef float TransformMatrix[MAXSTUDIOBONES][3][4];

#define VectorTransform(a,b,c){(c)[0]=a.Dot((b)[0])+(b)[0][3];(c)[1]=a.Dot((b)[1])+(b)[1][3];(c)[2]=a.Dot((b)[2])+(b)[2][3];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}

#define DEFAULT_FOV	90	// the default field of view

#define PM_DEAD_VIEWHEIGHT	-8

#define PM_VEC_DUCK_VIEW			12
#define PM_VEC_VIEW	17

#define OBS_NONE				0
#define OBS_CHASE_LOCKED		1
#define OBS_CHASE_FREE			2
#define OBS_ROAMING				3
#define OBS_IN_EYE				4
#define OBS_MAP_FREE			5
#define OBS_MAP_CHASE			6

#define BOMB_FLAG_DROPPED	0 // if the bomb was dropped due to voluntary dropping or death/disconnect
#define BOMB_FLAG_PLANTED	1 // if the bomb has been planted will also trigger the round timer to hide will also show where the dropped bomb on the Terrorist team's radar.

#define NUMBLOOPS 50.0f
#define TIMEALIVE 3.00f
#define OLDDAMPER 1.75f 
#define NEWDAMPER 0.75f
#define SVGRAVITY 3.75f
#define FLOORSTOP 0.20f

#define ARMOR_RATIO			0.5	// Armor Takes 50% of the damage
#define ARMOR_BONUS	0.5	// Each Point of Armor is work 1/x points of health

#define MAX_BOMB_RADIUS	2048

#define M_PI_F	((float)(M_PI)) // Shouldn't collide with anything.
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x ) ( (float)(x) * (float)(M_PI_F / 180.f) )

// player data iuser3
#define PLAYER_CAN_SHOOT		(1<<0)
#define PLAYER_FREEZE_TIME_OVER		(1<<1)
#define PLAYER_IN_BOMB_ZONE		(1<<2)
#define PLAYER_HOLDING_SHIELD		(1<<3)

#define MAX_PLAYER_NAME_LENGTH	32

struct CImageTexture
{
	unsigned int index;
	unsigned int width;
	unsigned int height;
};

enum FontRenderFlag_t
{
	FONT_LEFT = 0,
	FONT_RIGHT = 1,
	FONT_CENTER = 2
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
};

enum ArmorType
{
	ARMOR_NONE,	// no armor
	ARMOR_KEVLAR,	// body vest only
	ARMOR_VESTHELM,	// vest and helmet
};

enum CursorCode
{
	dc_user,
	dc_none,
	dc_arrow,
	dc_ibeam,
	dc_hourglass,
	dc_waitarrow,
	dc_crosshair,
	dc_up,
	dc_sizenwse,
	dc_sizenesw,
	dc_sizewe,
	dc_sizens,
	dc_sizeall,
	dc_no,
	dc_hand,
	dc_blank, // don't show any custom vgui cursor, just let windows do it stuff (for HTML widget)
	dc_last,
};

enum
{
	SEQUENCE_IDLE = 0,
	SEQUENCE_SHOOT = 1,
	SEQUENCE_RELOAD = 2,
	SEQUENCE_DIE = 4,
	SEQUENCE_THROW = 8,
	SEQUENCE_ARM_C4 = 16,
	SEQUENCE_SHIELD = 32,
	SEQUENCE_SHIELD_SIDE = 64
};

enum TeamName
{
	UNASSIGNED,
	TERRORIST,
	CT,
	SPECTATOR,
};

class CBomb
{
public:
	Vector vOrigin;
	int iFlag;
};

typedef void(*xcommand_t)(void);
typedef struct cmd_s
{
	struct cmd_s *next;
	const char *name;
	xcommand_t function;
	int flags;
} cmd_t, *pcmd_t;

typedef struct _UserMsg
{
	int iMsg;
	int iSize;
	char szName[16];
	struct _UserMsg* next;
	pfnUserMsgHook pfn;
} *UserMsg;

typedef struct
{
	Vector origin;

	char *name;

	DWORD timestamp;

	int id;
} my_sound_t;

struct CBasePlayerWeapon
{
	bool m_bDelayFire;
	unsigned int random_seed;
	int m_iWeaponState;
	int m_iFlags;
	int m_iClip;
	int m_iWeaponID;
	int m_iInReload;
	int iPenetration;
	int iBulletType;
	int iDamage1;
	int iDamage2;
	int m_iShotsFired;
	int iuser3;
	float prevtime;
	float curtime;
	float m_flDecreaseShotsFired;
	float m_flAccuracy;
	float m_flSpread;
	float m_flNextPrimaryAttack;
	float m_flNextSecondaryAttack;
	float m_flNextAttack;
	float flPenetrationDistance;
	float flWallPierce1;
	float flWallPierce2;
};

struct info_map_parameters
{
	const char *levelname;

	float m_flBombRadius;
};

struct player_extra_info_t
{
	char *szWeaponName;

	Vector vHitbox[21];
	Vector vHitboxMin[21];
	Vector vHitboxMax[21];
	Vector vHitboxPoints[21][8];

	bool bHitboxVisible[21];
	bool bHitboxPointsVisible[21][8];
	bool bHitboxBehindTheWall[21];
	bool bHitboxPointsBehindTheWall[21][8];

	float fHitboxFOV[21];
};

typedef struct cl_clientfuncs_s
{
	int(*Initialize) (cl_enginefunc_t *pEnginefuncs, int iVersion);
	int(*HUD_Init) (void);
	int(*HUD_VidInit) (void);
	void(*HUD_Redraw) (float time, int intermission);
	int(*HUD_UpdateClientData) (client_data_t *pcldata, float flTime);
	int(*HUD_Reset) (void);
	void(*HUD_PlayerMove) (struct playermove_s *ppmove, int server);
	void(*HUD_PlayerMoveInit) (struct playermove_s *ppmove);
	char(*HUD_PlayerMoveTexture) (char *name);
	void(*IN_ActivateMouse) (void);
	void(*IN_DeactivateMouse) (void);
	void(*IN_MouseEvent) (int mstate);
	void(*IN_ClearStates) (void);
	void(*IN_Accumulate) (void);
	void(*CL_CreateMove) (float frametime, struct usercmd_s *cmd, int active);
	int(*CL_IsThirdPerson) (void);
	void(*CL_CameraOffset) (float *ofs);
	struct kbutton_s *(*KB_Find) (const char *name);
	void(*CAM_Think) (void);
	void(*V_CalcRefdef) (struct ref_params_s *pparams);
	int(*HUD_AddEntity) (int type, struct cl_entity_s *ent, const char *modelname);
	void(*HUD_CreateEntities) (void);
	void(*HUD_DrawNormalTriangles) (void);
	void(*HUD_DrawTransparentTriangles) (void);
	void(*HUD_StudioEvent) (const struct mstudioevent_s *event, const struct cl_entity_s *entity);
	void(*HUD_PostRunCmd) (struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed);
	void(*HUD_Shutdown) (void);
	void(*HUD_TxferLocalOverrides) (struct entity_state_s *state, const struct clientdata_s *client);
	void(*HUD_ProcessPlayerState) (struct entity_state_s *dst, const struct entity_state_s *src);
	void(*HUD_TxferPredictionData) (struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd);
	void(*Demo_ReadBuffer) (int size, unsigned char *buffer);
	int(*HUD_ConnectionlessPacket) (struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size);
	int(*HUD_GetHullBounds) (int hullnumber, float *mins, float *maxs);
	void(*HUD_Frame) (double time);
	int(*HUD_Key_Event) (int down, int keynum, const char *pszCurrentBinding);
	void(*HUD_TempEntUpdate) (double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int(*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void(*Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp));
	struct cl_entity_s *(*HUD_GetUserEntity) (int index);
	int(*HUD_VoiceStatus) (int entindex, qboolean bTalking);
	int(*HUD_DirectorMessage) (unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags);
	int(*HUD_GetStudioModelInterface) (int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio);
	void(*HUD_CHATINPUTPOSITION_FUNCTION) (int *x, int *y);
	void(*CLIENTFACTORY) (void);
	int(*HUD_GETPLAYERTEAM_FUNCTION) (int iplayer);
} cl_clientfunc_t;