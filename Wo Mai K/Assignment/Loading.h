#pragma once

#include <string>
#include <sstream>

#include "Window.h"
#include "DirectX.h"
#include "Audio.h"
#include "GameState.h"

#include "GameStateManager.h"
#include "Level1.h"

class Loading : public GameState
{
public:

	Loading(DirectX& directx, Audio& audio, Player& player, Texture& texture, GameStateManager& gameStateManager);

	LPDIRECT3DTEXTURE9 loadingTexture = NULL;
	D3DXVECTOR2 loadingPosition;
	D3DXMATRIX loadingMat;
	D3DXVECTOR2 loadingScalling = D3DXVECTOR2(1.0f, 1.0f);
	float loadingRotation;
	int loadingWidth = 64;
	int loadingHeight = 64;
	D3DXVECTOR2 loadingCenter = D3DXVECTOR2(loadingWidth / 2, loadingHeight / 2);

	RECT fontRect;
	D3DXMATRIX fontMat;
	D3DXVECTOR2 fontScalling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 fontPosition;
	int fontWidth = 800;
	int fontHeight = 50;

	D3DXVECTOR2 loadingBarPosition = D3DXVECTOR2(100, 800);
	D3DXVECTOR2 loadingBarSize = D3DXVECTOR2(1720.0f, 64.0f);
	string loadingPercentageString;
	int loadingSpeed = 5;
	int loadingPercentage;
	int pause;
	int pauseTimer = 100;

	void CreateLoadingTexture(DirectX& directx);
	void DrawLoadingTexture(DirectX& directx);
	void ClearLoadingTexture();

	RECT FontRect(D3DXVECTOR2 textPosition, int textWidth, int textHeight);
	void DrawFont(DirectX& directx);

	void DrawLine(DirectX& directx);

	void Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
	void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) override;
	void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
	void Clear(Player& player, Texture& texture) override;

private:
	std::stack<GameState*> level;

	GameStateManager& gameStateManager;
	DirectX& directx;
	Audio& audio;
	Player& player;
	Texture& texture;
};

