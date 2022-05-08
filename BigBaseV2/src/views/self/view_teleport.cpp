#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport() 
	{
		components::button("Waypoint", [] 
		{
			teleport::to_waypoint();
		});

		components::button("Objective", [] 
		{
			static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };

			for (int i = 0; i < (sizeof(blips) / sizeof(*blips)); i++) 
			{
				if (teleport::to_blip(blips[i], 5)) 
					break;
			}
		});
	}
}