#pragma once
#include "common.hpp"

namespace big
{
	class backend_engine
	{
	public:
		static void anticheat_bypass();
		static void system_update_pointers();
		static void hud_transition_state();
		static void system_local_time();
		static void vehicle_despawn_bypass();
	};

	class backend_network
	{
	public:
		static void player_never_wanted();
		static void player_spectate();
	};

	class backend_self
	{
	public:
		static void free_cam();
		static void godmode();
		static void noclip();
		static void off_radar();
		static void police();
		static void fast_run();

		class tunables
		{
		public:
			static void no_idle_kick(); //This should be protection
		};

		class weapons
		{
		public:
			static void force_crosshairs();
			static void ammo_special_type();
			static void increased_damage();
			static void infinite_ammo();
			static void no_spread();

			class special
			{
			public:
				static void repair_gun();
				static void steal_vehicle_gun();
				static void vehicle_gun();
				static void cage_gun();
				static void delete_gun();
				static void gravity_gun();
			};
		};
	};

	class backend_vehicle
	{
	public:
		static void godmode();
		static void horn_boost();
		static void ls_customs();
		static void auto_repair();
	};
}