#include "backend/looped/looped.hpp"

#include "natives.hpp"

#include "util/globals.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void backend_vehicle::auto_repair()
	{
		static ULONGLONG tick_1 = 0;
		ULONGLONG now = GetTickCount64();

		Ped ped = PLAYER::PLAYER_PED_ID();

		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		if (now - tick_1 > 1000) //One second delay to prevent vehicle seizures
		{
			if (!g->vehicle.auto_repair)
				return;

			if (vehicle::owns_vehicle())
				vehicle::repair(vehicle);

			tick_1 = now;
		}
	}
}