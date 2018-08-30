#include "Required.h"

// This pointer to CStudioModelRenderer class !
StudioModelRenderer_d pThis;

//=========================
// StudioDrawModel
//=========================
int StudioDrawModel(int flags)
{
	return oStudioDrawModel(flags);
}

//=========================
// StudioDrawPlayer
//=========================
int StudioDrawPlayer(int flags, struct entity_state_s *pplayer)
{
	return oStudioDrawPlayer(flags, pplayer);
}

//=========================
// StudioGetAnim
// Look up animation data for sequence
//=========================
mstudioanim_t StudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc)
{
	return oStudioGetAnim(m_pSubModel, pseqdesc);
}

//=========================
// StudioSetUpTransform
// Interpolate model position and angles and set up matrices
//=========================
void StudioSetUpTransform(int trivial_accept)
{
	oStudioSetUpTransform(trivial_accept);
}

//=========================
// StudioSetupBones
// Set up model bone positions
//=========================
void StudioSetupBones(void)
{
	oStudioSetupBones();
}

//=========================
// StudioCalcAttachments
// Find final attachment points
//=========================
void StudioCalcAttachments(void)
{
	oStudioCalcAttachments();
}

//=========================
// StudioSaveBones
// Save bone matrices and names
//=========================
void StudioSaveBones(void)
{
	oStudioSaveBones();
}

//=========================
// StudioMergeBones
// Merge cached bones with current bones for model
//=========================
void StudioMergeBones(model_t *m_pSubModel)
{
	oStudioMergeBones(m_pSubModel);
}

//=========================
// StudioEstimateInterpolant
// Determine interpolation fraction
//=========================
float StudioEstimateInterpolant(void)
{
	return oStudioEstimateInterpolant();
}

//=========================
// StudioEstimateFrame
// Determine current frame for rendering
//=========================
float StudioEstimateFrame(mstudioseqdesc_t *pseqdesc)
{
	return oStudioEstimateFrame(pseqdesc);
}

//=========================
// StudioFxTransform
// Apply special effects to transform matrix
//=========================
void StudioFxTransform(cl_entity_t *ent, float transform[3][4])
{
	oStudioFxTransform(ent, transform);
}

//=========================
// StudioSlerpBones
// Spherical interpolation of bones
//=========================
void StudioSlerpBones(vec4_t q1[], float pos1[][3], vec4_t q2[], float pos2[][3], float s)
{
	oStudioSlerpBones(q1, pos1, q2, pos2, s);
}

//=========================
// StudioCalcBoneAdj
// Compute bone adjustments ( bone controllers )
//=========================
void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen)
{
	oStudioCalcBoneAdj(dadt, adj, pcontroller1, pcontroller2, mouthopen);
}

//=========================
// StudioCalcBoneQuaterion
// Get bone quaternions
//=========================
void StudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q)
{
	oStudioCalcBoneQuaterion(frame, s, pbone, panim, adj, q);
}

//=========================
// StudioCalcBonePosition
// Get bone positions
//=========================
void StudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos)
{
	oStudioCalcBonePosition(frame, s, pbone, panim, adj, pos);
}

//=========================
// StudioCalcRotations
// Compute rotations
//=========================
void StudioCalcRotations(float pos[][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f)
{
	oStudioCalcRotations(pos, q, pseqdesc, panim, f);
}

//=========================
// StudioRenderModel
// Send bones and verts to renderer
//=========================
void StudioRenderModel(void)
{
	cl_entity_s* ent = g_Studio.GetCurrentEntity();

	if (!cvar.hide_from_obs && cvar.esp && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot)
	{
		if (g_Utils.IsPlayer(ent) && ent->index != g_Local.iIndex)
		{
			if (cvar.disable_render_teammates && g_Player[ent->index].iTeam == g_Local.iTeam) 
				return;

			if (!cvar.esp_teammates && g_Player[ent->index].iTeam == g_Local.iTeam)
			{
				oStudioRenderModel();
				g_pGlobals.chams = false;
				return;
			}

			if (cvar.glow_players)
			{
				glDepthFunc(GL_GREATER);
				glDisable(GL_DEPTH_TEST);
				g_pStudio->SetForceFaceFlags(STUDIO_NF_CHROME);
				ent->curstate.renderfx = kRenderFxGlowShell;
				ent->curstate.renderamt = 12;
				ent->curstate.rendermode = 0;

				if (g_Player[ent->index].iTeam == TERRORIST)
				{
					ent->curstate.rendercolor.r = cvar.glow_players_t_r;
					ent->curstate.rendercolor.g = cvar.glow_players_t_g;
					ent->curstate.rendercolor.b = cvar.glow_players_t_b;
				}
				else if (g_Player[ent->index].iTeam == CT)
				{
					ent->curstate.rendercolor.r = cvar.glow_players_ct_r;
					ent->curstate.rendercolor.g = cvar.glow_players_ct_g;
					ent->curstate.rendercolor.b = cvar.glow_players_ct_b;
				}

				oStudioRenderFinal();
				glEnable(GL_DEPTH_TEST);

				if (!cvar.chams)
				{
					glDisable(GL_DEPTH_TEST);
					g_pStudio->SetForceFaceFlags(0);
					ent->curstate.renderfx = 0;
					oStudioRenderFinal();
					glEnable(GL_DEPTH_TEST);

					glDepthFunc(GL_LESS);
					oStudioRenderFinal();
				}
			}

			if (cvar.chams) 
			{
				g_pGlobals.chams = true;

				ent->curstate.rendermode = 0;
				ent->curstate.renderfx = 0;
				ent->curstate.renderamt = 0;
				g_pStudio->SetForceFaceFlags(0);

				if (cvar.chams_type != 3)
					glDisable(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, 0);

				ent->curstate.rendermode = 0;
				ent->curstate.renderfx = 0;
				ent->curstate.renderamt = 0;
				g_pStudio->SetForceFaceFlags(0);

				if (cvar.chams_behind_wall) {
					glDepthFunc(GL_GREATER);
					glDisable(GL_DEPTH_TEST);

					if (g_Player[ent->index].iTeam == TERRORIST) {
						g_pGlobals.chams_render_r = cvar.chams_t_invis_r;
						g_pGlobals.chams_render_g = cvar.chams_t_invis_g;
						g_pGlobals.chams_render_b = cvar.chams_t_invis_b;
					}
					else if (g_Player[ent->index].iTeam == CT) {
						g_pGlobals.chams_render_r = cvar.chams_ct_invis_r;
						g_pGlobals.chams_render_g = cvar.chams_ct_invis_g;
						g_pGlobals.chams_render_b = cvar.chams_ct_invis_b;
					}
					else {
						g_pGlobals.chams_render_r = 255;
						g_pGlobals.chams_render_g = 255;
						g_pGlobals.chams_render_b = 255;
					}

					oStudioRenderFinal();
				}

				//g_Engine.Con_Printf("1: %i %i %i\n", g_pGlobals.chams_color.r, g_pGlobals.chams_color.g);

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);

				if (g_Player[ent->index].iTeam == TERRORIST) {
					g_pGlobals.chams_render_r = cvar.chams_t_vis_r;
					g_pGlobals.chams_render_g = cvar.chams_t_vis_g;
					g_pGlobals.chams_render_b = cvar.chams_t_vis_b;
				}
				else if (g_Player[ent->index].iTeam == CT) {
					g_pGlobals.chams_render_r = cvar.chams_ct_vis_r;
					g_pGlobals.chams_render_g = cvar.chams_ct_vis_g;
					g_pGlobals.chams_render_b = cvar.chams_ct_vis_b;
				}
				else {
					g_pGlobals.chams_render_r = 255;
					g_pGlobals.chams_render_g = 255;
					g_pGlobals.chams_render_b = 255;
				}

				//g_Engine.Con_Printf("2: %i %i %i\n", g_pGlobals.chams_color.r, g_pGlobals.chams_color.g);

				oStudioRenderFinal();

				if (cvar.chams != 3)
					glEnable(GL_TEXTURE_2D);
			}
			else oStudioRenderModel();
		}
		else oStudioRenderModel();
	}
	else oStudioRenderModel();

	g_pGlobals.chams = false;
}

//=========================
// StudioRenderFinal
// Finalize rendering
//=========================
void StudioRenderFinal(void)
{
	oStudioRenderFinal();
}

//=========================
// StudioRenderFinal_Software
// Software renderer finishing function
//=========================
void StudioRenderFinal_Software(void)
{
	oStudioRenderFinal_Software();
}

//=========================
// StudioRenderFinal_Hardware
// GL&D3D renderer finishing function
//=========================
void StudioRenderFinal_Hardware(void)
{
	oStudioRenderFinal_Hardware();
}

//=========================
// StudioPlayerBlend
// Determine pitch and blending amounts for players
//=========================
void StudioPlayerBlend(mstudioseqdesc_t *pseqdesc, int *pBlend, float *pPitch)
{
	oStudioPlayerBlend(pseqdesc, pBlend, pPitch);
}

//=========================
// StudioEstimateGait
// Estimate gait frame for player
//=========================
void StudioEstimateGait(entity_state_t *pplayer)
{
	oStudioEstimateGait(pplayer);
}

//=========================
// StudioProcessGait
// Process movement of player
//=========================
void StudioProcessGait(entity_state_t *pplayer)
{
	oStudioProcessGait(pplayer);
}

//===================================================================================
// Callgates & Patchgates
//===================================================================================
void __declspec(naked) oStudioRenderModel(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioRenderModel;
	}
}
void __declspec(naked)StudioRenderModel_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderModel
	}
}

int __declspec(naked) oStudioDrawModel(int flags)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioDrawModel;
	}
}
void __declspec(naked) StudioDrawModel_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioDrawModel
	}
}

int __declspec(naked) oStudioDrawPlayer(int flags, struct entity_state_s *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioDrawPlayer;
	}
}
void __declspec(naked) StudioDrawPlayer_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioDrawPlayer
	}
}

mstudioanim_t __declspec(naked) oStudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioGetAnim;
	}
}
void __declspec(naked) StudioGetAnim_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioGetAnim
	}
}

void __declspec(naked) oStudioSetUpTransform(int trivial_accept)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioSetUpTransform;
	}
}
void __declspec(naked) StudioSetUpTransform_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSetUpTransform
	}
}

void __declspec(naked) oStudioSetupBones(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioSetupBones;
	}
}
void __declspec(naked) StudioSetupBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSetupBones
	}
}

void __declspec(naked) oStudioCalcAttachments(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioCalcAttachments;
	}
}
void __declspec(naked) StudioCalcAttachments_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcAttachments
	}
}

void __declspec(naked) oStudioSaveBones(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioSaveBones;
	}
}
void __declspec(naked) StudioSaveBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSaveBones
	}
}

void __declspec(naked) oStudioMergeBones(model_t *m_pSubModel)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioMergeBones;
	}
}
void __declspec(naked) StudioMergeBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioMergeBones
	}
}

float __declspec(naked) oStudioEstimateInterpolant(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioEstimateInterpolant;
	}
}
void __declspec(naked) StudioEstimateInterpolant_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateInterpolant
	}
}

float __declspec(naked) oStudioEstimateFrame(mstudioseqdesc_t *pseqdesc)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioEstimateFrame;
	}
}
void __declspec(naked) StudioEstimateFrame_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateFrame
	}
}

void __declspec(naked) oStudioFxTransform(cl_entity_t *ent, float transform[3][4])
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioFxTransform;
	}
}
void __declspec(naked) StudioFxTransforme_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioFxTransform
	}
}

void __declspec(naked) oStudioSlerpBones(vec4_t q1[], float pos1[][3], vec4_t q2[], float pos2[][3], float s)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioSlerpBones;
	}
}
void __declspec(naked) StudioSlerpBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSlerpBones
	}
}

void __declspec(naked) oStudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioCalcBoneAdj;
	}
}
void __declspec(naked) StudioCalcBoneAdj_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBoneAdj
	}
}

void __declspec(naked) oStudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioCalcBoneQuaterion;
	}
}
void __declspec(naked) StudioCalcBoneQuaterion_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBoneQuaterion
	}
}

void __declspec(naked) oStudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioCalcBonePosition;
	}
}
void __declspec(naked) StudioCalcBonePosition_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBonePosition
	}
}

void __declspec(naked) oStudioCalcRotations(float pos[][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioCalcRotations;
	}
}
void __declspec(naked) StudioCalcRotations_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcRotations
	}
}

void __declspec(naked) oStudioRenderFinal(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioRenderFinal;
	}
}
void __declspec(naked) StudioRenderFinal_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal
	}
}

void __declspec(naked) oStudioRenderFinal_Software(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioRenderFinal_Software;
	}
}
void __declspec(naked) StudioRenderFinal_Software_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal_Software
	}
}

void __declspec(naked) oStudioRenderFinal_Hardware(void)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioRenderFinal_Hardware;
	}
}
void __declspec(naked) StudioRenderFinal_Hardware_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal_Hardware
	}
}

void __declspec(naked) oStudioPlayerBlend(mstudioseqdesc_t *pseqdesc, int *pBlend, float *pPitch)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioPlayerBlend;
	}
}
void __declspec(naked) StudioPlayerBlend_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioPlayerBlend
	}
}

void __declspec(naked) oStudioEstimateGait(entity_state_t *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioEstimateGait;
	}
}
void __declspec(naked) StudioEstimateGait_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateGait
	}
}

void __declspec(naked) oStudioProcessGait(entity_state_t *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp g_StudioModelRenderer.StudioProcessGait;
	}
}
void __declspec(naked) StudioProcessGait_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioProcessGait
	}
}