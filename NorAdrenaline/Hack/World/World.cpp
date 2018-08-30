#include "../../Required.h"

CWorld World;
CBaseLocal g_Local;
CBasePlayer g_Player[MAX_CLIENTS + 1];
CBaseEntity g_Entities[256];
hud_player_info_t g_PlayerInfoList[MAX_CLIENTS + 1];
player_extra_info_t g_PlayerExtraInfoList[MAX_CLIENTS + 1];
info_map_parameters g_MapInfo;

void MyVectorTransform(Vector in1, float in2[3][4], float *out, int xyz, float multi)
{
	in1[xyz] *= multi;

	out[0] = in1.Dot(in2[0]) + in2[0][3];
	out[1] = in1.Dot(in2[1]) + in2[1][3];
	out[2] = in1.Dot(in2[2]) + in2[2][3];
}

void CWorld::GetHitboxes(struct cl_entity_s *ent)
{
	if (g_Utils.IsPlayer(ent) && ent->index != g_Local.iIndex) 
	{
		Vector vBBMin, vBBMax, vTransform, vMultiPoint;

		model_t *pModel = g_Studio.SetupPlayerModel(ent->index);

		if (pModel == NULL)
			return;

		studiohdr_t *pStudioHeader = (studiohdr_t*)g_Studio.Mod_Extradata(pModel);
		TransformMatrix *pBoneMatrix = (TransformMatrix*)g_Studio.StudioGetBoneTransform();
		mstudiobbox_t *pHitbox = (mstudiobbox_t*)((byte*)pStudioHeader + pStudioHeader->hitboxindex);

		g_Local.iMaxHitboxes = pStudioHeader->numhitboxes - 1;

		for (unsigned int i = 0; i < pStudioHeader->numhitboxes; i++)
		{
			VectorTransform(pHitbox[i].bbmin, (*pBoneMatrix)[pHitbox[i].bone], vBBMin);
			VectorTransform(pHitbox[i].bbmax, (*pBoneMatrix)[pHitbox[i].bone], vBBMax);

			g_PlayerExtraInfoList[ent->index].vHitboxMin[i] = vBBMin;
			g_PlayerExtraInfoList[ent->index].vHitboxMax[i] = vBBMax;
			g_PlayerExtraInfoList[ent->index].vHitbox[i] = (vBBMax + vBBMin) * 0.5f + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;

			g_PlayerExtraInfoList[ent->index].fHitboxFOV[i] = g_Local.vForward.AngleBetween(g_PlayerExtraInfoList[ent->index].vHitbox[i] - g_Local.vEye);

			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][0] = vBBMax + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][1] = vBBMin + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;

			vMultiPoint[0] = pHitbox[i].bbmin[0] / pHitbox[i].bbmax[0];
			vMultiPoint[1] = pHitbox[i].bbmin[1] / pHitbox[i].bbmax[1];
			vMultiPoint[2] = pHitbox[i].bbmin[2] / pHitbox[i].bbmax[2];

			MyVectorTransform(pHitbox[i].bbmax, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 0, vMultiPoint[0]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][2] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;
			MyVectorTransform(pHitbox[i].bbmax, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 1, vMultiPoint[1]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][3] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;
			MyVectorTransform(pHitbox[i].bbmax, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 2, vMultiPoint[2]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][4] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;

			vMultiPoint[0] = pHitbox[i].bbmax[0] / pHitbox[i].bbmin[0];
			vMultiPoint[1] = pHitbox[i].bbmax[1] / pHitbox[i].bbmin[1];
			vMultiPoint[2] = pHitbox[i].bbmax[2] / pHitbox[i].bbmin[2];

			MyVectorTransform(pHitbox[i].bbmin, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 0, vMultiPoint[0]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][5] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;
			MyVectorTransform(pHitbox[i].bbmin, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 1, vMultiPoint[1]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][6] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;
			MyVectorTransform(pHitbox[i].bbmin, (*pBoneMatrix)[pHitbox[i].bone], vTransform, 2, vMultiPoint[2]);
			g_PlayerExtraInfoList[ent->index].vHitboxPoints[i][7] = vTransform + g_Player[ent->index].vVelocity * g_Player[ent->index].flFrametime;

			
		}
	}
}

void CWorld::UpdateLocalPlayer(float frametime, struct usercmd_s *cmd)
{
	cl_entity_s *pLocal = g_Engine.GetLocalPlayer();

	if (pLocal && pLocal->player)
	{
		g_Local.iIndex = pLocal->index;
		g_Local.bAlive = g_Utils.IsLocalAlive(pLocal);
		g_Local.flFrametime = frametime;
		g_Local.flFPS = 1 / g_Local.flFrametime;
		g_Local.vViewAngles = cmd->viewangles;
		g_Local.flVelocity = pmove->velocity.Length2D();
		g_Local.vOrigin = pmove->origin;
		g_Local.vEye = pmove->origin + pmove->view_ofs;

		//Get Distance to Ground
		{
			Vector vtmp = pmove->origin; vtmp[2] = -4096.0f;

			pmtrace_t *trace = g_Engine.PM_TraceLine(pmove->origin, vtmp, 1, (pmove->flags & FL_DUCKING) ? 1 : 0, -1);

			g_Local.flHeightGround = pmove->origin.z - trace->endpos.z;
			g_Local.flGroundAngle = acos(trace->plane.normal[2]) / M_PI * 180.0f;

			//Get Distance to Player under me
			{
				pmtrace_t PlayerTrace;

				g_Engine.pEventAPI->EV_SetTraceHull((pmove->flags & FL_DUCKING) ? 1 : 0);
				g_Engine.pEventAPI->EV_PlayerTrace(pmove->origin, trace->endpos, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &PlayerTrace);

				if (PlayerTrace.fraction < 1.0f)
				{
					g_Local.flHeightGround = PlayerTrace.endpos.z - pmove->origin.z;

					int ind = g_Engine.pEventAPI->EV_IndexFromTrace(&PlayerTrace);
					if (ind >= 1 && ind <= g_Engine.GetMaxClients())
					{
						float dst = pmove->origin.z - (((pmove->flags & FL_DUCKING) ? 1 : 0) == 0 ? 32 : 18) - g_Player[ind].vOrigin.z - g_Local.flHeightGround;

						if (dst < 30)
							g_Local.flHeightGround -= 14.0000;
					}
				}
			}
		}

		//Get Distance to Plane
		{
			Vector vtmp_hull = pmove->origin; vtmp_hull[2] = -4096.0f;

			pmtrace_t *trace_hull = g_Engine.PM_TraceLine(pmove->origin, vtmp_hull, 1, 2, -1);

			g_Local.flHeightPlane = pmove->origin.z - trace_hull->endpos.z - (pmove->usehull == 1 ? 18.0f : 36.0f);
		}

		//Get Current Distance to Ground and Plane
		{
			g_Local.flHeight = g_Local.flHeightGround;

			if (g_Local.flGroundAngle >= 0.1f)
			{
				if ((g_Local.flHeightPlane - g_Local.flHeightGround) <= 20.0f)
					g_Local.flHeight = g_Local.flHeightPlane;
			}
		}
	}
}

void CWorld::UpdateEntities()
{
	float m_flBestDist = 64;
	unsigned int m_ResolvedEntities[MAX_CLIENTS + 1] = { 0 };

	for (unsigned int i = MAX_CLIENTS + 1; i < 256; i++)
	{
		cl_entity_s *ent = g_Engine.GetEntityByIndex(i);

		if (!g_Utils.IsEntityAlive(ent))
		{
			g_Entities[i].bUpdated = false;
			continue;
		}

		g_Entities[i].vOrigin = ent->curstate.origin;
		g_Entities[i].iIndex = ent->index;
		g_Entities[i].bIsWeapon = false;
		g_Entities[i].bIsFakeEntity = false;
		g_Entities[i].iResolvedIndex = 0;
		g_Entities[i].bUpdated = true;

		if (ent->model && ent->model->name)
		{
			g_Entities[i].szModelName = new char[strlen(ent->model->name) + 1];
			strcpy(g_Entities[i].szModelName, ent->model->name);
		}
		else
			g_Entities[i].szModelName = "null";

		if (strstr(g_Entities[i].szModelName, "/w_"))
			g_Entities[i].bIsWeapon = true;
		/*se if (strstr(g_Entities[i].szModelName, "models/player.mdl") && ent->curstate.effects & EF_NODRAW && ent->curstate.movetype == MOVETYPE_FLYMISSILE && ent->curstate.owner > 0 && ent->curstate.owner <= g_Engine.GetMaxClients())
		{
			g_Entities[i].bIsFakeEntity = true;
			g_Entities[i].iResolvedIndex = ent->curstate.owner;

			m_bResolved[ent->curstate.owner] = true;
		}*/
		else if (strstr(g_Entities[i].szModelName, "sprites/laserbeam.spr") && ent->curstate.movetype == MOVETYPE_NOCLIP && (ent->curstate.effects & EF_NODRAW || ent->curstate.rendermode == kRenderTransAlpha))
		{
			g_Entities[i].bIsFakeEntity = true;

			float diff = Vector(g_Local.vOrigin - g_Entities[i].vOrigin).Length();

			if (diff < m_flBestDist)
			{
				m_ResolvedEntities[g_Local.iIndex] = g_Entities[i].iIndex;

				for (unsigned int x = g_Local.iIndex + 1; x <= g_Engine.GetMaxClients(); x++)
					m_ResolvedEntities[x] = g_Entities[i].iIndex + (x - g_Local.iIndex);

				for (unsigned int x = g_Local.iIndex - 1; x > 0; x--)
					m_ResolvedEntities[x] = g_Entities[i].iIndex + (x - g_Local.iIndex);

				m_flBestDist = diff;
			}
		}
	}

	if (g_Local.bAlive)
	{
		bool m_bAllDead = false;

		unsigned int m_iVictims = 0;
		unsigned int m_iDeadVictims = 1;

		for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
		{
			if (i == g_Local.iIndex)
				continue;

			if (g_PlayerInfoList[i].ping < 1)
				continue;

			if (g_Local.iTeam == g_Player[i].iTeam)
				continue;

			m_iVictims++;
		}

		if (m_iVictims > 0) 
		{
			for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
			{
				if (i == g_Local.iIndex)
					continue;

				if (g_Local.iTeam == g_Player[i].iTeam)
					continue;

				if (g_PlayerInfoList[i].ping < 1)
					continue;

				if (!g_Player[i].bAliveInScoreTab)
					m_iDeadVictims++;
			}
		}

		if (m_iVictims > 0 && m_iDeadVictims >= m_iVictims)
			m_bAllDead = true;

		for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
		{
			if (i == g_Local.iIndex)
				continue;

			if (!m_bAllDead && !g_Player[i].bAliveInScoreTab)
				continue;

			unsigned int ent = m_ResolvedEntities[i];

			if (ent > 0 && ent < 256) 
				g_Entities[ent].iResolvedIndex = i;
		}
	}
}

void CWorld::UpdatePlayers()
{
	for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
	{
		if (i == g_Local.iIndex)
			continue;

		char buff[512 + sizeof(hud_player_info_t)];
		hud_player_info_t *thePlayerInfo = (hud_player_info_t *)&buff[0];
		memset(thePlayerInfo, NULL, 512 + sizeof(hud_player_info_t));
		g_Engine.pfnGetPlayerInfo(i, thePlayerInfo);
		memcpy(&g_PlayerInfoList[i], thePlayerInfo, sizeof(hud_player_info_t));

		cl_entity_s *ent = g_Engine.GetEntityByIndex(i);

		g_Player[i].bUpdated = g_Utils.IsPlayerUpdated(ent);

		if (!g_Player[i].bUpdated)
		{
			g_Player[i].iShotsFired = 0;
			g_Player[i].bAlive = false;
			continue;
		}

		g_Player[i].dwHistory = GetTickCount();

		g_PlayerExtraInfoList[ent->index].szWeaponName = "null";

		if (ent && ent->curstate.weaponmodel)
		{
			model_s* mdl = g_Studio.GetModelByIndex(ent->curstate.weaponmodel);

			if (mdl && mdl->name)
			{
				char *szWeapon = strstr(mdl->name, "/p_");

				if (szWeapon)
				{
					szWeapon = &szWeapon[3];
					g_Utils.StringReplace(szWeapon, ".mdl", "");
					g_PlayerExtraInfoList[ent->index].szWeaponName = new char[strlen(mdl->name) + 1];
					strcpy(g_PlayerExtraInfoList[ent->index].szWeaponName, szWeapon);
				}
			}
		}

		g_Player[i].bAlive = g_Utils.IsPlayerAlive(ent);

		if (!g_Player[i].bAlive)
			continue;

		g_Player[i].vAngles = Vector(-ent->angles[0] * 3, ent->angles[1], ent->angles[2]);//Restore original angles
		g_Player[i].flFrametime = ent->curstate.animtime - ent->prevstate.animtime;

		if (g_Player[i].flFrametime == NULL)
			g_Player[i].flFrametime = g_Local.flFrametime;

		g_Player[i].bDucked = ((ent->curstate.maxs[2] - ent->curstate.mins[2]) < 54 ? true : false);
		g_Player[i].vPrevOrigin = g_Player[i].vOrigin;
		g_Player[i].vOrigin = ent->curstate.origin;
		g_Player[i].vVelocity = ent->curstate.origin - ent->prevstate.origin;
		g_Player[i].flDist = g_Player[i].vOrigin.Distance(g_Local.vOrigin);

		int seq = Cstrike_SequenceInfo[ent->curstate.sequence];

		if (seq == SEQUENCE_RELOAD) {
			g_Player[i].iShotsFired = 0;
		}

		UpdateVisibility(i);
	}
}

void CWorld::UpdateVisibility(int id)
{
	g_Player[id].bVisible = false;
	g_Player[id].bBehindTheWall = true;

	bool teammates = false;
	bool walls = false;

	if (cvar.aim_teammates || cvar.legit_teammates)
		teammates = true;

	if (((cvar.aim && cvar.aim_penetration) || (cvar.legit[g_Local.weapon.m_iWeaponID].trigger && cvar.legit[g_Local.weapon.m_iWeaponID].trigger_penetration)) && IsCurWeaponGun())
		walls = true;

	if (!teammates && g_Player[id].iTeam == g_Local.iTeam)
		return;

	deque<unsigned int> Hitboxes;

	if (IsCurWeaponGun()) 
	{
		if (cvar.aim)//Rage aimbot
		{
			if (cvar.aim_hitbox == 1)//"Head", "Neck", "Chest", "Stomach"
			{
				Hitboxes.push_back(11);
			}
			else if (cvar.aim_hitbox == 2)
			{
				Hitboxes.push_back(10);
			}
			else if (cvar.aim_hitbox == 3)
			{
				Hitboxes.push_back(7);
			}
			else if (cvar.aim_hitbox == 4)
			{
				Hitboxes.push_back(0);
			}
			else if(cvar.aim_hitbox == 5)//All
			{
				for (unsigned int j = 0; j < g_Local.iMaxHitboxes; j++)
					Hitboxes.push_back(j);
			}
			else if (cvar.aim_hitbox == 6)//Vital
			{
				for (unsigned int j = 0; j <= 11; j++)
					Hitboxes.push_back(j);
			}
		}
		else if (cvar.legit[g_Local.weapon.m_iWeaponID].aim)
		{
			if (cvar.legit[g_Local.weapon.m_iWeaponID].aim_head)
				Hitboxes.push_back(11);

			if (cvar.legit[g_Local.weapon.m_iWeaponID].aim_chest)
				Hitboxes.push_back(7);

			if (cvar.legit[g_Local.weapon.m_iWeaponID].aim_stomach)
				Hitboxes.push_back(0);

			if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger)
			{
				if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_head && !cvar.legit[g_Local.weapon.m_iWeaponID].aim_head)
					Hitboxes.push_back(11);

				if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_chest && !cvar.legit[g_Local.weapon.m_iWeaponID].aim_chest)
				{
					Hitboxes.push_back(7);
					Hitboxes.push_back(8);
					Hitboxes.push_back(9);
					Hitboxes.push_back(10);
					Hitboxes.push_back(12);
					Hitboxes.push_back(17);
				}

				if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_stomach && !cvar.legit[g_Local.weapon.m_iWeaponID].aim_stomach)
					Hitboxes.push_back(0);
			}
		}
		else if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger)
		{
			if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_head)
				Hitboxes.push_back(11);

			if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_chest)
			{
				Hitboxes.push_back(7);
				Hitboxes.push_back(8);
				Hitboxes.push_back(9);
				Hitboxes.push_back(10);
				Hitboxes.push_back(12);
				Hitboxes.push_back(17);
			}

			if (cvar.legit[g_Local.weapon.m_iWeaponID].trigger_stomach)
				Hitboxes.push_back(0);
		}
	}
	else if (IsCurWeaponKnife() && cvar.knifebot)
	{
		Hitboxes.push_back(0);
	}

	if (Hitboxes.empty())
		return;

	pmtrace_t tr;
	int detect = 0;

	for (auto &&hitbox : Hitboxes)
	{
		g_Engine.pEventAPI->EV_SetTraceHull(2);

		if (cvar.bypass_trace_blockers)
			g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[id].vHitbox[hitbox], PM_WORLD_ONLY, -1, &tr);
		else
			g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[id].vHitbox[hitbox], PM_GLASS_IGNORE, -1, &tr);

		detect = g_Engine.pEventAPI->EV_IndexFromTrace(&tr);

		if ((cvar.bypass_trace_blockers && tr.fraction == 1 && !detect) || (!cvar.bypass_trace_blockers && detect == id))
		{
			g_Player[id].bVisible = true;
			g_Player[id].bBehindTheWall = false;
			g_PlayerExtraInfoList[id].bHitboxVisible[hitbox] = true;
			g_PlayerExtraInfoList[id].bHitboxBehindTheWall[hitbox] = false;
		}
		else {
			g_PlayerExtraInfoList[id].bHitboxVisible[hitbox] = false;
			g_PlayerExtraInfoList[id].bHitboxBehindTheWall[hitbox] = false;

			int iOriginalPenetration = CurPenetration();

			if (iOriginalPenetration && walls)
			{
				int iDamage = CurDamage();
				int iBulletType = CurBulletType();
				float flDistance = CurDistance();
				float flRangeModifier = CurWallPierce();

				int iCurrentDamage = g_Utils.FireBullets(g_Local.vEye, g_PlayerExtraInfoList[id].vHitbox[hitbox], flDistance, iOriginalPenetration, iBulletType, iDamage, flRangeModifier);

				if (iCurrentDamage > 0)
				{
					g_Player[id].bVisible = true;
					g_PlayerExtraInfoList[id].bHitboxVisible[hitbox] = true;
					g_PlayerExtraInfoList[id].bHitboxBehindTheWall[hitbox] = true;
				}
			}
		}

		if (cvar.aim && cvar.aim_multi_point > 0 && IsCurWeaponGun())
		{
			if (cvar.aim_multi_point == 1 && hitbox != 11)
				continue;

			if (cvar.aim_multi_point == 2 && hitbox > 11)
				continue;

			for (unsigned int point = 0; point <= 8; ++point)
			{
				g_Engine.pEventAPI->EV_SetTraceHull(2);

				if (cvar.bypass_trace_blockers) 
					g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[id].vHitboxPoints[hitbox][point], PM_WORLD_ONLY, -1, &tr);
				else 
					g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[id].vHitboxPoints[hitbox][point], PM_GLASS_IGNORE, -1, &tr);

				detect = g_Engine.pEventAPI->EV_IndexFromTrace(&tr);

				if ((cvar.bypass_trace_blockers && tr.fraction == 1 && !detect) || (!cvar.bypass_trace_blockers && detect == id))
				{
					g_Player[id].bVisible = true;
					g_Player[id].bBehindTheWall = false;
					g_PlayerExtraInfoList[id].bHitboxPointsVisible[hitbox][point] = true;
					g_PlayerExtraInfoList[id].bHitboxPointsBehindTheWall[hitbox][point] = false;
				}
				else {
					g_PlayerExtraInfoList[id].bHitboxPointsVisible[hitbox][point] = false;
					g_PlayerExtraInfoList[id].bHitboxPointsBehindTheWall[hitbox][point] = false;

					int iOriginalPenetration = CurPenetration();

					if (iOriginalPenetration && walls)
					{
						int iDamage = CurDamage();
						int iBulletType = CurBulletType();
						float flDistance = CurDistance();
						float flRangeModifier = CurWallPierce();

						int iCurrentDamage = g_Utils.FireBullets(g_Local.vEye, g_PlayerExtraInfoList[id].vHitboxPoints[hitbox][point], flDistance, iOriginalPenetration, iBulletType, iDamage, flRangeModifier);

						if (iCurrentDamage > 0)
						{
							g_Player[id].bVisible = true;
							g_PlayerExtraInfoList[id].bHitboxPointsVisible[hitbox][point] = true;
							g_PlayerExtraInfoList[id].bHitboxPointsBehindTheWall[hitbox][point] = true;
						}
					}
				}
			}
		}
	}
}

void CWorld::ClearLocalPlayer()
{
	memset(&g_Local, NULL, sizeof(CBaseLocal));
}

void CWorld::ClearPlayers()
{
	memset(g_Player, NULL, sizeof(CBasePlayer));
	memset(g_PlayerInfoList, NULL, sizeof(hud_player_info_t));
	memset(g_PlayerExtraInfoList, NULL, sizeof(player_extra_info_t));
}

void CWorld::ClearEntities()
{
	memset(g_Entities, NULL, sizeof(CBaseEntity));
}

void CWorld::ClearMapInfo()
{
	memset(&g_MapInfo, NULL, sizeof(info_map_parameters));
}

void CWorld::Reset()
{
	ClearLocalPlayer();
	ClearPlayers();
	ClearEntities();
}

void CWorld::Update(float frametime, struct usercmd_s *cmd)
{
	UpdateLocalPlayer(frametime, cmd);
	UpdatePlayers();
	UpdateEntities();
}

void CWorld::UpdateMapInfo()
{
	static bool map_changed = true;

	if (g_pIRunGameEngine->IsInGame() && map_changed)
	{
		g_MapInfo.levelname = g_Engine.pfnGetLevelName();

		if (g_MapInfo.levelname)
		{
			if (!lstrcmpA(g_MapInfo.levelname, "maps/de_dust2.bsp") || 
				!lstrcmpA(g_MapInfo.levelname, "maps/de_dust2_2x2.bsp") ||
				!lstrcmpA(g_MapInfo.levelname, "maps/de_inferno.bsp") || 
				!lstrcmpA(g_MapInfo.levelname, "maps/de_inferno_2x2.bsp") ||
				!lstrcmpA(g_MapInfo.levelname, "maps/de_train.bsp") || 
				!lstrcmpA(g_MapInfo.levelname, "maps/de_kabul.bsp") ||
				!lstrcmpA(g_MapInfo.levelname, "maps/de_mirage.bsp") ||
				!lstrcmpA(g_MapInfo.levelname, "maps/de_aztec.bsp"))
			{
				g_MapInfo.m_flBombRadius = 1750;
			}
			else if (!lstrcmpA(g_MapInfo.levelname, "maps/de_dust.bsp")) 
			{
				g_MapInfo.m_flBombRadius = 350;
			}
			else if (!lstrcmpA(g_MapInfo.levelname, "maps/de_cbble.bsp") ||
				!lstrcmpA(g_MapInfo.levelname, "maps/de_westwood.bsp"))
			{
				g_MapInfo.m_flBombRadius = 1050;
			}
			else {
				g_MapInfo.m_flBombRadius = 500;

				if (g_pGlobals.GamePath)
				{
					char buff[MAX_PATH];
					sprintf(buff, "%scstrike/%s", g_pGlobals.GamePath, g_MapInfo.levelname);
					g_Utils.StringReplace(buff, "/", "\\");

					if (g_Utils.bFileExists(buff))
					{
						std::ifstream ifs(buff, ios::binary);

						std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

						size_t pos = str.find("\"bombradius\" \"");

						if (pos != string::npos)
						{
							std::string str2(str.substr(pos + 14));

							size_t pos2 = str2.find("\"");

							if (pos2 != string::npos)
							{
								std::string str3(str2.substr(0, pos2));

								g_MapInfo.m_flBombRadius = atof(str3.c_str());
							}
						}
					}
				}
			}

			if (g_MapInfo.m_flBombRadius > MAX_BOMB_RADIUS)
			{
				g_MapInfo.m_flBombRadius = MAX_BOMB_RADIUS;
			}
			else if (g_MapInfo.m_flBombRadius <= 0)
			{
				g_MapInfo.m_flBombRadius = 500;
			}

			map_changed = false;
		}
	}
	else if (!g_pIRunGameEngine->IsInGame() && !map_changed)
	{
		map_changed = true;
	}
}