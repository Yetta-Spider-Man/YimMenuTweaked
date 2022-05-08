#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/mobile.hpp"
#include "services/mobile_service.hpp"

namespace big
{
	void view::mobile() 
	{
		components::button("Bring personal vehicle", [] 
		{
			Vehicle veh = globals::get_personal_vehicle();

			if (ENTITY::IS_ENTITY_DEAD(veh, false)) 
				return g_notification_service->push_error("Teleport", "Invalid vehicle handle...");

			Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

			vehicle::bring(veh, location);
		});

		components::button("Go to personal vehicle", []
		{
			Vehicle veh = globals::get_personal_vehicle();

			if (ENTITY::IS_ENTITY_DEAD(veh, false)) 
				return g_notification_service->push_error("Teleport", "Invalid vehicle handle...");

			teleport::to_coords(ENTITY::GET_ENTITY_COORDS(veh, true));
		});

		components::button("Fix all personal vehicles", [] 
		{
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile", fmt::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have"));
		});

		components::small_text("Personal vehicles");

		static char search[64];
		static std::string lower_search;

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(400.f);

		if (ImGui::InputTextWithHint("##search_pv_list", "Search", search, sizeof(search)))
		{
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		}

		if (ImGui::ListBoxHeader("##personal_veh_list", { 400.f, 500.f }))
		{
			for (auto& it : g_mobile_service->m_personal_vehicles)
			{
				std::string label = it.first;
				auto& personal_veh = it.second;

				std::string lower = label.c_str();
				std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

				if (lower.find(lower_search) != std::string::npos)
				{
					if (ImGui::Selectable(label.c_str(), personal_veh->get_id() == mobile::util::get_current_personal_vehicle()))
					{
						strcpy(search, "");
						lower_search = search;

						g_fiber_pool->queue_job([&personal_veh]
						{
							personal_veh->summon();
						});
					}
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();

		ImGui::BeginGroup();

		if (ImGui::Button("Fetch personal vehicles"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				g_mobile_service->register_vehicles();
			}
			QUEUE_JOB_END_CLAUSE
		}
		ImGui::Checkbox("Spawn in vehicle", &g->vehicle.pv_teleport_into);
			
	}
}