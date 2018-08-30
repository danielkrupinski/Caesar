class CMisc;
class CMisc
{
public:
	bool FakeEdge(float &angle);
	void FakeLag(struct usercmd_s *cmd);
	void AutoPistol(struct usercmd_s *cmd);
	void AutoReload(struct usercmd_s *cmd);
	void AntiAim(struct usercmd_s *cmd);
	void ThirdPerson(struct ref_params_s *pparams);
	void FastZoom(struct usercmd_s *cmd);
	void NameStealer();
};
extern CMisc g_Misc;