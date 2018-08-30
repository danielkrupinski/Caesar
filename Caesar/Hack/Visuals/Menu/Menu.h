#define LIMIT_LISTBOX 48
#define LIMIT_PALETTE 48
#define LIMIT_SAVE 16

class CMenu;
class CMenu
{
private:
	bool bInitialised;
	bool IsDragging;

	unsigned int iCurrentTab;

	unsigned int MenuX;
	unsigned int MenuY;

	int CursorX;
	int CursorY;

	CImageTexture background;

	CImageTexture icon_headshot;
	CImageTexture icon_headshot_not_selected;

	CImageTexture icon_aimbot;
	CImageTexture icon_aimbot_not_selected;

	CImageTexture icon_systems;
	CImageTexture icon_systems_not_selected;

	CImageTexture icon_options;
	CImageTexture icon_options_not_selected;

	CImageTexture icon_visuals;
	CImageTexture icon_visuals_not_selected;

	CImageTexture icon_members;
	CImageTexture icon_members_not_selected;

	bool bListBoxOpened[LIMIT_LISTBOX];
	bool bPaletteOpened[LIMIT_PALETTE];

	DWORD dwCheckboxBlockedTime;
	DWORD dwPaletteBlockedTime;
	DWORD dwListBlockedTime;
	DWORD dwSliderBlockedTime;

	bool bCursorInList;
	bool bCursorInPalette;

	int iPaletteIndex;
	int iListIndex;

	void Palette(int x, int y, float &r, float &g, float &b);
	void Checkbox(int x, int y, bool &value, char *text);
	void Slider(int x, int y, float min, float max, float &value, char *text = 0, bool ThisINT = false, char *amout = 0, bool extra = false);
	void SliderInPallete(int x, int y, float min, float max, float &value, char *text = 0, bool ThisINT = false, char *amout = 0, bool extra = false);
	void ListBox(int index, int x, int y, char *name, float &value, char **text, int size, bool default = false);
	bool DrawButton(int x, int y, char *text);
	void KeyBind(int x, int y, int &key);

	void DrawBox(int x, int y, int w, int h);
	void SelectTab();
	void DrawMenuTabs();
	void Tabs();
	void Drag();
	void Init();
public:
	bool bOpened;
	bool keys[256];

	void Run();
};
extern CMenu g_Menu;