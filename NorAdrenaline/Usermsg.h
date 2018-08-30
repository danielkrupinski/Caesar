int ResetHUD(const char *pszName, int iSize, void *pbuf);
int Battery(const char *pszName, int iSize, void *pbuf);
int BombDrop(const char *pszName, int iSize, void *pbuf);
int Health(const char *pszName, int iSize, void *pbuf);
int DeathMsg(const char *pszName, int iSize, void *pbuf);
int SetFOV(const char *pszName, int iSize, void *pbuf);
int TeamInfo(const char *pszName, int iSize, void *pbuf);
int ScoreAttrib(const char *pszName, int iSize, void *pbuf);

extern pfnUserMsgHook pResetHUD;
extern pfnUserMsgHook pBombDrop;
extern pfnUserMsgHook pBattery;
extern pfnUserMsgHook pHealth;
extern pfnUserMsgHook pDeathMsg;
extern pfnUserMsgHook pSetFOV;
extern pfnUserMsgHook pTeamInfo;
extern pfnUserMsgHook pScoreAttrib;