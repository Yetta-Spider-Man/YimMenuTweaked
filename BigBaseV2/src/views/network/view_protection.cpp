#include "views/view.hpp"

namespace big
{
	void view::protection()
	{
		ImGui::BeginGroup();

		ImGui::Checkbox("Bounty", &g->protections.script_events.bounty);
		ImGui::Checkbox("CEO ban", &g->protections.script_events.ceo_ban);
		ImGui::Checkbox("CEO kick", &g->protections.script_events.ceo_kick);
		ImGui::Checkbox("CEO money", &g->protections.script_events.ceo_money);
		ImGui::Checkbox("Wanted level", &g->protections.script_events.clear_wanted_level);
		ImGui::Checkbox("Fake deposit", &g->protections.script_events.fake_deposit);
		ImGui::Checkbox("Force mission", &g->protections.script_events.force_mission);

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();

		ImGui::Checkbox("Force teleport", &g->protections.script_events.force_teleport);
		ImGui::Checkbox("GTA banner", &g->protections.script_events.gta_banner);
		ImGui::Checkbox("Network bail", &g->protections.script_events.network_bail);
		ImGui::Checkbox("Personal vehicle destroyed", &g->protections.script_events.personal_vehicle_destroyed);
		ImGui::Checkbox("Remote off radar", &g->protections.script_events.remote_off_radar);
		ImGui::Checkbox("Rotate cam", &g->protections.script_events.rotate_cam);

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();

		ImGui::Checkbox("Send to cutscene", &g->protections.script_events.send_to_cutscene);
		ImGui::Checkbox("Send to island", &g->protections.script_events.send_to_island);
		ImGui::Checkbox("Sound spam", &g->protections.script_events.sound_spam);
		ImGui::Checkbox("Spectate", &g->protections.script_events.spectate);
		ImGui::Checkbox("Transaction error", &g->protections.script_events.transaction_error);
		ImGui::Checkbox("Vehicle kick", &g->protections.script_events.vehicle_kick);

		ImGui::EndGroup();
	}

}
