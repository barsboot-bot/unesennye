// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.3
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeWalkie
{
	protected Object m_Radio;

	void UnesennyeWalkie(Object radio)
	{
		m_Radio = radio;
	}

	void InsertCard(string cardClass, int playlistId)
	{
		UnesennyeClientManager.GetInstance().InsertSDCard(m_Radio, cardClass, playlistId);
	}

	void EjectCard()
	{
		UnesennyeClientManager.GetInstance().EjectSDCard(m_Radio);
	}

	void PlayTrack(string track)
	{
		UnesennyeClientManager.GetInstance().PlayTrack(m_Radio, track);
	}

	void StopTrack()
	{
		UnesennyeClientManager.GetInstance().StopTrack(m_Radio);
	}
};
