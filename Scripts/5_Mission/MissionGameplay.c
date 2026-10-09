// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
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
			{
				Param1<string> playData;
				if (ctx.Read(playData))
					UnesennyeClientManager.GetInstance().PlaySoundSet(playData.param1);
				break;
			}

			case UnesennyeConstants.RADIO_BROADCAST:
			{
				// Param3: playlistId, trackName, soundSetName
				Param3<int, string, string> radioData;
				if (ctx.Read(radioData))
				{
					string soundSet = radioData.param3;
					if (soundSet == "")
						soundSet = radioData.param2;
					UnesennyeClientManager.GetInstance().PlaySoundSet(soundSet);
				}
				break;
			}

			case UnesennyeConstants.ALBUM_BROADCAST:
			{
				Param1<string> albumData;
				if (ctx.Read(albumData))
					UnesennyeClientManager.GetInstance().PlaySoundSet(albumData.param1);
				break;
			}

			case UnesennyeConstants.BROADCAST_STOP:
			case UnesennyeConstants.RADIO_BROADCAST_STOP:
				UnesennyeClientManager.GetInstance().StopSound();
				break;

			case UnesennyeConstants.TRACK_LIST_RESP:
			case UnesennyeConstants.ALBUM_TRACKLIST_RESP:
			{
				Param1<string> listData;
				if (ctx.Read(listData))
					Print("[Unesennye Client] Track list: " + listData.param1);
				break;
			}
		}

		super.OnRPC(sender, target, rpc_type, ctx);
	}
};
