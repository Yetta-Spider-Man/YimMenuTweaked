#include "backend/looped/looped.hpp"
#include "services/player_service.hpp"
#include "util/toxic.hpp"

namespace big
{
	void backend_network::player_never_wanted()
	{
		if (!(g->player.player_never_wanted && g_player_service->get_selected()->is_valid()))
			return;

		toxic::clear_wanted_player(g_player_service->get_selected()->id());
	}
}
