#include "Required.h"

pcmd_t CommandByName(char* szName)
{
	pcmd_t pCmd = nullptr;
	pCmd = g_Engine.pfnGetCmdList();

	while (pCmd)
	{
		if (!strcmp(pCmd->name, szName))
			return pCmd;
		pCmd = pCmd->next;
	}

	return NULL;
}

UserMsg UserMsgByName(char* szMsgName)
{
	UserMsg Ptr = nullptr;
	Ptr = pUserMsgBase;

	while (Ptr->next)
	{
		if (!strcmp(Ptr->szName, szMsgName))
			return Ptr;
		Ptr = Ptr->next;
	}

	Ptr->pfn = 0;
	return Ptr;
}

pfnUserMsgHook HookUserMsg(char *szMsgName, pfnUserMsgHook pfn)
{
	UserMsg Ptr = nullptr;
	pfnUserMsgHook Original = nullptr;
	Ptr = UserMsgByName(szMsgName);

	if (Ptr->pfn != 0) {
		Original = Ptr->pfn;
		Ptr->pfn = pfn;
		return Original;
	}
	else
	{
		g_Offsets.Error(szMsgName);
		return NULL;
	}
}

bool VHookTable::HookTable(DWORD dwTablePtrPtr)
{
	DWORD dwIndexFunction = 0;

	dwPtrPtrTable = dwTablePtrPtr;
	dwPtrOldTable = *(PDWORD)dwPtrPtrTable;

	for (dwIndexFunction = 0; ((PDWORD)*(PDWORD)dwTablePtrPtr)[dwIndexFunction]; dwIndexFunction++)
		if (IsBadCodePtr((FARPROC)((PDWORD)*(PDWORD)dwTablePtrPtr)[dwIndexFunction]))
			break;

	dwSizeTable = sizeof(DWORD) * dwIndexFunction;

	if (dwIndexFunction && dwSizeTable)
	{
		dwPtrNewTable = (DWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeTable);
		memcpy((PVOID)dwPtrNewTable, (PVOID)*(PDWORD)dwTablePtrPtr, dwSizeTable);

		*(PDWORD)dwTablePtrPtr = dwPtrNewTable;

		return true;
	}

	return false;
}

void VHookTable::HookIndex(DWORD dwIndex, PVOID pAddress)
{
	((PDWORD)dwPtrNewTable)[dwIndex] = (DWORD)pAddress;
}

DWORD VHookTable::RetHookIndex(DWORD dwIndex, PVOID pAddress)
{
	DWORD old = ((PDWORD)dwPtrNewTable)[dwIndex];
	((PDWORD)dwPtrNewTable)[dwIndex] = (DWORD)pAddress;
	return old;
}

void VHookTable::UnHook()
{
	if (dwPtrPtrTable)
		*(PDWORD)dwPtrPtrTable = dwPtrOldTable;
}

void VHookTable::ReHook()
{
	if (dwPtrPtrTable)
		*(PDWORD)dwPtrPtrTable = dwPtrNewTable;
}