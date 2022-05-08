#include "views/view.hpp"
#include "core/data/speedo_meters.hpp"
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
		ImGui::SameLine();
		ImGui::BeginGroup();
        
		if (ImGui::TreeNode("Paint"))
		{
			ImGui::ListBox("RGB Type", &g->vehicle.rainbow_paint, vehicle::rgb_types, 3);

			if (g->vehicle.rainbow_paint)
				ImGui::SliderInt("RGB Speed", &g->rgb.speed, 1, 10);

			ImGui::TreePop();
		}

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Los Santos Customs");

		components::button("Start Los Santos Customs", [] 
		{
			g->vehicle.ls_customs = true;
		});

		ImGui::Separator();

		components::small_text("Speedo Meter");

		SpeedoMeter selected = g->vehicle.speedo_meter.type;

		ImGui::Text("Type:");
		if (ImGui::BeginCombo("###speedo_type", speedo_meters[(int)selected].name))
		{
			for (const speedo_meter& speedo : speedo_meters)
			{
				if (ImGui::Selectable(speedo.name, speedo.id == selected))
					g->vehicle.speedo_meter.type = speedo.id;

				if (speedo.id == selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::Text("Position");

		float pos[2];
		pos[0] = g->vehicle.speedo_meter.x;
		pos[1] = g->vehicle.speedo_meter.y;

		if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
		{
			g->vehicle.speedo_meter.x = pos[0];
			g->vehicle.speedo_meter.y = pos[1];
		}

		ImGui::Checkbox("Left Sided", &g->vehicle.speedo_meter.left_side);
	}
}