#include "../../../Required.h"

deque<my_sound_t> mySounds;

void ShotsFiredCounter(int entid, char *szSoundFile)
{
	static unsigned int iBackWeapons[MAX_CLIENTS + 1] = {};

	if (strstr(szSoundFile, "weapons"))
	{
		if (strstr(szSoundFile, "ak47-1") || strstr(szSoundFile, "ak47-2"))
		{
			if (iBackWeapons[entid] != WEAPON_AK47) 
			{
				iBackWeapons[entid] = WEAPON_AK47;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;

			if (g_Player[entid].iShotsFired > AK47_MAX_CLIP) 
				g_Player[entid].iShotsFired -= AK47_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "aug-1"))
		{
			if (iBackWeapons[entid] != WEAPON_AUG)
			{
				iBackWeapons[entid] = WEAPON_AUG;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;

			if (g_Player[entid].iShotsFired > AUG_MAX_CLIP) 
				g_Player[entid].iShotsFired -= AUG_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "awp1"))
		{
			if (iBackWeapons[entid] != WEAPON_AWP)
			{
				iBackWeapons[entid] = WEAPON_AWP;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > AWP_MAX_CLIP) 
				g_Player[entid].iShotsFired -= AWP_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "deagle-1") || strstr(szSoundFile, "deagle-2"))
		{
			if (iBackWeapons[entid] != WEAPON_DEAGLE)
			{
				iBackWeapons[entid] = WEAPON_DEAGLE;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > DEAGLE_MAX_CLIP) 
				g_Player[entid].iShotsFired -= DEAGLE_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "elite_fire"))
		{
			if (iBackWeapons[entid] != WEAPON_ELITE)
			{
				iBackWeapons[entid] = WEAPON_ELITE;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > ELITE_MAX_CLIP) 
				g_Player[entid].iShotsFired -= ELITE_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "famas-1") || strstr(szSoundFile, "famas-2"))
		{
			if (iBackWeapons[entid] != WEAPON_FAMAS)
			{
				iBackWeapons[entid] = WEAPON_FAMAS;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > FAMAS_MAX_CLIP) 
				g_Player[entid].iShotsFired -= FAMAS_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "fiveseven-1"))
		{
			if (iBackWeapons[entid] != WEAPON_FIVESEVEN)
			{
				iBackWeapons[entid] = WEAPON_FIVESEVEN;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > FIVESEVEN_MAX_CLIP)
				g_Player[entid].iShotsFired -= FIVESEVEN_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "g3gs1-1"))
		{
			if (iBackWeapons[entid] != WEAPON_G3SG1)
			{
				iBackWeapons[entid] = WEAPON_G3SG1;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > G3SG1_MAX_CLIP)
				g_Player[entid].iShotsFired -= G3SG1_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "galil-1") || strstr(szSoundFile, "galil-2"))
		{
			if (iBackWeapons[entid] != WEAPON_GALIL)
			{
				iBackWeapons[entid] = WEAPON_GALIL;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > GALIL_MAX_CLIP)
				g_Player[entid].iShotsFired -= GALIL_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "glock18-1") || strstr(szSoundFile, "glock18-2"))
		{
			if (iBackWeapons[entid] != WEAPON_GLOCK18)
			{
				iBackWeapons[entid] = WEAPON_GLOCK18;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > GLOCK18_MAX_CLIP)
				g_Player[entid].iShotsFired -= GLOCK18_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "m3-1"))
		{
			if (iBackWeapons[entid] != WEAPON_M3)
			{
				iBackWeapons[entid] = WEAPON_M3;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > M3_MAX_CLIP) 
				g_Player[entid].iShotsFired -= M3_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "m4a1_unsil-1") || strstr(szSoundFile, "m4a1_unsil-2") || strstr(szSoundFile, "m4a1-2"))
		{
			if (iBackWeapons[entid] != WEAPON_M4A1)
			{
				iBackWeapons[entid] = WEAPON_M4A1;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > M4A1_MAX_CLIP)
				g_Player[entid].iShotsFired -= M4A1_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "m249-1") || strstr(szSoundFile, "m249-2"))
		{
			if (iBackWeapons[entid] != WEAPON_M249)
			{
				iBackWeapons[entid] = WEAPON_M249;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > M249_MAX_CLIP) 
				g_Player[entid].iShotsFired -= M249_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "mac10-1"))
		{
			if (iBackWeapons[entid] != WEAPON_MAC10)
			{
				iBackWeapons[entid] = WEAPON_MAC10;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > MAC10_MAX_CLIP)
				g_Player[entid].iShotsFired -= MAC10_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "mp5-1") || strstr(szSoundFile, "mp5-2"))
		{
			if (iBackWeapons[entid] != WEAPON_MP5N)
			{
				iBackWeapons[entid] = WEAPON_MP5N;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > MP5N_MAX_CLIP) 
				g_Player[entid].iShotsFired -= MP5N_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "p90-1"))
		{
			if (iBackWeapons[entid] != WEAPON_P90)
			{
				iBackWeapons[entid] = WEAPON_P90;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > P90_MAX_CLIP)
				g_Player[entid].iShotsFired -= P90_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "p228-1"))
		{
			if (iBackWeapons[entid] != WEAPON_P228)
			{
				iBackWeapons[entid] = WEAPON_P228;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > P228_MAX_CLIP)
				g_Player[entid].iShotsFired -= P228_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "scout_fire-1"))
		{
			if (iBackWeapons[entid] != WEAPON_SCOUT)
			{
				iBackWeapons[entid] = WEAPON_SCOUT;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > SCOUT_MAX_CLIP)
				g_Player[entid].iShotsFired -= SCOUT_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "sg550-1"))
		{
			if (iBackWeapons[entid] != WEAPON_SG550)
			{
				iBackWeapons[entid] = WEAPON_SG550;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > SG550_MAX_CLIP)
				g_Player[entid].iShotsFired -= SG550_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "sg552-1") || strstr(szSoundFile, "sg552-2"))
		{
			if (iBackWeapons[entid] != WEAPON_SG552)
			{
				iBackWeapons[entid] = WEAPON_SG552;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > SG552_MAX_CLIP)
				g_Player[entid].iShotsFired -= SG552_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "tmp-1") || strstr(szSoundFile, "tmp-2"))
		{
			if (iBackWeapons[entid] != WEAPON_TMP)
			{
				iBackWeapons[entid] = WEAPON_TMP;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > TMP_MAX_CLIP)
				g_Player[entid].iShotsFired -= TMP_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "ump45-1"))
		{
			if (iBackWeapons[entid] != WEAPON_UMP45)
			{
				iBackWeapons[entid] = WEAPON_UMP45;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > UMP45_MAX_CLIP)
				g_Player[entid].iShotsFired -= UMP45_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "usp_unsil-1") || strstr(szSoundFile, "usp1") || strstr(szSoundFile, "usp2"))
		{
			if (iBackWeapons[entid] != WEAPON_USP)
			{
				iBackWeapons[entid] = WEAPON_USP;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > USP_MAX_CLIP)
				g_Player[entid].iShotsFired -= USP_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "xm1014-1"))
		{
			if (iBackWeapons[entid] != WEAPON_XM1014)
			{
				iBackWeapons[entid] = WEAPON_XM1014;
				g_Player[entid].iShotsFired = 0;
			}

			g_Player[entid].iShotsFired++;
			if (g_Player[entid].iShotsFired > XM1014_MAX_CLIP)
				g_Player[entid].iShotsFired -= XM1014_MAX_CLIP;
		}
		else if (strstr(szSoundFile, "reload")) 
		{
			g_Player[entid].iShotsFired = 0;
		}

		if (g_Player[entid].iShotsFired < 0)
			g_Player[entid].iShotsFired = 0;
	}
}

void PreS_DynamicSound(int entid, DWORD entchannel, char *szSoundFile, float *fOrigin, float fVolume, float fAttenuation, int iTimeOff, int iPitch) 
{
	cl_entity_s *ent = g_Engine.GetEntityByIndex(entid);

	if (ent && !ent->curstate.origin.IsZero() && (ent->curstate.origin[0] != fOrigin[0] || ent->curstate.origin[1] != fOrigin[1] || ent->curstate.origin[2] != fOrigin[2]))
	{
		//g_Engine.Con_Printf("%f %f %f | %f %f %f\n", fOrigin[0], fOrigin[1], fOrigin[2], ent->curstate.origin[0], ent->curstate.origin[1], ent->curstate.origin[2]);
		fOrigin = ent->curstate.origin;
	}

	if (g_pIRunGameEngine->IsInGame() && fVolume >= cvar.esp_sound_minimum_volume)
	{
		if (entid > 0 && entid <= g_Engine.GetMaxClients() && entid != g_Local.iIndex)
		{
			ShotsFiredCounter(entid, szSoundFile);

			if (strstr(szSoundFile, "player")) 
			{
				if (strstr(szSoundFile, "bhit_helmet")) 
				{
					g_Player[entid].iArmorType = ARMOR_VESTHELM;
					g_Player[entid].iHealth -= 80;
				}
				else if (strstr(szSoundFile, "bhit_kevlar")) 
				{
					g_Player[entid].iArmorType = ARMOR_KEVLAR;
					g_Player[entid].iHealth -= 20;
				}
				else if (strstr(szSoundFile, "bhit_flesh"))
				{
					g_Player[entid].iArmorType = ARMOR_NONE;
					g_Player[entid].iHealth -= 30;
				}
				else if (strstr(szSoundFile, "headshot")) 
				{
					g_Player[entid].iHealth -= 80;
				}
				else if (strstr(szSoundFile, "die") || strstr(szSoundFile, "death"))
				{
					g_Player[entid].iHealth = 0;
					g_Player[entid].iArmorType = ARMOR_NONE;
				}

				if (g_Player[entid].iHealth < 0)
				{
					g_Player[entid].iHealth = 0;
					g_Player[entid].iArmorType = ARMOR_NONE;
				}
			}
		}

		my_sound_t sound;
		sound.origin = fOrigin;
		sound.name = szSoundFile;
		sound.timestamp = GetTickCount();
		sound.id = entid;
		mySounds.push_back(sound);
	}

	PreS_DynamicSound_s(entid, entchannel, szSoundFile, fOrigin, fVolume, fAttenuation, iTimeOff, iPitch);
}