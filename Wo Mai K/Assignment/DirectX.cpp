#include "DirectX.h"

void DirectX::CreateDirectX(Window& window) {

	ZeroMemory(&d3dPP, sizeof(d3dPP));

	d3dPP.Windowed = true;// false;//ture;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = window.windowWidth;
	d3dPP.BackBufferHeight = window.windowHeight;
	d3dPP.hDeviceWindow = window.g_hWnd;

	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window.g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &directXGPU);

}

void DirectX::CleanUpDirectX() {
	directXGPU->Release();
	directXGPU = NULL;
}

void DirectX::CreateSpriteBrush() {
	D3DXCreateSprite(directXGPU, &spriteBrush);
}

void DirectX::ClearSpriteBrush() {
	spriteBrush->Release();
	spriteBrush = NULL;
}

void DirectX::ClearFont() {
	arialFont->Release();
	arialFont = NULL;
}

void DirectX::CreateFont() {
	CreateArialFont();
	CreateTNMFont();
}

void DirectX::CreateArialFont() {
	D3DXCreateFont(directXGPU, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &arialFont);
}

void DirectX::CreateTNMFont() {
	D3DXCreateFont(directXGPU, 250, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Times New Roman", &tnmFont);
}

void DirectX::CreateLine() {
	D3DXCreateLine(directXGPU, &line);
}

void DirectX::ClearLine() {
	line->Release();
	line = NULL;
}
