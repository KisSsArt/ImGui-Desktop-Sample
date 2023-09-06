#include "Window.h"

#include "ImGuiDesktop.h"
#include "DirectX.h"

#include <Windows.h>

using namespace DirectX;

LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (device && wideParameter != SIZE_MINIMIZED)
		{
			presentParams.BackBufferWidth = LOWORD(longParameter);
			presentParams.BackBufferHeight = HIWORD(wideParameter);
			DirectX::ResetDevice();
		}
		return 0;
	}
	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_LBUTTONDOWN: {
		Window::position = MAKEPOINTS(longParameter);
		return 0;
	}
	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = RECT{};
			GetWindowRect(Window::window, &rect);
			rect.left += points.x - Window::position.x;
			rect.top += points.y - Window::position.y;

			if (Window::position.x >= 0 &&
				Window::position.x <= presentParams.BackBufferWidth &&
				Window::position.y >= 0 &&
				Window::position.y <= presentParams.BackBufferHeight) //if you want to move only by the top put 30 or less
			{
				SetWindowPos(Window::window, HWND_TOPMOST, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
			}
		}
		return 0;
	}

	default:
		return DefWindowProcA(window, message, wideParameter, longParameter);
	}
	return 0;
}

void Window::_CreateWindow(HINSTANCE instance, LPCTSTR className)
{
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = instance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	windowClass.lpszClassName = className;

	RegisterClass(&windowClass);

	RECT screenRect;
	GetWindowRect(GetDesktopWindow(), &screenRect);
	int x = screenRect.right / 2 - ImGuiDesktop::size.x / 2;
	int y = screenRect.bottom / 2 - ImGuiDesktop::size.y / 2;

	window = CreateWindow(className, className, WS_POPUP, x, y, ImGuiDesktop::size.x, ImGuiDesktop::size.y, NULL, NULL, windowClass.hInstance, NULL);
}

void Window::_DestroyWindow()
{
	DestroyWindow(window);
	::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
}