#pragma once
#include "imgui.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/animator.hpp"
#include "gui/components/components.hpp"
#include "script.hpp"
#include "services/player_service.hpp"
#include "views/esp/view_esp.hpp"

namespace big
{
	class view
	{
		inline static animator window_animator = animator();
		inline static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav;

	public:
		static void root();

		static void heading();
		static void navigation();
		//static void player_navigation();
		static void active_view();

		static void self();
		static void teleport();
		static void weapons();
		static void weather();

		static void vehicle_options();
		static void mobile();
		static void spawn();

		static void handling_current_profile();
		static void handling_my_profiles();
		static void handling_saved_profiles();
		static void handling_search();

		static void session();
		static void esp();
		static void protection();
		static void spoofing();
	
		static void colors();
		static void hotkeys();
		static void notification_options();
		static void debug();
	
		static void view_player();
		static void players();

		static void notifications();

		static void always()
		{
			esp::draw();
			notifications();
		}
	};
}