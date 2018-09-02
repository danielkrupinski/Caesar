class CUtils;
class CUtils
{
private:
	Vector vViewForward, vViewRight, vViewUp, vAimForward, vAimRight, vAimUp;//backup for fixmove
	float forwardmove, sidemove, upmove;//backup for fixmove
public:
	bool IsBoxIntersectingRay(const Vector& boxMin, const Vector& boxMax, const Vector& origin, const Vector& delta);

	bool IsPlayer(struct cl_entity_s *ent);
	bool IsPlayerUpdated(struct cl_entity_s *ent);

	bool IsPlayerAlive(struct cl_entity_s *ent);
	bool IsLocalAlive(struct cl_entity_s *ent);
	bool IsEntityAlive(struct cl_entity_s *ent);

	void StringReplace(char* buf, const char* search, const char* replace);

	bool bFileExists(const char *cFileName);
	char *szDirFile(const char* pszName);
	char *cIniRead(char *cFileName, char *cSection, char *cKey, char *cDef);
	void cIniWrite(char *cFileName, char *cSection, char *cKey, char *cValue);

	bool bCalcScreen(float *pflOrigin, float *pflVecScreen);
	bool bPathFree(float *pflFrom, float *pflTo);

	void MakeAngle(bool addangle, float *angles, struct usercmd_s *cmd);
	void FixMoveStart(struct usercmd_s *cmd);
	void FixMoveEnd(struct usercmd_s *cmd);
	void VectorAngles(const float *forward, float *angles);

	//bool Intersect(Vector vHitboxMin, Vector vHitboxMax, Vector vSpreadDir, float &distance);

	float Armor(float flDamage, int ArmorValue);

	void bSendpacket(bool status);

	int FireBullets(Vector start, Vector end, float flDistance, int iOriginalPenetration, int iBulletType, int iDamage, float flRangeModifier);

	void GetFirstNonSolidPoint(const Vector& inStartPos, const Vector& inEndPos, Vector& outNonSolidPoint);

	bool GetTextureInfo(CImageTexture texture, unsigned int &index, unsigned int &w, unsigned int &h);
};
extern CUtils g_Utils;

extern unsigned int Cstrike_SequenceInfo[];

void NormalizeAngles(float *angles);
bool IsFreezePeriod(void);

void native_memwrite(uintptr_t adr, uintptr_t ptr, int size);