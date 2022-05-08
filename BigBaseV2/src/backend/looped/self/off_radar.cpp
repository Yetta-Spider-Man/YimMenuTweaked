#include "backend/looped/looped.hpp"
#include "util/mobile.hpp"

namespace big
{
	void backend_self::off_radar()
	{
		if (g->self.off_radar)
			mobile::lester::off_radar(g->self.off_radar);
	}
}