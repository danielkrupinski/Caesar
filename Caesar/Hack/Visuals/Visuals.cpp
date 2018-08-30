#include "../../Required.h"
#include "../../icons.h"

CVisuals g_Visuals;

typedef struct
{
	deque<Vector> vPoints;
	DWORD dwUpdated;
} grenadetracer_t;

grenadetracer_t Grenades[256];

void CVisuals::IconInit()
{
	static bool init = false;

	if (!init)
	{
		if (!wpn_p228.index) wpn_p228.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_scout.index) wpn_scout.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_hegrenade.index) wpn_hegrenade.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_xm1014.index) wpn_xm1014.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_c4.index) wpn_c4.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_mac10.index) wpn_mac10.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_aug.index) wpn_aug.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_smokegrenade.index) wpn_smokegrenade.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_elite.index) wpn_elite.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_fiveseven.index) wpn_fiveseven.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_ump45.index) wpn_ump45.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_sg550.index) wpn_sg550.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_galil.index) wpn_galil.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_famas.index) wpn_famas.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_usp.index) wpn_usp.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_glock18.index) wpn_glock18.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_awp.index) wpn_awp.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_mp5n.index) wpn_mp5n.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_m249.index) wpn_m249.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_m3.index) wpn_m3.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_m4a1.index) wpn_m4a1.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_tmp.index) wpn_tmp.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_g3sg1.index) wpn_g3sg1.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_flashbang.index) wpn_flashbang.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_deagle.index) wpn_deagle.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_sg552.index) wpn_sg552.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_ak47.index) wpn_ak47.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_knife.index) wpn_knife.index = g_pISurface->CreateNewTextureID(true);
		if (!wpn_p90.index) wpn_p90.index = g_pISurface->CreateNewTextureID(true);

		if (wpn_p228.index && wpn_scout.index && wpn_hegrenade.index && wpn_xm1014.index && wpn_c4.index && wpn_mac10.index && wpn_aug.index && wpn_smokegrenade.index && wpn_elite.index && wpn_fiveseven.index && wpn_ump45.index && wpn_sg550.index && wpn_galil.index && wpn_famas.index && wpn_usp.index && wpn_glock18.index && wpn_awp.index && wpn_mp5n.index && wpn_m249.index && wpn_m3.index && wpn_m4a1.index && wpn_tmp.index && wpn_g3sg1.index && wpn_flashbang.index && wpn_deagle.index && wpn_sg552.index && wpn_ak47.index && wpn_knife.index && wpn_p90.index)
		{
			wpn_p228.height = 30; wpn_scout.height = 26; wpn_hegrenade.height = 16; wpn_xm1014.height = 25; wpn_c4.height = 16; wpn_mac10.height = 40; wpn_aug.height = 34; wpn_smokegrenade.height = 16; wpn_elite.height = 26; wpn_fiveseven.height = 26; wpn_ump45.height = 40; wpn_sg550.height = 27; wpn_galil.height = 30; wpn_famas.height = 33; wpn_usp.height = 29; wpn_glock18.height = 27; wpn_awp.height = 26; wpn_mp5n.height = 37; wpn_m249.height = 36; wpn_m3.height = 22; wpn_m4a1.height = 34; wpn_tmp.height = 39; wpn_g3sg1.height = 30; wpn_flashbang.height = 16; wpn_deagle.height = 29; wpn_sg552.height = 30; wpn_ak47.height = 32; wpn_knife.height = 17; wpn_p90.height = 33;
			wpn_p228.width = 38; wpn_scout.width = 100; wpn_hegrenade.width = 48; wpn_xm1014.width = 97; wpn_c4.width = 48; wpn_mac10.width = 42; wpn_aug.width = 90; wpn_smokegrenade.width = 48; wpn_elite.width = 65; wpn_fiveseven.width = 35; wpn_ump45.width = 69; wpn_sg550.width = 95; wpn_galil.width = 94; wpn_famas.width = 81; wpn_usp.width = 62; wpn_glock18.width = 42; wpn_awp.width = 119; wpn_mp5n.width = 65; wpn_m249.width = 92; wpn_m3.width = 96; wpn_m4a1.width = 88; wpn_tmp.width = 45; wpn_g3sg1.width = 99; wpn_flashbang.width = 48; wpn_deagle.width = 49; wpn_sg552.width = 80; wpn_ak47.width = 97; wpn_knife.width = 73; wpn_p90.width = 73;

			g_pISurface->DrawSetTextureRGBA(wpn_ak47.index, icon_wpn_ak47, wpn_ak47.width, wpn_ak47.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_knife.index, icon_wpn_knife, wpn_knife.width, wpn_knife.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_deagle.index, icon_wpn_deagle, wpn_deagle.width, wpn_deagle.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_m4a1.index, icon_wpn_m4a1, wpn_m4a1.width, wpn_m4a1.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_awp.index, icon_wpn_awp, wpn_awp.width, wpn_awp.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_scout.index, icon_wpn_scout, wpn_scout.width, wpn_scout.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_mp5n.index, icon_wpn_mp5n, wpn_mp5n.width, wpn_mp5n.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_glock18.index, icon_wpn_glock18, wpn_glock18.width, wpn_glock18.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_p90.index, icon_wpn_p90, wpn_p90.width, wpn_p90.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_usp.index, icon_wpn_usp, wpn_usp.width, wpn_usp.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_xm1014.index, icon_wpn_xm1014, wpn_xm1014.width, wpn_xm1014.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_p228.index, icon_wpn_p228, wpn_p228.width, wpn_p228.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_sg552.index, icon_wpn_sg552, wpn_sg552.width, wpn_sg552.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_sg550.index, icon_wpn_sg550, wpn_sg550.width, wpn_sg550.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_m249.index, icon_wpn_m249, wpn_m249.width, wpn_m249.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_g3sg1.index, icon_wpn_g3sg1, wpn_g3sg1.width, wpn_g3sg1.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_m3.index, icon_wpn_m3, wpn_m3.width, wpn_m3.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_elite.index, icon_wpn_elite, wpn_elite.width, wpn_elite.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_aug.index, icon_wpn_aug, wpn_aug.width, wpn_aug.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_mac10.index, icon_wpn_mac10, wpn_mac10.width, wpn_mac10.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_tmp.index, icon_wpn_tmp, wpn_tmp.width, wpn_tmp.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_fiveseven.index, icon_wpn_fiveseven, wpn_fiveseven.width, wpn_fiveseven.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_ump45.index, icon_wpn_ump45, wpn_ump45.width, wpn_ump45.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_galil.index, icon_wpn_galil, wpn_galil.width, wpn_galil.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_famas.index, icon_wpn_famas, wpn_famas.width, wpn_famas.height, false, true);

			/*
			g_pISurface->DrawSetTextureRGBA(wpn_hegrenade.index, icon_wpn_hegrenade, wpn_hegrenade.width, wpn_hegrenade.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_c4.index, icon_wpn_c4, wpn_c4.width, wpn_c4.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_smokegrenade.index, icon_wpn_smokegrenade, wpn_smokegrenade.width, wpn_smokegrenade.height, false, true);
			g_pISurface->DrawSetTextureRGBA(wpn_flashbang.index, icon_wpn_flashbang, wpn_flashbang.width, wpn_flashbang.height, false, true);
			*/

			init = true;
		}
	}
}

void CVisuals::DrawHistory(int i)
{
	if (!cvar.esp)
		return;

	if (!cvar.esp_behind && g_Player[i].bBehindTheWall)
		return;

	if (!cvar.esp_teammates && g_Player[i].iTeam == g_Local.iTeam)
		return;

	byte r = 105;
	byte g = 105;
	byte b = 105;

	Vector Top = Vector(g_Player[i].vOrigin.x, g_Player[i].vOrigin.y, g_Player[i].vOrigin.z - 36);
	Vector Bot = Vector(g_Player[i].vOrigin.x, g_Player[i].vOrigin.y, g_Player[i].vOrigin.z + 36);

	float ScreenTop[2], ScreenBot[2];

	bool m_bScreenTop = g_Utils.bCalcScreen(Top, ScreenTop);
	bool m_bScreenBot = g_Utils.bCalcScreen(Bot, ScreenBot);

	if (m_bScreenTop && m_bScreenBot)
	{
		float _h = ScreenBot[1] - ScreenTop[1];
		float box_height = g_Player[i].bDucked ? _h : _h * 0.9f;
		float box_width = box_height * 0.3f;

		if (cvar.esp_box)
			g_Drawing.DrawPlayerBox(ScreenTop[0], ScreenTop[1], box_width, box_height, r, g, b, 255);

		char *szWeapon = g_PlayerExtraInfoList[i].szWeaponName;

		if (cvar.esp_weapon > 0 && szWeapon)
		{
			unsigned int y = ScreenBot[1] + (8 - _h);

			g_Drawing.DrawString(ESP, ScreenTop[0], y, r, g, b, 255, FONT_CENTER, "%s", szWeapon);
		}

		if (cvar.esp_distance)
		{
			unsigned int y = ScreenBot[1] + (-8 - _h);

			g_Drawing.DrawString(ESP, ScreenTop[0], y, r, g, b, cvar.esp_alpha, FONT_CENTER, "%.f", g_Player[i].flDist);
		}

		if (cvar.esp_name && g_PlayerInfoList[i].name != NULL)
		{
			unsigned int y = box_height - 8 + ScreenTop[1];

			g_Drawing.DrawString(ESP, ScreenTop[0], y, r, g, b, cvar.esp_alpha, FONT_CENTER, "%s", g_PlayerInfoList[i].name);
		}
	}
}

void TriggerStatus()
{
	static DWORD dwTemporaryBlockTimer = GetTickCount();
	static bool old = g_AimBot.TriggerKeyStatus;

	if (cvar.trigger_key > 0 && cvar.trigger_key < 255) {
		if (g_AimBot.TriggerKeyStatus != old)
		{
			old = g_AimBot.TriggerKeyStatus;
			dwTemporaryBlockTimer = GetTickCount();
		}

		if (GetTickCount() - dwTemporaryBlockTimer < 2000)
		{
			if (g_AimBot.TriggerKeyStatus)
				g_Drawing.DrawString(ESP, g_Screen.iWidth / 2, g_Screen.iHeight / 2 + 64, 0, 255, 0, cvar.esp_alpha, FONT_CENTER, "Trigger activated");
			else
				g_Drawing.DrawString(ESP, g_Screen.iWidth / 2, g_Screen.iHeight / 2 + 64, 255, 0, 0, cvar.esp_alpha, FONT_CENTER, "Trigger deactivated");
		}
	}
}

void CVisuals::Run()
{
	IconInit();

	if (!g_pIRunGameEngine->IsInGame()) 
		return;

	while (mySounds.size() && GetTickCount() - mySounds.front().timestamp >= 300)
		mySounds.pop_front();

	if (g_pGlobals.bSnapshot || g_pGlobals.bScreenshot) 
		return;

	DrawEntities();

	Bomb();

	for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
	{
		if (i == g_Local.iIndex)
			continue;

		if (!g_Player[i].bAlive)
			continue;

		PlayerESP(i);
	}

	for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
	{
		if (i == g_Local.iIndex)
			continue;

		if (g_Player[i].bUpdated)
			continue;

		if (!g_Player[i].bAliveInScoreTab)
			continue;

		if (GetTickCount() - g_Player[i].dwHistory > 2000)
			continue;

		DrawHistory(i);
	}

	SoundESP();

	Debug();

	g_NoRecoil.DrawRecoil();
	g_NoSpread.DrawSpread();

	TraceGrenade();

	g_NoFlash.Redraw();

	RemoveScope();
	Crosshair();
	DrawAimBotFOV();

	PenetrationInfo();
	TriggerStatus();
}

void CVisuals::DrawAimBotFOV()
{
	if (g_Local.bAlive && IsCurWeaponGun() && !cvar.aim && cvar.draw_aim_fov && g_AimBot.m_flCurrentFOV > 0 && g_AimBot.m_flCurrentFOV < 45 && g_Local.iFOV)
	{
		float x = g_Screen.iWidth * 0.5f;
		float y = g_Screen.iHeight * 0.5f;
		float dx = g_Screen.iWidth / g_Local.iFOV;
		float dy = g_Screen.iHeight / g_Local.iFOV;

		float radius = tanf(DEG2RAD(g_AimBot.m_flCurrentFOV) * 0.5f) / tanf(DEG2RAD(g_Local.iFOV) * 0.5f) * g_Screen.iWidth;

		float positions[2];
		positions[0] = (x - (dx * g_Local.vNoRecoilAngle[1]));
		positions[1] = (y + (dy * g_Local.vNoRecoilAngle[0]));

		g_Drawing.DrawCircle(positions, 30, radius, cvar.draw_aim_fov_r, cvar.draw_aim_fov_g, cvar.draw_aim_fov_b, 120);
	}
}

void CVisuals::RemoveScope() 
{
	if (g_Local.bScoped && cvar.remove_scope) 
	{
		g_Engine.pfnTintRGBA(1, g_Screen.iHeight / 2, g_Screen.iWidth, 1, 0, 0, 0, 255);
		g_Engine.pfnTintRGBA(g_Screen.iWidth / 2, 1, 1, g_Screen.iHeight, 0, 0, 0, 255);
	}
}

void CVisuals::PenetrationInfo()
{
	if (cvar.penetration_info && g_Local.bAlive)
	{
		int iOriginalPenetration = CurPenetration();

		int iPenetration = iOriginalPenetration;

		if (iOriginalPenetration > 0)
		{
			int iDamage = CurDamage();
			int iBulletType = CurBulletType();
			float flDistance = CurDistance();
			float flRangeModifier = CurWallPierce();

			pmtrace_t tr;

			Vector vOut;
			Vector vStart = g_Local.vEye;

			int iWalls = 0;

			while (iPenetration > 0)
			{
				g_Engine.pEventAPI->EV_SetTraceHull(2);
				g_Engine.pEventAPI->EV_PlayerTrace(vStart, vStart + g_Local.vForward * 8192, PM_NORMAL, -1, &tr);

				g_Utils.GetFirstNonSolidPoint(tr.endpos + g_Local.vForward * 16, tr.endpos + g_Local.vForward * 8192, vOut);

				int tmp = g_Utils.FireBullets(vStart, vOut + g_Local.vForward * 16, flDistance, iOriginalPenetration, iBulletType, iDamage, flRangeModifier);

				if (tmp > 0)
					iWalls++;
				else break;

				vStart = vOut + g_Local.vForward * 16;

				iPenetration--;
			}

			if(iWalls > 0)
				g_Drawing.DrawString(ESP,g_Screen.iWidth / 2, g_Screen.iHeight / 2 + 32, 0, 255, 0, cvar.esp_alpha, FONT_CENTER, "Wallbang (%i)", iWalls);
		}
	}
}

void CVisuals::Crosshair()
{
	static char *old = NULL;

	if (cvar.crosshair && g_Local.iFOV == DEFAULT_FOV)
	{
		int r = cvar.crosshair_r, g = cvar.crosshair_g, b = cvar.crosshair_b;

		if ((int)g_Engine.pfnGetCvarFloat("crosshair") != 0)
		{
			old = g_Engine.pfnGetCvarString("cl_crosshair_color");
			g_Engine.Cvar_SetValue("cl_crosshair_color", 0);
			g_Engine.Cvar_SetValue("crosshair", 0);
			g_Engine.Cvar_SetValue("cl_crosshair_translucent", 1);
		}

		g_Engine.pfnTintRGBA(g_Screen.iWidth / 2 - 14, g_Screen.iHeight / 2, 9, 2, r, g, b, 200);
		g_Engine.pfnTintRGBA(g_Screen.iWidth / 2 + 6, g_Screen.iHeight / 2, 9, 2, r, g, b, 200);
		g_Engine.pfnTintRGBA(g_Screen.iWidth / 2, g_Screen.iHeight / 2 - 14, 2, 9, r, g, b, 200);
		g_Engine.pfnTintRGBA(g_Screen.iWidth / 2, g_Screen.iHeight / 2 + 7, 2, 9, r, g, b, 200);
	}
	else
	{
		if ((int)g_Engine.pfnGetCvarFloat("crosshair") == 0)
		{
			if(old) g_Engine.pfnCvar_Set("cl_crosshair_color", old);
			g_Engine.Cvar_SetValue("crosshair", 1);
			g_Engine.Cvar_SetValue("cl_crosshair_translucent", 0);
		}
	}
}

void CVisuals::TraceGrenade()
{
	if (!cvar.grenade_trajectory || !IsCurWeaponNade() || !g_Local.bAlive) return;

	Vector vecAngles, vecForward, vecStart, vecEnd, vecOut;
	pmtrace_t pmtrace;

	float flGravity = pmove->movevars->gravity / SVGRAVITY;

	g_Engine.GetViewAngles(vecAngles);

	if (vecAngles[0] < 0)
		vecAngles[0] = -10 + vecAngles[0] * ((90 - 10) / 90.0);
	else
		vecAngles[0] = -10 + vecAngles[0] * ((90 + 10) / 90.0);

	float flVel = (90 - vecAngles[0]) * 4;

	if (flVel > 500)
		flVel = 500;

	g_Engine.pfnAngleVectors(vecAngles, vecForward, NULL, NULL);

	vecStart = g_Local.vEye + vecForward * 16;

	vecForward = (vecForward * flVel) + pmove->velocity;

	uint iCollisions = 0;
	float flTimeAlive;
	float flStep = (TIMEALIVE / NUMBLOOPS);

	for (flTimeAlive = 0; flTimeAlive < TIMEALIVE; flTimeAlive += flStep)
	{
		vecEnd = vecStart + vecForward * flStep;

		g_Engine.pEventAPI->EV_SetTraceHull(2);
		g_Engine.pEventAPI->EV_PlayerTrace(vecStart, vecEnd, PM_STUDIO_BOX, -1, &pmtrace);

		if (pmtrace.ent != g_Local.iIndex && pmtrace.fraction < 1.0) //hits a wall
		{
			//hitpoint
			vecEnd = vecStart + vecForward * pmtrace.fraction * flStep;

			float fScreen[2];

			if (g_Utils.bCalcScreen(vecEnd, fScreen)) {
				g_pISurface->DrawSetColor(255, 0, 0, 200);
				g_pISurface->DrawFilledRect(fScreen[0] - 3, fScreen[1] - 3, fScreen[0] + 3, fScreen[1] + 3);
			}

			if (pmtrace.plane.normal[2] > 0.9 && vecForward[2] <= 0 && vecForward[2] >= (-1 * flGravity * FLOORSTOP))
			{
				vecOut = vecEnd;
				return;
			}

			float flProj = vecForward.Dot(pmtrace.plane.normal);

			vecForward = (vecForward * OLDDAMPER - flProj * 2 * pmtrace.plane.normal) * NEWDAMPER; //reflection off the wall

			iCollisions++;

			if (iCollisions > 30)
				break;

			flTimeAlive -= (flStep * (1 - pmtrace.fraction));
		}

		float fScreenStart[2];
		float fScreenEnd[2];

		if (g_Utils.bCalcScreen(vecStart, fScreenStart) && g_Utils.bCalcScreen(vecEnd, fScreenEnd))
			g_Drawing.DrawLine(fScreenStart[0], fScreenStart[1], fScreenEnd[0], fScreenEnd[1], 0, 255, 0, 255);

		vecStart = vecEnd;

		vecForward[2] -= flGravity * pmtrace.fraction * flStep; //gravity
	}

	vecOut = vecStart;
}

void CVisuals::SoundESP() 
{
	if (cvar.esp_sound)
	{
		for (my_sound_t sound : mySounds)
		{
			float screen[2] = {};
			float size = 10.0f * (1000 - (GetTickCount() - sound.timestamp)) / 1000.0f;

			if (g_Utils.bCalcScreen(sound.origin, screen))
			{
				if (!g_Utils.bPathFree(g_Local.vEye, sound.origin)) 
				{
					if (!strstr(sound.name, "pl_shell") && 
						!strstr(sound.name, "ric") && 
						!strstr(sound.name, "die") && 
						!strstr(sound.name, "glass") && 
						!strstr(sound.name, "debris")) 
					{
						color24 color;
						color.r = 255;
						color.g = 255;
						color.b = 255;

						if (strstr(sound.name, "weapons")) 
						{
							if (strstr(sound.name, "explode3") || strstr(sound.name, "explode4") || strstr(sound.name, "he_bounce")) {
								color.g = 0; color.b = 0;
							}
							else if (strstr(sound.name, "sg_explode")) {
								color.r = 0; color.b = 0;
							}
							else if (strstr(sound.name, "c4_")) {
								color.r = 0; color.g = 0;
							}
							else if (strstr(sound.name, "flashbang")) {
								color.r = 0; color.g = 100; color.b = 100;
							}
							else {
								color.r = 162; color.g = 0;
							}
						}
						else if (strstr(sound.name, "player") && strstr(sound.name, "pl_")) {
							color.r = 100; color.g = 200; color.b = 160;
						}

						g_Drawing.DrawBox(screen[0] - size, screen[1] - size, 10, 10, color.r, color.g, color.b, 255);
					}
				}
			}
		}
	}
}

void CVisuals::PlayerESP(unsigned int i)
{
	if (!cvar.esp) 
		return;

	if (!cvar.esp_behind && g_Player[i].bBehindTheWall)
		return;

	if (!cvar.esp_teammates && g_Player[i].iTeam == g_Local.iTeam)
		return;

	cl_entity_s *ent = g_Engine.GetEntityByIndex(i);

	if (!ent) 
		return;

	byte r = 0, g = 0, b = 0;

	if (!g_Player[i].bFriend) 
	{
		if (g_Player[i].iTeam == TERRORIST)
		{
			if (g_Player[i].bVisible)
			{
				r = cvar.esp_box_t_vis_r;
				g = cvar.esp_box_t_vis_g;
				b = cvar.esp_box_t_vis_b;
			}
			else
			{
				r = cvar.esp_box_t_invis_r;
				g = cvar.esp_box_t_invis_g;
				b = cvar.esp_box_t_invis_b;
			}
		}
		else if (g_Player[i].iTeam == CT) 
		{
			if (g_Player[i].bVisible)
			{
				r = cvar.esp_box_ct_vis_r;
				g = cvar.esp_box_ct_vis_g;
				b = cvar.esp_box_ct_vis_b;
			}
			else
			{
				r = cvar.esp_box_ct_invis_r;
				g = cvar.esp_box_ct_invis_g;
				b = cvar.esp_box_ct_invis_b;
			}
		}
	}
	else if (g_Player[i].bFriend) 
	{
		r = cvar.esp_box_friends_r;
		g = cvar.esp_box_friends_g;
		b = cvar.esp_box_friends_b;
	}

	Vector Top = Vector(ent->origin.x, ent->origin.y, ent->origin.z + ent->curstate.mins.z);
	Vector Bot = Vector(ent->origin.x, ent->origin.y, ent->origin.z + ent->curstate.maxs.z);

	float ScreenTop[2], ScreenBot[2];

	bool m_bScreenTop = g_Utils.bCalcScreen(Top, ScreenTop);
	bool m_bScreenBot = g_Utils.bCalcScreen(Bot, ScreenBot);

	if (m_bScreenTop && m_bScreenBot)
	{
		float _h = ScreenBot[1] - ScreenTop[1];
		float box_height = g_Player[i].bDucked ? _h : _h * 0.9f;
		float box_width = box_height * 0.3f;

		if (cvar.esp_box)
			g_Drawing.DrawPlayerBox(ScreenTop[0], ScreenTop[1], box_width, box_height, r, g, b, 255);

		char *szWeapon = g_PlayerExtraInfoList[i].szWeaponName;

		if (cvar.esp_weapon > 0 && szWeapon)
		{
			if (cvar.esp_weapon == 2) //Icon
			{
				unsigned int y = ScreenBot[1] + (2 - _h);

				unsigned int texture = 0;
				unsigned int w = 0;
				unsigned int h = 0;
				
				if (!lstrcmpA(szWeapon, "knife"))
					g_Utils.GetTextureInfo(wpn_knife, texture, w, h);
				else if (!lstrcmpA(szWeapon, "ak47"))
					g_Utils.GetTextureInfo(wpn_ak47, texture, w, h);
				else if (!lstrcmpA(szWeapon, "m4a1"))
					g_Utils.GetTextureInfo(wpn_m4a1, texture, w, h);
				else if (!lstrcmpA(szWeapon, "deagle"))
					g_Utils.GetTextureInfo(wpn_deagle, texture, w, h);
				else if (!lstrcmpA(szWeapon, "awp"))
					g_Utils.GetTextureInfo(wpn_awp, texture, w, h);
				else if (!lstrcmpA(szWeapon, "scout"))
					g_Utils.GetTextureInfo(wpn_scout, texture, w, h);
				else if (!lstrcmpA(szWeapon, "mp5"))
					g_Utils.GetTextureInfo(wpn_mp5n, texture, w, h);
				else if (!lstrcmpA(szWeapon, "glock"))
					g_Utils.GetTextureInfo(wpn_glock18, texture, w, h);
				else if (!lstrcmpA(szWeapon, "p90"))
					g_Utils.GetTextureInfo(wpn_p90, texture, w, h);
				else if (!lstrcmpA(szWeapon, "usp"))
					g_Utils.GetTextureInfo(wpn_usp, texture, w, h);
				else if (!lstrcmpA(szWeapon, "xm1014"))
					g_Utils.GetTextureInfo(wpn_xm1014, texture, w, h);
				else if (!lstrcmpA(szWeapon, "p228"))
					g_Utils.GetTextureInfo(wpn_p228, texture, w, h);
				else if (!lstrcmpA(szWeapon, "sg550"))
					g_Utils.GetTextureInfo(wpn_sg550, texture, w, h);
				else if (!lstrcmpA(szWeapon, "sg552"))
					g_Utils.GetTextureInfo(wpn_sg552, texture, w, h);
				else if (!lstrcmpA(szWeapon, "m249"))
					g_Utils.GetTextureInfo(wpn_m249, texture, w, h);
				else if (!lstrcmpA(szWeapon, "g3sg1"))
					g_Utils.GetTextureInfo(wpn_g3sg1, texture, w, h);
				else if (!lstrcmpA(szWeapon, "m3"))
					g_Utils.GetTextureInfo(wpn_m3, texture, w, h);
				else if (!lstrcmpA(szWeapon, "elite"))
					g_Utils.GetTextureInfo(wpn_elite, texture, w, h);
				else if (!lstrcmpA(szWeapon, "aug"))
					g_Utils.GetTextureInfo(wpn_aug, texture, w, h);
				else if (!lstrcmpA(szWeapon, "mac10"))
					g_Utils.GetTextureInfo(wpn_mac10, texture, w, h);
				else if (!lstrcmpA(szWeapon, "fiveseven"))
					g_Utils.GetTextureInfo(wpn_fiveseven, texture, w, h);
				else if (!lstrcmpA(szWeapon, "ump45"))
					g_Utils.GetTextureInfo(wpn_ump45, texture, w, h);
				else if (!lstrcmpA(szWeapon, "tmp"))
					g_Utils.GetTextureInfo(wpn_tmp, texture, w, h);
				else if (!lstrcmpA(szWeapon, "galil"))
					g_Utils.GetTextureInfo(wpn_galil, texture, w, h);
				else if (!lstrcmpA(szWeapon, "famas"))
					g_Utils.GetTextureInfo(wpn_famas, texture, w, h);

				w /= 2;
				h /= 2;

				if (texture && w && h) 
				{
					unsigned int x0 = ScreenTop[0] - (w / 2);
					unsigned int y0 = y;
					unsigned int x1 = ScreenTop[0] + (w / 2);
					unsigned int y1 = y0 + h;

					g_Drawing.DrawTexture(texture, x0, y0, x1, y1, cvar.esp_weapon_r, cvar.esp_weapon_g, cvar.esp_weapon_b, 255);
				}
				else goto default_draw_weapon;
			}
			else {
			default_draw_weapon:
				unsigned int y = ScreenBot[1] + (8 - _h);

				g_Drawing.DrawString(ESP, ScreenTop[0], y, 255, 255, 255, 255, FONT_CENTER, "%s", szWeapon);
			}
		}

		if (cvar.esp_distance)
		{
			unsigned int y = ScreenBot[1] + (-8 - _h);

			g_Drawing.DrawString(ESP, ScreenTop[0], y, 255, 255, 255, cvar.esp_alpha, FONT_CENTER, "%.f", g_Player[i].flDist);
		}

		if (cvar.esp_name && g_PlayerInfoList[i].name != NULL)
		{
			unsigned int y = box_height - 8 + ScreenTop[1];

			g_Drawing.DrawString(ESP, ScreenTop[0], y, 255, 255, 255, cvar.esp_alpha, FONT_CENTER, "%s", g_PlayerInfoList[i].name);
		}

		static unsigned int indent = 4;

		if (cvar.esp_flags)
		{
			unsigned int seq = Cstrike_SequenceInfo[ent->curstate.sequence];

			unsigned int y = 4;

			if (cvar.esp_shots_fired) {
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "%i", g_Player[i].iShotsFired);
				y += 12;
			}

			if (seq == SEQUENCE_RELOAD) {
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "R");
				y += 12;
			}
			else if (seq == SEQUENCE_ARM_C4) {
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "P");
				y += 12;
			}

			if (g_Player[i].bDucked)
			{
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "D");
				y += 12;
			}

			if (cvar.debug) {
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "P: %.3f", g_Player[i].vAngles[0]);
				y += 12;

				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + y + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "Y: %.3f", g_Player[i].vAngles[1]);
				y += 12;
			}
		}
		else {
			if (cvar.esp_shots_fired) {
				g_Drawing.DrawString(ESP, ScreenTop[0] - box_width + indent, box_height + 4 + ScreenTop[1], 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "%i", g_Player[i].iShotsFired);
			}
		}

		if (cvar.esp_hitboxes) 
		{
			float flScreenHead[2], flScreenHead2[2];

			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][0], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][2], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][0], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][3], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][0], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][4], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);

			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][6], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][1], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][6], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][2], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][6], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][4], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);

			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][5], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][1], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][5], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][3], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][5], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][4], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);

			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][7], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][1], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][7], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][2], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][7], flScreenHead);
			g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitboxPoints[11][3], flScreenHead2);
			g_Drawing.DrawLine(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 0, 255, 0, 255);

			for (unsigned int x = 0; x < 21; x++)
			{
				float ft1[2];

				if (g_Utils.bCalcScreen(g_PlayerExtraInfoList[i].vHitbox[x], ft1)) 
				{
					g_Drawing.DrawString(ESP, ft1[0], ft1[1], 0, 255, 0, cvar.esp_alpha, FONT_CENTER, "%i", x);
				}
			}
		}

		if (cvar.esp_health && !cvar.hide_from_obs)
		{
			float health_width = box_width - 5;

			unsigned int hp = g_Player[i].iHealth;

			if (hp < 0)
				hp = 0;
			else if (hp > 100)
				hp = 100;

			byte Red = 255 - (hp * 2.55);
			byte Green = hp * 2.55;

			float health_height = (box_height / 100) * hp;

			g_Drawing.DrawRect((ScreenTop[0] + health_width), ScreenTop[1], 1, health_height, Red, Green, 0, 255);

			g_Drawing.DrawOutlinedRect((ScreenTop[0] + health_width) - 1, ScreenTop[1], 3, box_height, 0, 0, 0, 255);
		}
	}
	else if(!m_bScreenTop && !m_bScreenBot)
	{
		byte a = (255 / HISTORY_MAX) * ent->current_position;
		ScreenESP(i, r, g, b, a);
	}
}

void CVisuals::Debug() 
{
	if (cvar.debug && g_Local.bAlive) 
	{
		int y = 135;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_iWeaponID: %i", g_Local.weapon.m_iWeaponID);
		y += 15;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_iWeaponState: %i", g_Local.weapon.m_iWeaponState);
		y += 15;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_iFlags: %i", g_Local.weapon.m_iFlags);
		y += 15;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_flSpread: %.3f", g_Local.weapon.m_flSpread);
		y += 15;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_flAccuracy: %.3f", g_Local.weapon.m_flAccuracy);
		y += 15;
		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + y, 255, 255, 255, cvar.esp_alpha, FONT_LEFT, "m_flBombRadius: %.3f", g_MapInfo.m_flBombRadius);
		y += 15;
	}
}

void FindPoint(float *point, int screenwidth, int screenheight, int degrees)
{
	float x2 = screenwidth / 2;
	float y2 = screenheight / 2;

	float d = sqrt(pow((point[0] - x2), 2) + (pow((point[1] - y2), 2))); //Distance
	float r = degrees / d; //Segment ratio

	point[0] = r * point[0] + (1 - r) * x2; //find point that divides the segment
	point[1] = r * point[1] + (1 - r) * y2; //into the ratio (1-r):r
}

bool WorldToScreen(float *vOrigin, float *vScreen, bool &behind)
{
	qboolean st = g_Engine.pTriAPI->WorldToScreen(vOrigin, vScreen);

	if (st)
		behind = true;
	else
		behind = false;

	float x = g_Screen.iWidth / 2 + 0.5 * vScreen[0] * g_Screen.iWidth + 0.5;
	float y = g_Screen.iHeight / 2 - 0.5 * vScreen[1] * g_Screen.iHeight + 0.5;

	vScreen[0] = x;
	vScreen[1] = y;

	if (vScreen[0] > g_Screen.iHeight || vScreen[0] < 0 || vScreen[1] > g_Screen.iWidth || vScreen[1] < 0 || st)
	{
		FindPoint(vScreen, g_Screen.iWidth, g_Screen.iHeight, g_Screen.iHeight / 2);

		return false;
	}

	return true;
}

void CVisuals::ScreenESP(unsigned int i, byte r, byte g, byte b, byte a)
{
	if (!cvar.esp_screen || !g_Local.bAlive) 
		return;

	float vecBottom[2], vecTop[2];

	bool behind, behind2;

	cl_entity_s *ent = g_Engine.GetEntityByIndex(i);

	if (!ent)
		return;

	WorldToScreen(ent->origin + Vector(0, 0, 32), vecTop, behind);
	WorldToScreen(ent->origin, vecBottom, behind2);

	if (behind) {
		vecTop[0] = g_Screen.iWidth - vecTop[0];
		vecTop[1] = g_Screen.iHeight - vecTop[1];
	}

	if (behind2) {
		vecBottom[0] = g_Screen.iWidth - vecBottom[0];
		vecBottom[1] = g_Screen.iHeight - vecBottom[1];
	}

	g_Drawing.DrawLine(vecTop[0], vecTop[1], vecBottom[0], vecBottom[1], r, g, b, a);
}

bool UTIL_EntityInSphere(cl_entity_s *ent, Vector center, float radius)
{
	float distance;
	float delta;

	float radiusSquared = radius * radius;

	delta = center.x - ent->curstate.origin.x;
	delta *= delta;

	if (delta > radiusSquared)
		return false;

	distance = delta;

	delta = center.y - ent->curstate.origin.y;
	delta *= delta;

	distance += delta;
	if (distance > radiusSquared)
		return false;

	delta = center.z - (ent->curstate.mins.z + ent->curstate.maxs.z) * 0.5;
	delta *= delta;

	distance += delta;
	if (distance > radiusSquared)
		return false;

	return true;
}

float GetAmountOfPlayerVisible(Vector vecSrc, cl_entity_s *entity)
{
	float retval = 0.0f;

	if (!entity->player) 
		return retval;

	pmtrace_t tr;

	const float topOfHead = 25.0f;
	const float standFeet = 34.0f;
	const float crouchFeet = 14.0f;
	const float edgeOffset = 13.0f;

	const float damagePercentageChest = 0.40f;
	const float damagePercentageHead = 0.20f;
	const float damagePercentageFeet = 0.20f;
	const float damagePercentageRightSide = 0.10f;
	const float damagePercentageLeftSide = 0.10f;

	// check chest
	Vector vecChest = entity->origin;
	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecChest, 0, -1, &tr);

	if (tr.fraction == 1.0f)
		retval += damagePercentageChest;

	// check top of head
	Vector vecHead = entity->origin + Vector(0, 0, topOfHead);
	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecHead, 0, -1, &tr);

	if (tr.fraction == 1.0f)
		retval += damagePercentageHead;

	// check feet
	Vector vecFeet = entity->origin;
	bool ducked = ((entity->curstate.maxs[2] - entity->curstate.mins[2]) < 54 ? true : false);
	vecFeet.z -= (ducked) ? crouchFeet : standFeet;

	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecFeet, 0, -1, &tr);

	if (tr.fraction == 1.0f)
		retval += damagePercentageFeet;

	Vector dir;
	dir = (entity->origin - vecSrc);
	dir[2] = 0;
	dir.Normalize2D();

	float perp[2];
	perp[0] = -dir.y * edgeOffset;
	perp[1] = dir.x * edgeOffset;
	Vector vecRightSide = entity->origin + Vector(perp[0], perp[1], 0);
	Vector vecLeftSide = entity->origin - Vector(perp[0], perp[1], 0);

	// check right "edge"
	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecRightSide, 0, -1, &tr);

	if (tr.fraction == 1.0f)
		retval += damagePercentageRightSide;

	// check left "edge"
	g_Engine.pEventAPI->EV_SetTraceHull(2);
	g_Engine.pEventAPI->EV_PlayerTrace(vecSrc, vecLeftSide, 0, -1, &tr);

	if (tr.fraction == 1.0f)
		retval += damagePercentageLeftSide;

	return retval;
}

void CVisuals::Bomb()
{
	if (cvar.esp_bomb && g_Local.Bomb.iFlag == BOMB_FLAG_PLANTED)
	{
		float flDamage = 500;
		float falloff;

		if (g_MapInfo.m_flBombRadius)
			falloff = flDamage / g_MapInfo.m_flBombRadius;
		else
			falloff = 1.0;

		Vector vecCenter = g_Local.Bomb.vOrigin;

		if (UTIL_EntityInSphere(g_Engine.GetLocalPlayer(), vecCenter, g_MapInfo.m_flBombRadius))
		{
			float damageRatio = GetAmountOfPlayerVisible(vecCenter, g_Engine.GetLocalPlayer());
			float length = (vecCenter - g_Local.vOrigin).Length();
			float flAdjustedDamage = flDamage - length * falloff;

			if (flAdjustedDamage > 0)
			{
				if (flAdjustedDamage >= g_Local.iHealth) {
					g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + 15, 255, 0, 0, cvar.esp_alpha, FONT_LEFT, "FATAL", flAdjustedDamage);
				}
				else {
					g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + 15, 0, 255, 0, cvar.esp_alpha, FONT_LEFT, "-%i HP", (int)flAdjustedDamage);
				}
			}
		}

		float flScreen[2];

		if (g_Utils.bCalcScreen(g_Local.Bomb.vOrigin, flScreen))
		{
			g_Drawing.DrawString(ESP, flScreen[0], flScreen[1], cvar.esp_bomb_r, cvar.esp_bomb_g, cvar.esp_bomb_b, cvar.esp_alpha, FONT_CENTER, "Bomb");
		}
	}
}

void CVisuals::Lightmap()
{
	if (g_pIRunGameEngine->IsInGame())
	{
		static bool replaced = false;
		static float brightness_r = cvar.brightness_r;
		static float brightness_g = cvar.brightness_g;
		static float brightness_b = cvar.brightness_b;
		static float brightness = cvar.brightness;

		if (cvar.brightness > 0 && !cvar.hide_from_obs)
		{
			if (!replaced) {
				g_Engine.OverrideLightmap(1);
				g_Engine.SetLightmapColor(cvar.brightness_r, cvar.brightness_g, cvar.brightness_b);
				g_Engine.SetLightmapDarkness(cvar.brightness);
				replaced = true;
			}
			else {
				if (brightness_r != cvar.brightness_r || brightness_g != cvar.brightness_g || brightness_b != cvar.brightness_b || brightness != cvar.brightness)
					replaced = false;
			}
		}
		else {
			g_Engine.OverrideLightmap(0);
			replaced = false;
		}
	}
}

void CVisuals::DrawFake(int PlayerID, int EntityID)
{
	if (!g_Player[PlayerID].bAlive && g_PlayerInfoList[PlayerID].name != NULL && (g_Player[PlayerID].iTeam == TERRORIST || g_Player[PlayerID].iTeam == CT))
	{
		if (!cvar.esp_teammates && g_Player[PlayerID].iTeam == g_Local.iTeam)
			return;

		if (!g_Utils.bPathFree(g_Local.vEye, g_Entities[EntityID].vOrigin))
		{
			byte r = 0, g = 0, b = 0;

			if (g_Player[PlayerID].iTeam == TERRORIST)
			{
				r = cvar.esp_box_t_invis_r;
				g = cvar.esp_box_t_invis_g;
				b = cvar.esp_box_t_invis_b;
			}
			else if (g_Player[PlayerID].iTeam == CT)
			{
				r = cvar.esp_box_ct_invis_r;
				g = cvar.esp_box_ct_invis_g;
				b = cvar.esp_box_ct_invis_b;
			}

			Vector Top = Vector(g_Entities[EntityID].vOrigin.x, g_Entities[EntityID].vOrigin.y, g_Entities[EntityID].vOrigin.z - 36);
			Vector Bot = Vector(g_Entities[EntityID].vOrigin.x, g_Entities[EntityID].vOrigin.y, g_Entities[EntityID].vOrigin.z + 36);

			float ScreenTop[2], ScreenBot[2];

			bool m_bScreenTop = g_Utils.bCalcScreen(Top, ScreenTop);
			bool m_bScreenBot = g_Utils.bCalcScreen(Bot, ScreenBot);

			if (m_bScreenTop && m_bScreenBot)
			{
				float _h = ScreenBot[1] - ScreenTop[1];
				float box_height = _h * 0.9f;
				float box_width = box_height * 0.3f;

				float Screen[2];

				if (g_Utils.bCalcScreen(g_Entities[EntityID].vOrigin, Screen))
				{
					g_Drawing.DrawString(ESP, Screen[0], Screen[1], 255, 0, 0, cvar.esp_alpha, FONT_CENTER, "FAKE");
				}

				if (cvar.esp_box)
				{
					g_Drawing.DrawPlayerBox(ScreenTop[0], ScreenTop[1], box_width, box_height, r, g, b, 255);
				}

				if (cvar.esp_distance)
				{
					float y = ScreenBot[1] + (-8 - _h);

					g_Drawing.DrawString(ESP, ScreenTop[0], y, 255, 255, 255, cvar.esp_alpha, FONT_CENTER, "%.f", g_Local.vOrigin.Distance(g_Entities[EntityID].vOrigin));
				}

				if (cvar.esp_name && g_PlayerInfoList[PlayerID].name != NULL)
				{
					float y = box_height - 8 + ScreenTop[1];

					g_Drawing.DrawString(ESP, ScreenTop[0], y, 255, 255, 255, cvar.esp_alpha, FONT_CENTER, "%s", g_PlayerInfoList[PlayerID].name);
				}
			}
		}
	}
}

void CVisuals::DrawEntities()
{
	for (unsigned int i = MAX_CLIENTS + 1; i < 256; i++)
	{
		if (!g_Entities[i].bUpdated)
		{
			if (cvar.grenade_trajectory) {
				Grenades[i].vPoints.clear();
				Grenades[i].dwUpdated = 0;
			}
			continue;
		}

		if (cvar.debug) 
		{
			float flScreen[2];

			if (g_Utils.bCalcScreen(g_Entities[i].vOrigin, flScreen))
			{
				g_Drawing.DrawString(ESP, flScreen[0], flScreen[1], 255, 255, 255, cvar.esp_alpha, FONT_CENTER, "%s (id: %i)", g_Entities[i].szModelName, i);
			}
		}

		if (g_Entities[i].bIsWeapon)
		{
			if (cvar.esp_world_weapon > 0)
			{
				float flScreen[2];

				if (g_Utils.bCalcScreen(g_Entities[i].vOrigin, flScreen))
				{
					char *szWeapon = strstr(g_Entities[i].szModelName, "/w_");

					if (szWeapon)
					{
						szWeapon = &szWeapon[3];
						g_Utils.StringReplace(szWeapon, ".mdl", "");

						if (cvar.esp_world_weapon == 2)
						{
							unsigned int texture = 0;
							unsigned int w = 0;
							unsigned int h = 0;

							if (!lstrcmpA(szWeapon, "knife"))
								g_Utils.GetTextureInfo(wpn_knife, texture, w, h);
							else if (!lstrcmpA(szWeapon, "ak47"))
								g_Utils.GetTextureInfo(wpn_ak47, texture, w, h);
							else if (!lstrcmpA(szWeapon, "m4a1"))
								g_Utils.GetTextureInfo(wpn_m4a1, texture, w, h);
							else if (!lstrcmpA(szWeapon, "deagle"))
								g_Utils.GetTextureInfo(wpn_deagle, texture, w, h);
							else if (!lstrcmpA(szWeapon, "awp"))
								g_Utils.GetTextureInfo(wpn_awp, texture, w, h);
							else if (!lstrcmpA(szWeapon, "scout"))
								g_Utils.GetTextureInfo(wpn_scout, texture, w, h);
							else if (!lstrcmpA(szWeapon, "mp5"))
								g_Utils.GetTextureInfo(wpn_mp5n, texture, w, h);
							else if (!lstrcmpA(szWeapon, "glock"))
								g_Utils.GetTextureInfo(wpn_glock18, texture, w, h);
							else if (!lstrcmpA(szWeapon, "p90"))
								g_Utils.GetTextureInfo(wpn_p90, texture, w, h);
							else if (!lstrcmpA(szWeapon, "usp"))
								g_Utils.GetTextureInfo(wpn_usp, texture, w, h);
							else if (!lstrcmpA(szWeapon, "xm1014"))
								g_Utils.GetTextureInfo(wpn_xm1014, texture, w, h);
							else if (!lstrcmpA(szWeapon, "p228"))
								g_Utils.GetTextureInfo(wpn_p228, texture, w, h);
							else if (!lstrcmpA(szWeapon, "sg550"))
								g_Utils.GetTextureInfo(wpn_sg550, texture, w, h);
							else if (!lstrcmpA(szWeapon, "sg552"))
								g_Utils.GetTextureInfo(wpn_sg552, texture, w, h);
							else if (!lstrcmpA(szWeapon, "m249"))
								g_Utils.GetTextureInfo(wpn_m249, texture, w, h);
							else if (!lstrcmpA(szWeapon, "g3sg1"))
								g_Utils.GetTextureInfo(wpn_g3sg1, texture, w, h);
							else if (!lstrcmpA(szWeapon, "m3"))
								g_Utils.GetTextureInfo(wpn_m3, texture, w, h);
							else if (!lstrcmpA(szWeapon, "elite"))
								g_Utils.GetTextureInfo(wpn_elite, texture, w, h);
							else if (!lstrcmpA(szWeapon, "aug"))
								g_Utils.GetTextureInfo(wpn_aug, texture, w, h);
							else if (!lstrcmpA(szWeapon, "mac10"))
								g_Utils.GetTextureInfo(wpn_mac10, texture, w, h);
							else if (!lstrcmpA(szWeapon, "fiveseven"))
								g_Utils.GetTextureInfo(wpn_fiveseven, texture, w, h);
							else if (!lstrcmpA(szWeapon, "ump45"))
								g_Utils.GetTextureInfo(wpn_ump45, texture, w, h);
							else if (!lstrcmpA(szWeapon, "tmp"))
								g_Utils.GetTextureInfo(wpn_tmp, texture, w, h);
							else if (!lstrcmpA(szWeapon, "galil"))
								g_Utils.GetTextureInfo(wpn_galil, texture, w, h);
							else if (!lstrcmpA(szWeapon, "famas"))
								g_Utils.GetTextureInfo(wpn_famas, texture, w, h);

							w /= 2;
							h /= 2;

							if (texture && w && h)
							{
								unsigned int x0 = flScreen[0] - (w / 2);
								unsigned int y0 = flScreen[1];
								unsigned int x1 = flScreen[0] + (w / 2);
								unsigned int y1 = y0 + h;

								g_Drawing.DrawTexture(texture, x0, y0, x1, y1, cvar.esp_world_weapon_r, cvar.esp_world_weapon_g, cvar.esp_world_weapon_b, 255);
							}
							else goto default_draw_weapon;
						}
						else {
						default_draw_weapon:
							g_Drawing.DrawString(ESP, flScreen[0], flScreen[1], cvar.esp_world_weapon_r, cvar.esp_world_weapon_g, cvar.esp_world_weapon_b, cvar.esp_alpha, FONT_CENTER, "%s", szWeapon);
						}
					}
				}
			}

			if (cvar.grenade_trajectory && (strstr(g_Entities[i].szModelName, "flashbang") || strstr(g_Entities[i].szModelName, "smokegrenade") || strstr(g_Entities[i].szModelName, "hegrenade")))
			{
				if (!Grenades[i].vPoints.empty() && Grenades[i].vPoints[Grenades[i].vPoints.size() - 1] != g_Entities[i].vOrigin)
					Grenades[i].dwUpdated = GetTickCount();

				Grenades[i].vPoints.push_back(g_Entities[i].vOrigin);
			}
		}
		else if (cvar.esp && cvar.esp_fake && g_Entities[i].bIsFakeEntity && g_Entities[i].iResolvedIndex != g_Local.iIndex)
		{
			DrawFake(g_Entities[i].iResolvedIndex, i);
		}
	}

	if (cvar.grenade_trajectory) 
	{
		float flScreen[2], flScreenLast[2];

		for (unsigned int i = MAX_CLIENTS + 1; i < 256; i++)
		{
			if (Grenades[i].vPoints.empty())
				continue;

			if (GetTickCount() - Grenades[i].dwUpdated > 1500)
				continue;

			for (unsigned int x = 1; x < Grenades[i].vPoints.size(); x++)
			{
				if (g_Utils.bCalcScreen(Grenades[i].vPoints[x], flScreen) && g_Utils.bCalcScreen(Grenades[i].vPoints[x - 1], flScreenLast))
				{
					g_Drawing.DrawLine(flScreen[0], flScreen[1], flScreenLast[0], flScreenLast[1], 255, 0, 0, cvar.esp_alpha);
				}
			}
		}
	}
}