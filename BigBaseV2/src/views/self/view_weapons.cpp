#include "core/data/custom_weapons.hpp"
#include "fiber_pool.hpp"
#include "gta/Weapons.h"
#include "script.hpp"
#include "core/data/special_ammo_types.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons() 
	{
		components::small_text("Ammo");

		ImGui::Checkbox("Infinite ammo", &g->weapons.infinite_ammo);

		ImGui::SameLine();

		ImGui::Checkbox("Infinite clip", &g->weapons.infinite_mag);

		ImGui::Checkbox("Enable special ammo", &g->weapons.ammo_special.toggle);

		eAmmoSpecialType selected_ammo = g->weapons.ammo_special.type;

		if (ImGui::BeginCombo("Special ammo", SPECIAL_AMMOS[(int)selected_ammo].name))
		{
			for (const auto& special_ammo : SPECIAL_AMMOS)
			{
				if (ImGui::Selectable(special_ammo.name, special_ammo.type == selected_ammo))
					g->weapons.ammo_special.type = special_ammo.type;

				if (special_ammo.type == selected_ammo)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::small_text("Misc");

		ImGui::Checkbox("Force crosshair", &g->weapons.force_crosshairs);

		ImGui::SameLine();

		ImGui::Checkbox("Disable recoil", &g->weapons.no_recoil);

		ImGui::SameLine();

		ImGui::Checkbox("Disable spread", &g->weapons.no_spread);

		if (ImGui::Button("Give all weapons"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				for (auto const& weapon : weapon_list) 
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weapon, 9999, false);
				}

				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), -72657034, 0, true);
			}
			QUEUE_JOB_END_CLAUSE
		}

		ImGui::SliderFloat("Damage multiplier", &g->weapons.increased_damage, 1.f, 10.f, "%.1f");

		ImGui::Separator();

		components::small_text("Custom weapons");

		CustomWeapon selected = g->weapons.custom_weapon;

		if (ImGui::BeginCombo("Weapon", custom_weapons[(int)selected].name))
		{
			for (const custom_weapon& weapon : custom_weapons)
			{
				if (ImGui::Selectable(weapon.name, weapon.id == selected))
					g->weapons.custom_weapon = weapon.id;

				if (weapon.id == selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		switch (selected)
		{

		case CustomWeapon::VEHICLE_GUN:
			ImGui::Text("Shooting Model:");
			ImGui::InputText("##vehicle_gun_model", g->weapons.vehicle_gun_model, 12);
			break;
		}
	}
}