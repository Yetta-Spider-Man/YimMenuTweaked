#include "backend/looped/looped.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"

namespace big
{
	void backend_self::weapons::infinite_ammo()
	{
		if (!g->weapons.infinite_ammo)
			return;

		Hash weaponHash;
		auto const ped = PLAYER::PLAYER_PED_ID();

		WEAPON::GET_CURRENT_PED_WEAPON(ped, &weaponHash, 1);

		if (weaponHash == RAGE_JOAAT("WEAPON_UNARMED"))
			return;

		WEAPON::GIVE_WEAPON_TO_PED(ped, weaponHash, 9999, false, false);
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g->weapons.infinite_ammo);
	}
}