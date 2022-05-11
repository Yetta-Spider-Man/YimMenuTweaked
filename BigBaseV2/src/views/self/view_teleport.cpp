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
				teleport::to_objective();
			});
	}
}