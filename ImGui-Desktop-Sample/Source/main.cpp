#include <Windows.h>

#include "ImGuiDesktop.h"
#include "GUI.h"

int __stdcall WinMain(HINSTANCE instance, HINSTANCE lastInstance, LPSTR lpCmdLine, int cmdShow)
{
	const char* name = "ImGui Desktop";

	if (!ImGuiDesktop::Initialize(instance, name))
	{
		UnregisterClass(name, instance);
		return EXIT_FAILURE;
	}

	auto active = true;

	while (active)
	{
		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				active = false;
		}

		if (!active)
			break;

		ImGuiDesktop::Begin();
		active = GUI::Render();
		ImGuiDesktop::End();
	}

	ImGuiDesktop::Release();

	return EXIT_SUCCESS;
}