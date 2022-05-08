#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	void view::spoofing()
	{ 
		components::small_text("To spoof any of the below credentials you need to reconnect with the lobby.");

		components::small_text("Username");

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
		QUEUE_JOB_END_CLAUSE

		ImGui::Checkbox("Spoof username", &g->spoofing.spoof_username);

		static char name[20];
		strcpy_s(name, sizeof(name), g->spoofing.username.c_str());

		ImGui::Text("New username:");
		ImGui::InputText("##username_input", name, sizeof(name));

		if (name != g->spoofing.username)
			g->spoofing.username = std::string(name);

		ImGui::Separator();

		components::small_text("IP address");

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
		QUEUE_JOB_END_CLAUSE

		ImGui::Checkbox("Spoof IP", &g->spoofing.spoof_ip);

		ImGui::Text("New IP address:");
		ImGui::DragInt4("##ip_fields", g->spoofing.ip_address, 0, 255);

		ImGui::Separator();

		components::small_text("Rockstar ID");

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
		QUEUE_JOB_END_CLAUSE

		ImGui::Checkbox("Spoof RSID", &g->spoofing.spoof_rockstar_id);

		ImGui::Text("New RSID:");
		ImGui::InputScalar("##rockstar_id_input", ImGuiDataType_U64, &g->spoofing.rockstar_id);

		ImGui::Separator();

		ImGui::Checkbox("Spoof chat censorhip", &g->spoofing.spoof_chat_censor);
	}
}
