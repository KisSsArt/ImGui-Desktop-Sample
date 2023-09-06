#include "ImGuiDesktop.h"

#include "Window.h"
#include "DirectX.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx9.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/imgui_internal.h>

using namespace Window;
using namespace DirectX;

void ImGuiDesktop::Install_ImGui()
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
	
	ImGui::StyleColorsLight();
}

void ImGuiDesktop::Uninstall_ImGui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiDesktop::Begin()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiDesktop::End()
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	//Handle loss of the D3D9 device
	const auto resl = device->Present(0, 0, 0, 0);
	if (resl == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		DirectX::ResetDevice();
}

bool ImGuiDesktop::Initialize(HINSTANCE instance, LPCTSTR className) noexcept
{
	Window::_CreateWindow(instance, className);

	if (!DirectX::CreateDevice())
		return false;

	Install_ImGui();

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);

	return true;
}

void ImGuiDesktop::Release() noexcept
{
	Uninstall_ImGui();
	DirectX::DestroyDevice();
	Window::_DestroyWindow();
}
