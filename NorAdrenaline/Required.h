#include <SDKDDKVer.h>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include "Wininet.h"
#include <comdef.h>
#include <Wbemidl.h>
#include <sstream>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib,"Wininet.lib")

#define M_PI 3.14159265358979323846
#include "Vector.h"
#include "QAngle.h"
#define vec3_t Vector

#include "Structures.h"
#include "Offsets.h"
#include "Hook.h"
#include "detours.h"
#include "StudioModelRenderer.h"

#define VIRTUALIZER_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \

#define VIRTUALIZER_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0D \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \

typedef void(*Snapshot_t)();
typedef void(*Screenshot_t)();
typedef void(*PreS_DynamicSound_t)(int, DWORD, char *, float *, float, float, int, int);
typedef void(*CL_Move_t)();

extern cl_clientfunc_t *g_pClient;
extern cl_clientfunc_t g_Client;
extern cl_enginefunc_t *g_pEngine;
extern cl_enginefunc_t g_Engine;
extern engine_studio_api_t *g_pStudio;
extern engine_studio_api_t g_Studio;
extern playermove_t *pmove;
extern UserMsg pUserMsgBase;
extern VHookTable PanelHook;
extern SCREENINFO g_Screen;
extern Snapshot_t Snapshot_s;
extern Screenshot_t Screenshot_s;
extern CL_Move_t CL_Move_s;
extern PreS_DynamicSound_t PreS_DynamicSound_s;
extern StudioModelRenderer_t g_StudioModelRenderer;
extern StudioModelRenderer_t* g_pStudioModelRenderer;

void HookClient();
void WINAPI PaintTraversePanel(vgui::IPanel* vguiPanel, bool forceRepaint, bool allowForce);
void AntiScreen();
void HookOpenGL();

std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);
std::string encryptDecrypt(std::string toEncrypt);
string StringToHex(const string input);

string GetUrlData(string url);

#include "Hack\Hack.h"
#include "Usermsg.h"