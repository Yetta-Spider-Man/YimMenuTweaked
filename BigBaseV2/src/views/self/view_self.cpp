#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "views/view.hpp"

namespace big
{
	void view::self() 
	{
		components::small_text("General");

		ImGui::BeginGroup();

		ImGui::Checkbox("Godmode", &g->self.godmode);
		ImGui::Checkbox("Off radar", &g->self.off_radar);
		ImGui::Checkbox("Fast run", &g->self.fast_run);
		ImGui::Checkbox("Invisibility", &g->self.invisibility);
		if (g->self.invisibility)
			ImGui::Checkbox("Locally visible", &g->self.local_visibility);

		ImGui::EndGroup();

		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Noclip", &g->self.noclip);
		ImGui::Checkbox("Freecam", &g->self.free_cam);
		ImGui::Checkbox("No idle kick", &g->tunables.no_idle_kick); //Should be protection
		ImGui::Checkbox("Disable phone", &g->tunables.disable_phone);

		ImGui::EndGroup();
		ImGui::SameLine();

		ImGui::Separator();

		components::small_text("Police");

		ImGui::Checkbox("Never wanted", &g->self.never_wanted);

		if (!g->self.never_wanted)
		{
			ImGui::Checkbox("Force wanted level", &g->self.force_wanted_level);

			ImGui::Text("Wanted level");

			if (ImGui::SliderInt("###wanted_level", &g->self.wanted_level, 0, 5) && !g->self.force_wanted_level)
				g_local_player->m_player_info->m_wanted_level = g->self.wanted_level;
		}

		ImGui::Separator();

		components::small_text("Model");

		static char model[32];

		components::input_text_with_hint("Model name###player_ped_model", "Player Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			g_fiber_pool->queue_job([]
			{
				const Hash hash = rage::joaat(model);

				for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
				{
					STREAMING::REQUEST_MODEL(hash);

					script::get_current()->yield();
				}

				if (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model?");
					return;
				}

				PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
				script::get_current()->yield();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			});
		});

		ImGui::Separator();

		components::small_text("Misc");

		components::button("Suicide", []
		{
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
		});

		ImGui::SameLine();

		components::button("Skip cutscene", []
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		});
	}
}