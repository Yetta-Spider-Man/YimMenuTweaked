#pragma once
#include "CAmmoInfo.hpp"
#include "enums.hpp"
#include "file_manager.hpp"
#include "imgui.h"

namespace big
{
	class menu_settings;
	inline menu_settings* g{};

	class menu_settings 
	{
		nlohmann::json default_options;
		nlohmann::json options;

		struct debug 
		{
			bool script_event_logging = false;
		};

		struct notifications
		{
			struct pair
			{
				bool log = true;
				bool notify = true;
			};

			pair debug{};
			pair protection{};
			pair players{};
			pair modder_detection{};
			pair misc{};
		};

		struct player 
		{
			int character_slot = 1;
			bool player_never_wanted = false;
			int set_level = 130;
			bool spectating = false;
		};

		struct protections 
		{
			bool script_events = true;
			bool game_events = true;
			bool chat = true;
			bool NET_ARRAY_HANDLER = true;
			bool TASK_VEHICLE_TEMP_ACTION = true;

			bool afk_kick = true;
			bool vote_kick = true;

			bool stats = true;
			bool rate_limit = true;

			bool freemode_terminated = false;
		};

		struct self {
			bool force_wanted_level = false;
			bool free_cam = false;
			bool godmode = false;
			bool never_wanted = false;
			bool noclip = false;
			bool off_radar = false;
			bool fast_run = false;
			int wanted_level = 0;
		};

		struct session
		{
			int local_weather = 0;
			bool override_time = {};
			bool override_weather = false;
			struct 
			{
				int hour{}, minute{}, second{}; 
			} custom_time;
		};

		struct settings 
		{
			struct hotkeys
			{
				bool editing_menu_toggle = false;
				int menu_toggle = VK_DELETE;
				int teleport_waypoint = 0;
			};

			hotkeys hotkeys{};
		};

		struct spawn
		{
			bool preview_vehicle = false;
			bool spawn_inside = false;
			bool spawn_maxed = false;
		}; 

		struct spoofing
		{
			bool spoof_username = false;
			std::string username = "";

			bool spoof_ip = true;
			int ip_address[4] = { 42, 42, 42, 42 };

			bool spoof_rockstar_id = false;
			uint64_t rockstar_id = 0;

			bool spoof_chat_censor = false;
		};

		struct vehicle 
		{
			bool auto_repair = false;
			bool god_mode = false;
			bool horn_boost = false;
			bool ls_customs = false; // don't save this to disk
			bool pv_teleport_into = false;
		};

		struct weapons 
		{
			struct ammo_special
			{
				bool toggle = false;
				eAmmoSpecialType type = eAmmoSpecialType::None;
			} ammo_special;

			CustomWeapon custom_weapon = CustomWeapon::NONE;
			bool force_crosshairs = false;
			bool infinite_ammo = false;
			float increased_damage = 1;
			bool no_spread = false;
			char vehicle_gun_model[12] = "bus";
		};

		struct window {
			bool debug = false;
			bool handling = false;
			bool log = false;
			bool main = true;
			bool users = true;
			bool player = false;

			ImU32 color = 3357612055;

			ImFont* font_title = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small = nullptr;

			bool switched_view = true;
		};

		struct esp
		{
			bool enabled = true;
			bool hide_self = true;
			float global_render_distance[2] = { 0.f, 600.f };
			float tracer_render_distance[2] = { 200.f, 600.f };
			float box_render_distance[2] = { 0.f, 150.f };
			bool tracer = true;
			float tracer_draw_position[2] = { 0.5f, 1.f };
			bool box = true;
			bool health = true;
			bool armor = true;
			bool god = true;
			bool distance = true;
			bool name = true;
			bool change_esp_color_from_dist = false;
			bool scale_health_from_dist = false;
			bool scale_armor_from_dist = false;
			float distance_threshold[2] = { 100.f, 200.f };
			ImU32 enemy_color = 4281479904;
			ImU32 enemy_near_color = 4283794943;
			ImU32 default_color = 4285713522;
			ImU32 friend_color = 4293244509;
		};

	public:
		int friend_count = 0;
		int player_count = 0;

		debug debug{};
		notifications notifications{};
		player player{};
		protections protections{};
		self self{};
		session session{};
		settings settings{};
		spawn spawn{};
		spoofing spoofing{};
		vehicle vehicle{};
		weapons weapons{};
		window window{};
		esp esp{};

		menu_settings(file save_file)
			: m_save_file(std::move(save_file))
		{
			g = this;
		}

		~menu_settings()
		{
			g = nullptr;
		}

		void from_json(const nlohmann::json& j)
		{
			this->notifications.debug.log = j["notifications"]["debug"]["log"];
			this->notifications.debug.notify= j["notifications"]["debug"]["notify"];
			this->notifications.protection.log = j["notifications"]["protection"]["log"];
			this->notifications.protection.notify = j["notifications"]["protection"]["notify"];
			this->notifications.players.log = j["notifications"]["players"]["log"];
			this->notifications.players.notify = j["notifications"]["players"]["notify"];
			this->notifications.modder_detection.log = j["notifications"]["modder_detection"]["log"];
			this->notifications.modder_detection.notify = j["notifications"]["modder_detection"]["notify"];
			this->notifications.misc.log = j["notifications"]["misc"]["log"];
			this->notifications.misc.notify = j["notifications"]["misc"]["notify"];

			/*this->protections.script_events = j["protections"]["script_events"];
			this->protections.game_events = j["protections"]["game_events"];
			this->protections.chat = j["protections"]["chat"];
			this->protections.NET_ARRAY_HANDLER = j["protections"]["NET_ARRAY_HANDLER"];
			this->protections.TASK_VEHICLE_TEMP_ACTION = j["protections"]["TASK_VEHICLE_TEMP_ACTION"];
			this->protections.afk_kick = j["protections"]["afk_kick"];
			this->protections.vote_kick = j["protections"]["vote_kick"];
			this->protections.stats = j["protections"]["stats"];
			this->protections.rate_limit = j["protections"]["rate_limit"];*/

			this->self.godmode = j["self"]["godmode"];
			this->self.never_wanted = j["self"]["never_wanted"];
			this->self.off_radar = j["self"]["off_radar"];
			this->self.fast_run = j["self"]["fast_run"];

			this->settings.hotkeys.menu_toggle = j["settings"]["hotkeys"]["menu_toggle"];

			this->spawn.preview_vehicle = j["spawn"]["preview_vehicle"];
			this->spawn.spawn_inside = j["spawn"]["spawn_inside"];
			this->spawn.spawn_maxed = j["spawn"]["spawn_maxed"];

			this->spoofing.spoof_ip = j["spoofing"]["spoof_ip"];
			this->spoofing.spoof_rockstar_id = j["spoofing"]["spoof_rockstar_id"];
			this->spoofing.spoof_username = j["spoofing"]["spoof_username"];
			this->spoofing.spoof_chat_censor = j["spoofing"]["spoof_chat_censor"];

			for (int i = 0; i < 4; i++)
				this->spoofing.ip_address[i] = j["spoofing"]["ip_address"].at(i);
			this->spoofing.rockstar_id = j["spoofing"]["rockstar_id"];
			this->spoofing.username = j["spoofing"]["username"];

			this->vehicle.auto_repair = j["vehicle"]["auto_repair"];
			this->vehicle.god_mode = j["vehicle"]["god_mode"];
			this->vehicle.horn_boost = j["vehicle"]["horn_boost"];
			this->vehicle.pv_teleport_into = j["vehicle"]["pv_teleport_into"];

			this->weapons.custom_weapon = (CustomWeapon)j["weapons"]["custom_weapon"];
			this->weapons.force_crosshairs = j["weapons"]["force_crosshairs"];
			this->weapons.infinite_ammo = j["weapons"]["infinite_ammo"];
			this->weapons.increased_damage = j["weapons"]["increased_damage"];
			this->weapons.no_spread = j["weapons"]["no_spread"];

			this->weapons.ammo_special.type = (eAmmoSpecialType)j["weapons"]["ammo_special"]["type"];
			this->weapons.ammo_special.toggle = j["weapons"]["ammo_special"]["toggle"];

			this->window.color = j["window"]["color"];
			this->window.debug = j["window"]["debug"];
			this->window.handling = j["window"]["handling"];
			this->window.log = j["window"]["log"];
			this->window.main = j["window"]["main"];
			this->window.users = j["window"]["users"];

			this->esp.enabled = j["esp"]["enabled"];
			this->esp.hide_self = j["esp"]["hide_self"];
			this->esp.enemy_color = j["esp"]["enemy_color"];
			this->esp.enemy_near_color = j["esp"]["enemy_near_color"];
			this->esp.default_color = j["esp"]["default_color"];
			this->esp.friend_color = j["esp"]["friend_color"];
			this->esp.box = j["esp"]["box"];
			this->esp.distance = j["esp"]["distance"];
			this->esp.god = j["esp"]["god"];
			this->esp.health = j["esp"]["health"];
			this->esp.armor = j["esp"]["armor"];
			this->esp.name = j["esp"]["name"];
			this->esp.change_esp_color_from_dist = j["esp"]["change_esp_color_from_dist"];
			this->esp.scale_health_from_dist = j["esp"]["scale_health_from_dist"];
			this->esp.scale_armor_from_dist = j["esp"]["scale_armor_from_dist"];
			for (int i = 0; i < 2; i++)
				this->esp.global_render_distance[i] = j["esp"]["global_render_distance"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.tracer_render_distance[i] = j["esp"]["tracer_render_distance"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.box_render_distance[i] = j["esp"]["box_render_distance"].at(i);
			this->esp.tracer = j["esp"]["tracer"];
			for (int i = 0; i < 2; i++)
				this->esp.tracer_draw_position[i] = j["esp"]["tracer_draw_position"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.distance_threshold[i] = j["esp"]["distance_threshold"].at(i);
		}

		nlohmann::json to_json()
		{
			constexpr auto return_notify_pair = [](const notifications::pair& notify_pair) -> auto
			{
				return nlohmann::json{
					{ "log", notify_pair.log },
					{ "notify", notify_pair.notify }
				};
			};

			return nlohmann::json{
				{
					"debug",
					{
						{ "script_event_logging", this->debug.script_event_logging }
					}
				},
				{
					"notifications", {
						{ "debug", return_notify_pair(g->notifications.debug) },
						{ "protection", return_notify_pair(g->notifications.protection) },
						{ "players", return_notify_pair(g->notifications.players) },
						{ "modder_detection", return_notify_pair(g->notifications.modder_detection) },
						{ "misc", return_notify_pair(g->notifications.misc) }
					}
				},
				/*{
					"protections", {
						{ "script_events", this->protections.script_events },
						{ "game_events", this->protections.game_events },
						{ "chat", this->protections.chat },
						{ "NET_ARRAY_HANDLER", this->protections.NET_ARRAY_HANDLER },
						{ "TASK_VEHICLE_TEMP_ACTION", this->protections.TASK_VEHICLE_TEMP_ACTION },
						{ "vote_kick", this->protections.vote_kick },
						{ "afk_kick", this->protections.afk_kick },
						{ "stats", this->protections.stats },
						{ "rate_limit", this->protections.rate_limit }
					}
				},*/
				{
					"self", {
						{ "godmode", this->self.godmode },
						{ "never_wanted", this->self.never_wanted },
						{ "off_radar", this->self.off_radar },
						{ "fast_run", this->self.fast_run }
					}
				},
				{
					"settings", {
						{ "hotkeys", {
								{ "menu_toggle", this->settings.hotkeys.menu_toggle }
							}
						}
					}
				},
				{
					"spawn", {
						{ "preview_vehicle", this->spawn.preview_vehicle },
						{ "spawn_inside", this->spawn.spawn_inside },
						{ "spawn_maxed", this->spawn.spawn_maxed}
					}
				},
				{
					"spoofing", {
						{ "spoof_ip", this->spoofing.spoof_ip },
						{ "spoof_rockstar_id", this->spoofing.spoof_rockstar_id },
						{ "spoof_username", this->spoofing.spoof_username },
						{ "spoof_chat_censor", this->spoofing.spoof_chat_censor },
						{ "ip_address", nlohmann::json::array({
							this->spoofing.ip_address[0],
							this->spoofing.ip_address[1],
							this->spoofing.ip_address[2],
							this->spoofing.ip_address[3] })
						},
						{ "rockstar_id", this->spoofing.rockstar_id },
						{ "username", this->spoofing.username }
					}
				},
				{
					"vehicle", {
						{ "auto_repair", this->vehicle.auto_repair },
						{ "god_mode", this->vehicle.god_mode },
						{ "horn_boost", this->vehicle.horn_boost },
						{ "pv_teleport_into", this->vehicle.pv_teleport_into },
					}
				},
				{
					"weapons", {
						{ "ammo_special", {
							{ "toggle", this->weapons.ammo_special.toggle },
							{ "type", (int)this->weapons.ammo_special.type },
								
							}
						},
						{ "custom_weapon", (int)this->weapons.custom_weapon },
						{ "force_crosshairs", this->weapons.force_crosshairs },
						{ "increased_damage", this->weapons.increased_damage },
						{ "infinite_ammo", this->weapons.infinite_ammo },
						{ "no_spread", this->weapons.no_spread }
					}
				},
				{
					"window", {
						{ "color", this->window.color },
						{ "debug", this->window.debug },
						{ "handling", this->window.handling },
						{ "log", this->window.log },
						{ "main", this->window.main },
						{ "users", this->window.users }
					}
				},
				{
					"esp", {
						{ "enabled", this->esp.enabled },
						{ "hide_self", this->esp.hide_self },
						{ "global_render_distance", nlohmann::json::array({
						this->esp.global_render_distance[0],
						this->esp.global_render_distance[1] })
						},
						{ "tracer_render_distance", nlohmann::json::array({
						this->esp.tracer_render_distance[0],
						this->esp.tracer_render_distance[1] })
						},
						{ "box_render_distance", nlohmann::json::array({
						this->esp.box_render_distance[0],
						this->esp.box_render_distance[1] })
						},
						{ "enemy_color", this->esp.enemy_color },
						{ "enemy_near_color", this->esp.enemy_near_color },
						{ "default_color", this->esp.default_color },
						{ "friend_color", this->esp.friend_color },
						{ "distance", this->esp.distance },
						{ "box", this->esp.box },
						{ "god", this->esp.god },
						{ "health", this->esp.health },
						{ "armor", this->esp.armor },
						{ "name", this->esp.name },
						{ "tracer", this->esp.tracer },
						{ "change_esp_color_from_dist", this->esp.change_esp_color_from_dist },
						{ "scale_health_from_dist", this->esp.scale_health_from_dist },
						{ "scale_armor_from_dist", this->esp.scale_armor_from_dist },
						{ "tracer_draw_position", nlohmann::json::array({
						this->esp.tracer_draw_position[0],
						this->esp.tracer_draw_position[1] })
						},
						{ "distance_threshold", nlohmann::json::array({
						this->esp.distance_threshold[0],
						this->esp.distance_threshold[1] })
						}
					}
				}
			};
		}

		void attempt_save()
		{
			const nlohmann::json& j = this->to_json();

			if (deep_compare(this->options, j, true))
				this->save();
		}
	
		bool load()
		{
			this->default_options = this->to_json();

			std::ifstream file(m_save_file.get_path());

			if (!file.is_open())
			{
				this->write_default_config();

				file.open(m_save_file.get_path());
			}

			try
			{
				file >> this->options;

				file.close();
			}
			catch (const std::exception&)
			{
				file.close();

				LOG(WARNING) << "Detected corrupt settings, writing default config...";

				this->write_default_config();

				return this->load();
			}

			const bool should_save = this->deep_compare(this->options, this->default_options);

			this->from_json(this->options);

			if (should_save)
			{
				LOG(INFO) << "Updating settings.";
				save();
			}

			return true;
		}

	private:
		file m_save_file;

		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false)
		{
			bool should_save = false;

			for (auto& e : default_settings.items())
			{
				const std::string& key = e.key();

				if (current_settings.count(key) == 0 || (compare_value && current_settings[key] != e.value()))
				{
					current_settings[key] = e.value();

					should_save = true;
				}
				else if (current_settings[key].is_object() && e.value().is_object())
				{
					if (deep_compare(current_settings[key], e.value(), compare_value))
						should_save = true;
				}
				else if (!current_settings[key].is_object() && e.value().is_object()) {
					current_settings[key] = e.value();

					should_save = true;
				}
			}

			return should_save;
		}

		bool save()
		{
			std::ofstream file(m_save_file.get_path(), std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}

		bool write_default_config()
		{
			std::ofstream file(m_save_file.get_path(), std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}
	};
}
