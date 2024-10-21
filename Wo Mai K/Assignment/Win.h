#pragma once

#include <d3dx9.h>
#include <string>

#include"Window.h"
#include "DirectX.h"
#include "Audio.h"
#include "FrameTimer.h"
#include "MainMenu.h"

#include "GameState.h"
#include "GameStateManager.h"

class Win : public GameState
{
public:

	Win(GameStateManager& gameStateManager, DirectX& directx, Audio& audio, Player& player, Texture& texture);

	RECT winRect;
	D3DXVECTOR2 winScalling = D3DXVECTOR2(1.0f, 1.0f);

	D3DXMATRIX ggezMat;
	D3DXVECTOR2 ggezPosition = D3DXVECTOR2(200.0f, 10.0f);
	D3DXVECTOR2 ggezVelocity = D3DXVECTOR2(5.0f, 5.0f);
	D3DXVECTOR2 ggezSize = D3DXVECTOR2(675, 200);

	LPDIRECT3DTEXTURE9 buttonTexture = NULL;
	RECT winExitButton;
	RECT exitTextureRect;
	D3DXVECTOR2 winExitButtonPosition = D3DXVECTOR2(0, 900);
	D3DXVECTOR2 exitTexturePosition = D3DXVECTOR2(240.0f, 20.0f);
	D3DXVECTOR2 winExitButtonSize = D3DXVECTOR2(127, 166);
	D3DXMATRIX winExitMat;
	
	RECT WinRect(D3DXVECTOR2 textPosition, D3DXVECTOR2 size);

	void DrawGgez(DirectX& directx);

	void CreateExitTexture(DirectX& directx);
	void DrawExitTexture(DirectX& directx);
	void ClearExitTexture();

	void Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
	void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) override;
	void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
	void Clear(Player& player, Texture& texture);

private:
	GameStateManager& gameStateManager;
	DirectX& directx;
	Texture& texture;
	Player& player;
	Audio& audio;

};

