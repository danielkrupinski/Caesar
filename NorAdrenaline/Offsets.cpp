#include "Required.h"

COffsets g_Offsets;

void COffsets::Error(PCHAR msg)
{
	MessageBoxA(NULL, msg, "FATAL ERROR", MB_OK | MB_ICONERROR);
	TerminateProcess(GetCurrentProcess(), 0);
}

void COffsets::PatchInterpolation(void)
{
	static bool patched = false;

	if (patched)
		return;

	DWORD Address = FindPush(hardware.base, hardware.end, "cl_updaterate minimum is %f") - 0x18;

	native_memwrite(Address, (uintptr_t)"\xEB", 1);

	Address = FindPush(hardware.base, hardware.end, "cl_updaterate maximum is %f") - 0x18;

	native_memwrite(Address, (uintptr_t)"\xEB", 1);

	Address = FindPush(hardware.base, hardware.end, "ex_interp forced up to %i msec\n");
	Address = FindPattern("\x7D", Address-0x9, Address, 0);

	native_memwrite(Address, (uintptr_t)"\xEB", 1);

	Address = FindPush(hardware.base, hardware.end, "ex_interp forced down to %i msec\n") - 0x5;

	native_memwrite(Address, (uintptr_t)"\xEB", 1);

	patched = true;
}

DWORD COffsets::FindSpeed(void)
{
	DWORD Address = FindPattern("Texture load: %6.1fms", hardware.base, hardware.end, 0);
	PVOID SpeedPtr = (PVOID)*(DWORD*)(FindReference(hardware.base, hardware.end, Address) - 7);

	if (FarProc((DWORD)SpeedPtr, hardware.base, hardware.end))
		Error("Speed: not found.");
	else
		EnablePageWrite((DWORD)SpeedPtr, sizeof(double));

	return (DWORD)SpeedPtr;
}

DWORD COffsets::CL_Move(void)
{
	DWORD Address = FindPattern("\x56\x57\x33\xFF\x3B\xC7\x0F\x84\x00\x00\x00\x00\x83\xF8\x01\x0F\x84\x00\x00\x00\x00\x83\xF8\x02\x0F\x84\x00\x00\x00\x00\x83\xF8\x03\x75\x22", "xxxxxxx????xxxxx????xxxxx????xxxxx", hardware.base, hardware.end, 0);

	if (FarProc((DWORD)Address, hardware.base, hardware.end))
		Error("CL_Move: not found.");
	else {
		Address = FindPattern("\xC3\x90", "xx", Address - 0x12, hardware.end, 0x2);

		if (FarProc((DWORD)Address, hardware.base, hardware.end))
			Error("CL_Move: #2 not found.");
	}

	return Address;
}

void COffsets::GlobalTime()
{
	dwSendPacketPointer = FindPattern("\x75\x13\xD9\x05\x00\x00\x00\x00\xD8\x1D\x00\x00\x00\x00\xDF\xE0\xF6\xC4\x00\x00\x00\xD9\x05\x00\x00\x00\x00\xDC\x1D\x00\x00\x00\x00\xDF\xE0\xF6\xC4\x41", "xxxx????xx????xxxx???xx????xx????xxxxx", hardware.base, hardware.end, 0x1b) + 2;

	if (FarProc(dwSendPacketPointer, hardware.base, hardware.end))
		Error("dwSendPacket: not found.");

	dwSendPacketBackup = *((uintptr_t *)(dwSendPacketPointer));

	EnablePageWrite(dwSendPacketPointer, sizeof(DWORD));
}

PVOID COffsets::FindStudioModelRenderer(void)
{
	DWORD Address = FindPattern("\x56\x8B\xF1\xE8\xFF\xFF\xFF\xFF\xC7\x06\xFF\xFF\xFF\xFF\xC6\x86\xFF\xFF\xFF\xFF\xFF\x8B\xC6\x5E\xC3", "xxxx????xx????xx?????xxxx", client.base, client.end, 0);

	if (FarProc((DWORD)Address, client.base, client.end))
		Error("StudioModelRenderer: not found.");

	return (void*)*(DWORD*)(Address + 0x0A);
}

DWORD COffsets::PreS_DynamicSound(void)
{
	DWORD Address = Absolute(FindPush(hardware.base, hardware.end, "CL_Parse_Sound: ent = %i, cl.max_edicts %i") - 0x10);

	if (FarProc(Address, hardware.base, hardware.end))
	{
		Address = Absolute(FindPush(hardware.base, hardware.end, "CL_Parse_Sound: ent = %i, cl.max_edicts %i") - 0x11);

		if (FarProc(Address, hardware.base, hardware.end))
			Error("PreS_DynamicSound: not found.");

		return Address;
	}

	return Address;
}

UserMsg COffsets::FindUserMsgBase(void)
{
	DWORD Address = (DWORD)g_Engine.pfnHookUserMsg;

	DWORD UserMsgBase = Absolute(FindPattern("\x52\x50\xE8\xFF\xFF\xFF\xFF\x83", "xxx????x", Address, Address + 0x32, 3));

	if (FarProc(UserMsgBase, hardware.base, hardware.end))
		Error("UserMsg: not found.");

	UserMsgBase = FindPattern("\xFF\xFF\xFF\x0C\x56\x8B\x35\xFF\xFF\xFF\xFF\x57", "???xxxx????x", UserMsgBase, UserMsgBase + 0x32, 7);

	if (FarProc(UserMsgBase, hardware.base, hardware.end))
		Error("UserMsg: #2 not found.");

	return UserMsg(**(PDWORD*)UserMsgBase);
}

PVOID COffsets::FindPlayerMove(void)
{
	DWORD Address = FindPattern("ScreenFade", hardware.base, hardware.end, 0);
	PVOID Ptr = (PVOID)*(PDWORD)(FindReference(hardware.base, hardware.end, Address) + 0x18);

	if (FarProc((DWORD)Ptr, hardware.base, hardware.end))
		Error("PlayerMove: not found.");

	return Ptr;
}

PVOID COffsets::FindEngine(void)
{
	PVOID Pointer = (cl_enginefunc_t*)*(DWORD*)((DWORD)g_pClient->Initialize + 0x22); // old patch

	if (FarProc((DWORD)Pointer, hardware.base, hardware.end))
	{
		Pointer = (cl_enginefunc_t*)*(DWORD*)((DWORD)g_pClient->Initialize + 0x1C); // new patch

		if (FarProc((DWORD)Pointer, client.base, client.end))
		{
			Pointer = (cl_enginefunc_t*)*(DWORD*)((DWORD)g_pClient->Initialize + 0x1D); // steam

			if (FarProc((DWORD)Pointer, client.base, client.end))
			{
				Pointer = (cl_enginefunc_t*)*(DWORD*)((DWORD)g_pClient->Initialize + 0x37); // hl-steam

				if (FarProc((DWORD)Pointer, client.base, client.end))
					Error("Engine: not found.");
			}
		}
	}

	return Pointer;
}

PVOID COffsets::FindStudio(void)
{
	PVOID Pointer = (engine_studio_api_t*)*(DWORD*)((DWORD)g_pClient->HUD_GetStudioModelInterface + 0x30);

	if (FarProc((DWORD)Pointer, hardware.base, hardware.end))
	{
		Pointer = (engine_studio_api_t*)*(DWORD*)((DWORD)g_pClient->HUD_GetStudioModelInterface + 0x1A);

		if (FarProc((DWORD)Pointer, client.base, client.end))
			Error("Studio: not found.");
	}

	return Pointer;
}

PVOID COffsets::FindClient(void)
{
	DWORD Address = FindPattern((PCHAR)"ScreenFade", hardware.base, hardware.end, 0);
	PVOID Pointer = (PVOID)*(PDWORD)(FindReference(hardware.base, hardware.end, Address) + 0x13); // all patch

	if (FarProc((DWORD)Pointer, hardware.base, hardware.end))
		Error("Client: not found.");

	return Pointer;
}

bool COffsets::FindHardware(void)
{
	if (!FindModuleByName("hw.dll", &hardware))
		return false;

	if (!FindModuleByName("client.dll", &client))
		return false;

	if (!FindModuleByName("gameui.dll", &gameui))
		return false;

	if (!FindModuleByName("vgui2.dll", &vgui2))
		return false;

	return true;
}

DWORD COffsets::Absolute(DWORD Address)
{
	return Address + *(PDWORD)Address + 4;
}

DWORD COffsets::FarProc(const DWORD Address, DWORD LB, DWORD HB)
{
	return ((Address < LB) || (Address > HB));
}

DWORD COffsets::FindReference(DWORD start, DWORD end, DWORD Address)
{
	char szPattern[] = { 0x68 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
	*(PDWORD)&szPattern[1] = Address;
	return FindPattern(szPattern, start, end, 0);
}

DWORD COffsets::FindPush(DWORD start, DWORD end, PCHAR Message)
{
	char bPushAddrPattern[] = { 0x68 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
	DWORD Address = FindPattern(Message, start, end, 0);
	*(PDWORD)&bPushAddrPattern[1] = Address;
	Address = FindPattern((PCHAR)bPushAddrPattern, start, end, 0);
	return Address;
}

DWORD COffsets::GetModuleSize(DWORD Address)
{
	return PIMAGE_NT_HEADERS(Address + (DWORD)PIMAGE_DOS_HEADER(Address)->e_lfanew)->OptionalHeader.SizeOfImage;
}

bool COffsets::FindModuleByName(const char *moduleName, Module *module)
{
	if (!moduleName || !*moduleName || !module)
		return false;

	HMODULE hModuleDll = GetModuleHandle(moduleName);

	if (!hModuleDll)
		return false;

	module->base = (DWORD)hModuleDll;
	module->size = GetModuleSize(module->base);
	module->end = module->base + module->size - 1;

	return true;
}

bool COffsets::EnablePageWrite(DWORD addr, DWORD size)
{
	return VirtualProtect((void *)addr, size, PAGE_EXECUTE_READWRITE, &dwOldPageProtection) != 0;
}

bool COffsets::RestorePageProtection(DWORD addr, DWORD size)
{
	bool ret = VirtualProtect((void *)addr, size, dwOldPageProtection, &dwOldPageProtection) != 0;
	FlushInstructionCache(GetCurrentProcess(), (void *)addr, size);
	return ret;
}

DWORD COffsets::FindPattern(PCHAR pattern, PCHAR mask, DWORD start, DWORD end, DWORD offset)
{
	if (start > end)
	{
		DWORD reverse = end;
		end = start;
		start = reverse;
	}

	size_t patternLength = strlen(pattern);
	bool found = false;

	for (DWORD i = start; i < end - patternLength; i++)
	{
		found = true;

		for (size_t idx = 0; idx < patternLength; idx++)
		{
			if (mask[idx] == 'x' && pattern[idx] != *(PCHAR)(i + idx))
			{
				found = false;
				break;
			}
		}

		if (found)
			return i + offset;
	}

	return 0;
}

DWORD COffsets::FindPattern(PCHAR pattern, DWORD start, DWORD end, DWORD offset)
{
	if (start > end)
	{
		DWORD reverse = end;
		end = start;
		start = reverse;
	}

	size_t patternLength = strlen(pattern);
	bool found = false;

	for (DWORD i = start; i < end - patternLength; i++)
	{
		found = true;

		for (size_t idx = 0; idx < patternLength; idx++)
		{
			if (pattern[idx] != *(PCHAR)(i + idx))
			{
				found = false;
				break;
			}
		}

		if (found)
			return i + offset;
	}

	return 0;
}