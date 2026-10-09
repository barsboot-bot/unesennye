// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeRadioCar
{
	protected Object m_Vehicle;
	protected bool m_IsPlaying;

	void UnesennyeRadioCar(Object vehicle)
	{
		m_Vehicle = vehicle;
		m_IsPlaying = false;
	}

	void Play(string soundSet)
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
			return;

		Param1<string> p = new Param1<string>(soundSet);
		GetGame().RPCSingleParam(m_Vehicle, UnesennyeConstants.RADIO_PLAY, p, true, null);
		m_IsPlaying = true;
	}

	void Stop()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
			return;

		GetGame().RPCSingleParam(m_Vehicle, UnesennyeConstants.RADIO_STOP, null, true, null);
		m_IsPlaying = false;
	}

	bool IsPlaying()
	{
		return m_IsPlaying;
	}
};
