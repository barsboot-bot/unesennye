// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionUnesennyeInsertMedia);
		actions.Insert(ActionUnesennyeEjectMedia);
		actions.Insert(ActionUnesennyePlayTrack);
		actions.Insert(ActionUnesennyeStopTrack);
	}
};
