#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void backend_self::weapons::force_crosshairs()
	{
		if (g->weapons.force_crosshairs) {
			HUD::SHOW_HUD_COMPONENT_THIS_FRAME(14 /*RETICLE*/);
		}
	}
}