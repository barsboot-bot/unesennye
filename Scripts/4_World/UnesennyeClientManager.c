// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.3
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeClientManager
{
	protected static ref UnesennyeClientManager m_Instance;

	protected bool m_IsAuthorized = false;
	protected int  m_HsAttempts   = 0;
	protected ref Timer m_HsTimer;

	static UnesennyeClientManager GetInstance()
	{
		if (!m_Instance)
			m_Instance = new UnesennyeClientManager();
		return m_Instance;
	}

	void UnesennyeClientManager()
	{
		Print("[Unesennye Client] Manager created | v" + UnesennyeConstants.MOD_VERSION + " | Author: " + UnesennyeConstants.AUTHOR);
	}

	void StartHandshake()
	{
		m_IsAuthorized = false;
		m_HsAttempts   = 0;

		SendHandshakeRequest();

		m_HsTimer = new Timer(CALL_CATEGORY_SYSTEM);
		m_HsTimer.Run(UnesennyeConstants.HS_CHECK_INTERVAL / 1000.0, this, "OnHandshakeTick", null, true);
	}

	void OnHandshakeTick()
	{
		if (m_IsAuthorized)
		{
			if (m_HsTimer) m_HsTimer.Stop();
			return;
		}

		m_HsAttempts++;
		if (m_HsAttempts * UnesennyeConstants.HS_CHECK_INTERVAL >= UnesennyeConstants.HS_TIMEOUT_MS)
		{
			if (m_HsTimer) m_HsTimer.Stop();
			BlockAndDisconnect();
			return;
		}

		SendHandshakeRequest();
	}

	void SendHandshakeRequest()
	{
		GetGame().RPCSingleParam(null, UnesennyeConstants.HS_REQUEST, null, true, null);
	}

	void OnHandshakeResponse()
	{
		m_IsAuthorized = true;
		if (m_HsTimer) m_HsTimer.Stop();
		Print("[Unesennye Client] Handshake OK | Author: " + UnesennyeConstants.AUTHOR);
	}

	void BlockAndDisconnect()
	{
		m_IsAuthorized = false;
		Print("[Unesennye Client] " + UnesennyeConstants.DISCONNECT_MSG);
		GetGame().GetUIManager().ShowDialog("Unesennye", UnesennyeConstants.DISCONNECT_MSG, 0, DBT_OK, DBB_OK, DMT_EXCLAMATION, null);
		GetGame().DisconnectSessionForce();
	}

	bool IsAuthorized()
	{
		return m_IsAuthorized;
	}

	// ---- SD Card helpers ----
	void InsertSDCard(Object target, string cardClass, int playlistId)
	{
		if (!IsAuthorized()) return;
		Param2<string, int> p = new Param2<string, int>(cardClass, playlistId);
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_INSERT_CARD, p, true, null);
	}

	void EjectSDCard(Object target)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_EJECT_CARD, null, true, null);
	}

	void PlayTrack(Object target, string trackName)
	{
		if (!IsAuthorized()) return;
		Param1<string> p = new Param1<string>(trackName);
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_PLAY_TRACK, p, true, null);
	}

	void StopTrack(Object target)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_STOP_TRACK, null, true, null);
	}
};
