// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class CfgPatches
{
	class unesennye
	{
		units[] = {"Unesennye_SD_Card", "Unesennye_SD_Card_Empty"};
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
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Unesennye Music System";
		credits = "KRa Tos (Константин)";
		author = "KRa Tos (Константин)";
		authorID = "";
		version = "1.2.4";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"unesennye/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"unesennye/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"unesennye/Scripts/5_Mission"};
			};
		};
	};
};

class CfgSlots
{
	class Slot_Unesennye_SDCard
	{
		name = "Unesennye_SDCard";
		displayName = "SD Card";
		ghostIcon = "set:dayz_inventory image:battery1";
	};
};

class CfgVehicles
{
	class Inventory_Base;

	class Unesennye_SD_Card_Empty : Inventory_Base
	{
		scope = 2;
		displayName = "SD Card (Empty)";
		descriptionShort = "Empty SD card. Record music from Unesennye Music DB.";
		model = "\dz\gear\tools\battery.p3d";
		weight = 15;
		itemSize[] = {1, 1};
		inventorySlot[] = {"Unesennye_SDCard"};
		varQuantityInit = 0;
		varQuantityMin = 0;
		varQuantityMax = 99;
		quantityBar = 0;
	};

	class Unesennye_SD_Card : Unesennye_SD_Card_Empty
	{
		scope = 2;
		displayName = "SD Card";
		descriptionShort = "SD card with music. Insert into radio or car. Quantity = playlist ID.";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 99;
	};

	// Full attachments override (+= is unreliable in DayZ config)
	class Transmitter_Base;
	class PersonalRadio : Transmitter_Base
	{
		attachments[] = {"BatteryD", "Unesennye_SDCard"};
	};

	// Cars: append SD slot by re-declaring common attachment lists.
	// Note: some vehicles have more slots; extend per-vehicle if needed.
	class CarScript;
	class OffroadHatchback : CarScript
	{
		attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"};
	};
	class Hatchback_02 : CarScript
	{
		attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"};
	};
	class CivilianSedan : CarScript
	{
		attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"};
	};
	class Sedan_02 : CarScript
	{
		attachments[] = {"CarBattery", "Reflector_1_1", "Reflector_2_1", "EngineBelt", "CarRadiator", "SparkPlug", "Unesennye_SDCard"};
	};
};
