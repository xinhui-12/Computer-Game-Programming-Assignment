#pragma once

#include <d3dx9.h>
#include "Window.h"
#include "DirectX.h"
#include "DirectInput.h"
#include "FrameTimer.h"
#include "Audio.h"
#include "Player.h"
#include "Texture.h"
#include "GameState.h"
#include "Level3.h"

class Level2 : public GameState {
public:
	Level2(GameStateManager& gameStateManager, DirectX& directx, Audio& audio, Player& player, Texture& texture);

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

