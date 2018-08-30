#include "../../Required.h"

CSystems g_Systems;

void ComputeMove(int id, float forwardmove, float sidemove)
{
	Vector vecVelocity = g_Player[id].vVelocity;

	float wtf_const = 33.4;

	float flSpeed = vecVelocity.Length2D() * wtf_const;

	cl_entity_s *ent = g_Engine.GetEntityByIndex(id);

	if (flSpeed > 0 && ent)
	{
		QAngle QAngles = ent->angles;

		Vector vecVelocityRotated;
		vecVelocityRotated.VectorRotate(vecVelocity, QAngles);

		forwardmove = vecVelocityRotated[0] * wtf_const;
		sidemove = -1 * vecVelocityRotated[1] * wtf_const;

		if (forwardmove > 250)
			forwardmove = 250;
		
		if (sidemove > 250)
			sidemove = 250;
	}
	else {
		forwardmove = 0;
		sidemove = 0;
	}
}

void CSystems::KnifeBot(struct usercmd_s *cmd)
{
	if (IsCurWeaponKnife() && CanAttack() && cvar.knifebot)
	{
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

			if (!g_Player[i].bVisible)
				continue;

			if (g_Player[i].iTeam == g_Local.iTeam)
				continue;

			if (g_Player[i].flDist < flDist || id == NULL)
			{
				flDist = g_Player[i].flDist;
				id = i;
			}
		}

		if(id > 0)
		{
			cl_entity_s *ent = g_Engine.GetEntityByIndex(id);

			if (!ent) 
				return;

			int fDidHit = FALSE;

			Vector vecPlayerOrigin = ent->origin + g_Player[id].vVelocity * g_Player[id].flFrametime;

			if (vecPlayerOrigin.Distance(pmove->origin) < 64)
			{
				// hit
				fDidHit = TRUE;

				float flDamage = 65.0f;

				Vector vecForwardPlayer, vecForward;

				Vector vecSrc = g_Local.vEye;

				QAngle QAimAngle;

				g_Utils.VectorAngles(vecPlayerOrigin - vecSrc, QAimAngle);

				QAimAngle.Normalize();

				g_Engine.pfnAngleVectors(QAimAngle, vecForward, 0, 0);
				g_Engine.pfnAngleVectors(ent->angles, vecForwardPlayer, 0, 0);

				vecForwardPlayer.Normalize();
				vecForward.Normalize();

				float flDot = vecForward.Dot2D(vecForwardPlayer);

				//Triple the damage if we are stabbing them in the back.
				if (flDot > 0.80f)
				{
					flDamage *= 3.0f;
				}

				if (fDidHit) 
				{
					g_Utils.MakeAngle(false, QAimAngle, cmd);

					cmd->buttons |= IN_ATTACK2;
				}
			}
		}
	}
}

void CSystems::BunnyHop(struct usercmd_s *cmd)
{
	if (cvar.bunnyhop)
	{
		if (cmd->buttons&IN_JUMP)
		{
			cmd->buttons &= ~IN_JUMP;

			if (pmove->flags & FL_ONGROUND || pmove->waterlevel >= 2)
			{
				cmd->buttons |= IN_JUMP;
			}
		}
	}
}

void CSystems::AutoStrafe(struct usercmd_s *cmd)
{
	

	/*cmd->buttons &= ~(IN_MOVELEFT | IN_MOVERIGHT | IN_FORWARD | IN_BACK);

	if (cmd->sidemove < 0.f)
		cmd->buttons |= IN_MOVELEFT;
	else
		cmd->buttons |= IN_MOVERIGHT;

	if (cmd->forwardmove < 0.f)
		cmd->buttons |= IN_BACK;
	else
		cmd->buttons |= IN_FORWARD;*/
}