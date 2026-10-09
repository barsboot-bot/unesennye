// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.3
// Do not remove this header. Unauthorized redistribution is prohibited.

modded class MissionGameplay
{
	override void OnInit()
	{
		super.OnInit();
		UnesennyeClientManager.GetInstance();
		Print("[Unesennye Client] MissionGameplay.OnInit | Author: KRa Tos (Константин)");
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
		// Start handshake shortly after world load
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartHS, 2000, false);
	}

	void StartHS()
	{
		UnesennyeClientManager.GetInstance().StartHandshake();
	}

	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		switch (rpc_type)
		{
			case UnesennyeConstants.HS_RESPONSE:
				UnesennyeClientManager.GetInstance().OnHandshakeResponse();
				break;

			case UnesennyeConstants.AUTH_FAIL:
				UnesennyeClientManager.GetInstance().BlockAndDisconnect();
				break;

			case UnesennyeConstants.BROADCAST_PLAY:
			case UnesennyeConstants.RADIO_BROADCAST:
			case UnesennyeConstants.ALBUM_BROADCAST:
				// TODO: play local sound from music_db using received track/playlistId
				break;

			case UnesennyeConstants.BROADCAST_STOP:
			case UnesennyeConstants.RADIO_BROADCAST_STOP:
				// TODO: stop local sound
				break;

			case UnesennyeConstants.TRACK_LIST_RESP:
			case UnesennyeConstants.ALBUM_TRACKLIST_RESP:
				// TODO: update UI track list
				break;
		}

		super.OnRPC(sender, target, rpc_type, ctx);
	}
};
