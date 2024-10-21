#include "Win.h"

Win::Win(GameStateManager& gameStateManager, DirectX& directx, Audio& audio, Player& player, Texture& texture) : gameStateManager(gameStateManager), directx(directx), audio(audio), player(player), texture(texture) {}


RECT Win::WinRect(D3DXVECTOR2 position, D3DXVECTOR2 size) {
	winRect.left = position.x;
	winRect.right = position.x + size.x;
	winRect.top = position.y;
	winRect.bottom = position.y + size.y;
	return winRect;
}

//==============================================================================================================================================================//

void Win::DrawGgez(DirectX& directx) {
	WinRect(ggezPosition, ggezSize);
	D3DXMatrixTransformation2D(&ggezMat, NULL, 0.0, NULL, NULL, NULL, NULL);
	directx.spriteBrush->SetTransform(&ggezMat);
	directx.tnmFont->DrawText(directx.spriteBrush, "GG EZ", -1, &winRect, 0, D3DCOLOR_XRGB(0, 0, 0));
}

//==============================================================================================================================================================//

void Win::CreateExitTexture(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/UI.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &buttonTexture);
}

void Win::DrawExitTexture(DirectX& directx) {

	exitTextureRect = WinRect(exitTexturePosition, winExitButtonSize);
	D3DXMatrixTransformation2D(&winExitMat, NULL, 0.0, &winScalling, NULL, 0.0f, &winExitButtonPosition);
	directx.spriteBrush->SetTransform(&winExitMat);
	directx.spriteBrush->Draw(buttonTexture, &exitTextureRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Win::ClearExitTexture() {
	buttonTexture->Release();
	buttonTexture = NULL;
}

//==============================================================================================================================================================//

void Win::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
	audio.LoadSoundWin();
	CreateExitTexture(directx);
	audio.PlayWin(0.3);
}

void Win::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {

	audio.UpdateSound();

	audio.PlayingBGM();
	if (!audio.bgmIsPlaying) {
		audio.PlayBGM(audio.bgmVolume);
	}

	WinRect(ggezPosition, ggezSize);
	ggezPosition += ggezVelocity;

	if (ggezPosition.y < 0 || ggezPosition.y > window.windowHeight - ggezSize.y) {
		ggezVelocity.y *= -1;
	}
	if (ggezPosition.x < 0 || ggezPosition.x > window.windowWidth - ggezSize.x) {
		ggezVelocity.x *= -1;
	}

	winExitButton = WinRect(winExitButtonPosition, winExitButtonSize);

	audio.Clicking();
}

void Win::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
	directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(192, 192, 192), 1.0f, 0);
	directx.directXGPU->BeginScene();
	directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	DrawGgez(directx);
	DrawExitTexture(directx);

	directx.spriteBrush->End();
	directx.directXGPU->EndScene();
	directx.directXGPU->Present(NULL, NULL, NULL, NULL);
}

void Win::Clear(Player& player, Texture& texture) {
	ClearExitTexture();
}
