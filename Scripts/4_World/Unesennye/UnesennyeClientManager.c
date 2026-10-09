// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
class UnesennyeClientManager
{
	protected static ref UnesennyeClientManager m_Instance;
	protected bool m_IsAuthorized;
	protected int m_HsAttempts;
	protected EffectSound m_CurrentSound;
	protected vector m_SoundPos;

	static UnesennyeClientManager GetInstance()
	{
		if (!m_Instance) m_Instance = new UnesennyeClientManager();
		return m_Instance;
	}

	void StartHandshake()
	{
		m_IsAuthorized = false;
		m_HsAttempts = 0;
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

	void SendHandshakeRequest() { GetGame().RPCSingleParam(null, UnesennyeConstants.HS_REQUEST, null, true, null); }

	void OnHandshakeResponse()
	{
		m_IsAuthorized = true;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OnHandshakeTick);
		Print("[Unesennye Client] Handshake OK");
	}

	void BlockAndDisconnect()
	{
		m_IsAuthorized = false;
		GetGame().GetUIManager().ShowDialog("Unesennye", UnesennyeConstants.DISCONNECT_MSG, 0, DBT_OK, DBB_OK, DMT_EXCLAMATION, null);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DoForceDisconnect, 1500, false);
	}

	void DoForceDisconnect() { GetGame().DisconnectSessionForce(); }
	bool IsAuthorized() { return m_IsAuthorized; }

	void InsertSDCard(Object target, string cardClass, int playlistId)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_INSERT_CARD, new Param2<string, int>(cardClass, playlistId), true, null);
	}

	void EjectSDCard(Object target)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_EJECT_CARD, null, true, null);
	}

	void PlayTrack(Object target, string trackName)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_PLAY_TRACK, new Param1<string>(trackName), true, null);
	}

	void StopTrack(Object target)
	{
		if (!IsAuthorized()) return;
		GetGame().RPCSingleParam(target, UnesennyeConstants.RADIO_STOP_TRACK, null, true, null);
	}

	void PlaySoundSetAt(string soundSetName, vector pos)
	{
		StopSound();
		if (soundSetName == "") return;
		m_SoundPos = pos;
		m_CurrentSound = SEffectManager.PlaySound(soundSetName, pos);
		if (m_CurrentSound)
		{
			m_CurrentSound.SetSoundAutodestroy(true);
			Print("[Unesennye Client] Play " + soundSetName + " at " + pos.ToString());
		}
	}

	void PlaySoundSet(string soundSetName)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		vector pos = "0 0 0";
		if (player) pos = player.GetPosition();
		PlaySoundSetAt(soundSetName, pos);
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
