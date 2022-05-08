#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastInvisibility = false;

	void backend_self::invisibility()
	{
		bool bInvisibility = g->self.invisibility;

		if (bInvisibility || (!bInvisibility && bInvisibility != bLastInvisibility))
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !g->self.invisibility, 0);

			bLastInvisibility = g->self.invisibility;
		}

		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			if (!g->self.invisibility)
			{
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PLAYER::PLAYER_PED_ID());
			}
		}
		else 
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}
	}
}
