#pragma once

namespace big
{
	namespace freemode
	{
		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			std::string msg = "NETWORK_BAIL triggered!";

			if (g->notifications.debug.log)
				LOG(WARNING) << msg;

			if (g->notifications.debug.notify)
				g_notification_service->push_warning("NETWORK_BAIL", msg);

			src->set_return_value<BOOL>(FALSE);
		}

		inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src)
		{
			std::string msg = "NETWORK_CAN_BAIL triggered!";

			if (g->notifications.protection.log)
				LOG(WARNING) << msg;

			if (g->notifications.debug.notify)
				g_notification_service->push_warning("NETWORK_BAIL", msg);

			src->set_return_value<BOOL>(FALSE);
		}

		inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			//std::string msg = "NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA triggered!";

			//if (g->notifications.debug.log)
			//	LOG(WARNING) << msg;

			//if (g->notifications.debug.notify)
			//	g_notification_service->push_warning("NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA", msg);

			src->set_return_value<BOOL>(TRUE);
		}

		inline void NETWORK_SESSION_GET_KICK_VOTE(rage::scrNativeCallContext* src)
		{
			if (g->protections.vote_kick) //If you log any of this you get constantly spammed, not worth it.
				src->set_return_value<BOOL>(FALSE);
		}
	}
}