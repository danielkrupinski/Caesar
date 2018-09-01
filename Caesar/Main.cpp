#include "Required.h"
#include <Shlobj.h>
#include "Reflective\ReflectiveLoader.h"

IVGuiModuleLoader* g_pIVGuiModuleLoader = nullptr;
IRunGameEngine* g_pIRunGameEngine = nullptr;
IGameUI* g_pGameUI = nullptr;
IGameConsole* g_pConsole = nullptr;
vgui::IPanel* g_pIPanel = nullptr;
vgui::ISurface* g_pISurface = nullptr;
vgui::IEngineVGui* g_pIEngineVGui = nullptr;
cl_clientfunc_t *g_pClient = nullptr;
cl_clientfunc_t g_Client;
cl_enginefunc_t *g_pEngine = nullptr;
cl_enginefunc_t g_Engine;
engine_studio_api_t *g_pStudio = nullptr;
engine_studio_api_t g_Studio;
playermove_t *pmove = nullptr;
UserMsg pUserMsgBase = nullptr;
Snapshot_t Snapshot_s = nullptr;
Screenshot_t Screenshot_s = nullptr;
CL_Move_t CL_Move_s = nullptr;
PreS_DynamicSound_t PreS_DynamicSound_s = nullptr;
StudioModelRenderer_t g_StudioModelRenderer;
StudioModelRenderer_t* g_pStudioModelRenderer = nullptr;

VHookTable PanelHook;

LRESULT CALLBACK Hooked_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		g_Menu.keys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		g_Menu.keys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		g_Menu.keys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		g_Menu.keys[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		g_Menu.keys[wParam] = true;
		break;
	case WM_KEYUP:
		g_Menu.keys[wParam] = false;
		break;
	default: break;
	}

	return CallWindowProc(g_pGlobals.WndProcBackup, hwnd, uMsg, wParam, lParam);
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

string GetUrlData(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
		return request_data;

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "hack.ovh", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	if (!hHttpSession)
		return request_data;

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str(), "HTTP/1.1", NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID, NULL);

	if (!hHttpSession)
		return request_data;

	char* szHeaders = "Content-Type: text/html\r\nUser-Agent: NorAdrenaline";
	char szRequest[1024] = { 0 };

	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
		return request_data;

	CHAR szBuffer[1024] = { 0 };
	DWORD dwRead = 0;

	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
		request_data.append(szBuffer, dwRead);

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return request_data;
}

DWORD WINAPI Hook(LPVOID lpThreadParameter)
{
	CreateInterfaceFn gameui_factory = CaptureFactory("gameui.dll");
	CreateInterfaceFn vgui2_factory = CaptureFactory("vgui2.dll");
	CreateInterfaceFn hardware_factory = CaptureFactory("hw.dll");
	CreateInterfaceFn client_factory = CaptureFactory("client.dll");

	if (gameui_factory && vgui2_factory && hardware_factory && client_factory)
	{
		VIRTUALIZER_START
		while (!g_Offsets.FindHardware())
			Sleep(100);

		g_pIVGuiModuleLoader = (IVGuiModuleLoader*)(CaptureInterface(gameui_factory, VGUIMODULELOADER_INTERFACE_VERSION));
		g_pIRunGameEngine = (IRunGameEngine*)(CaptureInterface(gameui_factory, RUNGAMEENGINE_INTERFACE_VERSION));
		g_pGameUI = (IGameUI*)(CaptureInterface(gameui_factory, GAMEUI_INTERFACE_VERSION));
		g_pConsole = (IGameConsole*)(CaptureInterface(gameui_factory, GAMECONSOLE_INTERFACE_VERSION));
		g_pIPanel = (vgui::IPanel*)(CaptureInterface(vgui2_factory, VGUI_PANEL_INTERFACE_VERSION));
		g_pISurface = (vgui::ISurface*)(CaptureInterface(hardware_factory, VGUI_SURFACE_INTERFACE_VERSION));
		g_pIEngineVGui = (vgui::IEngineVGui*)(CaptureInterface(hardware_factory, VENGINE_VGUI_VERSION));
		g_pClient = (cl_clientfunc_t*)g_Offsets.FindClient();
		g_pEngine = (cl_enginefunc_t*)g_Offsets.FindEngine();
		g_pStudio = (engine_studio_api_t*)g_Offsets.FindStudio();
		g_pStudioModelRenderer = (StudioModelRenderer_t*)g_Offsets.FindStudioModelRenderer();

		/*if (License())
		{
			g_Offsets.Error("Bad license.");
			return 1;
		}*/
		
		while (!g_Client.V_CalcRefdef)
			RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t));

		while (!g_Engine.V_CalcShake)
			RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t));

		while (!g_Studio.StudioSetupSkin)
			RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));

		while (!g_StudioModelRenderer.StudioSlerpBones)
			RtlCopyMemory(&g_StudioModelRenderer, g_pStudioModelRenderer, sizeof(StudioModelRenderer_t));

		while (!pmove)
			pmove = (playermove_t*)g_Offsets.FindPlayerMove();

		while (!pUserMsgBase)
			pUserMsgBase = g_Offsets.FindUserMsgBase();

		g_Drawing.SetupFonts();

		if (PanelHook.HookTable((DWORD)g_pIPanel))
		{
			PanelHook.HookIndex(41, PaintTraversePanel);
		}

		g_NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x17);

		if (IsBadReadPtr(g_NoFlash.pScreenFade, sizeof(screenfade_t)))
			g_NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x18);

		g_Offsets.GlobalTime();

		g_Offsets.dwSpeedPointer = (DWORD)g_Offsets.FindSpeed();

		while (!g_pGlobals.hWindow)
		{
			if (!(g_pGlobals.hWindow = FindWindowA("Valve001", NULL)))
				g_pGlobals.hWindow = FindWindowA(NULL, "Counter-Strike");

			Sleep(200);
		}

		lstrcpyA(g_pGlobals.IniPath, g_Utils.szDirFile(HACK_FILE));

		g_pGlobals.WndProcBackup = (WNDPROC)SetWindowLongA(g_pGlobals.hWindow, GWL_WNDPROC, (LONG_PTR)&Hooked_WndProc);

		HookClient();
		VIRTUALIZER_END
	}

	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_QUERY_HMODULE)
	{
		if (lpReserved != NULL)
			*(HMODULE *)lpReserved = hAppInstance;
	}
	else if (dwReason == DLL_PROCESS_ATTACH)
	{
		hAppInstance = hinstDLL;

		DisableThreadLibraryCalls(hinstDLL);

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, g_pGlobals.BaseDir)))
		{
			GetModuleFileNameA(NULL, g_pGlobals.GamePath, MAX_PATH);

			char* pos = g_pGlobals.GamePath + strlen(g_pGlobals.GamePath);
			while (pos >= g_pGlobals.GamePath && *pos != '\\') --pos; pos[1] = 0;

			pos = g_pGlobals.BaseDir + strlen(g_pGlobals.BaseDir);
			while (pos >= g_pGlobals.BaseDir && *pos != '\\') --pos; pos[1] = 0;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hook, NULL, NULL, NULL);
		}
	}
	return TRUE;
}
