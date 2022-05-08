#include "backend/looped/looped.hpp"

namespace big
{
	void backend_vehicle::is_targetable()
	{
		if (g_local_player && g_local_player->m_vehicle)
			g_local_player->m_vehicle->m_is_targetable = g->vehicle.is_targetable;
	}
}