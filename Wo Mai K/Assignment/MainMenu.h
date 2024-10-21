#pragma once

#include <d3dx9.h>
#include <dinput.h>

#include "Window.h"
#include "DirectX.h"
#include "Audio.h"
#include "FrameTimer.h"
#include "GameState.h"

#include "GameStateManager.h"
#include "Loading.h"


class MainMenu : public GameState
{
public:

	MainMenu(GameStateManager& gameStateManager, DirectX& directx, Audio& audio, Player& player, Texture& texture);

	LPDIRECT3DTEXTURE9 menuBackgroundTexture = NULL;
	D3DXMATRIX menuBackgroundMat;
	D3DXVECTOR2 menuBackgroundScalling = D3DXVECTOR2(4.0f, 3.0f);

	LPDIRECT3DTEXTURE9 uiTexture = NULL;
	RECT uiRect;
	D3DXMATRIX buttonMat;
	D3DXVECTOR2 buttonScalling = D3DXVECTOR2(1.0f, 1.0f);

	D3DXVECTOR2 startButtonPosition = D3DXVECTOR2(600.0f, 200.0f);
	D3DXVECTOR2 startButtonTexturePosition = D3DXVECTOR2(10.0f, 10.0f);
	D3DXVECTOR2 startButtonScalling = D3DXVECTOR2(3.0f, 3.0f);
	RECT startButton;
	int startButtonWidth = 207;
	int startButtonHeight = 186;

	D3DXVECTOR2 exitButtonPosition = D3DXVECTOR2(0.0f, 900.0f);
	D3DXVECTOR2 exitButtonTexturePosition = D3DXVECTOR2(240.0f, 20.0f);
	RECT exitButton;
	int exitButtonWidth = 127;
	int exitButtonHeight = 166;

	D3DXVECTOR2 volumeUpButtonPosition = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 volumeDownButtonPosition = D3DXVECTOR2(0.0f, 70.0f);

	D3DXVECTOR2 volumeUpButtonTexturePosition = D3DXVECTOR2(407.0f, 29.0f);
	D3DXVECTOR2 volumeDownButtonTexturePosition = D3DXVECTOR2(408.0f, 100.0f);
	RECT volumeUpButton;
	RECT volumeDownButton;
	int volumeButtonWidth = 67;
	int volumeButtonHeight = 67;

	LPDIRECT3DTEXTURE9 mouseTexture = NULL;
	D3DXMATRIX mouseMat;
	D3DXVECTOR2 mouseScalling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 mousePosition = D3DXVECTOR2(500.0f, 500.0f);
	RECT mouseRect;
	int mouseWidth = 32;
	int mouseHeight = 32;
	bool leftMouseButton;
	bool rightMouseButton;

	RECT titleRect;
	D3DXMATRIX titleMat;
	D3DXVECTOR2 titlePosition = D3DXVECTOR2(300, 800) ;
	D3DXVECTOR2 titleSize = D3DXVECTOR2(1500, 300);
	D3DXVECTOR2 titleScalling = D3DXVECTOR2(1.0f, 1.0f);

	void CreateMouseTexture(DirectX& directx);
	void DrawMouse(DirectX& directx);
	void MouseUpdate(Audio& audio);
	void ClearMouseTexture();

	void CreateButtton(DirectX& directx);

	void DrawStartButton(DirectX& directx);
	void DrawExitButton(DirectX& directx);
	void DrawVolumeUpButton(DirectX& directx);
	void DrawVolumeDownButton(DirectX& directx);
	void DrawButton(DirectX& directx);
	void ClearButton();

	void CreateMenuBackground(DirectX& directx);
	void DrawMenuBackground(DirectX& directx);
	void ClearMenuBackground();

    RECT TitleRect(D3DXVECTOR2 titlePosition, D3DXVECTOR2 titleSize);
    void DrawGameTitle(DirectX& directx);

    RECT UIRect(D3DXVECTOR2 uiPosition, int uiTextureWidth, int uiTextureHeight, D3DXVECTOR2 scalling);

    bool MouseOnButton(RECT a, RECT b);

	void Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture);
	void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture);
	void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture);
	void Clear(Player& player, Texture& texture);


private:
	std::stack<GameState*> level;

	GameStateManager& gameStateManager;
	DirectX& directx;
	Texture& texture;
	Player& player;
	Audio& audio;
};

