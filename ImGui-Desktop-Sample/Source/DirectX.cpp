#include "DirectX.h"

#include "Window.h"

#include <imgui/backends/imgui_impl_dx9.h>

#pragma comment(lib, "d3d9.lib")
#include "d3d9.h"
#include "d3dx9.h"
#pragma comment(lib, "D3dx9.lib")
#include <d3dx9tex.h>

bool DirectX::CreateDevice()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParams, sizeof(presentParams));

	presentParams.Windowed = TRUE;
	presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParams.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParams.EnableAutoDepthStencil = TRUE;
	presentParams.AutoDepthStencilFormat = D3DFMT_D16;
	presentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParams, &device) < 0)
	{
		DestroyDevice();
		return false;
	}


	return true;
}

void DirectX::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParams);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void DirectX::DestroyDevice()
{
	if (device) { device->Release(); device = nullptr; }

	if (d3d) { d3d->Release(); d3d = nullptr; }
}