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

		if (g->protections.script_events) //Replace dumb switch case with find function
		{
			switch (hash)
			{
			case eRemoteEvent::Bounty:
				format_string(player_name, "Bounty", notify.log, notify.notify);
				return true;

			case eRemoteEvent::CeoBan:
				format_string(player_name, "Ceo Ban", notify.log, notify.notify);
				return true;

			case eRemoteEvent::CeoKick:
				format_string(player_name, "Ceo Kick", notify.log, notify.notify);
				return true;

			case eRemoteEvent::CeoMoney:
				format_string(player_name, "Ceo Money", notify.log, notify.notify);
				return true;

			case eRemoteEvent::ClearWantedLevel:
				format_string(player_name, "Clear Wanted Level", notify.log, notify.notify);

				return true;

			case eRemoteEvent::FakeDeposit:
				format_string(player_name, "Fake Deposit", notify.log, notify.notify);

				return true;

			case eRemoteEvent::ForceMission:
				format_string(player_name, "Force Mission", notify.log, notify.notify);

				return true;

			case eRemoteEvent::GtaBanner:
				format_string(player_name, "GTA Banner", notify.log, notify.notify);

				return true;

			case eRemoteEvent::NetworkBail:
				format_string(player_name, "Network Bail", notify.log, notify.notify);

				return true;

			case eRemoteEvent::PersonalVehicleDestroyed:
				format_string(player_name, "Personal Vehicle Destroyed", notify.log, notify.notify);

				return true;

			case eRemoteEvent::RemoteOffradar:
				format_string(player_name, "Off Radar", notify.log, notify.notify);

				return true;

			case eRemoteEvent::RotateCam:
				if (CNetworkPlayerMgr* player_mgr = gta_util::get_network_player_mgr(); player_mgr != nullptr)
					if (args[2] == player_mgr->m_local_net_player->m_player_id)
						format_string(player_name, "Rotate Cam", notify.log, notify.notify);

				return true;

			case eRemoteEvent::SendToCutscene:
				format_string(player_name, "Send to Cutscene", notify.log, notify.notify);

				return true;

			case eRemoteEvent::SendToIsland:
				format_string(player_name, "Send to Island", notify.log, notify.notify);

				return true;

			case eRemoteEvent::SoundSpam:
				format_string(player_name, "Sound Spamn", notify.log, notify.notify);

				return true;

			case eRemoteEvent::Spectate:
				format_string(player_name, "Spectate", notify.log, notify.notify);

				return true;

			case eRemoteEvent::Teleport:
				format_string(player_name, "Apartment Invite", notify.log, notify.notify);

				return true;

			case eRemoteEvent::TransactionError:
				format_string(player_name, "Transaction Error", notify.log, notify.notify);

				return true;

			case eRemoteEvent::VehicleKick:
				format_string(player_name, "Vehicle Kick", notify.log, notify.notify);

				return true;
			}
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