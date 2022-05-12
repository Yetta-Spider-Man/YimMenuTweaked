#include "backend/looped/looped.hpp"
#include "pointers.hpp"

//https://github.com/Yimura/YimMenu/commits?author=xM4ddy
//PLEASE LEARN HOW TO CODE!!!

namespace big
{
	static std::vector<std::pair<uint32_t, float>> og_spread_values{};
	static std::vector<std::pair<uint32_t, float>> og_recoil_values{};
	static uint32_t prev_weapon_hash{};

	bool is_spread_value_cached(uint32_t hash) { return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry) {return hash == entry.first; }) != og_spread_values.end(); }

	float get_og_spread_value(uint32_t hash) { return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry) {return hash == entry.first; })->second; }

	float get_spread_value(uint32_t hash) { return g->weapons.no_spread ? 0.f : get_og_spread_value(hash); }

	bool is_recoil_value_cached(uint32_t hash) { return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry) {return hash == entry.first; }) != og_recoil_values.end(); }

	float get_og_recoil_value(uint32_t hash) { return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry) {return hash == entry.first; })->second; }

	float get_recoil_value(uint32_t hash) { return g->weapons.no_spread ? 0.f : get_og_recoil_value(hash); }

	void backend_self::weapons::no_spread()
	{
		if (!g_local_player)
			return;

		if (auto* const weapon_mgr = g_local_player->m_weapon_manager; weapon_mgr)
		{
			auto const cur_weapon_hash = weapon_mgr->m_selected_weapon_hash;
			if (prev_weapon_hash != cur_weapon_hash)
			{
				if (!is_spread_value_cached(cur_weapon_hash))
					og_spread_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_accuracy_spread });

				weapon_mgr->m_weapon_info->m_accuracy_spread = get_spread_value(cur_weapon_hash);

				if (!is_recoil_value_cached(cur_weapon_hash))
					og_recoil_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_explosion_shake_amplitude });

				weapon_mgr->m_weapon_info->m_explosion_shake_amplitude = get_recoil_value(cur_weapon_hash); // m_explosion_shake_amplitude is the right offset in https://github.com/Yimura/GTAV-Classes
			}
		}
	}
}