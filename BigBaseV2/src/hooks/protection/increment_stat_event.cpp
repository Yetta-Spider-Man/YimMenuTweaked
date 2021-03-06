#include "hooking.hpp"
#include "util/find.hpp"

namespace big
{
	const uint32_t blocked_stat[] =
	{
		RAGE_JOAAT("MPPLY_BECAME_CHEATER_NUM"),RAGE_JOAAT("MPPLY_GRIEFING"),RAGE_JOAAT("MPPLY_VC_ANNOYINGME"),RAGE_JOAAT("MPPLY_VC_HATE"),RAGE_JOAAT("MPPLY_TC_ANNOYINGME"),RAGE_JOAAT("MPPLY_TC_HATE"),
		RAGE_JOAAT("MPPLY_OFFENSIVE_LANGUAGE"),RAGE_JOAAT("MPPLY_OFFENSIVE_TAGPLATE"),RAGE_JOAAT("MPPLY_OFFENSIVE_UGC"),RAGE_JOAAT("MPPLY_BAD_CREW_NAME"),
		RAGE_JOAAT("MPPLY_BAD_CREW_MOTTO"),RAGE_JOAAT("MPPLY_BAD_CREW_STATUS"),RAGE_JOAAT("MPPLY_BAD_CREW_EMBLEM"),RAGE_JOAAT("MPPLY_GAME_EXPLOITS"),RAGE_JOAAT("MPPLY_EXPLOITS"),
		RAGE_JOAAT("MPPLY_DM_CHEAT_START"),RAGE_JOAAT("MPPLY_DM_CHEAT_END"),RAGE_JOAAT("MPPLY_DM_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_RACE_CHEAT_START"),RAGE_JOAAT("MPPLY_RACE_CHEAT_END"),
		RAGE_JOAAT("MPPLY_RACE_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_MC_CHEAT_START"),RAGE_JOAAT("MPPLY_MC_CHEAT_END"),RAGE_JOAAT("MPPLY_MC_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_MGAME_CHEAT_START"),
		RAGE_JOAAT("MPPLY_MGAME_CHEAT_END"),RAGE_JOAAT("MPPLY_MGAME_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_VOTED_OUT"),RAGE_JOAAT("MPPLY_VOTED_OUT_DELTA"),RAGE_JOAAT("MPPLY_VOTED_OUT_QUIT"),
		RAGE_JOAAT("MPPLY_CAP_CHEAT_START"),RAGE_JOAAT("MPPLY_CAP_CHEAT_END"),RAGE_JOAAT("MPPLY_CAP_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_SUR_CHEAT_START"),RAGE_JOAAT("MPPLY_SUR_CHEAT_END"),
		RAGE_JOAAT("MPPLY_SUR_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_LTS_CHEAT_START"),RAGE_JOAAT("MPPLY_LTS_CHEAT_END"),RAGE_JOAAT("MPPLY_LTS_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_PARA_CHEAT_START"),
		RAGE_JOAAT("MPPLY_PARA_CHEAT_END"),RAGE_JOAAT("MPPLY_PARA_CHEAT_QUIT"),RAGE_JOAAT("MPPLY_FMEVN_CHEAT_START"),RAGE_JOAAT("MPPLY_FMEVN_CHEAT_END"),RAGE_JOAAT("MPPLY_FMEVN_CHEAT_QUIT"),
		RAGE_JOAAT("MPPLY_ISPUNISHED"), RAGE_JOAAT("MPPLY_OVERALL_CHEAT"), RAGE_JOAAT("MPPLY_OVERALL_BADSPORT")
	};

	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender, int64_t a3)
	{
		auto stat = net_event->m_stat;

		if (g->protections.stats)
		{
			if (FIND(stat, blocked_stat))
			{
				const std::string report = fmt::format("From: {}", sender->get_name());

				if (g->notifications.protection.log)
					LOG(INFO) << "Blocked report; " << report;

				if (g->notifications.protection.notify)
					g_notification_service->push_warning("BLOCKED REPORT", report);
			}
		}

		return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event, sender, a3);
	}
}