#pragma once

namespace big
{
	namespace freemode
	{
		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NETWORK_BAIL triggered";

			src->set_return_value<BOOL>(FALSE);
		}

		inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NETWORK_CAN_BAIL triggered";

			src->set_return_value<BOOL>(FALSE);
		}

		inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(TRUE);
		}
	}
}