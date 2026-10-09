// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
class ActionUnesennyeStopTrack : ActionSingleUseBase
{
	void ActionUnesennyeStopTrack()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_Text = "#STR_Unesennye_Action_Stop";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return UnesennyeClientManager.GetInstance().IsAuthorized();
	}

	override void OnExecuteClient(ActionData action_data)
	{
		Object target = action_data.m_Target.GetObject();
		if (target)
			UnesennyeClientManager.GetInstance().StopTrack(target);
	}
};
