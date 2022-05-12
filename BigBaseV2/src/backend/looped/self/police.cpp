#include "backend/looped/looped.hpp"

namespace big
{
	void backend_self::police()
	{
		auto playerInfo = g_local_player->m_player_info;

		if (g_local_player == nullptr || playerInfo == nullptr)
			return;

		if (g->self.never_wanted)
			playerInfo->m_wanted_level = 0;
		else if (g->self.force_wanted_level)
			playerInfo->m_wanted_level = g->self.wanted_level;
	}
}