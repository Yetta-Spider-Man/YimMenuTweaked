#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	static float run_speed = 10.f;
	static float run_cap = 100.f;
	static bool super_run_state = false;

	void backend_self::fast_run()
	{
		Player player = PLAYER::PLAYER_ID();

		if (g->self.fast_run)
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.45f);
		else
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.f);
	}
}