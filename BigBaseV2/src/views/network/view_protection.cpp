#include "views/view.hpp"

namespace big
{
	void view::protection()
	{
		ImGui::BeginGroup();

		components::small_text("Kick");

		ImGui::Checkbox("Script events", &g->protections.script_events);
		ImGui::Checkbox("Game events", &g->protections.game_events);
		
		components::small_text("Crash");

		ImGui::Checkbox("NET_ARRAY_HANDLER", &g->protections.NET_ARRAY_HANDLER);
		ImGui::Checkbox("TASK_VEHICLE_TEMP_ACTION", &g->protections.TASK_VEHICLE_TEMP_ACTION);

		components::small_text("Misc");

		ImGui::Checkbox("Chat spam", &g->protections.chat);
		ImGui::Checkbox("AFK kick", &g->protections.afk_kick);
		ImGui::Checkbox("Vote kick", &g->protections.vote_kick);
		ImGui::Checkbox("Stat increments", &g->protections.stats);

		ImGui::EndGroup();
	}

}
