#pragma once

#include <Windows.h>
#include <thread>
#include <d3d9.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx9.h"
#include "imgui/backends/imgui_impl_win32.h"

namespace ImGuiDesktop
{
	inline ImVec2 size(640, 480);

	void Install_ImGui();
	void Uninstall_ImGui();

	void Begin();
	void End();

	bool Initialize(HINSTANCE instance, LPCTSTR className) noexcept;
	void Release() noexcept;
}