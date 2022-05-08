#include "fiber_pool.hpp"
#include "views/view.hpp"
#include "util/session.hpp"
#include "util/entity.hpp"

namespace big
{
	//Todo: make this look pretty
	void view::weather()
	{
		ImGui::Checkbox("Override time", &g->session.override_time);

		if (g->session.override_time)
		{
			ImGui::SliderInt("Hour", &g->session.custom_time.hour, 0, 23);
			ImGui::SliderInt("Minute", &g->session.custom_time.minute, 0, 59);
			ImGui::SliderInt("Second", &g->session.custom_time.second, 0, 59);
		}

		if (ImGui::Button("Clear weather override"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				MISC::CLEAR_OVERRIDE_WEATHER();
			}
			QUEUE_JOB_END_CLAUSE
		}

		ImGui::Text("Override weather:");

		if (ImGui::ListBox("", &g->session.local_weather, session::weathers, 15))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				session::local_weather();
			}
			QUEUE_JOB_END_CLAUSE

			ImGui::ListBoxFooter();
		}
	}
}