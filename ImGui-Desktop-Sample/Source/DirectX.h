#pragma once

#include <d3d9.h>

namespace DirectX
{
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParams = {};

	bool CreateDevice();
	void ResetDevice();
	void DestroyDevice();
}