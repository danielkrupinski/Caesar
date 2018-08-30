#include "../../Required.h"

CMisc g_Misc;

void CMisc::FastZoom(struct usercmd_s *cmd)
{
	if (!cvar.aim && cvar.fastzoom && IsCurWeaponSniper() && g_Local.iFOV == DEFAULT_FOV && cmd->buttons & IN_ATTACK)
	{
		cmd->buttons &= ~IN_ATTACK;
		cmd->buttons |= IN_ATTACK2;
	}
}

void CMisc::FakeLag(struct usercmd_s *cmd) 
{
	if (cvar.aim && cvar.fakelag)
	{
		int m_InAttack = (cmd->buttons & IN_ATTACK);

		bool fakelag = false;

		if (!(m_InAttack && CanAttack()))
			fakelag = true;

		if (cvar.fakelag_while_shooting && m_InAttack && CanAttack())
			fakelag = true;

		if (cvar.fakelag_move == 1)//On land
		{
			if (g_Local.flVelocity > 0)
				fakelag = false;
		}
		else if (cvar.fakelag_move == 2)//On move
		{
			if (g_Local.flVelocity <= 0)
				fakelag = false;
		}
		else if (cvar.fakelag_move == 3)//In air
		{
			if (g_Local.flHeight <= 0)
				fakelag = false;
		}
		
		if (fakelag) 
		{
			static int choked = 0;
			static int good = 0;

			if (cvar.fakelag_type == 1)//Dynamic
			{
				if (choked < cvar.fakelag_limit)
				{
					g_Utils.bSendpacket(false);

					choked++;

					good = 0;
				}
				else {
					float one = cvar.fakelag_limit / 100;
					float tmp = one * cvar.fakelag_variance;

					good++;

					if (good > tmp) {
						choked = 0;
					}
				}
			}
			else if (cvar.fakelag_type == 2)//Maximum
			{
				choked++;

				if (choked > 0)
					g_Utils.bSendpacket(false);

				if (choked > cvar.fakelag_limit)
					choked = -1;//1 tick valid
			}
			else if (cvar.fakelag_type == 3)//Flucture
			{
				static bool jitter = false;

				if(jitter)
					g_Utils.bSendpacket(false);

				jitter = !jitter;
			}
			else if (cvar.fakelag_type == 4)//Break lag compensation
			{
				Vector velocity = pmove->velocity;
				velocity.z = 0;

				float len = velocity.Length() * g_Local.flFrametime;

				if (len < 64.0f && velocity.Length() > 0.05f)
				{
					int need_choke = 64.0f / len;

					if (need_choke > cvar.fakelag_limit)
						need_choke = cvar.fakelag_limit;

					//g_Engine.Con_NPrintf(1, "need_choke: %i", need_choke);

					if (choked < need_choke)
					{
						g_Utils.bSendpacket(false);

						choked++;
					}
					else {
						choked = 0;
					}

					//g_Engine.Con_NPrintf(2, "choked: %i", choked);
				}
			}
		}
	}
}

bool CMisc::FakeEdge(float &angle)
{
	float edge_dist = 128;

	Vector position = g_Local.vEye;

	float closest_distance = 100.0f;

	float radius = edge_dist + 0.1f;
	float step = M_PI * 2.0 / 8;

	for (float a = 0; a < (M_PI * 2.0); a += step)
	{
		Vector location(radius * cos(a) + position.x, radius * sin(a) + position.y, position.z);

		pmtrace_t tr;

		g_Engine.pEventAPI->EV_SetTraceHull(2);
		g_Engine.pEventAPI->EV_PlayerTrace(position, location, PM_GLASS_IGNORE, -1, &tr);

		float distance = position.Distance(tr.endpos);

		if (distance < closest_distance)
		{
			closest_distance = distance;
			angle = RAD2DEG(a);
		}
	}

	return closest_distance < edge_dist;
}

void CMisc::AntiAim(struct usercmd_s *cmd)
{
	if (cvar.aim) 
	{
		int m_OnLadder = (pmove->movetype == MOVETYPE_FLY);// determine if we are on a ladder
		int m_Use = (cmd->buttons & IN_USE);
		int m_InAttack = (cmd->buttons & IN_ATTACK);

		if (!m_Use && IsCurWeaponGun() && !(m_InAttack && CanAttack()))
		{
			g_Utils.FixMoveStart(cmd);

			int id = NULL;
			float flDist = 8192.f;

			for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
			{
				if (i == g_Local.iIndex)
					continue;

				if (!g_Player[i].bAlive)
					continue;

				if (g_Player[i].bFriend)
					continue;

				if (!cvar.aim_teammates && g_Player[i].iTeam == g_Local.iTeam)
					continue;

				if (g_Player[i].flDist < flDist || id == NULL)
				{
					flDist = g_Player[i].flDist;
					id = i;
				}
			}

			Vector vAngles = cmd->viewangles;

			if(id > 0)
				g_Utils.VectorAngles(g_PlayerExtraInfoList[id].vHitbox[0] - g_Local.vEye, vAngles);

			//Yaw
			if (g_Local.flVelocity > 0) {
				if (cvar.aa_yaw_while_running > 0) {
					if (cvar.aa_yaw_while_running == 1) {//180
						cmd->viewangles.y = vAngles[1] + 180;
					}
					else if (cvar.aa_yaw_while_running == 2) {//180 Jitter
						static bool jitter = false;

						if (jitter)
							cmd->viewangles.y = vAngles[1] + 180;
						else
							cmd->viewangles.y = vAngles[1];

						jitter = !jitter;
					}
					else if (cvar.aa_yaw_while_running == 3) {//Spin
						int spin = 30;
						cmd->viewangles.y = fmod(g_Engine.GetClientTime()*spin*360.0f, 360.0f);
					}
					else if (cvar.aa_yaw_while_running == 4) {//Jitter
						static unsigned int m_side = 0;

						if (m_side == 0)
							cmd->viewangles.y = vAngles[1] + 0;
						else if (m_side == 1)
							cmd->viewangles.y = vAngles[1] + 90;
						else if (m_side == 2)
							cmd->viewangles.y = vAngles[1] + 180;
						else if (m_side >= 3) {
							cmd->viewangles.y = vAngles[1] + -90;
							m_side = 0;
						}

						m_side++;
					}
					else if (cvar.aa_yaw_while_running == 5) {//Sideway
						static bool jitter = false;

						if (jitter)
							cmd->viewangles.y = vAngles[1] + 90;
						else
							cmd->viewangles.y = vAngles[1] - 90;

						jitter = !jitter;
					}
					else if (cvar.aa_yaw_while_running == 6) {//Random
						cmd->viewangles.y = rand() % 361;
						if (cmd->viewangles.y > 180)
							cmd->viewangles.y -= 360;
					}
					else if (cvar.aa_yaw_while_running == 7) {//Static
						cmd->viewangles.y = vAngles[1] + cvar.aa_yaw_static;
					}
				}

				float angle = cmd->viewangles.y;

				if ((cvar.aa_edge == 2 || cvar.aa_edge == 3) && FakeEdge(angle))
					cmd->viewangles.y = angle;
			}
			else {
				if (cvar.aa_yaw > 0) {
					if (cvar.aa_yaw == 1) {//180
						cmd->viewangles.y = vAngles[1] + 180;
					}
					else if (cvar.aa_yaw == 2) {//180 Jitter
						static bool jitter = false;

						if (jitter)
							cmd->viewangles.y = vAngles[1] + 180;
						else
							cmd->viewangles.y = vAngles[1];

						jitter = !jitter;
					}
					else if (cvar.aa_yaw == 3) {//Spin
						int spin = 30;
						cmd->viewangles.y = fmod(g_Engine.GetClientTime()*spin*360.0f, 360.0f);
					}
					else if (cvar.aa_yaw == 4) {//Jitter
						static unsigned int m_side = 0;

						if (m_side == 0)
							cmd->viewangles.y = vAngles[1] + 0;
						else if (m_side == 1)
							cmd->viewangles.y = vAngles[1] + 90;
						else if (m_side == 2)
							cmd->viewangles.y = vAngles[1] + 180;
						else if (m_side >= 3) {
							cmd->viewangles.y = vAngles[1] + -90;
							m_side = 0;
						}

						m_side++;
					}
					else if (cvar.aa_yaw == 5) {//Sideway
						static bool jitter = false;

						if (jitter)
							cmd->viewangles.y = vAngles[1] + 90;
						else
							cmd->viewangles.y = vAngles[1] - 90;

						jitter = !jitter;
					}
					else if (cvar.aa_yaw == 6) {//Random
						cmd->viewangles.y = rand() % 361;
						if (cmd->viewangles.y > 180)
							cmd->viewangles.y -= 360;
					}
					else if (cvar.aa_yaw == 7) {//Static
						cmd->viewangles.y = vAngles[1] + cvar.aa_yaw_static;
					}
				}

				float angle = cmd->viewangles.y;

				if ((cvar.aa_edge == 1 || cvar.aa_edge == 3 || cvar.aa_edge == 4) && FakeEdge(angle))
				{
					static float timer = g_Local.weapon.curtime;

					if (g_Local.weapon.curtime - timer > 3 && cvar.aa_edge == 4)
					{
						timer = g_Local.weapon.curtime;

						cmd->viewangles.y = angle + 180;
					}
					else {
						cmd->viewangles.y = angle;
					}
				}
			}
			
			//Pitch
			if (cvar.aa_pitch > 0)
			{
				if (cvar.aa_pitch == 1) {//Fakedown
					cmd->viewangles.x = 180;
				}
				else if (cvar.aa_pitch == 2) {//Down
					cmd->viewangles.x = -88;
				}
				else if (cvar.aa_pitch == 3) {//Up
					cmd->viewangles.x = 88;
				}
				else if (cvar.aa_pitch == 4) {//Jitter
					static bool jitter = false;

					if (jitter)
						cmd->viewangles.x = 88;
					else
						cmd->viewangles.x = -88;

					jitter = !jitter;
				}
				else if (cvar.aa_pitch == 5) {//Random
					cmd->viewangles.x = rand() % 361;
					if (cmd->viewangles.x > 180)
						cmd->viewangles.x -= 360;
				}
			}

			g_Utils.FixMoveEnd(cmd);
		}
	}
}

void CMisc::AutoPistol(struct usercmd_s *cmd) 
{
	if (cvar.autopistol && cmd->buttons & IN_ATTACK && IsCurWeaponPistol() && !g_Local.weapon.m_iInReload)
	{
		static bool bFire = false;

		if (CanAttack() && bFire)
		{
			cmd->buttons |= IN_ATTACK;
			bFire = false;
		}
		else if (!bFire) 
		{
			cmd->buttons &= ~IN_ATTACK;
			bFire = true;
		}
	}
}

void CMisc::AutoReload(struct usercmd_s *cmd)
{
	if (cvar.autoreload && cmd->buttons & IN_ATTACK && g_Local.weapon.m_iClip < 1 && IsCurWeaponGun()) 
	{
		cmd->buttons &= ~IN_ATTACK;
		cmd->buttons |= IN_RELOAD;
	}
}

void CMisc::ThirdPerson(struct ref_params_s *pparams)
{
	if (g_Local.bAlive && cvar.thirdperson > 0 && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot && !cvar.hide_from_obs) 
	{
		Vector Offset(0, 0, 0);
		Vector r, u, b;

		VectorMul(pparams->right, 0, r);
		VectorMul(pparams->up, 15, u);
		VectorMul(pparams->forward, -(cvar.thirdperson), b);

		Offset = Offset + r;
		Offset = Offset + u;
		Offset = Offset + b;

		pparams->vieworg[0] += Offset[0];
		pparams->vieworg[1] += Offset[1];
		pparams->vieworg[2] += Offset[2];
	}
}

void change_name(char *str)
{
	if (strstr(str, "  ") != NULL)
	{
		strcpy(strstr(str, "  "), strstr(str, "  ") + 1);
		return;
	}
	if (str[0] == str[strlen(str) - 1])
	{
		char buf[256];
		char sbuf[2] = "A";
		sbuf[0] = str[0];
		strcpy_s(buf, sbuf);
		strcat_s(buf, str);
		strcpy(str, buf);
		return;
	}
	if (strlen(str)>16)
	{
		str[strlen(str) - 1] = 0;
		return;
	}
	if (strstr(str, ".") != NULL)
	{
		*strstr(str, ".") = ',';
		return;
	}
	if (strstr(str, ",") != NULL)
	{
		*strstr(str, ",") = '.';
		return;
	}
	if (strstr(str, " ") != NULL)
	{
		char buf[256];
		strcpy_s(buf, str);
		strcpy(strstr(buf, " ") + 1, strstr(str, " "));
		strcpy(str, buf);
		return;
	}
	if (strstr(str, "-") != NULL)
	{
		*strstr(str, "-") = '=';
		return;
	}
	if (strstr(str, "=") != NULL)
	{
		*strstr(str, "=") = '-';
		return;
	}
	if (strstr(str, ":") != NULL)
	{
		*strstr(str, ":") = ';';
		return;
	}
	if (str[strlen(str) - 1] == str[strlen(str) - 2])
	{
		str[strlen(str) - 1] = 0;
		return;
	}
	strcat(str, ".");
}

void CMisc::NameStealer()
{
	static DWORD timer = GetTickCount();

	if (cvar.name_stealer > 0)
	{
		char cNames[MAX_CLIENTS][MAX_PLAYER_NAME_LENGTH];
		unsigned int iCount = 0;

		if (GetTickCount() - timer < cvar.name_stealer)
			return;

		for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
		{
			if (i == g_Local.iIndex)
				continue;

			if (g_PlayerInfoList[i].name == NULL || g_PlayerInfoList[i].name == "")
				continue;

			if (strlen(g_PlayerInfoList[i].name) <= 1)
				continue;

			strcpy_s(cNames[iCount++], g_PlayerInfoList[i].name);
		}

		if (iCount > 0)
		{
			char cmdstr[256];
			char name[MAX_PLAYER_NAME_LENGTH];
			unsigned int n = rand() % iCount;
			strcpy_s(cmdstr, "name \"");
			strcpy_s(name, cNames[n]);
			change_name(name);
			strcat_s(cmdstr, name);
			strcat_s(cmdstr, "\"");
			g_Engine.pfnClientCmd(cmdstr);
		}

		timer = GetTickCount();
	}
}