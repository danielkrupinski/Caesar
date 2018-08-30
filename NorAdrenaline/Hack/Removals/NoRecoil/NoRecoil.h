class CNoRecoil;
class CNoRecoil
{
public:
	void V_CalcRefdef(struct ref_params_s *pparams);
	void CL_CreateMove(struct usercmd_s *cmd);
	void DrawRecoil();
};
extern CNoRecoil g_NoRecoil;