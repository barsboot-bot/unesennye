// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.3
class ActionUnesennyeInsertMedia : ActionSingleUseBase
{
	void ActionUnesennyeInsertMedia()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_Text = "#STR_Unesennye_Action_Insert";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

	bool IsMediaItem(string t)
	{
		return t == "Unesennye_SD_Card" || t == "Unesennye_SD_Card_Empty"
			|| t == "Unesennye_Cassette" || t == "Unesennye_Disk"
			|| t == "Unesennye_CD" || t == "Unesennye_DVD" || t == "Unesennye_DVD_R";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!item || !target) return false;
		if (!IsMediaItem(item.GetType())) return false;
		EntityAI ent = EntityAI.Cast(target.GetObject());
		if (!ent) return false;
		return ent.GetInventory() && ent.GetInventory().HasAttachmentSlot(InventorySlots.GetSlotIdFromString("Unesennye_SDCard"));
	}

	override void OnExecuteServer(ActionData action_data)
	{
		EntityAI target = EntityAI.Cast(action_data.m_Target.GetObject());
		ItemBase item = action_data.m_MainItem;
		if (!target || !item) return;
		target.GetInventory().TakeEntityAsAttachment(InventoryMode.SERVER, item);
	}

	override void OnExecuteClient(ActionData action_data)
	{
		Object target = action_data.m_Target.GetObject();
		ItemBase item = action_data.m_MainItem;
		if (!target || !item) return;
		UnesennyeClientManager.GetInstance().InsertSDCard(target, item.GetType(), item.GetQuantity());
	}
};
