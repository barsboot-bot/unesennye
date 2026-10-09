// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.1
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeUIManager
{
	protected static ref UnesennyeUIManager m_Instance;
	protected ref UnesennyeMusicMenu m_MusicMenu;

	static UnesennyeUIManager GetInstance()
	{
		if (!m_Instance)
			m_Instance = new UnesennyeUIManager();
		return m_Instance;
	}

	void OpenMusicMenu(Object target)
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
		{
			Print("[Unesennye Client] UI blocked — not authorized");
			return;
		}

		if (GetGame().GetUIManager().GetMenu())
		{
			// already some menu open
			return;
		}

		m_MusicMenu = new UnesennyeMusicMenu();
		m_MusicMenu.SetTarget(target);
		GetGame().GetUIManager().ShowScriptedMenu(m_MusicMenu, null);
	}

	void CloseMusicMenu()
	{
		if (m_MusicMenu)
		{
			m_MusicMenu.Close();
			m_MusicMenu = null;
		}
	}

	UnesennyeMusicMenu GetMusicMenu()
	{
		return m_MusicMenu;
	}

	void OnTrackListResponse(string csv)
	{
		if (m_MusicMenu)
			m_MusicMenu.ApplyTrackList(csv);
	}
};
