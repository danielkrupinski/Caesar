#include "../../Required.h"
#include <io.h>

CUtils g_Utils;

unsigned int Cstrike_SequenceInfo[] =
{
	0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // 0..9   
	0,    1,    2,    0,    1,    2,    0,    1,    2,    0, // 10..19 
	1,    2,    0,    1,    1,    2,    0,    1,    1,    2, // 20..29 
	0,    1,    2,    0,    1,    2,    0,    1,    2,    0, // 30..39 
	1,    2,    0,    1,    2,    0,    1,    2,    0,    1, // 40..49 
	2,    0,    1,    2,    0,    0,    0,    8,    0,    8, // 50..59 
	0,    16,   0,   16,    0,    0,    1,    1,    2,    0, // 60..69
	1,    1,    2,    0,    1,    0,    1,    0,    1,    2, // 70..79 
	0,    1,    2,   32,   40,   32,   40,   32,   32,   32, // 80..89
	33,   32,   33,   34,   64,    4,   34,   32,   32,    4, // 90..99
	4,    4,    4,    4,    4,    4,    4,    4,    4,    4, // 100..109
	4														 // 110
};

void native_memwrite(uintptr_t adr, uintptr_t ptr, int size)
{
	DWORD dwOldProtect;
	VirtualProtect(LPVOID(adr), size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy(LPVOID(adr), LPVOID(ptr), size);
	VirtualProtect(LPVOID(adr), size, dwOldProtect, &dwOldProtect);
}

bool CUtils::GetTextureInfo(CImageTexture texture, unsigned int &index, unsigned int &w, unsigned int &h)
{
	if (g_pISurface->IsTextureIDValid(texture.index))
	{
		index = texture.index;
		w = texture.width;
		h = texture.height;
		return true;
	}
	return false;
}

void CUtils::bSendpacket(bool status) 
{
	static bool bsendpacket_status = true;
	static DWORD NULLTIME = NULL;

	if (status && !bsendpacket_status) {
		bsendpacket_status = true;

		*(DWORD*)(g_Offsets.dwSendPacketPointer) = g_Offsets.dwSendPacketBackup;
	}
	if (!status && bsendpacket_status) {
		bsendpacket_status = false;

		*(DWORD*)(g_Offsets.dwSendPacketPointer) = (DWORD)&NULLTIME;
	}
}

float CUtils::Armor(float flDamage, int ArmorValue)
{
	if (ArmorValue > 0) 
	{
		float flNew = flDamage * ARMOR_RATIO;
		float flArmor = (flDamage - flNew) * ARMOR_BONUS;

		if (flArmor > ArmorValue) {
			flArmor *= (1.f / ARMOR_BONUS);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}

bool CUtils::bCalcScreen(float *pflOrigin, float *pflVecScreen)
{
	int iResult = g_Engine.pTriAPI->WorldToScreen(pflOrigin, pflVecScreen);

	if (pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult)
	{
		pflVecScreen[0] = pflVecScreen[0] * (g_Screen.iWidth / 2) + (g_Screen.iWidth / 2);
		pflVecScreen[1] = -pflVecScreen[1] * (g_Screen.iHeight / 2) + (g_Screen.iHeight / 2);

		return true;
	}

	return false;
}

bool CUtils::bFileExists(const char *cFileName) { return _access(cFileName, 0) != -1; }

void CUtils::cIniWrite(char *cFileName, char *cSection, char *cKey, char *cValue)
{
	WritePrivateProfileStringA((LPCSTR)cSection, (LPCSTR)cKey, cValue, (LPCSTR)cFileName);
}

char *CUtils::cIniRead(char *cFileName, char *cSection, char *cKey, char *cDef)
{
	char cTempString[32] = { 0 };

	GetPrivateProfileStringA((LPCSTR)cSection, (LPCSTR)cKey, cDef, cTempString, sizeof(cTempString), (LPCSTR)cFileName);

	return cTempString;
}

char *CUtils::szDirFile(const char* pszName)
{
	char *o = new char[MAX_PATH];

	strcpy(o, g_pGlobals.BaseDir);
	strcat(o, pszName);

	return o;
}

bool CUtils::IsPlayer(struct cl_entity_s *ent)
{
	if (ent == NULL)
		return false;

	if (!ent->player)
		return false;

	if (ent->index > g_Engine.GetMaxClients() || ent->index < 1)
		return false;

	return true;
}

bool CUtils::IsEntityAlive(struct cl_entity_s *ent)
{
	if (ent == NULL)
		return false;

	if (ent->player)
		return false;

	if (g_Local.iIndex == ent->index)
		return false;

	if (ent->index > 256 || ent->index < 0)
		return false;

	cl_entity_s *pLocal = g_Engine.GetLocalPlayer();

	if (!pLocal)
		return false;

	if (ent->curstate.messagenum < pLocal->curstate.messagenum)
		return false;

	return true;
}

bool CUtils::IsPlayerUpdated(struct cl_entity_s *ent)
{
	if (ent == NULL)
		return false;

	if (!ent->player)
		return false;

	if (g_Local.iIndex == ent->index)
		return false;

	if (ent->index > MAX_CLIENTS || ent->index < 1)
		return false;

	if (g_Player[ent->index].iTeam != TERRORIST && g_Player[ent->index].iTeam != CT)
		return false;

	if (ent->curstate.mins.IsZero())
		return false;

	if (ent->curstate.maxs.IsZero())
		return false;

	cl_entity_s *pLocal = g_Engine.GetLocalPlayer();

	if (!pLocal)
		return false;

	if (ent->curstate.messagenum < pLocal->curstate.messagenum)
		return false;

	if (pLocal->curstate.iuser1 == OBS_IN_EYE && pLocal->curstate.iuser2 == ent->index)
		return false;

	return true;
}

bool CUtils::IsPlayerAlive(struct cl_entity_s *ent)
{
	if (!g_Player[ent->index].bUpdated)
		return false;

	if (Cstrike_SequenceInfo[ent->curstate.sequence] == SEQUENCE_DIE && !ent->curstate.weaponmodel && !g_Player[ent->index].bAliveInScoreTab)
		return false;

	return true;
}

bool CUtils::IsLocalAlive(struct cl_entity_s *ent) 
{
	if (ent == NULL)
		return false;

	if (!ent->player)
		return false;

	if (g_Local.iHealth <= NULL)
		return false;

	if (g_Local.iTeam != TERRORIST && g_Local.iTeam != CT)
		return false;

	if (ent->curstate.iuser1 != OBS_NONE)
		return false;

	if (pmove->view_ofs[2] == PM_DEAD_VIEWHEIGHT)
		return false;

	if (ent->curstate.mins.IsZero())
		return false;

	if (ent->curstate.maxs.IsZero())
		return false;

	return true;
}

void UTIL_TextureHit(Vector vecSrc, Vector vecEnd, Vector vecDir, int ignore, pmtrace_t &tr)
{
	if (vecSrc[0] == vecEnd[0] && vecSrc[1] == vecEnd[1] && vecSrc[2] == vecEnd[2])
	{
		memset(&tr, NULL, sizeof(pmtrace_t));

		tr.endpos = vecEnd;
		tr.fraction = 1.0f;
		return;
	}

	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecEnd, PM_GLASS_IGNORE, ignore, &tr);

	if (tr.fraction == 0 && tr.startsolid && !tr.allsolid)
	{
		Vector vecTmp = vecSrc;

		while (!tr.allsolid && tr.fraction == 0.f)
		{
			vecTmp = vecTmp + vecDir;

			g_Engine.pEventAPI->EV_SetTraceHull(2);
			g_Engine.pEventAPI->EV_PlayerTrace(vecTmp, vecEnd, PM_WORLD_ONLY, ignore, &tr);
		}

		if (!tr.allsolid && tr.fraction != 1.0f)
		{
			vecTmp = vecEnd - vecSrc;

			float Length1 = vecTmp.Length();

			vecTmp = tr.endpos - vecSrc;

			float Length2 = vecTmp.Length();

			tr.fraction = Length1 / Length2;
			tr.startsolid = 1.0f;
		}
	}

	if (tr.allsolid)
		tr.fraction = 1.0f;
}

int CUtils::FireBullets(Vector start, Vector end, float flDistance, int iOriginalPenetration, int iBulletType, int iDamage, float flRangeModifier)
{
	Vector vecSrc, vecEnd, vecDir, vecTmp;
	int iPenetration = iOriginalPenetration + 1;
	int iPenetrationPower;
	int iCurrentDamage = iDamage;
	float flPenetrationDistance;
	float flCurrentDistance;

	pmtrace_t tr;
	vecSrc = start;
	vecEnd = end;

	switch (iBulletType)
	{
	case BULLET_PLAYER_9MM:
		iPenetrationPower = 21;
		flPenetrationDistance = 800;
		break;
	case BULLET_PLAYER_45ACP:
		iPenetrationPower = 15;
		flPenetrationDistance = 500;
		break;
	case BULLET_PLAYER_50AE:
		iPenetrationPower = 30;
		flPenetrationDistance = 1000;
		break;
	case BULLET_PLAYER_762MM:
		iPenetrationPower = 39;
		flPenetrationDistance = 5000;
		break;
	case BULLET_PLAYER_556MM:
		iPenetrationPower = 35;
		flPenetrationDistance = 4000;
		break;
	case BULLET_PLAYER_338MAG:
		iPenetrationPower = 45;
		flPenetrationDistance = 8000;
		break;
	case BULLET_PLAYER_57MM:
		iPenetrationPower = 30;
		flPenetrationDistance = 2000;
		break;
	case BULLET_PLAYER_357SIG:
		iPenetrationPower = 25;
		flPenetrationDistance = 800;
		break;
	default:
		iPenetrationPower = 0;
		flPenetrationDistance = 0;
		break;
	}

	vecDir = vecEnd - vecSrc;

	float Length = vecDir.Length();

	vecDir /= Length;

	vecEnd = vecDir * flDistance + vecSrc;

	float flDamageModifier = 0.5;

	while (iPenetration)
	{
		UTIL_TextureHit(vecSrc, vecEnd, vecDir, -1, tr);

		char cTextureType = GetTextureType(&tr, vecSrc, vecEnd);

		switch (cTextureType)
		{
		case CHAR_TEX_CONCRETE:
			iPenetrationPower *= 0.25;
			break;
		case CHAR_TEX_GRATE:
			iPenetrationPower *= 0.5;
			flDamageModifier = 0.4;
			break;
		case CHAR_TEX_METAL:
			iPenetrationPower *= 0.15;
			flDamageModifier = 0.2;
			break;
		case CHAR_TEX_COMPUTER:
			iPenetrationPower *= 0.4;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_TILE:
			iPenetrationPower *= 0.65;
			flDamageModifier = 0.3;
			break;
		case CHAR_TEX_VENT:
			iPenetrationPower *= 0.5;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_WOOD:
			flDamageModifier = 0.6;
			break;
		default:
			break;
		}

		if (tr.fraction != 1.0)
		{
			iPenetration--;

			vecTmp = tr.endpos - start;

			float tmplen = vecTmp.Length();

			if (tmplen >= Length)
			{
				vecTmp = end - vecSrc;

				float Length1 = vecTmp.Length();

				vecTmp = vecEnd - vecSrc;

				float Length2 = vecTmp.Length();

				tr.fraction = Length1 / Length2;

				flCurrentDistance = flDistance * tr.fraction;

				iCurrentDamage *= pow(flRangeModifier, flCurrentDistance / 500);

				return iCurrentDamage;
			}

			flCurrentDistance = flDistance * tr.fraction;

			iCurrentDamage *= pow(flRangeModifier, flCurrentDistance / 500);

			if (flCurrentDistance > flPenetrationDistance)
				iPenetration = 0;

			if (iPenetration)
			{
				vecSrc = iPenetrationPower * vecDir + tr.endpos;

				flDistance = (flDistance - flCurrentDistance) * 0.5;

				vecEnd = vecDir * flDistance + vecSrc;

				flCurrentDistance = iCurrentDamage;

				iCurrentDamage = flCurrentDistance * flDamageModifier;
			}
			else
			{
				vecSrc = 42 * vecDir + tr.endpos;

				flDistance = (flDistance - flCurrentDistance) * 0.75;

				vecEnd = vecDir * flDistance + vecSrc;

				iCurrentDamage *= 0.75;
			}
		}
		else iPenetration = 0;
	}
	return 0;
}

bool CUtils::bPathFree(float *pflFrom, float *pflTo)
{
	pmtrace_t pTrace;

	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(pflFrom, pflTo, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &pTrace);

	return (bool)(pTrace.fraction == 1.0f);
}

void CUtils::VectorAngles(const float *forward, float *angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < -180) { angles[1] += 360; }
	while (angles[1] > 180) { angles[1] -= 360; }
}

void CUtils::FixMoveStart(struct usercmd_s *cmd)
{
	forwardmove = cmd->forwardmove;
	sidemove = cmd->sidemove;
	upmove = cmd->upmove;

	if (pmove->movetype == MOVETYPE_WALK)
		g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vViewForward, vViewRight, vViewUp);
	else
		g_Engine.pfnAngleVectors(cmd->viewangles, vViewForward, vViewRight, vViewUp);
}

void CUtils::FixMoveEnd(struct usercmd_s *cmd)
{
	NormalizeAngles(cmd->viewangles);

	if (pmove->movetype == MOVETYPE_WALK)
		g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vAimForward, vAimRight, vAimUp);
	else
		g_Engine.pfnAngleVectors(cmd->viewangles, vAimForward, vAimRight, vAimUp);

	Vector forwardmove_normalized = forwardmove*vViewForward;
	Vector sidemove_normalized = sidemove*vViewRight;
	Vector upmove_normalized = upmove*vViewUp;

	cmd->forwardmove = forwardmove_normalized.Dot(vAimForward) + sidemove_normalized.Dot(vAimForward) + upmove_normalized.Dot(vAimForward);
	cmd->sidemove = forwardmove_normalized.Dot(vAimRight) + sidemove_normalized.Dot(vAimRight) + upmove_normalized.Dot(vAimRight);
	cmd->upmove = forwardmove_normalized.Dot(vAimUp) + sidemove_normalized.Dot(vAimUp) + upmove_normalized.Dot(vAimUp);

	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vecMove, vecRealView(cmd->viewangles);
	VectorAngles(vMove, vecMove);
	flYaw = (cmd->viewangles.y - vecRealView.y + vecMove.y) * M_PI / 180.0f;

	cmd->forwardmove = cos(flYaw) * flSpeed;

	if (cmd->viewangles.x >= 90 || cmd->viewangles.x <= -90)
		cmd->forwardmove *= -1;

	cmd->sidemove = sin(flYaw) * flSpeed;
}

void CUtils::MakeAngle(bool addangle, float *angles, struct usercmd_s *cmd)
{
	FixMoveStart(cmd);

	if (addangle) 
	{
		cmd->viewangles[0] += angles[0];
		cmd->viewangles[1] += angles[1];
		cmd->viewangles[2] += angles[2];
	}
	else {
		cmd->viewangles[0] = angles[0];
		cmd->viewangles[1] = angles[1];
		cmd->viewangles[2] = angles[2];
	}

	FixMoveEnd(cmd);
}

void CUtils::StringReplace(char* buf, const char* search, const char* replace)
{
	char* p = buf;

	size_t l1 = strlen(search);
	size_t l2 = strlen(replace);

	while (p = strstr(p, search))
	{
		memmove(p + l2, p + l1, strlen(p + l1) + 1U);
		memcpy(p, replace, l2);
		p += l2;
	}
}

bool CUtils::IsBoxIntersectingRay(const Vector& boxMin, const Vector& boxMax, const Vector& origin, const Vector& delta)
{
	ASSERT(boxMin[0] <= boxMax[0]);
	ASSERT(boxMin[1] <= boxMax[1]);
	ASSERT(boxMin[2] <= boxMax[2]);

	// FIXME: Surely there's a faster way
	float tmin = -FLT_MAX;
	float tmax = FLT_MAX;

	for (int i = 0; i < 3; ++i)
	{
		// Parallel case...
		if (fabs(delta[i]) < 1e-8)
		{
			// Check that origin is in the box
			// if not, then it doesn't intersect..
			if ((origin[i] < boxMin[i]) || (origin[i] > boxMax[i]))
				return false;

			continue;
		}

		// non-parallel case
		// Find the t's corresponding to the entry and exit of
		// the ray along x, y, and z. The find the furthest entry
		// point, and the closest exit point. Once that is done,
		// we know we don't collide if the closest exit point
		// is behind the starting location. We also don't collide if
		// the closest exit point is in front of the furthest entry point

		float invDelta = 1.0f / delta[i];
		float t1 = (boxMin[i] - origin[i]) * invDelta;
		float t2 = (boxMax[i] - origin[i]) * invDelta;
		if (t1 > t2)
		{
			float temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0)
			return false;
	}

	return true;
}

/*bool CUtils::Intersect(Vector vHitboxMin, Vector vHitboxMax, Vector vSpreadDir, float &distance)
{
	Vector origin = g_Local.vEye;
	Vector directionInverse;

	if (!vSpreadDir.IsValid())
		return false;

	directionInverse.x = 1.0f / vSpreadDir.x;
	directionInverse.y = 1.0f / vSpreadDir.y;
	directionInverse.z = 1.0f / vSpreadDir.z;
	// If line is parallel and outsite the box it is not possible to intersect 
	if (vSpreadDir.x == 0.0f && (origin.x < min(vHitboxMin.x, vHitboxMax.x) || origin.x > max(vHitboxMin.x, vHitboxMax.x)))
		return false;

	if (vSpreadDir.y == 0.0f && (origin.y < min(vHitboxMin.y, vHitboxMax.y) || origin.y > max(vHitboxMin.y, vHitboxMax.y)))
		return false;

	if (vSpreadDir.z == 0.0f && (origin.z < min(vHitboxMin.z, vHitboxMax.z) || origin.z > max(vHitboxMin.z, vHitboxMax.z)))
		return false;

	float t1 = (vHitboxMin.x - origin.x) * directionInverse.x;
	float t2 = (vHitboxMax.x - origin.x) * directionInverse.x;
	float t3 = (vHitboxMin.y - origin.y) * directionInverse.y;
	float t4 = (vHitboxMax.y - origin.y) * directionInverse.y;
	float t5 = (vHitboxMin.z - origin.z) * directionInverse.z;
	float t6 = (vHitboxMax.z - origin.z) * directionInverse.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	if (tmax < 0) {
		distance = tmax;
		return false;
	}

	if (tmin > tmax) {
		distance = tmax;
		return false;
	}

	distance = tmin;
	return true;
}*/

void CUtils::GetFirstNonSolidPoint(const Vector& inStartPos, const Vector& inEndPos, Vector& outNonSolidPoint)
{
	Vector theStartPos;
	Vector theEndPos;
	theStartPos = inStartPos;
	outNonSolidPoint = inStartPos;
	theEndPos = inEndPos;

	pmtrace_t tr;
	g_Engine.pEventAPI->EV_PlayerTrace(theStartPos, theEndPos, PM_NORMAL, -1, &tr);

	// Put this workaround in because a bug in EV_PlayerTrace means that when it starts solid, tr.fraction isn't returned (but it is in UTIL_TraceLine)
	if ((tr.startsolid) && (tr.fraction == 0.0f))
	{
		int			theFoundEntity = -1;
		bool		theDone = false;

		Vector theStartToEnd;
		theStartToEnd = inEndPos - inStartPos;

		g_Engine.pEventAPI->EV_SetTraceHull(2);

		float theIncrement = 10.0f / theStartToEnd.Length();
		float theT = 0.0f;
		int theNumIterations = 0;

		do
		{
			theStartPos = inStartPos + theT*theStartToEnd;
			g_Engine.pEventAPI->EV_PlayerTrace(theStartPos, theEndPos, PM_WORLD_ONLY, -1, &tr);

			theNumIterations++;

			// If start point is solid, bisect area and move start point 1/2 between current start and current end
			if (tr.startsolid)
			{
				theT += theIncrement;
			}
			// else if start point isn't solid, bisect area and move start point back towards original start point
			else
			{
				theDone = true;
			}
		} while (!theDone && (theNumIterations < 200));

		// Always set end location to show where invalid position is
		if (!theDone)
		{
			outNonSolidPoint = inStartPos;
		}
		else
		{
			outNonSolidPoint = theStartPos;
		}
	}
}

void NormalizeAngles(float *angles)
{
	for (int i = 0; i < 3; ++i)
	{
		float flRevolutions = angles[i] / 360;

		if (angles[i] > 180 || angles[i] < -180)
		{
			if (flRevolutions < 0)
			{
				flRevolutions = -flRevolutions;
			}

			flRevolutions = round(flRevolutions);

			if (angles[i] < 0)
			{
				angles[i] = (angles[i] + 360 * flRevolutions);
			}
			else
			{
				angles[i] = (angles[i] - 360 * flRevolutions);
			}
		}
	}
}

bool IsFreezePeriod(void)
{
	if (g_Local.weapon.iuser3 & PLAYER_FREEZE_TIME_OVER)
		return true;

	return false;
}