// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.3
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeAlbum
{
	void NextTrack()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized()) return;
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_NEXT_TRACK, null, true, null);
	}

	void PrevTrack()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized()) return;
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_PREV_TRACK, null, true, null);
	}

	void SetTrack(string track)
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized()) return;
		Param1<string> p = new Param1<string>(track);
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_SET_TRACK, p, true, null);
	}

	void RequestTracklist()
	{
		if (!UnesennyeClientManager.GetInstance().IsAuthorized()) return;
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_GET_TRACKLIST, null, true, null);
	}
};
