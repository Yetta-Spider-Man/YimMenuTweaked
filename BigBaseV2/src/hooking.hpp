#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/fwddec.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"
#include "vmt_hook.hpp"

namespace big
{
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);
		static void *convert_thread_to_fiber(void *param);

		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);

		static void set_warning_message_with_header(
			const char* entryHeader,
			const char* entryLine1,
			int instructionalKey,
			const char* entryLine2,
			bool p4,
			Any p5,
			Any* showBackground,
			Any* p7,
			bool p8,
			Any p9
		);

		static GtaThread* gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState gta_thread_tick(GtaThread* a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);

		static void network_player_mgr_shutdown(CNetworkPlayerMgr* _this);

		static bool net_array_handler(__int64 netArrayHandlerBaseMgr, CNetGamePlayer* a2, rage::datBitBuffer* datbitbuffer, unsigned int bytes_to_read, __int16 a5);

		static void player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player);
		static void player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player);

		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, int64_t a3);
		static bool is_dlc_present(Hash dlc_hash);

		static void received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* buffer);

		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);
		static bool send_net_info_to_lobby(rage::netPlayerData* player, int64_t a2, int64_t a3, DWORD* a4);

		static __int64* chat_receive(__int64 chat_pointer, __int64 unk2, __int64 peerId, const char* msg, char IsTeam);
		static int censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;

		WNDPROC m_og_wndproc = nullptr;
		detour_hook m_set_cursor_pos_hook;

		detour_hook m_run_script_threads_hook;
		detour_hook m_convert_thread_to_fiber_hook;

		detour_hook m_error_screen_hook;

		detour_hook m_gta_thread_start_hook;
		detour_hook m_gta_thread_tick_hook;
		detour_hook m_gta_thread_kill_hook;

		detour_hook m_network_player_mgr_shutdown_hook;

		detour_hook m_net_array_handler_hook;

		detour_hook m_player_has_joined_hook;
		detour_hook m_player_has_left_hook;

		detour_hook m_increment_stat_hook;
		detour_hook m_is_dlc_present_hook;

		detour_hook m_received_event_hook;

		detour_hook m_send_net_info_to_lobby;

		detour_hook m_chat_receive_hook;
		detour_hook m_censor_chat_text_hook;
	};

	inline hooking *g_hooking{};
}
