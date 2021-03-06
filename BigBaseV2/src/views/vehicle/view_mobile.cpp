#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/mobile.hpp"
#include "services/mobile_service.hpp"

namespace big
{
	void view::mobile()
	{
		components::button("Fix all personal vehicles", []
			{
				int amount_fixed = mobile::mors_mutual::fix_all();
				//g_notification_service->push("Mobile", fmt::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have"));
			});

		components::small_text("Personal vehicles list");

		static char search[64];
		static std::string lower_search;

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(200.f);

		if (ImGui::InputTextWithHint("##search_pv_list", "Search", search, sizeof(search)))
		{
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		}

		g_mobile_service->refresh_personal_vehicles();
		if (ImGui::ListBoxHeader("##personal_veh_list", { 200.f, 200.f }))
		{
			if (g_mobile_service->personal_vehicles().empty())
				ImGui::Text("No personal vehicles found. Join GTA V Online");
			else
			{
				const auto personal_veh_idx = mobile::util::get_current_personal_vehicle();

				for (const auto& it : g_mobile_service->personal_vehicles())
				{
					const auto& label = it.first;
					const auto& personal_veh = it.second;

					auto lower = label;
					std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

					if (lower.find(lower_search) != std::string::npos)
					{
						if (ImGui::Selectable(label.c_str(), personal_veh->get_id() == personal_veh_idx))
						{
							strcpy(search, "");
							lower_search = search;

							g_fiber_pool->queue_job([&personal_veh] { personal_veh->summon(); });
						}
					}
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();

		ImGui::BeginGroup();

		ImGui::Checkbox("Spawn in Vehicle", &g->vehicle.pv_teleport_into);

		ImGui::EndGroup();
	}
}