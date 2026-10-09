// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
class ActionUnesennyeEjectMedia : ActionSingleUseBase
{
	void ActionUnesennyeEjectMedia()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_Text = "#STR_Unesennye_Action_Eject";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		EntityAI ent = EntityAI.Cast(target.GetObject());
		if (!ent) return false;
		EntityAI att = ent.FindAttachmentBySlotName("Unesennye_SDCard");
		return att != null;
	}

	override void OnExecuteClient(ActionData action_data)
	{
		Object target = action_data.m_Target.GetObject();
		if (target)
			UnesennyeClientManager.GetInstance().EjectSDCard(target);
	}
};
