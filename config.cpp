// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.2
// Do not remove this header. Unauthorized redistribution is prohibited.

class CfgPatches
{
	class unesennye
	{
		units[] = {"Unesennye_SD_Card", "Unesennye_SD_Card_Empty", "Unesennye_Cassette", "Unesennye_Disk"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Tools", "DZ_Vehicles_Wheeled"};
	};
};

class CfgMods
{
	class unesennye
	{
		dir = "unesennye";
		name = "Unesennye Music System";
		credits = "KRa Tos (Константин)";
		author = "KRa Tos (Константин)";
		version = "1.3.2";
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		class defs
		{
			class gameScriptModule { value = ""; files[] = {"unesennye/Scripts/3_Game"}; };
			class worldScriptModule { value = ""; files[] = {"unesennye/Scripts/4_World"}; };
			class missionScriptModule { value = ""; files[] = {"unesennye/Scripts/5_Mission"}; };
		};
	};
};

class CfgSlots
{
	class Slot_Unesennye_SDCard
	{
		name = "Unesennye_SDCard";
		displayName = "$STR_Unesennye_Slot_SD";
		ghostIcon = "set:dayz_inventory image:battery1";
	};
};

class CfgVehicles
{
	class Inventory_Base;

	// ---- Базовый класс носителя ----
	class Unesennye_Media_Base : Inventory_Base
	{
		scope = 0;
		model = "\dz\gear\tools\battery.p3d";
		weight = 15;
		itemSize[] = {1, 1};
		inventorySlot[] = {"Unesennye_SDCard"};
		varQuantityInit = 0;
		varQuantityMin = 0;
		varQuantityMax = 99;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"unesennye\data\textures\sd_card_empty_co.paa"};
		hiddenSelectionsMaterials[] = {"unesennye\data\materials\sd_card_empty.rvmat"};
	};

	class Unesennye_SD_Card_Empty : Unesennye_Media_Base
	{
		scope = 2;
		displayName = "$STR_Unesennye_SD_Empty";
		descriptionShort = "$STR_Unesennye_SD_Empty_Desc";
		hiddenSelectionsTextures[] = {"unesennye\data\textures\sd_card_empty_co.paa"};
		hiddenSelectionsMaterials[] = {"unesennye\data\materials\sd_card_empty.rvmat"};
	};

	class Unesennye_SD_Card : Unesennye_Media_Base
	{
		scope = 2;
		displayName = "$STR_Unesennye_SD";
		descriptionShort = "$STR_Unesennye_SD_Desc";
		varQuantityInit = 1;
		hiddenSelectionsTextures[] = {"unesennye\data\textures\sd_card_co.paa"};
		hiddenSelectionsMaterials[] = {"unesennye\data\materials\sd_card.rvmat"};
	};

	class Unesennye_Cassette : Unesennye_Media_Base
	{
		scope = 2;
		displayName = "$STR_Unesennye_Cassette";
		descriptionShort = "$STR_Unesennye_Cassette_Desc";
		varQuantityInit = 1;
		hiddenSelectionsTextures[] = {"unesennye\data\textures\cassette_co.paa"};
		hiddenSelectionsMaterials[] = {"unesennye\data\materials\cassette.rvmat"};
	};

	class Unesennye_Disk : Unesennye_Media_Base
	{
		scope = 2;
		displayName = "$STR_Unesennye_Disk";
		descriptionShort = "$STR_Unesennye_Disk_Desc";
		varQuantityInit = 1;
		hiddenSelectionsTextures[] = {"unesennye\data\textures\disk_co.paa"};
		hiddenSelectionsMaterials[] = {"unesennye\data\materials\disk.rvmat"};
	};

	class Transmitter_Base;
	class PersonalRadio : Transmitter_Base
	{
		attachments[] = {"BatteryD", "Unesennye_SDCard"};
	};

	class CarScript;
	class OffroadHatchback : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
	class Hatchback_02 : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
	class CivilianSedan : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
	class Sedan_02 : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
	class Truck_01_Covered : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
	class Offroad_02 : CarScript { attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"}; };
};
