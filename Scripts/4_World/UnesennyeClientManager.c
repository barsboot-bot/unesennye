// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeClientManager
{
	protected static ref UnesennyeClientManager m_Instance;

	protected bool m_IsAuthorized = false;
	protected int  m_HsAttempts   = 0;
	protected EffectSound m_CurrentSound;

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
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(OnHandshakeTick, UnesennyeConstants.HS_CHECK_INTERVAL, true);
	}

	void OnHandshakeTick()
	{
		if (m_IsAuthorized)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OnHandshakeTick);
			return;
		}

		m_HsAttempts++;
		if (m_HsAttempts * UnesennyeConstants.HS_CHECK_INTERVAL >= UnesennyeConstants.HS_TIMEOUT_MS)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OnHandshakeTick);
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
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OnHandshakeTick);
		Print("[Unesennye Client] Handshake OK | Author: " + UnesennyeConstants.AUTHOR);
	}

	void BlockAndDisconnect()
	{
		m_IsAuthorized = false;
		Print("[Unesennye Client] " + UnesennyeConstants.DISCONNECT_MSG);
		// Show message first, disconnect after short delay
		GetGame().GetUIManager().ShowDialog("Unesennye", UnesennyeConstants.DISCONNECT_MSG, 0, DBT_OK, DBB_OK, DMT_EXCLAMATION, null);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DoForceDisconnect, 1500, false);
	}

	void DoForceDisconnect()
	{
		GetGame().DisconnectSessionForce();
	}

	bool IsAuthorized()
	{
		return m_IsAuthorized;
	}

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

	// ---- Local sound playback ----
	void PlaySoundSet(string soundSetName)
	{
		StopSound();
		if (soundSetName == "")
			return;

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return;

		m_CurrentSound = SEffectManager.PlaySound(soundSetName, player.GetPosition());
		if (m_CurrentSound)
		{
			m_CurrentSound.SetSoundAutodestroy(true);
			Print("[Unesennye Client] Playing SoundSet: " + soundSetName);
		}
		else
		{
			Print("[Unesennye Client] Failed to play SoundSet: " + soundSetName + " (missing in music_db?)");
		}
	}

	void StopSound()
	{
		if (m_CurrentSound)
		{
			m_CurrentSound.SoundStop();
			m_CurrentSound = null;
		}
	}
};
