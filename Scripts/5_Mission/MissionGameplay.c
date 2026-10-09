// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
modded class MissionGameplay
{
	override void OnInit()
	{
		super.OnInit();
		UnesennyeClientManager.GetInstance();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartHS, 2000, false);
	}

	void StartHS() { UnesennyeClientManager.GetInstance().StartHandshake(); }

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
				Param1<string> p1;
				if (ctx.Read(p1))
				{
					vector pos = "0 0 0";
					if (target) pos = target.GetPosition();
					UnesennyeClientManager.GetInstance().PlaySoundSetAt(p1.param1, pos);
				}
				break;
			}
			case UnesennyeConstants.RADIO_BROADCAST:
			case UnesennyeConstants.ALBUM_BROADCAST:
			{
				Param3<int, string, string> p3;
				if (ctx.Read(p3))
				{
					string ss = p3.param3;
					if (ss == "") ss = p3.param2;
					vector pos2 = "0 0 0";
					if (target) pos2 = target.GetPosition();
					else
					{
						PlayerBase pb = PlayerBase.Cast(GetGame().GetPlayer());
						if (pb) pos2 = pb.GetPosition();
					}
					UnesennyeClientManager.GetInstance().PlaySoundSetAt(ss, pos2);
				}
				break;
			}
			case UnesennyeConstants.BROADCAST_STOP:
			case UnesennyeConstants.RADIO_BROADCAST_STOP:
				UnesennyeClientManager.GetInstance().StopSound();
				break;
		}
		super.OnRPC(sender, target, rpc_type, ctx);
	}
};
