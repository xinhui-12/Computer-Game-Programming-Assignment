#pragma once

#include <d3dx9.h>
#include <random>

#include "Window.h"
#include "DirectX.h"
#include "FrameTimer.h"
#include "Audio.h"
#include "Player.h"
#include "Texture.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "Win.h"

class Level3 : public GameState {
public:
    Level3(GameStateManager& gameStateManager, DirectX& directx, Audio& audio, Player& player, Texture& texture);

    void Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
    void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) override;
    void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) override;
    void Clear(Player& player, Texture& texture);

private:
    GameStateManager& gameStateManager;
    DirectX& directx;
    Audio& audio;
    Player& player;
    Texture& texture;

    int score = 0;
    bool staticMove = false;
};