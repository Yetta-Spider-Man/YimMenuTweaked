#include "api/api.hpp"
#include "backend.hpp"
#include "fiber_pool.hpp"
#include "looped/looped.hpp"
#include "script.hpp"
#include "thread_pool.hpp"

namespace big
{
	void backend::loop()
	{
		g->attempt_save();

		backend_engine::system_update_pointers();

		if (g_local_player != nullptr)
		{
			g_thread_pool->push([]
			{
				CPlayerInfo* player_info = g_local_player->m_player_info;
				rage::netPlayerData& netData = player_info->m_net_player_data;
			});
		}

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::hud_transition_state();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_vehicle::rgb::synced_fade();
			backend_vehicle::rgb::synced_spasm();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_self::tunables::no_idle_kick();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_self::free_cam();
			backend_self::godmode();
			backend_self::off_radar();
			backend_self::police();
			backend_self::fast_run();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::system_local_time();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_network::player_never_wanted();
			backend_network::player_spectate();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_self::noclip();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_self::weapons::ammo_special_type();
			backend_self::weapons::cage_gun();
			backend_self::weapons::delete_gun();
			backend_self::weapons::force_crosshairs();
			backend_self::weapons::gravity_gun();
			backend_self::weapons::increased_damage();
			backend_self::weapons::infinite_ammo();
			backend_self::weapons::no_spread();
			backend_self::weapons::repair_gun();
			backend_self::weapons::steal_vehicle_gun();
			backend_self::weapons::vehicle_gun();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::vehicle_despawn_bypass();
			backend_vehicle::godmode();
			backend_vehicle::horn_boost();
			backend_vehicle::rainbow_paint();
			backend_vehicle::speedo_meter();
			backend_vehicle::auto_repair();

		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_vehicle::ls_customs();

		}QUEUE_JOB_END_CLAUSE
	}
}