#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	static constexpr float hornBoostSpeedDefault = 10.f;
	static float hornBoostSpeed = hornBoostSpeedDefault;
	static constexpr float hostBoostSpeedMax = 200.f;

	void backend_vehicle::horn_boost()
	{
		Player player = PLAYER::PLAYER_ID();
		Ped ped = PLAYER::PLAYER_PED_ID();

		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		if (!g->vehicle.horn_boost)
			return;

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN) && PLAYER::IS_PLAYER_PRESSING_HORN(player))
		{
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 79);
			}
		}
	}
}