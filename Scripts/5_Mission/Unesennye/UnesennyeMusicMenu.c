// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.1
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeMusicMenu extends UIScriptedMenu
{
	protected TextListboxWidget m_TrackList;
	protected TextWidget m_LblPlaylist;
	protected TextWidget m_LblStatus;
	protected ButtonWidget m_BtnPlay;
	protected ButtonWidget m_BtnStop;
	protected ButtonWidget m_BtnNext;
	protected ButtonWidget m_BtnPrev;
	protected ButtonWidget m_BtnClose;

	protected Object m_Target;
	protected ref array<string> m_Tracks;
	protected int m_SelectedIndex;
	protected string m_PlaylistLabel;

	void UnesennyeMusicMenu()
	{
		m_Tracks = new array<string>;
		m_SelectedIndex = 0;
		m_PlaylistLabel = "Playlist: —";
	}

	void SetTarget(Object target)
	{
		m_Target = target;
	}

	Object GetTarget()
	{
		return m_Target;
	}

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets(UnesennyeConstants.LAYOUT_MUSIC);
		if (!layoutRoot)
		{
			Print("[Unesennye Client] Failed to load layout: " + UnesennyeConstants.LAYOUT_MUSIC);
			return null;
		}

		m_TrackList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TrackList"));
		m_LblPlaylist = TextWidget.Cast(layoutRoot.FindAnyWidget("LblPlaylist"));
		m_LblStatus = TextWidget.Cast(layoutRoot.FindAnyWidget("LblStatus"));
		m_BtnPlay = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnPlay"));
		m_BtnStop = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnStop"));
		m_BtnNext = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnNext"));
		m_BtnPrev = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnPrev"));
		m_BtnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClose"));

		RefreshPlaylistLabel();
		SetStatus("Ready");
		RequestTrackList();
		return layoutRoot;
	}

	void RequestTrackList()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
		{
			SetStatus("Not authorized");
			return;
		}
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_GET_TRACKLIST, null, true, null);
		GetGame().RPCSingleParam(null, UnesennyeConstants.TRACK_LIST_REQ, null, true, null);
		SetStatus("Loading tracks...");
	}

	void ApplyTrackList(string csv)
	{
		m_Tracks.Clear();
		if (m_TrackList)
			m_TrackList.ClearItems();

		if (csv == "")
		{
			SetStatus("No tracks");
			return;
		}

		array<string> parts = new array<string>;
		csv.Split(",", parts);
		for (int i = 0; i < parts.Count(); i++)
		{
			string t = parts.Get(i);
			t = t.Trim();
			if (t == "") continue;
			m_Tracks.Insert(t);
			if (m_TrackList)
				m_TrackList.AddItem(t, null, 0);
		}

		if (m_Tracks.Count() > 0)
		{
			m_SelectedIndex = 0;
			if (m_TrackList)
				m_TrackList.SelectRow(0);
		}

		SetStatus("Tracks: " + m_Tracks.Count().ToString());
	}

	void SetPlaylistName(string name)
	{
		m_PlaylistLabel = "Playlist: " + name;
		RefreshPlaylistLabel();
	}

	void RefreshPlaylistLabel()
	{
		if (m_LblPlaylist)
			m_LblPlaylist.SetText(m_PlaylistLabel);
	}

	void SetStatus(string s)
	{
		if (m_LblStatus)
			m_LblStatus.SetText("Status: " + s);
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_BtnClose)
		{
			Close();
			return true;
		}

		if (w == m_BtnPlay)
		{
			OnPlay();
			return true;
		}

		if (w == m_BtnStop)
		{
			OnStop();
			return true;
		}

		if (w == m_BtnNext)
		{
			OnNext();
			return true;
		}

		if (w == m_BtnPrev)
		{
			OnPrev();
			return true;
		}

		return super.OnClick(w, x, y, button);
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		if (w == m_TrackList)
		{
			OnPlay();
			return true;
		}
		return super.OnDoubleClick(w, x, y, button);
	}

	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_TrackList && m_TrackList)
		{
			m_SelectedIndex = m_TrackList.GetSelectedRow();
			if (m_SelectedIndex < 0) m_SelectedIndex = 0;
		}
		return super.OnChange(w, x, y, finished);
	}

	void OnPlay()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
		{
			SetStatus("Not authorized");
			return;
		}

		if (m_TrackList)
			m_SelectedIndex = m_TrackList.GetSelectedRow();

		string track = "";
		if (m_SelectedIndex >= 0 && m_SelectedIndex < m_Tracks.Count())
			track = m_Tracks.Get(m_SelectedIndex);

		if (m_Target)
			UnesennyeClientManager.GetInstance().PlayTrack(m_Target, track);
		else
		{
			Param1<string> p = new Param1<string>(track);
			GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_SET_TRACK, p, true, null);
		}

		SetStatus("Playing: " + track);
	}

	void OnStop()
	{
		if (m_Target)
			UnesennyeClientManager.GetInstance().StopTrack(m_Target);
		else
			GetGame().RPCSingleParam(null, UnesennyeConstants.RADIO_STOP, null, true, null);

		UnesennyeClientManager.GetInstance().StopSound();
		SetStatus("Stopped");
	}

	void OnNext()
	{
		GetGame().RPCSingleParam(m_Target, UnesennyeConstants.ALBUM_NEXT_TRACK, null, true, null);
		if (m_Tracks.Count() > 0)
		{
			m_SelectedIndex = (m_SelectedIndex + 1) % m_Tracks.Count();
			if (m_TrackList)
				m_TrackList.SelectRow(m_SelectedIndex);
		}
		SetStatus("Next");
	}

	void OnPrev()
	{
		GetGame().RPCSingleParam(m_Target, UnesennyeConstants.ALBUM_PREV_TRACK, null, true, null);
		if (m_Tracks.Count() > 0)
		{
			m_SelectedIndex = m_SelectedIndex - 1;
			if (m_SelectedIndex < 0)
				m_SelectedIndex = m_Tracks.Count() - 1;
			if (m_TrackList)
				m_TrackList.SelectRow(m_SelectedIndex);
		}
		SetStatus("Prev");
	}

	override void OnHide()
	{
		super.OnHide();
	}
};
