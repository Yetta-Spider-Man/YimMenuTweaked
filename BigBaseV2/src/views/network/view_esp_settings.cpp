#include "views/view.hpp"

namespace big
{
	void view::esp()
	{
		ImGui::Checkbox("ESP enabled", &g->esp.enabled);

		if (g->esp.enabled)
		{
			ImGui::SliderFloat2("Global render distance", g->esp.global_render_distance, 0.f, 1500.f);

			ImGui::Checkbox("Tracers", &g->esp.tracer);
			if (g->esp.tracer)
				ImGui::SliderFloat2("Tracer render distance", g->esp.tracer_render_distance, g->esp.global_render_distance[0], g->esp.global_render_distance[1]);

			ImGui::Checkbox("Box ESP", &g->esp.box);
			if (g->esp.box)
				ImGui::SliderFloat2("Box render distance", g->esp.box_render_distance, g->esp.global_render_distance[0], g->esp.global_render_distance[1]);

			ImGui::Checkbox("Show player distance", &g->esp.distance);
			ImGui::Checkbox("Show player godmode", &g->esp.god);
			ImGui::Checkbox("Show player health", &g->esp.health);
			ImGui::Checkbox("Show player name", &g->esp.name);

			static ImVec4 col_esp = ImGui::ColorConvertU32ToFloat4(g->esp.color);
			static ImVec4 col_friend = ImGui::ColorConvertU32ToFloat4(g->esp.friend_color);

			if (ImGui::ColorEdit4("ESP color##esp_picker", (float*)&col_esp, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				g->esp.color = ImGui::ColorConvertFloat4ToU32(col_esp);
			
			if (ImGui::ColorEdit4("Friend ESP color##friend_picker", (float*)&col_friend, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				g->esp.friend_color = ImGui::ColorConvertFloat4ToU32(col_friend);
		}
	}
}
