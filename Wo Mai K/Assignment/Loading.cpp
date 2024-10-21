#include "Loading.h"

Loading::Loading(DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture, GameStateManager& _gameStateManager) : directx(_directx), audio(_audio), player(_player), texture(_texture), gameStateManager(_gameStateManager){}


void Loading::CreateLoadingTexture(DirectX& directx) {
	D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/Loading.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &loadingTexture);
}

void Loading::DrawLoadingTexture(DirectX& directx) {
	D3DXMatrixTransformation2D(&loadingMat, NULL, 0.0, &loadingScalling, &loadingCenter, loadingRotation, &loadingPosition);
	directx.spriteBrush->SetTransform(&loadingMat);
	directx.spriteBrush->Draw(loadingTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Loading::ClearLoadingTexture() {
	loadingTexture->Release();
	loadingTexture = NULL;
}

//================================================================================================================================================================//

RECT Loading::FontRect(D3DXVECTOR2 textPosition, int textWidth, int textHeight) {
	fontRect.left = textPosition.x;
	fontRect.right = textPosition.x + textWidth;
	fontRect.top = textPosition.y;
	fontRect.bottom = textPosition.y + textHeight;
	return fontRect;
}

void Loading::DrawFont(DirectX& directx) {

	string loadingPercentageString = "Loading Forever...... " + to_string(loadingPercentage) + "%";
	FontRect(fontPosition, fontWidth, fontHeight);
	D3DXMatrixTransformation2D(&fontMat, NULL, 0.0, &fontScalling, NULL, NULL, NULL);
	directx.spriteBrush->SetTransform(&fontMat);
	directx.arialFont->DrawText(directx.spriteBrush, loadingPercentageString.c_str(), -1, &fontRect, 0, D3DCOLOR_XRGB(255, 255, 255));
}

//================================================================================================================================================================//

void Loading::DrawLine(DirectX& directx) {
	D3DXVECTOR2 loadingBar[] = { loadingBarPosition,
								{loadingBarPosition.x + loadingBarSize.x, loadingBarPosition.y},
								{loadingBarPosition.x + loadingBarSize.x, loadingBarPosition.y + loadingBarSize.y},
								{loadingBarPosition.x, loadingBarPosition.y + loadingBarSize.y},
								loadingBarPosition };

	directx.line->Draw(loadingBar, 5, D3DCOLOR_XRGB(255, 255, 255));
}

//================================================================================================================================================================//

void Loading::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
	audio.LoadSoundLoading();
	audio.PlayTalkSound();
	CreateLoadingTexture(directx);
	loadingPosition = loadingBarPosition;
	fontPosition = { loadingPosition.x, loadingPosition.y - fontHeight };
}

void Loading::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {


	if (loadingPercentage < 100) {
		loadingPosition.x += loadingSpeed;
		loadingPercentage = 100 - (((loadingBarSize.x - loadingPosition.x + loadingWidth) / loadingBarSize.x) * 100);
	}

	if (loadingPosition.x >= (loadingBarPosition.x + loadingBarSize.x - loadingWidth)) {
		loadingPosition.x = loadingBarPosition.x + loadingBarSize.x - loadingWidth;
		loadingPercentage = 100;
		loadingRotation += 0.5;

		pause++;
		if (pause >= pauseTimer) {
			pause = 0;
			cout << "Transition at Loading.Update() << Here" << endl;
			audio.ClearSound();
			gameStateManager.ChangeState(new Level1(gameStateManager, directx, audio, player, texture));
			//gameStateManager.GetCurrentState();
			//level.push(new Level1(directx, audio, player, texture));
			//level.top()->Initialize(directx, audio, player, texture);
		}
	}
}

void Loading::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {

	directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	directx.directXGPU->BeginScene();

	directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
	DrawLoadingTexture(directx);
	DrawFont(directx);
	directx.spriteBrush->End();

	//================================================================================================================================================================//

	directx.line->Begin();
	DrawLine(directx);
	directx.line->End();

	directx.directXGPU->EndScene();
	directx.directXGPU->Present(NULL, NULL, NULL, NULL);

}

void Loading::Clear(Player& player, Texture& texture) {
	ClearLoadingTexture();
}