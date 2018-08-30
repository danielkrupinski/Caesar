class CAimBot;
class CAimBot
{
public:
	void Trigger(struct usercmd_s *cmd);
	void Run(struct usercmd_s *cmd);

	DWORD dwReactionTime;

	float m_flCurrentFOV;

	bool TriggerKeyStatus;
private:
	void LegitAimbot(struct usercmd_s *cmd);
	void RageAimbot(struct usercmd_s *cmd);
};
extern CAimBot g_AimBot;

void SmoothAimAngles(QAngle MyViewAngles, QAngle AimAngles, QAngle &OutAngles, float Smoothing, bool bSpiral, float SpiralX, float SpiralY);