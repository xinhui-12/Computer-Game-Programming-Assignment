#include "Texture.h"

void Texture::InitializePlatformLevel1() {
	portalPosition = { 950.0f, 122.0f };
	platformPosition0 = { -100.0f, 950.0f };
	platformPosition1 = { 600.0f, 850.0f };
	platformPosition2 = { 900.0f, 750.0f };
	platformPosition3 = { 1150.0f, 650.0f };
	platformPosition4 = { 900.0f, 450.0f };
	platformPosition5 = { 650.0f, 350.0f };
	platformPosition6 = { 950.0f, 250.0f };
}

void Texture::InitializePlatformLevel2() {
	portalPosition = { 950.0f, 222.0f };
	platformPosition0 = { -150.0f, 950.0f };
	platformPosition1 = { 700.0f, 750.0f };
	platformPosition2 = { 1000.0f, 700.0f };
	platformPosition3 = { 1250.0f, 550.0f };
	platformPosition4 = { 750.0f, 550.0f };
	platformPosition5 = { 550.0f, 450.0f };
	platformPosition6 = { 950.0f, 350.0f };
}

//================================================================================================================================================//

void Texture::CreateBackground(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/Background.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &backgroundTexture);
}

RECT Texture::BackgroundRect(D3DXVECTOR2 backgroundPosition) {
	backgroundRect.left = backgroundPosition.x;
	backgroundRect.right = backgroundPosition.x + backgroundWidth;
	backgroundRect.top = backgroundPosition.y;
	backgroundRect.bottom = backgroundPosition.y + backgroundHeight;
	return backgroundRect;
}

void Texture::DrawBackground(D3DXVECTOR2 backgroundPosition, DirectX& directx) {
	BackgroundRect(backgroundPosition);
	D3DXMatrixTransformation2D(&backgroundMat, NULL, 0.0, &backgroundScalling, NULL, 0.0f, NULL);
	directx.spriteBrush->SetTransform(&backgroundMat);
	directx.spriteBrush->Draw(backgroundTexture, &backgroundRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

//================================================================================================================================================//

void Texture::CreateRockPlatform(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/rock.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &rockPlatformTexture);
}

void Texture::CreateCloudPlatform(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/cloud.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0),
		NULL, NULL, &cloudPlatformTexture);
}

RECT Texture::PlatformRect(D3DXVECTOR2 platformPosition) {
	platformRect.left = platformPosition.x;
	platformRect.right = platformPosition.x + platformTextureWidth * platformScaling.x;
	platformRect.top = platformPosition.y;
	platformRect.bottom = platformPosition.y + platformTextureHeight * platformScaling.y;
	return platformRect;
}

void Texture::DrawPlatform(D3DXVECTOR2 platformPosition, D3DXVECTOR2 platformScaling, LPDIRECT3DTEXTURE9 platformTexture, DirectX& directx) {
	D3DXMatrixTransformation2D(&platformMat, NULL, 0.0, &platformScaling, NULL, 0.0f, &platformPosition);
	directx.spriteBrush->SetTransform(&platformMat);
	directx.spriteBrush->Draw(platformTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

//================================================================================================================================================//

void Texture::CreatePortal(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/portal.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &portalTexture);
}

RECT Texture::PortalRect(D3DXVECTOR2 portalPosition) {
	portalRect.left = portalPosition.x;
	portalRect.right = portalPosition.x + portalWidth * portalScalling.x;
	portalRect.top = portalPosition.y;
	portalRect.bottom = portalPosition.y + portalHeight * portalScalling.y;
	return portalRect;
}

void Texture::DrawPortal(D3DXVECTOR2 portalPosition, DirectX& directx) {
	D3DXMatrixTransformation2D(&portalMat, NULL, 0.0, &portalScalling, NULL, 0.0f, &portalPosition);
	directx.spriteBrush->SetTransform(&portalMat);
	directx.spriteBrush->Draw(portalTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

//================================================================================================================================================//

void Texture::ClearPortal() {
	portalTexture->Release();
	portalTexture = NULL;
}

void Texture::ClearRockPlatform() {
	rockPlatformTexture->Release();
	rockPlatformTexture = NULL;
}

void Texture::ClearCloudPlatform() {
	cloudPlatformTexture->Release();
	cloudPlatformTexture = NULL;
}

void Texture::ClearBackground() {
	backgroundTexture->Release();
	backgroundTexture = NULL;
}





