#pragma once

#include "Window.h"
#include "Player.h"
#include "FrameTimer.h"
#include "DirectX.h"
#include "Audio.h"

class GameState
{
public:

	virtual void Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) = 0;
	virtual void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) = 0;
	virtual void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) = 0;
	virtual void Clear(Player& player, Texture& texture) = 0;

};

