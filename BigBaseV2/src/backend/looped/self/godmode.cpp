#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void backend_self::godmode()
	{
		const Ped player = PLAYER::PLAYER_PED_ID();

		if (g->self.godmode)
			entity::clean_ped(player);

		ENTITY::SET_ENTITY_INVINCIBLE(player, g->self.godmode);
		ENTITY::SET_ENTITY_INVINCIBLE(player, g->self.godmode);

		PED::SET_PED_CAN_RAGDOLL(player, !g->self.godmode);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(player, !g->self.godmode);
		PED::SET_PED_RAGDOLL_ON_COLLISION(player, !g->self.godmode);
	}
}