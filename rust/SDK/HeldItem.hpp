#pragma once
#include "Imports.hpp"
#include "Driver.hpp"
#include "Utils.hpp"

class HeldItem {
public:

	HeldItem() {}

	HeldItem(uint64_t _ent) {
		this->ent = _ent;

		this->name = GetItemName();

		this->bp = Read<uintptr_t>(this->ent + 0x98); //private EntityRef heldEntity;

		this->recoil_properties = Read<uintptr_t>(this->bp + 0x2C8); //	public RecoilProperties recoil;

		this->primary_mag = Read<uint64_t>(this->bp + 0x2A0);
	}

	std::string GetItemName()
	{
		uint64_t info = Read<uint64_t>(this->ent + 0x20);

		uint64_t display_name = Read<uint64_t>(info + 0x20);

		std::wstring wide_name = ReadUnicode(display_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return safe_str("No Item");
	}


	std::string GetActiveWeaponName(uint64_t myWeapon)
	{
		uint64_t itemDefinition = Read<uint64_t>(myWeapon + 0x20);
		uint64_t display_name = Read<uint64_t>(itemDefinition + 0x28);
		uint64_t english = Read<uint64_t>(display_name + 0x18);
		if (!english)
			return std::string();
		else
			return safe_str("nothing");
	}

	void setNoAimCone() {
		Write<float>(this->bp + 0x2D0, 0.f);
		Write<float>(this->bp + 0x2D4, 0.f);
		Write<float>(this->bp + 0x2D8, 0.f);
		Write<float>(this->bp + 0x2DC, 0.f);
		Write<float>(this->bp + 0x2E8, 0.f);
	}

	void setNoSway() {
		Write<float>(this->bp + 0x2B8, 0.f);
		Write<float>(this->bp + 0x2BC, 0.f);
	}

	void noRecoil() {
			const auto recoil_properties = Read<uintptr_t>(this->bp + 0x2C8); //	public RecoilProperties recoil;
			if (!recoil_properties)
				return;

			for (int i = 0; i < 8; i++)
				Write<float>(recoil_properties + 0x18 + i * 4, 0);
	}

	void rapidFire() {
			Write<float>(this->bp + 0x1DC, Settings::rapidfirevalue);
			Write<bool>(this->bp + 0x270, true); //this is automatic fire
	}

	void instantCompound() {
			Write<float>(bp + 0x358, 0);//stringHoldDurationMax
			Write<float>(bp + 0x35C, 1000000);//stringBonusDamage
			Write<float>(bp + 0x368, 1000000);//movementPenaltyRampUpTime
	}

	void fastSwitch() {
			Write<float>(bp + 0x1D8, 0);//deployDelay | instant deploy
	}


	//causes a crash if switched to another weapon (i will fix - johnn)
	void instantEoka() {
		if (this->name.find(safe_str("eoka")) != std::string::npos)
		{
			Write<bool>(this->bp + 0x358, true);//_didSparkThisFrame
			Write<float>(this->bp + 0x348, 100.f);//successFraction
		}
	}



	//some issues atm will fix later o


	void WeaponLoops()
	{
		/* place multiple useless features in here instead of multiple voids */
		if (Settings::thickBullet)//Change to fastBullet
		{
			Write<float>(this->bp + 0x26C, 0.5f);//projectileVelocityScale
		}
	}

	bool IsWeapon()
	{
		if (this->name.find(safe_str("rifle")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("pistol")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("bow")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("lmg")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("shotgun")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("smg")) != std::string::npos)
		{
			return true;
		}
		else
			return false;
	}

	std::string GetAmmoType()
	{
		uint64_t item_def = Read<uint64_t>(this->primary_mag + 0x20);
		uint64_t short_name = Read<uint64_t>(item_def + 0x20);

		std::wstring wide_name = ReadUnicode(short_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return safe_str("No Ammo");
	}

public:
	uint64_t ent;
	uintptr_t bp;
	uint64_t playerMovement2{};
	uintptr_t recoil_properties;
	uint64_t primary_mag;
	std::string name;
};