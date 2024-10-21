#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Window.h"

class DirectX
{
public:
	Window window;

	//Direct3D object pointer
	IDirect3DDevice9* directXGPU;
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	LPD3DXSPRITE spriteBrush = NULL;
	LPD3DXFONT arialFont = NULL;
	LPD3DXFONT tnmFont = NULL;;
	LPD3DXLINE line = NULL;

	//Direct3D device pointer	
	D3DPRESENT_PARAMETERS d3dPP;

	HRESULT hr;
	void CreateDirectX(Window& window);
	void CleanUpDirectX();

	void CreateSpriteBrush();
	void ClearSpriteBrush();

	void CreateArialFont();
	void CreateTNMFont();
	void CreateFont();
	void ClearFont();

	void CreateLine();
	void ClearLine();



};
