#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g->notifications.gta_thread_kill)& option)
	{
		ImGui::Text("%s", name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Log", &option.log);
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::PopID();
	}

	void view::notification_options()
	{
		components::small_text("GTA Threads");

		draw_pair_option("Terminate", g->notifications.gta_thread_kill);
		draw_pair_option("Start", g->notifications.gta_thread_start);

		components::small_text("Network player manager");

		ImGui::Text("Player join");

		ImGui::Checkbox("Above map", &g->notifications.player_join.above_map);
		ImGui::Checkbox("Log", &g->notifications.player_join.log);
		ImGui::Checkbox("Notify", &g->notifications.player_join.notify);

		ImGui::SameLine();

		draw_pair_option("Player leave", g->notifications.player_leave);
		draw_pair_option("Shutdown", g->notifications.network_player_mgr_shutdown);

		components::small_text("Received event");

		auto& received_event = g->notifications.received_event;

		ImGui::BeginGroup();
		draw_pair_option("Clear ped tasks", received_event.clear_ped_task);
		draw_pair_option("Modder detection", received_event.modder_detect);
		draw_pair_option("Report cash spawn", received_event.report_cash_spawn);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Request control event", received_event.request_control_event);
		draw_pair_option("Vehicle Temp Action", received_event.vehicle_temp_action);
		ImGui::EndGroup();

		components::small_text("Script event handler");

		auto& script_event_handler = g->notifications.script_event_handler;

		ImGui::BeginGroup();
		draw_pair_option("Bounty", script_event_handler.bounty);
		draw_pair_option("CEO ban", script_event_handler.ceo_ban);
		draw_pair_option("CEO kick", script_event_handler.ceo_kick);
		draw_pair_option("CEO money", script_event_handler.ceo_money);
		draw_pair_option("Wanted level", script_event_handler.clear_wanted_level);
		draw_pair_option("Fake deposit", script_event_handler.fake_deposit);
		draw_pair_option("Force mission", script_event_handler.force_mission);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Force teleport", script_event_handler.force_teleport);
		draw_pair_option("GTA banner", script_event_handler.gta_banner);
		draw_pair_option("Network bail", script_event_handler.network_bail);
		draw_pair_option("Destroy personal vehicle", script_event_handler.personal_vehicle_destroyed);
		draw_pair_option("Remote off radar", script_event_handler.remote_off_radar);
		draw_pair_option("Rotate cam", script_event_handler.rotate_cam);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Send to cutscene", script_event_handler.send_to_cutscene);
		draw_pair_option("Send to island", script_event_handler.send_to_island);
		draw_pair_option("Sound spam", script_event_handler.sound_spam);
		draw_pair_option("Spectate", script_event_handler.spectate);
		draw_pair_option("Transaction error", script_event_handler.transaction_error);
		draw_pair_option("Vehicle kick", script_event_handler.vehicle_kick);
		ImGui::EndGroup();

		components::small_text("Other");

		draw_pair_option("Chat spam", g->notifications.chat_receive);
		draw_pair_option("Net array error", g->notifications.net_array_error);
		draw_pair_option("Reports", g->notifications.reports);
		draw_pair_option("Transaction error / rate limit", g->notifications.transaction_rate_limit);	
	}
}
