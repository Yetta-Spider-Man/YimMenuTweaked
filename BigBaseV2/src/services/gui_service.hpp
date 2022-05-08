#pragma once
#include "views/view.hpp"

namespace big
{
	enum class tabs 
	{
		NONE,

		MAIN_LOCAL,
		MAIN_VEHICLE,
		MAIN_NETWORK,
		MAIN_SETTINGS,

		SELF,
		WEAPONS,
		TELEPORT,
		WEATHER,

		HANDLING,
		HANDLING_SEARCH,
		HANDLING_SAVED_PROFILE,
		HANDLING_MY_PROFILES,
		HANDLING_CURRENT_PROFILE,
		VEHICLE_OPTIONS,
		MOBILE,
		SPAWN,

		SESSION,
		ESP,
		PROTECTION,
		SPOOFING,

		HOTKEYS,
		COLORS,
		NOTIFICATIONS,
		DEBUG,

		PLAYER,
	};

	struct navigation_struct
	{
		const char name[32] = "";
		std::function<void()> func = nullptr;
		std::unordered_map<tabs, navigation_struct> sub_nav{};
	};

	class gui_service final
	{
		std::vector<tabs> current_tab{};
		bool switched_view = true;

		std::unordered_map<tabs, navigation_struct> nav = 
		{
			{ tabs::MAIN_LOCAL, { "Local", nullptr,
			{
				{ tabs::SELF, { "Player", view::self }},
				{ tabs::WEAPONS, { "Weapons", view::weapons }},
				{ tabs::TELEPORT, { "Teleport", view::teleport }},
				{ tabs::WEATHER, { "Weather", view::weather }},
			}}},

			{ tabs::MAIN_VEHICLE, {"Vehicle", nullptr,
			{
				{ tabs::VEHICLE_OPTIONS, { "Options", view::vehicle_options }},
				{ tabs::MOBILE, { "Mobile", view::mobile }},
				{ tabs::SPAWN, { "Spawn", view::spawn }},

				{ tabs::HANDLING, {"Handling", nullptr,
				{
					{ tabs::HANDLING_CURRENT_PROFILE, {"Current Profile", view::handling_current_profile } },
					{ tabs::HANDLING_MY_PROFILES, {"My Profiles", view::handling_my_profiles } },
					{ tabs::HANDLING_SAVED_PROFILE, {"Saved Profiles", view::handling_saved_profiles } },
					{ tabs::HANDLING_SEARCH, {"Search Handling", view::handling_search } },
				}}},
			}}},

			{ tabs::MAIN_NETWORK, { "Network", nullptr,
			{
				{ tabs::SESSION, { "Session", view::session }},
				{ tabs::ESP, { "ESP", view::esp }},
				{ tabs::PROTECTION, { "Protection", view::protection }},
				{ tabs::SPOOFING, { "Spoofing", view::spoofing }},
			}}},

			{ tabs::MAIN_SETTINGS, { "Settings", nullptr,
			{
				{ tabs::HOTKEYS, { "Hotkeys", view::hotkeys }},
				{ tabs::COLORS, { "Colors", view::colors }},
				{ tabs::NOTIFICATIONS, { "Notifications", view::notification_options }},
				{ tabs::DEBUG, { "Debug", view::debug }},
			}}},

			{ tabs::PLAYER, { "", view::view_player } }
		};

	public:
		gui_service();
		virtual ~gui_service();

		int nav_ctr = 0;

		navigation_struct* get_selected();
		std::vector<tabs> get_selected_tab();
		bool has_switched_view();
		void set_selected(tabs);
		void set_nav_size(int);
		void increment_nav_size();
		void reset_nav_size();
		std::unordered_map<tabs, navigation_struct> get_navigation();
	};

	inline gui_service* g_gui_service{};
}
