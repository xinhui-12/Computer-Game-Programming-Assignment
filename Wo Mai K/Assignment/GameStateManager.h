#pragma once

#include <stack>

#include "GameState.h"
#include "DirectX.h"
#include "Player.h"
#include "Audio.h"
#include "Texture.h"

class MainMenu;  
class Loading;

class GameStateManager
{
public:
    GameStateManager(DirectX& directx, Audio& audio, Player& player, Texture& texture);

    void PushState(GameState* state);
    void PopState();
    void ChangeState(GameState* state);
    GameState* GetCurrentState();

    void Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture);
    void Render(DirectX& directx, Audio& audio, Player& player, Texture& texture);

private:
    std::stack<GameState*> gameStates;

    DirectX& directx;
    Audio& audio;
    Player& player;
    Texture& texture;

};

