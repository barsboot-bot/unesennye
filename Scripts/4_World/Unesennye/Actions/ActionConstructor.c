// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.1
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionUnesennyeInsertMedia);
		actions.Insert(ActionUnesennyeEjectMedia);
		actions.Insert(ActionUnesennyePlayTrack);
		actions.Insert(ActionUnesennyeStopTrack);
		actions.Insert(ActionUnesennyeOpenMenu);
	}
};
