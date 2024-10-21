#pragma once

#include "DirectX.h"
#include "Window.h"
#include <d3dx9.h>

class Texture
{

public:
	//Portal
	LPDIRECT3DTEXTURE9 portalTexture = NULL;
	D3DXMATRIX portalMat;
	D3DXVECTOR2 portalScalling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 portalPosition;
	RECT portalRect;
	int portalWidth = 128;
	int portalHeight = 128;

	//Background
	LPDIRECT3DTEXTURE9 backgroundTexture = NULL;
	D3DXMATRIX backgroundMat;
	D3DXVECTOR2 backgroundScalling = D3DXVECTOR2(3.0f, 3.5f);

	//D3DXVECTOR2 backgroundPosition = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 backgroundPosition1 = D3DXVECTOR2(0.0f, 640.0f);
	D3DXVECTOR2 backgroundPosition2 = D3DXVECTOR2(0.0f, 320.0f);
	D3DXVECTOR2 backgroundPosition3 = D3DXVECTOR2(0.0f, 0.0f);
	RECT backgroundRect;
	int backgroundWidth = 640;
	int backgroundHeight = 320;

	//Rock Platform	
	LPDIRECT3DTEXTURE9 rockPlatformTexture = NULL;
	LPDIRECT3DTEXTURE9 cloudPlatformTexture = NULL;
	D3DXMATRIX platformMat;
	D3DXVECTOR2 platformScaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 baseScaling = D3DXVECTOR2(20.0f, 10.0f);
	D3DXVECTOR2 platformPosition0;
	D3DXVECTOR2 platformPosition1;
	D3DXVECTOR2 platformPosition2;
	D3DXVECTOR2 platformPosition3;
	D3DXVECTOR2 platformPosition4;
	D3DXVECTOR2 platformPosition5;
	D3DXVECTOR2 platformPosition6;
	RECT platformRect;
	int platformTextureWidth = 128;
	int platformTextureHeight = 64;

	void InitializePlatformLevel1();
	void InitializePlatformLevel2();

	RECT BackgroundRect(D3DXVECTOR2 backgroundPosition);
	void CreateBackground(DirectX& directx);
	void DrawBackground(D3DXVECTOR2 backgroundPosition, DirectX& directx);

	RECT PlatformRect(D3DXVECTOR2 rockPosition);
	void CreateRockPlatform(DirectX& directx);
	void CreateCloudPlatform(DirectX& directx);
	void DrawPlatform(D3DXVECTOR2 platformPosition, D3DXVECTOR2 scaling, LPDIRECT3DTEXTURE9 platformTexture, DirectX& directx);

	RECT PortalRect(D3DXVECTOR2 portalPosition);
	void CreatePortal(DirectX& directx);
	void DrawPortal(D3DXVECTOR2 portalPosition, DirectX& directx);

	void ClearPortal();
	void ClearRockPlatform();
	void ClearCloudPlatform();
	void ClearBackground();


};

