#pragma once

#include <Windows.h>
#include <imgui/imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter);

namespace Window
{
	inline HWND window = nullptr;
	inline WNDCLASS windowClass = { 0 };

	inline POINTS position = {};

	void _CreateWindow(HINSTANCE instance, LPCTSTR className);
	void _DestroyWindow();
}