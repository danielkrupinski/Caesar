#include "Required.h"

pfnUserMsgHook pResetHUD;
pfnUserMsgHook pBombDrop;
pfnUserMsgHook pBattery;
pfnUserMsgHook pHealth;
pfnUserMsgHook pDeathMsg;
pfnUserMsgHook pSetFOV;
pfnUserMsgHook pTeamInfo;
pfnUserMsgHook pScoreAttrib;

int ScoreAttrib(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	byte PlayerID = READ_BYTE();
	byte Flags = READ_BYTE();

	g_Player[PlayerID].bAliveInScoreTab = !(Flags & (1 << 0));

	return pScoreAttrib(pszName, iSize, pbuf);
}

int TeamInfo(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	int iIndex = READ_BYTE();
	char *szTeam = READ_STRING();

	int iLocalIndex = 0;
	cl_entity_s *pLocal = g_Engine.GetLocalPlayer();
	if (pLocal) iLocalIndex = pLocal->index;

	if (iIndex > 0 && iIndex <= g_Engine.GetMaxClients()) 
	{
		if (!lstrcmpA(szTeam, "TERRORIST"))
		{
			if (iIndex == iLocalIndex)
				g_Local.iTeam = TERRORIST;
			else
				g_Player[iIndex].iTeam = TERRORIST;
		}
		else if (!lstrcmpA(szTeam, "CT"))
		{
			if (iIndex == iLocalIndex)
				g_Local.iTeam = CT;
			else
				g_Player[iIndex].iTeam = CT;
		}
		else
		{
			if (iIndex == iLocalIndex)
				g_Local.iTeam = UNASSIGNED;
			else
				g_Player[iIndex].iTeam = UNASSIGNED;
		}
	}

	return pTeamInfo(pszName, iSize, pbuf);
}

int SetFOV(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	int iFOV = READ_BYTE();

	g_Local.iFOV = iFOV;

	if (iFOV == DEFAULT_FOV)
		g_Local.bScoped = false;
	else if(iFOV > 0)
		g_Local.bScoped = true;

	if (cvar.remove_scope && g_Local.bScoped) 
	{
		iFOV = DEFAULT_FOV;

		return (*pSetFOV)(pszName, iSize, &iFOV);
	}

	return (*pSetFOV)(pszName, iSize, pbuf);
}

int BombDrop(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	g_Local.Bomb.vOrigin[0] = READ_COORD();
	g_Local.Bomb.vOrigin[1] = READ_COORD();
	g_Local.Bomb.vOrigin[2] = READ_COORD();

	g_Local.Bomb.iFlag = READ_BYTE();

	return pBombDrop(pszName, iSize, pbuf);
}

int ResetHUD(const char *pszName, int iSize, void *pbuf)
{
	g_Local.Bomb.iFlag = BOMB_FLAG_DROPPED;

	for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
	{
		if (i == g_Local.iIndex)
			continue;

		g_Player[i].iArmorType = ARMOR_NONE;
		g_Player[i].iHealth = 100;
		g_Player[i].iShotsFired = 0;
	}

	return pResetHUD(pszName, iSize, pbuf);
}

int Battery(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	g_Local.iArmor = READ_BYTE();

	return pBattery(pszName, iSize, pbuf);
}

int Health(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	g_Local.iHealth = READ_BYTE();

	return pHealth(pszName, iSize, pbuf);
}

int DeathMsg(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	int KillerID = READ_BYTE();
	int VictimID = READ_BYTE();
	int IsHeadshot = READ_BYTE();
	char *TruncatedWeaponName = READ_STRING();

	if (KillerID != VictimID && KillerID == g_Local.iIndex && VictimID > 0 && VictimID <= g_Engine.GetMaxClients())
		g_AimBot.dwReactionTime = GetTickCount();

	if (VictimID != g_Local.iIndex) 
	{
		g_Player[VictimID].iHealth = 100;
		g_Player[VictimID].iArmorType = ARMOR_NONE;
		g_Player[VictimID].iShotsFired = 0;
	}

	return pDeathMsg(pszName, iSize, pbuf);
}