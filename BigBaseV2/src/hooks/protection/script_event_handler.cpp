#include "hooking.hpp"
#include "gta_util.hpp"

namespace big
{
	void format_string(std::string_view player_name, std::string_view protection_type, bool should_log, bool should_notify)
	{
		if (should_log)
			LOG(WARNING) << "BLOCKED_SCRIPT_EVENT";

		if (should_notify)
			g_notification_service->push_warning("Script Event Protection",fmt::format("From: {}\nEvent Type: {}", player_name.data(), protection_type.data()));
	}

	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;

		const auto hash = static_cast<eRemoteEvent>(args[0]);
		const auto player_name = player->get_name();

		const auto& notify = g->notifications.protection;

		switch (hash)
		{
		case eRemoteEvent::Bounty:
			if (g->protections.script_events.bounty)
			{
				format_string(player_name, "Bounty", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoBan:
			if (g->protections.script_events.ceo_ban)
			{
				format_string(player_name, "Ceo Ban", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoKick:
			if (g->protections.script_events.ceo_kick)
			{
				format_string(player_name, "Ceo Kick", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoMoney:
			if (g->protections.script_events.ceo_money)
			{
				format_string(player_name, "Ceo Money", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::ClearWantedLevel:
			if (g->protections.script_events.clear_wanted_level)
			{
				format_string(player_name, "Clear Wanted Level", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::FakeDeposit:
			if (g->protections.script_events.fake_deposit)
			{
				format_string(player_name, "Fake Deposit", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::ForceMission:
			if (g->protections.script_events.force_mission)
			{
				format_string(player_name, "Force Mission", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::GtaBanner:
			if (g->protections.script_events.gta_banner)
			{
				format_string(player_name, "GTA Banner", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::NetworkBail:
			if (g->protections.script_events.network_bail)
			{
				format_string(player_name, "Network Bail", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			if (g->protections.script_events.personal_vehicle_destroyed)
			{
				format_string(player_name, "Personal Vehicle Destroyed", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::RemoteOffradar:
			if (g->protections.script_events.remote_off_radar)
			{
				format_string(player_name, "Off Radar", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::RotateCam:
			if (g->protections.script_events.rotate_cam)
			{
				if (CNetworkPlayerMgr* player_mgr = gta_util::get_network_player_mgr(); player_mgr != nullptr)
					if (args[2] == player_mgr->m_local_net_player->m_player_id)
						format_string(player_name, "Rotate Cam", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::SendToCutscene:
			if (g->protections.script_events.send_to_cutscene)
			{
				format_string(player_name, "Send to Cutscene", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::SendToIsland:
			if (g->protections.script_events.send_to_island)
			{
				format_string(player_name, "Send to Island", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::SoundSpam:
			if (g->protections.script_events.sound_spam)
			{
				format_string(player_name, "Sound Spamn", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::Spectate:
			if (g->protections.script_events.spectate)
			{
				format_string(player_name, "Spectate", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::Teleport:
			if (g->protections.script_events.force_teleport)
			{
				format_string(player_name, "Apartment Invite", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::TransactionError:
			if (g->protections.script_events.transaction_error)
			{
				format_string(player_name, "Transaction Error", notify.log, notify.notify);

				return true;
			}
			break;
		case eRemoteEvent::VehicleKick:
			if (g->protections.script_events.vehicle_kick)
			{
				format_string(player_name, "Vehicle Kick", notify.log, notify.notify);

				return true;
			}
			break;
		}

		if (g->debug.script_event_logging)
		{
			LOG(INFO) << "== Begin of Script Event ==";
			LOG(INFO) << "Player: " << player->get_name();
			LOG(INFO) << "Hash/Arg #0: " << (int)hash;

			for (std::size_t i = 1; i < sizeof(args); i++)
				LOG(INFO) << "Arg #" << i << ": " << args[i];

			LOG(INFO) << "== End of Script Event ==";
		}

		return false;
	}
}