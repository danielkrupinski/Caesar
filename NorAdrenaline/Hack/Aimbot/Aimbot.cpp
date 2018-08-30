#include "../../Required.h"

CAimBot g_AimBot;

void SmoothAimAngles(QAngle MyViewAngles, QAngle AimAngles, QAngle &OutAngles, float Smoothing, bool bSpiral, float SpiralX, float SpiralY)
{
	if (Smoothing < 1)
	{
		OutAngles = AimAngles;
		return;
	}

	OutAngles = AimAngles - MyViewAngles;

	OutAngles.Normalize();

	Vector vecViewAngleDelta = OutAngles;

	if (bSpiral & SpiralX != 0 && SpiralY != 0)
		vecViewAngleDelta += Vector(vecViewAngleDelta.y / SpiralX, vecViewAngleDelta.x / SpiralY, 0.0f);

	if (!isnan(Smoothing))
		vecViewAngleDelta /= Smoothing;

	OutAngles = MyViewAngles + vecViewAngleDelta;

	OutAngles.Normalize();
}

void CAimBot::Run(struct usercmd_s *cmd)
{
	if (cvar.aim)
	{
		RageAimbot(cmd);
	}
	else
	{
		LegitAimbot(cmd);
		Trigger(cmd);
	}
}

void CAimBot::Trigger(struct usercmd_s *cmd)
{
	if (cvar.trigger_key > 0 && cvar.trigger_key < 255)
	{
		static DWORD dwTemporaryBlockTimer = 0;

		if (GetTickCount() - dwTemporaryBlockTimer > 200)
		{
			if (g_Menu.keys[cvar.trigger_key]) {
				TriggerKeyStatus = !TriggerKeyStatus;
				dwTemporaryBlockTimer = GetTickCount();
			}
		}

		if (!TriggerKeyStatus)
			return;
	}

	if (!IsCurWeaponGun() || !CanAttack())
		return;

	unsigned int m_iWeaponID = g_Local.weapon.m_iWeaponID;

	if (!cvar.legit[m_iWeaponID].trigger)
		return;

	if (cvar.trigger_only_zoomed && IsCurWeaponSniper() && g_Local.iFOV == DEFAULT_FOV)
		return;

	deque<unsigned int> Hitboxes;

	if (cvar.legit[m_iWeaponID].trigger_head)
	{
		Hitboxes.push_back(11);
	}

	if (cvar.legit[m_iWeaponID].trigger_chest)
	{
		Hitboxes.push_back(7);
		Hitboxes.push_back(8);
		Hitboxes.push_back(9);
		Hitboxes.push_back(10);
		Hitboxes.push_back(11);
		Hitboxes.push_back(12);
		Hitboxes.push_back(17);
	}

	if (cvar.legit[m_iWeaponID].trigger_stomach)
	{
		Hitboxes.push_back(0);
	}

	float flAccuracy = cvar.legit[m_iWeaponID].trigger_accuracy;

	Vector vecSpreadDir, vecForward, vecRight, vecUp, vecRandom;

	QAngle QAngles;

	g_Engine.GetViewAngles(QAngles);

	if (flAccuracy > 0)//Recoil
	{
		QAngles[0] += g_Local.vPunchangle[0];
		QAngles[1] += g_Local.vPunchangle[1];
		QAngles[2] = NULL;
	}

	QAngles.Normalize();

	QAngles.AngleVectors(&vecForward, &vecRight, &vecUp);

	if (flAccuracy > 1)//Recoil / Spread
	{
		g_NoSpread.GetSpreadXY(g_Local.weapon.random_seed, 1, vecRandom);

		vecSpreadDir = vecForward + (vecRight * vecRandom[0]) + (vecUp * vecRandom[1]);

		vecSpreadDir.Normalize();
	}
	else {//Empty or Recoil
		vecSpreadDir = vecForward;

		vecSpreadDir.Normalize();
	}

	for (unsigned int id = 1; id <= g_Engine.GetMaxClients(); ++id)
	{
		if (id == g_Local.iIndex)
			continue;

		if (!g_Player[id].bAlive)
			continue;

		if (!g_Player[id].bVisible)
			continue;

		if (g_Player[id].bFriend)
			continue;

		if (!cvar.legit_teammates && g_Player[id].iTeam == g_Local.iTeam)
			continue;

		for (auto &&hitbox : Hitboxes)
		{
			if (g_Utils.IsBoxIntersectingRay(g_PlayerExtraInfoList[id].vHitboxMin[hitbox], g_PlayerExtraInfoList[id].vHitboxMax[hitbox], g_Local.vEye, vecSpreadDir))
			{
				cmd->buttons |= IN_ATTACK;
				break;
			}
		}
	}
}

void CAimBot::LegitAimbot(struct usercmd_s *cmd)
{
	static DWORD dwBlockAttack = 0;

	static float flSpeedSpiralX = 1.3;
	static float flSpeedSpiralY = 3.7;

	m_flCurrentFOV = 0;

	if (!IsCurWeaponGun() || g_Local.weapon.m_iInReload || g_Local.weapon.m_iClip < 1 || g_Local.weapon.m_flNextAttack > 0.0)
		return;

	unsigned int iWeaponID = g_Local.weapon.m_iWeaponID;

	if (!cvar.legit[iWeaponID].aim)
		return;

	float flFOV = cvar.legit[iWeaponID].aim_fov;

	if (flFOV <= 0)
		return;

	float flSpeed = cvar.legit[iWeaponID].aim_speed_in_attack;

	if (cvar.legit[iWeaponID].aim_speed > 0 && !(cmd->buttons & IN_ATTACK))//Auto aim smooth
		flSpeed = cvar.legit[iWeaponID].aim_speed;

	if (flSpeed <= 0)
		return;

	deque<unsigned int> Hitboxes;

	if (cvar.legit[iWeaponID].aim_head)
		Hitboxes.push_back(11);

	if (cvar.legit[iWeaponID].aim_chest)
	{
		Hitboxes.push_back(7);
		Hitboxes.push_back(8);
		Hitboxes.push_back(9);
		Hitboxes.push_back(10);
		Hitboxes.push_back(12);
		Hitboxes.push_back(17);
	}

	if (cvar.legit[iWeaponID].aim_stomach)
		Hitboxes.push_back(0);

	if (Hitboxes.empty())
		return;

	float flReactionTime = cvar.legit[iWeaponID].aim_reaction_time;

	if (flReactionTime > 0 && GetTickCount() - dwReactionTime < flReactionTime)
		return;

	float flSpeedScaleFov = cvar.legit[iWeaponID].aim_speed_scale_fov;

	bool bSpeedSpiral = cvar.legit[iWeaponID].aim_humanize;

	if (!g_Local.vPunchangle.IsZero2D())
		bSpeedSpiral = false;

	float flRecoilCompensationPitch = 0.02 * cvar.legit[iWeaponID].aim_recoil_compensation_pitch;
	float flRecoilCompensationYaw = 0.02 * cvar.legit[iWeaponID].aim_recoil_compensation_yaw;

	unsigned int iRecoilCompensationAfterShotsFired = cvar.legit[iWeaponID].aim_recoil_compensation_after_shots_fired;

	if (iRecoilCompensationAfterShotsFired > 0 && g_Local.weapon.m_iShotsFired <= iRecoilCompensationAfterShotsFired)
	{
		flRecoilCompensationPitch = 0;
		flRecoilCompensationYaw = 0;
	}

	float flBlockAttackAfterKill = cvar.block_attack_after_kill;

	float flAccuracy = cvar.legit[iWeaponID].aim_accuracy;

	float flPSilent = cvar.legit[iWeaponID].aim_psilent;

	Vector vecFOV = {};
	{
		QAngle QAngles = cmd->viewangles + g_Local.vPunchangle * 2;
		QAngles.Normalize();
		QAngles.AngleVectors(&vecFOV, NULL, NULL);
		vecFOV.Normalize();
	}
	
	m_flCurrentFOV = flFOV;

	unsigned int iTarget = 0;
	unsigned int iHitbox = 0;

	float flBestFOV = flFOV;

	for (unsigned int id = 1; id <= g_Engine.GetMaxClients(); ++id)
	{
		if (id == g_Local.iIndex)
			continue;

		if (!g_Player[id].bAlive)
			continue;

		if (!g_Player[id].bVisible)
			continue;

		if (g_Player[id].bFriend)
			continue;

		if (!cvar.legit_teammates && g_Player[id].iTeam == g_Local.iTeam)
			continue;

		for (auto &&hitbox : Hitboxes)
		{
			if (!g_PlayerExtraInfoList[id].bHitboxVisible[hitbox])
				continue;

			if (cvar.legit[iWeaponID].aim_head && (cvar.legit[iWeaponID].aim_chest || cvar.legit[iWeaponID].aim_stomach) && hitbox == 11 && (!(g_Local.weapon.m_iFlags & FL_ONGROUND) || g_Local.flVelocity > 140 || g_Local.weapon.m_iShotsFired > 5))
				continue;

			if (cvar.legit[iWeaponID].aim_chest && cvar.legit[iWeaponID].aim_stomach && hitbox != 0 && hitbox != 11 && (!(g_Local.weapon.m_iFlags & FL_ONGROUND) || g_Local.weapon.m_iShotsFired > 15))
				continue;

			float fov = vecFOV.AngleBetween(g_PlayerExtraInfoList[id].vHitbox[hitbox] - g_Local.vEye);

			if (fov < flBestFOV)
			{
				flBestFOV = fov;
				iTarget = id;
				iHitbox = hitbox;
			}
		}
	}

	if (iTarget > 0)
	{
		bool bAttack = false;
		bool bBlock = false;//Block IN_ATTACK?

		if (cvar.legit[iWeaponID].aim_quick_stop)
		{
			cmd->forwardmove = 0;
			cmd->sidemove = 0;
			cmd->upmove = 0;
		}

		QAngle QMyAngles, QAimAngles, QNewAngles, QSmoothAngles;

		Vector vAimOrigin = g_PlayerExtraInfoList[iTarget].vHitbox[iHitbox];

		g_Engine.GetViewAngles(QMyAngles);

		g_Utils.VectorAngles(vAimOrigin - g_Local.vEye, QAimAngles);

		if (flPSilent > 0 && flPSilent <= 1 && CanAttack())
		{
			QAngle QAnglePerfectSilent = QAimAngles;

			QAnglePerfectSilent += g_Local.vPunchangle;

			QAnglePerfectSilent.Normalize();

			g_NoSpread.GetSpreadOffset(g_Local.weapon.random_seed, 1, QAnglePerfectSilent, QAnglePerfectSilent);

			Vector vecPsilentFOV;
			QAnglePerfectSilent.AngleVectors(&vecPsilentFOV, NULL, NULL);
			vecPsilentFOV.Normalize();

			float fov = vecPsilentFOV.AngleBetween(g_PlayerExtraInfoList[iTarget].vHitbox[iHitbox] - g_Local.vEye);

			if (fov <= flPSilent)
			{
				cmd->buttons |= IN_ATTACK;

				g_Utils.MakeAngle(false, QAnglePerfectSilent, cmd);
				g_Utils.bSendpacket(false);

				dwBlockAttack = GetTickCount();
				return;
			}
		}

		QNewAngles[0] = QAimAngles[0] - g_Local.vPunchangle[0] * flRecoilCompensationPitch;
		QNewAngles[1] = QAimAngles[1] - g_Local.vPunchangle[1] * flRecoilCompensationYaw;
		QNewAngles[2] = 0;

		QNewAngles.Normalize();

		/*if (cmd->buttons & IN_ATTACK && CanAttack())
			g_NoSpread.GetSpreadOffset(g_Local.weapon.random_seed, 1, QNewAngles, QNewAngles);*/

		if (flSpeedScaleFov > 0 && flSpeedScaleFov <= 100 && g_Local.vPunchangle.IsZero() && !isnan(g_PlayerExtraInfoList[iTarget].fHitboxFOV[iHitbox]))
			flSpeed = flSpeed - (((g_PlayerExtraInfoList[iTarget].fHitboxFOV[iHitbox] * (flSpeed / m_flCurrentFOV)) * flSpeedScaleFov) / 100);//speed - (((fov * (speed / 180)) * scale) / 100)

		SmoothAimAngles(QMyAngles, QNewAngles, QSmoothAngles, flSpeed, bSpeedSpiral, flSpeedSpiralX, flSpeedSpiralY);

		if (flAccuracy > 0)
		{
			bBlock = true;

			QAngle QAngleAccuracy = QAimAngles;

			Vector vecSpreadDir;

			if (flAccuracy == 1)//Aiming
			{
				QSmoothAngles.AngleVectors(&vecSpreadDir, NULL, NULL);

				vecSpreadDir.Normalize();
			}
			else if (flAccuracy == 2) //Recoil
			{
				Vector vecRandom, vecForward;

				SmoothAimAngles(QMyAngles, QAimAngles, QAngleAccuracy, flSpeed, bSpeedSpiral, flSpeedSpiralX, flSpeedSpiralY);

				QAngleAccuracy[0] += g_Local.vPunchangle[0];
				QAngleAccuracy[1] += g_Local.vPunchangle[1];
				QAngleAccuracy[2] = NULL;

				QAngleAccuracy.Normalize();

				QAngleAccuracy.AngleVectors(&vecForward, NULL, NULL);

				vecSpreadDir = vecForward;

				vecSpreadDir.Normalize();
			}
			else //Recoil / Spread
			{
				Vector vecRandom, vecRight, vecUp, vecForward;

				SmoothAimAngles(QMyAngles, QAimAngles, QAngleAccuracy, flSpeed, bSpeedSpiral, flSpeedSpiralX, flSpeedSpiralY);

				QAngleAccuracy[0] += g_Local.vPunchangle[0];
				QAngleAccuracy[1] += g_Local.vPunchangle[1];
				QAngleAccuracy[2] = NULL;

				QAngleAccuracy.Normalize();

				QAngleAccuracy.AngleVectors(&vecForward, &vecRight, &vecRight);

				g_NoSpread.GetSpreadXY(g_Local.weapon.random_seed, 1, vecRandom);

				vecSpreadDir = vecForward + (vecRight * vecRandom[0]) + (vecUp * vecRandom[1]);

				vecSpreadDir.Normalize();
			}

			for (unsigned int x = 0; x < Hitboxes.size(); x++)
			{
				unsigned int hitbox = Hitboxes[x];

				if (g_Utils.IsBoxIntersectingRay(g_PlayerExtraInfoList[iTarget].vHitboxMin[hitbox], g_PlayerExtraInfoList[iTarget].vHitboxMax[hitbox], g_Local.vEye, vecSpreadDir))
				{
					bBlock = false;
					break;
				}
			}
		}

		if (cmd->buttons & IN_ATTACK)
			bAttack = true;
		else if (cvar.legit[iWeaponID].aim_speed > 0)//Auto aim
		{
			bAttack = true;
			bBlock = true;
		}

		if (bAttack)
		{
			QSmoothAngles.Normalize();

			g_Utils.MakeAngle(false, QSmoothAngles, cmd);

			g_Engine.SetViewAngles(QSmoothAngles);

			if (!bBlock)
				cmd->buttons |= IN_ATTACK;
			else if (cmd->buttons & IN_ATTACK)
				cmd->buttons &= ~IN_ATTACK;

			if (!g_Local.vPunchangle.IsZero2D())
				dwBlockAttack = GetTickCount();
		}
	}
	else if (flBlockAttackAfterKill > 0 && GetTickCount() - dwBlockAttack < flBlockAttackAfterKill)
	{
		cmd->buttons &= ~IN_ATTACK;
	}
}

void CAimBot::RageAimbot(struct usercmd_s *cmd)
{
	if (!cvar.aim && !IsCurWeaponGun() || !CanAttack())
		return;

	deque<unsigned int> Hitboxes;

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
	else if (cvar.aim_hitbox == 5)//All
	{
		for (unsigned int j = 0; j <= 11; j++)
			Hitboxes.push_front(j);

		for (unsigned int k = 12; k < g_Local.iMaxHitboxes; k++)
			Hitboxes.push_back(k);
	}
	else if (cvar.aim_hitbox == 6)//Vital
	{
		for (unsigned int j = 0; j <= 11; j++)
			Hitboxes.push_front(j);
	}

	if (Hitboxes.empty())
		return;

	unsigned int m_iTarget = 0;
	int m_iHitbox = -1;
	int m_iPoint = -1;

	float m_flBestFOV = 180;
	float m_flBestDist = 8192;

	for (unsigned int id = 1; id <= g_Engine.GetMaxClients(); ++id)
	{
		if (id == g_Local.iIndex)
			continue;

		if (!g_Player[id].bAlive)
			continue;

		if (g_Player[id].bFriend)
			continue;

		if (!g_Player[id].bVisible)
			continue;

		if (!cvar.aim_teammates && g_Player[id].iTeam == g_Local.iTeam)
			continue;

		if (cvar.aim_delay_shot)
		{
			cl_entity_s *ent = g_Engine.GetEntityByIndex(id);

			if (ent && ent->curstate.frame != 0)
				continue;
		}

		for (auto &&hitbox : Hitboxes)
		{
			if (g_PlayerExtraInfoList[id].bHitboxVisible[hitbox])
			{
				m_iHitbox = hitbox;
				break;
			}
		}

		if (m_iHitbox == -1)
		{
			for (auto &&hitbox : Hitboxes)
			{
				if (cvar.aim_multi_point > 0)
				{
					if (cvar.aim_multi_point == 1 && hitbox != 11)
						continue;

					if (cvar.aim_multi_point == 2 && hitbox > 11)
						continue;

					for (unsigned int point = 0; point <= 8; ++point)
					{
						if (g_PlayerExtraInfoList[id].bHitboxPointsVisible[hitbox][point] && !g_PlayerExtraInfoList[id].bHitboxVisible[hitbox])
						{
							m_iPoint = point;
							m_iHitbox = hitbox;
							break;
						}
					}
				}
			}
		}

		if (m_iHitbox < 0 || m_iHitbox > g_Local.iMaxHitboxes)
			continue;

		if (g_Player[id].bPriority)
		{
			m_iTarget = id;
			break;
		}
		//"Field of view", "Distance", "Cycle"
		if (cvar.aim_target_selection == 1)
		{
			if (g_PlayerExtraInfoList[id].fHitboxFOV[m_iHitbox] < m_flBestFOV)
			{
				m_flBestFOV = g_PlayerExtraInfoList[id].fHitboxFOV[m_iHitbox];
				m_iTarget = id;
			}
		}
		else if (cvar.aim_target_selection == 2) 
		{
			if (g_Player[id].flDist < m_flBestDist)
			{
				m_flBestDist = g_Player[id].flDist;
				m_iTarget = id;
			}
		}
		else if (cvar.aim_target_selection == 3)
		{
			if (g_PlayerExtraInfoList[id].fHitboxFOV[m_iHitbox] < m_flBestFOV)
			{
				if (g_Player[id].flDist < m_flBestDist)
				{
					m_flBestFOV = g_PlayerExtraInfoList[id].fHitboxFOV[m_iHitbox];
					m_flBestDist = g_Player[id].flDist;
					m_iTarget = id;
				}
			}
		}
	}

	if (m_iTarget > 0)
	{
		if (cvar.quick_stop_duck)
		{
			cmd->forwardmove = 0;
			cmd->sidemove = 0;
			cmd->upmove = 0;
			cmd->buttons |= IN_DUCK;
		}
		else if (cvar.quick_stop)
		{
			cmd->forwardmove = 0;
			cmd->sidemove = 0;
			cmd->upmove = 0;
		}

		if (cvar.aim_autoscope && IsCurWeaponSniper() && g_Local.iFOV == DEFAULT_FOV)
		{
			cmd->buttons |= IN_ATTACK2;
		}
		else if (CanAttack())
		{
			QAngle QMyAngles, QAimAngles, QSmoothAngles;

			Vector vAimOrigin;

			if(m_iPoint >= 0 && m_iPoint < 8)
				vAimOrigin = g_PlayerExtraInfoList[m_iTarget].vHitboxPoints[m_iHitbox][m_iPoint];
			else
				vAimOrigin = g_PlayerExtraInfoList[m_iTarget].vHitbox[m_iHitbox];

			g_Engine.GetViewAngles(QMyAngles);

			g_Utils.VectorAngles(vAimOrigin - g_Local.vEye, QAimAngles);

			if (cvar.aim_perfect_silent)
			{
				g_Utils.MakeAngle(false, QAimAngles, cmd);
				g_Utils.bSendpacket(false);
			}
			else {
				g_Utils.MakeAngle(false, QAimAngles, cmd);

				if (!cvar.aim_silent)
					g_Engine.SetViewAngles(QAimAngles);
			}

			cmd->buttons |= IN_ATTACK;
		}
		else {
			cmd->buttons &= ~IN_ATTACK;
		}
	}
}