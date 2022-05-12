#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g->notifications.debug)& option)
	{
		ImGui::Text("%s", name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Log", &option.log);
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::PopID();
	}

	void view::notification_options()
	{
		draw_pair_option("Debug alerts", g->notifications.debug);
		draw_pair_option("Protection alerts", g->notifications.protection);
		draw_pair_option("Player alerts", g->notifications.players);
		draw_pair_option("Modder detection alerts", g->notifications.modder_detection);
		draw_pair_option("Misc", g->notifications.misc);
	}
}
