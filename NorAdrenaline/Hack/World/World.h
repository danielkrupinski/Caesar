class CWorld;
class CWorld {
public:
	void Reset();
	void UpdateVisibility(int id);
	void ClearLocalPlayer();
	void ClearPlayers();
	void ClearEntities();
	void ClearMapInfo();
	void Update(float frametime, struct usercmd_s *cmd);
	void UpdateLocalPlayer(float frametime, struct usercmd_s *cmd);
	void UpdatePlayers();
	void UpdateEntities();
	void GetHitboxes(struct cl_entity_s *ent);
	void UpdateMapInfo();
};
extern CWorld World;

class CBaseLocal
{
public:
	int iIndex;
	int iTeam;
	int iHealth;
	int iArmor;
	int iFOV;
	int iMaxHitboxes;

	float flFrametime;
	float flFPS;
	float flVelocity;
	float flHeightGround;
	float flGroundAngle;
	float flHeight;
	float flHeightPlane;

	bool bAlive;
	bool bScoped;

	Vector vViewAngles;
	Vector vOrigin;
	Vector vEye;
	Vector vForward;
	Vector vRight;
	Vector vUp;
	Vector vPunchangle;
	Vector vNoSpreadAngle;
	Vector vNoRecoilAngle;

	CBomb Bomb;

	CBasePlayerWeapon weapon;

	net_status_s status;
};
extern CBaseLocal g_Local;

extern hud_player_info_t g_PlayerInfoList[MAX_CLIENTS + 1];
extern player_extra_info_t g_PlayerExtraInfoList[MAX_CLIENTS + 1];

class CBasePlayer
{
public:
	int iTeam;
	int iHealth;
	int iArmorType;
	int iShotsFired;

	bool bUpdated;
	bool bAlive;
	bool bAliveInScoreTab;
	bool bDucked;
	bool bVisible;
	bool bFriend;
	bool bPriority;
	bool bBehindTheWall;

	float flFrametime;
	float flDist;

	Vector vAngles;
	Vector vVelocity;
	Vector vOrigin;
	Vector vPrevOrigin;

	DWORD dwHistory;
};
extern CBasePlayer g_Player[MAX_CLIENTS + 1];

class CBaseEntity
{
public:
	char *szModelName;

	unsigned int iIndex;
	unsigned int iResolvedIndex;

	bool bUpdated;
	bool bIsFakeEntity;
	bool bIsWeapon;

	Vector vOrigin;
};
extern CBaseEntity g_Entities[256];

extern info_map_parameters g_MapInfo;