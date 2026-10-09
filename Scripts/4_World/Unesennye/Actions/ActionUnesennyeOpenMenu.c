// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.1
class ActionUnesennyeOpenMenu : ActionSingleUseBase
{
	void ActionUnesennyeOpenMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_Text = "Open Unesennye Music";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!GetGame().IsClient())
			return false;
		if (!UnesennyeClientManager.GetInstance().IsAuthorized())
			return false;

		EntityAI ent = EntityAI.Cast(target.GetObject());
		if (!ent)
			return false;

		// radio / car with media slot or media already attached
		if (ent.FindAttachmentBySlotName("Unesennye_SDCard"))
			return true;

		return ent.GetInventory() && ent.GetInventory().HasAttachmentSlot(InventorySlots.GetSlotIdFromString("Unesennye_SDCard"));
	}

	override void OnExecuteClient(ActionData action_data)
	{
		Object target = action_data.m_Target.GetObject();
		UnesennyeUIManager.GetInstance().OpenMusicMenu(target);
	}
};
