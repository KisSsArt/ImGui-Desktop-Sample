#include "GUI.h"

#include "ImGuiDesktop.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>


bool GUI::Render() noexcept
{
	static ImGuiWindowFlags flags = { ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse };

	ImGui::SetNextWindowPos({ (float)0, (float)0 });
	ImGui::SetNextWindowSize(ImGuiDesktop::size);

	bool open = true;

	if (ImGui::Begin("ImGui Desktop", &open, flags))
	{
		ImGui::Button("Button", ImVec2(50, 50));
		ImGui::End();
	}

	return open;
}
