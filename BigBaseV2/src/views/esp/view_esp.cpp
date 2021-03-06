#include "view_esp.hpp"
#include "pointers.hpp"
#include "services/player_service.hpp"
#include "util/math.hpp"
#include "gta_util.hpp"
#include "util/misc.hpp"

namespace big
{
	float esp::calculate_distance(rage::fvector3 player_position)
	{
		const Vector3 plyr_coords = { player_position.x, player_position.y, player_position.z };
		const Vector3 cam_coords = g_pointers->m_get_gamplay_cam_coords();

		return (float)math::distance_between_vectors(plyr_coords, cam_coords);
	}

	void esp::draw() 
	{
		if (!g->esp.enabled) 
			return;

		static ImColor death_bg = ImColor(0.117f, 0.113f, 0.172f, .75f);
		static ImColor armor_blue_bg = ImColor(0.36f, 0.71f, 0.89f, .75f);
		static ImColor armor_blue = ImColor(0.36f, 0.71f, 0.89f, 1.f);
		static ImColor health_green_bg = ImColor(0.29f, 0.69f, 0.34f, .75f);
		static ImColor health_green = ImColor(0.29f, 0.69f, 0.34f, 1.f);
		static ImColor health_yellow_bg = ImColor(0.69f, 0.49f, 0.29f, .75f);
		static ImColor health_yellow = ImColor(0.69f, 0.49f, 0.29f, 1.f);
		static ImColor health_red_bg = ImColor(0.69f, 0.29f, 0.29f, .75f);
		static ImColor health_red = ImColor(0.69f, 0.29f, 0.29f, 1.f);

		if (const auto draw_list = ImGui::GetBackgroundDrawList(); draw_list)
		{
			for (auto& item : g_player_service->m_players)
			{
				const std::unique_ptr<player>& plyr = item.second;

				if (g->esp.hide_self && plyr->id() == gta_util::get_network_player_mgr()->m_local_net_player->m_player_id ||
					!plyr->is_valid() ||
					!plyr->get_ped() ||
					!plyr->get_ped()->m_navigation) continue;

				rage::fvector3& player_pos = plyr->get_ped()->m_navigation->m_position;

				float screen_x, screen_y;

				const float distance = calculate_distance(player_pos);
				const float multplr = distance > g->esp.global_render_distance[1] ? -1.f : 6.17757f / distance;

				if (multplr == -1.f || g->esp.global_render_distance[0] > distance) continue;

				bool god = misc::has_bit_set((int*)&plyr->get_ped()->m_damage_bits, 8);

				if (g_pointers->m_get_screen_coords_for_world_coords(player_pos.data, &screen_x, &screen_y))
				{
					const float esp_x = (float)*g_pointers->m_resolution_x * screen_x;
					const float esp_y = (float)*g_pointers->m_resolution_y * screen_y;

					const float esp_side_x = esp_x + (67.5f * multplr);

					std::string name_str = "";
					ImVec2 name_pos = { esp_x - (62.5f * multplr), esp_y - (175.f * multplr) - 20.f };
					ImU32 esp_color = g->esp.default_color;

					if (plyr->is_friend()) {
						esp_color = g->esp.friend_color;
					}
					else if (g->esp.change_esp_color_from_dist) {
						if (distance >= g->esp.distance_threshold[0] && distance < g->esp.distance_threshold[1])
							esp_color = g->esp.enemy_near_color;
						else
							esp_color = g->esp.enemy_color;
					}

					float armor_perc = plyr->get_ped()->m_armor / 50;
					armor_perc = armor_perc < 0.f ? 0.f : armor_perc;

					float health_perc = (plyr->get_ped()->m_health - 100) / (plyr->get_ped()->m_maxhealth - 100);
					health_perc = health_perc < 0.f ? 0.f : health_perc;

					if (distance < g->esp.tracer_render_distance[1] && distance > g->esp.tracer_render_distance[0] && g->esp.tracer)
						draw_list->AddLine({ (float)*g_pointers->m_resolution_x * g->esp.tracer_draw_position[0], (float)*g_pointers->m_resolution_y * g->esp.tracer_draw_position[1] }, { esp_x, esp_y }, esp_color);

					if (distance < g->esp.box_render_distance[1] && distance > g->esp.box_render_distance[0] && g->esp.box)
						draw_list->AddRect({ esp_x - (62.5f * multplr), esp_y - (175.f * multplr) }, { esp_x - (62.5f * multplr) + (125.f * multplr), esp_y - (175.f * multplr) + (350.f * multplr) }, esp_color);

					if (g->esp.name)
						name_str = plyr->get_name();

					if (g->esp.distance) {
						if (g->esp.name)
							name_str += " | ";
						name_str += std::to_string((int)distance);
						name_str += "m";
					}

					draw_list->AddText(name_pos, esp_color, name_str.c_str());

					if (god && g->esp.god) {
						draw_list->AddText({ esp_x - (62.5f * multplr), esp_y - (175.f * multplr) - 40.f }, ImColor(1.f, 0.f, 0.f, 1.f), "GOD");
					}
					else {
						if (g->esp.health) {
							if (g->esp.scale_health_from_dist) {
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f }, { esp_x - (62.5f * multplr) + (125.f * multplr), esp_y + (175.f * multplr) + 5.f }, health_perc == 0.f ? death_bg : health_perc < 0.25f ? health_red_bg : health_perc < 0.65f ? health_yellow_bg : health_green_bg, 4);
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f }, { esp_x - (62.5f * multplr) + (125.f * multplr) * health_perc, esp_y + (175.f * multplr) + 5.f }, health_perc < 0.25f ? health_red : health_perc < 0.65f ? health_yellow : health_green, 4);
							}
							else {
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f }, { esp_x - (62.5f * multplr) + (100.f), esp_y + (175.f * multplr) + 5.f }, health_perc == 0.f ? death_bg : health_perc < 0.25f ? health_red_bg : health_perc < 0.65f ? health_yellow_bg : health_green_bg, 4);
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f }, { esp_x - (62.5f * multplr) + (100.f * health_perc), esp_y + (175.f * multplr) + 5.f }, health_perc < 0.25f ? health_red : health_perc < 0.65f ? health_yellow : health_green, 4);
							}
						}
						if (g->esp.armor && plyr->get_ped()->m_armor > 0) {
							if (g->esp.scale_armor_from_dist) {
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 10.f }, { esp_x - (62.5f * multplr) + (125.f * multplr), esp_y + (175.f * multplr) + 10.f }, armor_blue_bg, 4);
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 10.f }, { esp_x - (62.5f * multplr) + (125.f * multplr) * armor_perc, esp_y + (175.f * multplr) + 10.f }, armor_blue, 4);
							}
							else {
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 10.f }, { esp_x - (62.5f * multplr) + (100.f), esp_y + (175.f * multplr) + 10.f }, armor_blue_bg, 4);
								draw_list->AddLine({ esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 10.f }, { esp_x - (62.5f * multplr) + (100.f * armor_perc), esp_y + (175.f * multplr) + 10.f }, armor_blue, 4);
							}
						}
					}
				}
			}
		}
	}
}