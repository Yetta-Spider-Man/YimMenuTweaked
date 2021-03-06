#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };
	static Entity ent;

	void backend_self::weapons::special::steal_vehicle_gun()
	{
		bool bStealVehicleGun = g->weapons.custom_weapon == CustomWeapon::STEAL_VEHICLE_GUN;

		if (bStealVehicleGun)
		{
			Ped player = PLAYER::PLAYER_PED_ID();

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::GET_PLAYER_INDEX(), true);

				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					if (entity::raycast(&ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
						{
							for (size_t i = 0; i < 8 && !VEHICLE::IS_VEHICLE_SEAT_FREE(ent, -1, 0); i++)
							{
								Ped ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ent, -1, 0);
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

								script::get_current()->yield();
							}

							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), ent, -1);
						}
						//else 
							//g_notification_service->push_warning("Weapons", "Entity is not a vehicle.");
					}
					//else 
						//g_notification_service->push_warning("Weapons", "No entity found.");
				}
			}
		}
	}
}