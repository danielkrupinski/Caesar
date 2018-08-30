class CNoFlash;
class CNoFlash
{
public:
	float Flashed;
	float FadeEnd;

	screenfade_t* pScreenFade;

	void Redraw();
};
extern CNoFlash g_NoFlash;