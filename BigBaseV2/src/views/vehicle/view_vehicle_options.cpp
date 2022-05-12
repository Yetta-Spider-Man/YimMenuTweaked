#include "views/view.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::vehicle_options() 
	{
		ImGui::BeginGroup();

		ImGui::Checkbox("Godmode", &g->vehicle.god_mode);
		ImGui::Checkbox("Horn boost", &g->vehicle.horn_boost);
		ImGui::Checkbox("Auto repair", &g->vehicle.auto_repair);

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Los Santos Customs");

		components::button("Enter mod shop instantly", [] 
		{
			g->vehicle.ls_customs = true;
		});
	}
}