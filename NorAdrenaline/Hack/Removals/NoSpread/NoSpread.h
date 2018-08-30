class CNoSpread;
class CNoSpread
{
public:
	void GetSpreadXY(unsigned int seed, int future, float *vec, bool simulate = false);
	void GetSpreadOffset(unsigned int seed, int future, float *inangles, float *outangles);
	void V_CalcRefdef(struct ref_params_s *pparams);
	void CL_CreateMove(usercmd_s *cmd);
	void DrawSpread();
};
extern CNoSpread g_NoSpread;