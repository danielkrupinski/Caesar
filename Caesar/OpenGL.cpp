#include "Required.h"

typedef void (APIENTRY *glBegin_t)(GLenum);
typedef void (APIENTRY *glVertex3fv_t)(const GLfloat *v);
typedef void (APIENTRY *glColor4f_t)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef BOOL (APIENTRY *wglSwapBuffers_t)(HDC  hdc);
typedef void (APIENTRY *glClear_t)(GLbitfield mask);
typedef void (APIENTRY *glViewport_t)(GLint x, GLint y, GLsizei width, GLsizei height);

glBegin_t pglBegin = NULL;
glVertex3fv_t pglVertex3fv = NULL;
glColor4f_t pglColor4f = NULL;
wglSwapBuffers_t pwglSwapBuffers = NULL;
glClear_t pglClear = NULL;
glViewport_t pglViewport = NULL;

bool bSmoke = false;

GLint viewport[4];

void APIENTRY Hooked_glBegin(GLenum mode)
{
	if (g_pIRunGameEngine->IsInGame() && !cvar.hide_from_obs)
	{
		if (cvar.nosmoke && mode == GL_QUADS)
		{
			GLfloat smokecol[4];

			glGetFloatv(GL_CURRENT_COLOR, smokecol);

			if ((smokecol[0] == smokecol[1]) && (smokecol[0] == smokecol[2]) && smokecol[0] != 0.0 && smokecol[0] != 1.0) 
				bSmoke = true;
			else 
				bSmoke = false;
		}
	}

	(*pglBegin)(mode);
}

void APIENTRY Hooked_glVertex3fv(GLfloat *v)
{
	if (g_pIRunGameEngine->IsInGame() && g_Local.bAlive && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot && !cvar.hide_from_obs)
	{
		if (cvar.nosmoke && bSmoke && !g_Menu.bOpened) return;
	}

	(*pglVertex3fv)(v);
}

void APIENTRY Hooked_glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	if (g_pGlobals.chams)
	{
		if (cvar.chams_type == 2) 
		{
			red = (g_pGlobals.chams_render_r / 255) * red;
			green = (g_pGlobals.chams_render_g / 255) * green;
			blue = (g_pGlobals.chams_render_b / 255) * blue;
		}
		else 
		{
			red = g_pGlobals.chams_render_r / 255;
			green = g_pGlobals.chams_render_g / 255;
			blue = g_pGlobals.chams_render_b / 255;
		}
	}

	(*pglColor4f)(red, green, blue, alpha);
}

BOOL APIENTRY Hooked_wglSwapBuffers(HDC hdc)
{
	if (cvar.hide_from_obs && GetTickCount() - g_pGlobals.dwLoadingFinished > 1000 && g_Engine.pfnGetCvarFloat("r_norefresh") == 0)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, viewport[2], viewport[3], 0, 0, 1);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		g_Visuals.Run();
		g_Menu.Run();

		g_pISurface->DrawSetTextFont(ESP);
		g_pISurface->DrawSetTextColor(0, 0, 0, 0);
		g_pISurface->DrawSetTextPos(1, 1);
		g_pISurface->DrawPrintText((wchar_t*)__func__, wcslen((wchar_t*)__func__));//Fix rendering

		g_pISurface->DrawFlushText();

		AntiScreen();

		glDisable(GL_BLEND);

		glPopMatrix();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}

	return(*pwglSwapBuffers)(hdc);
}

void APIENTRY Hooked_glClear(GLbitfield mask) 
{
	if (mask == GL_DEPTH_BUFFER_BIT)
	{
		(*pglClear)(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	(*pglClear)(mask);
}

void APIENTRY Hooked_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	viewport[0] = x;
	viewport[1] = y;
	viewport[2] = width;
	viewport[3] = height;
	(*pglViewport)(x, y, width, height);
}

void HookOpenGL()
{
	HMODULE hmOpenGL = GetModuleHandle("opengl32.dll");
	pglBegin = (glBegin_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "glBegin"), (LPBYTE)&Hooked_glBegin);
	pglColor4f = (glColor4f_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "glColor4f"), (LPBYTE)&Hooked_glColor4f);
	pglVertex3fv = (glVertex3fv_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "glVertex3fv"), (LPBYTE)&Hooked_glVertex3fv);
	pglClear = (glClear_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "glClear"), (LPBYTE)&Hooked_glClear);
	pwglSwapBuffers = (wglSwapBuffers_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "wglSwapBuffers"), (LPBYTE)&Hooked_wglSwapBuffers);
	pglViewport = (glViewport_t)DetourFunction((LPBYTE)GetProcAddress(hmOpenGL, "glViewport"), (LPBYTE)&Hooked_glViewport);
}