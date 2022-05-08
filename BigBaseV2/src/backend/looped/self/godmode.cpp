#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void looped::self_godmode()
	{
		Ped player = PLAYER::PLAYER_PED_ID();

		ENTITY::SET_ENTITY_INVINCIBLE(player, g->self.godmode);

		if (g->self.godmode)
		{
			entity::clean_ped(player);

			PED::SET_PED_CAN_RAGDOLL(player, !g->self.godmode);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(player, !g->self.godmode);
			PED::SET_PED_RAGDOLL_ON_COLLISION(player, !g->self.godmode);
		}
	}
}