#include "MainMenu.h"

MainMenu::MainMenu(GameStateManager& _gameStateManager, DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture): gameStateManager(_gameStateManager), directx(_directx), audio(_audio), player(_player), texture(_texture) {}

void MainMenu::CreateMenuBackground(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/MenuBackground.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &menuBackgroundTexture);
}

void MainMenu::DrawMenuBackground(DirectX& directx) {
	D3DXMatrixTransformation2D(&menuBackgroundMat, NULL, 0.0, &menuBackgroundScalling, NULL, 0.0f, NULL);
	directx.spriteBrush->SetTransform(&menuBackgroundMat);
	directx.spriteBrush->Draw(menuBackgroundTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::ClearMenuBackground() {
	menuBackgroundTexture->Release();
	menuBackgroundTexture = NULL;
}

//=====================================================================================================================//

RECT MainMenu::UIRect(D3DXVECTOR2 uiPosition, int uiTextureWidth, int uiTextureHeight, D3DXVECTOR2 scalling) {
	uiRect.left = uiPosition.x;
	uiRect.right = uiPosition.x + uiTextureWidth * scalling.x;
	uiRect.top = uiPosition.y;
	uiRect.bottom = uiPosition.y + uiTextureHeight * scalling.y;
	return uiRect;
}

void MainMenu::CreateButtton(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/UI.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &uiTexture);
}

void MainMenu::DrawStartButton(DirectX& directx) {
	UIRect(startButtonTexturePosition, startButtonWidth, startButtonHeight, buttonScalling);
	D3DXMatrixTransformation2D(&buttonMat, NULL, 0.0, &startButtonScalling, NULL, 0.0f, &startButtonPosition);
	directx.spriteBrush->SetTransform(&buttonMat);
	directx.spriteBrush->Draw(uiTexture, &uiRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::DrawExitButton(DirectX& directx) {
	UIRect(exitButtonTexturePosition, exitButtonWidth, exitButtonHeight, buttonScalling);
	D3DXMatrixTransformation2D(&buttonMat, NULL, 0.0, &buttonScalling, NULL, 0.0f, &exitButtonPosition);
	directx.spriteBrush->SetTransform(&buttonMat);
	directx.spriteBrush->Draw(uiTexture, &uiRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::DrawVolumeUpButton(DirectX& directx) {
	UIRect(volumeUpButtonTexturePosition, volumeButtonWidth, volumeButtonHeight, buttonScalling);
	D3DXMatrixTransformation2D(&buttonMat, NULL, 0.0, &buttonScalling, NULL, 0.0f, &volumeUpButtonPosition);
	directx.spriteBrush->SetTransform(&buttonMat);
	directx.spriteBrush->Draw(uiTexture, &uiRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::DrawVolumeDownButton(DirectX& directx) {
	UIRect(volumeDownButtonTexturePosition, volumeButtonWidth, volumeButtonHeight, buttonScalling);
	D3DXMatrixTransformation2D(&buttonMat, NULL, 0.0, &buttonScalling, NULL, 0.0f, &volumeDownButtonPosition);
	directx.spriteBrush->SetTransform(&buttonMat);
	directx.spriteBrush->Draw(uiTexture, &uiRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::DrawButton(DirectX& directx) {
	DrawStartButton(directx);
	DrawExitButton(directx);
	DrawVolumeUpButton(directx);
	DrawVolumeDownButton(directx);
}

void MainMenu::ClearButton() {
	uiTexture->Release();
	uiTexture = NULL;
}
//=====================================================================================================================//

void MainMenu::CreateMouseTexture(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/pointer.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &mouseTexture);
}

void MainMenu::DrawMouse(DirectX& directx) {
	D3DXMatrixTransformation2D(&mouseMat, NULL, 0.0, &mouseScalling, NULL, 0.0f, &mousePosition);
	directx.spriteBrush->SetTransform(&mouseMat);
	directx.spriteBrush->Draw(mouseTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::ClearMouseTexture() {
	mouseTexture->Release();
	mouseTexture = NULL;
}

//=====================================================================================================================//

bool MainMenu::MouseOnButton(RECT a, RECT b) {

	if (a.top > b.bottom)
		return false;
	if (a.bottom < b.top)
		return false;
	if (a.left > b.right)
		return false;
	if (a.right < b.left)
		return false;
	return true;
}

void MainMenu::MouseUpdate(Audio& audio) {

	mouseRect = UIRect(mousePosition, mouseWidth, mouseHeight, buttonScalling);
	startButton = UIRect(startButtonPosition, startButtonWidth, startButtonHeight, startButtonScalling);
	exitButton = UIRect(exitButtonPosition, exitButtonWidth, exitButtonHeight, buttonScalling);
	volumeUpButton = UIRect(volumeUpButtonPosition, volumeButtonWidth, volumeButtonHeight, buttonScalling);
	volumeDownButton = UIRect(volumeDownButtonPosition, volumeButtonWidth, volumeButtonHeight, buttonScalling);

	audio.Clicking();

	if ((leftMouseButton || rightMouseButton) && (!audio.mouseClickIsPlaying)) {

		audio.playClickSound();
	}

	if (MouseOnButton(mouseRect, startButton) && leftMouseButton) {
		cout << "Start" << endl;
		audio.ClearSound();
		gameStateManager.PushState(new Loading(directx, audio, player, texture, gameStateManager));

	}

	if (MouseOnButton(mouseRect, exitButton) && leftMouseButton) {
		cout << "Exit" << endl;
		PostQuitMessage(0);
	}

	if (MouseOnButton(mouseRect, volumeUpButton) && leftMouseButton) {
		audio.channel1->stop();
		audio.bgmVolume += 0.01;
		if (audio.bgmVolume > 1)
			audio.bgmVolume = 1;
	}

	if (MouseOnButton(mouseRect, volumeDownButton) && leftMouseButton) {
		audio.channel1->stop();
		audio.bgmVolume -= 0.01;
		if (audio.bgmVolume <= 0)
			audio.bgmVolume = 0;
	}
}

//=====================================================================================================================//

RECT MainMenu::TitleRect(D3DXVECTOR2 titlePosition, D3DXVECTOR2 titleSize) {
	titleRect.left = titlePosition.x;
	titleRect.right = titlePosition.x + titleSize.x;
	titleRect.top = titlePosition.y;
	titleRect.bottom = titlePosition.y + titleSize.y;
	return titleRect;
}

void MainMenu::DrawGameTitle(DirectX& directx) {

	TitleRect(titlePosition, titleSize);
	D3DXMatrixTransformation2D(&titleMat, NULL, 0.0, &titleScalling, NULL, NULL, NULL);
	directx.spriteBrush->SetTransform(&titleMat);
	directx.tnmFont->DrawText(directx.spriteBrush, "Wo Mai K", -1, &titleRect, 0, D3DCOLOR_XRGB(255, 255, 255));
}

//=====================================================================================================================//

void MainMenu::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {

	audio.LoadSoundMenu();
	CreateMenuBackground(directx);
	CreateButtton(directx);
	CreateMouseTexture(directx);
}

void MainMenu::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {

	MouseUpdate(audio);
	audio.UpdateSound();

	audio.PlayingBGM();
	if (!audio.bgmIsPlaying) {
		audio.PlayBGM(audio.bgmVolume);
	}

}

void MainMenu::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {

	directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 192, 203), 1.0f, 0);
	directx.directXGPU->BeginScene();
	directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	DrawMenuBackground(directx);
	DrawGameTitle(directx);
	DrawButton(directx);
	DrawMouse(directx);

	directx.spriteBrush->End();
	directx.directXGPU->EndScene();
	directx.directXGPU->Present(NULL, NULL, NULL, NULL);
}

void MainMenu::Clear(Player& player, Texture& texture) {
	ClearMouseTexture();
	ClearButton();
	ClearMenuBackground();
}

