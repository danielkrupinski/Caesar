#include "../../../Required.h"

CNoFlash g_NoFlash;

void CNoFlash::Redraw()
{
	if (cvar.noflash > 0)
	{
		if (g_NoFlash.pScreenFade->fadeEnd > g_Engine.GetClientTime())
		{
			g_NoFlash.FadeEnd = g_NoFlash.pScreenFade->fadeEnd;

			if ((int)cvar.noflash >= 255.0f)	
				g_NoFlash.pScreenFade->fadeEnd = 0.0f;
			else if (g_NoFlash.pScreenFade->fadealpha > (int)cvar.noflash) 
				g_NoFlash.pScreenFade->fadealpha = (int)cvar.noflash;
		}

		if (g_NoFlash.FadeEnd > g_Engine.GetClientTime())
			g_NoFlash.Flashed = (g_NoFlash.FadeEnd - g_Engine.GetClientTime()) * g_NoFlash.pScreenFade->fadeSpeed;
		else 
			g_NoFlash.Flashed = 0.0f;

		if (g_NoFlash.Flashed > 255.0f) g_NoFlash.Flashed = 255.0f;

		if (g_NoFlash.Flashed < 0.0f) g_NoFlash.Flashed = 0.0f;

		float Percentage = (g_NoFlash.Flashed / 255.0f) * 100.0f;

		if (Percentage > 0.0f)
			g_Drawing.DrawString(ESP, g_Screen.iWidth / 2, g_Screen.iHeight / 1.7, 255, 255, 255, 200, FONT_CENTER, "Flashed: %.0f", Percentage);
	}
}