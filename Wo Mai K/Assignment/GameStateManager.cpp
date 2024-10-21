#include "GameStateManager.h"

GameStateManager::GameStateManager(DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture) : directx(_directx), audio(_audio), player(_player), texture(_texture) {}

void GameStateManager::PushState(GameState* state) {
    if (!gameStates.empty()) {
        // USE THIS IF GAME NEED TO PUT THE GAME IN PAUSE STATE
        //gameStates.top()->Pause();
        
    }
    gameStates.push(state);
    state->Initialize(directx, audio, player, texture);
}

void GameStateManager::PopState() {
    if (!gameStates.empty()) {     
        gameStates.top()->Clear(player, texture);
    
        delete gameStates.top();
        gameStates.pop();

        if (!gameStates.empty()) {
            // USE THIS IF GAME NEED TO RESUME THE PAUSE STATE
            //gameStates.top()->Resume();
        }
    }
}

void GameStateManager::ChangeState(GameState* state) {
    if (!gameStates.empty()) {
        gameStates.top()->Clear(player, texture);
        delete gameStates.top();
        gameStates.pop();
    }
    gameStates.push(state);
    state->Initialize(directx, audio, player, texture);
}

GameState* GameStateManager::GetCurrentState()
{
    if (!gameStates.empty())
    {
        return gameStates.top();
    }
    return NULL; 
}

void GameStateManager::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {
    if (!gameStates.empty()) {
        gameStates.top()->Update(window, frameTimer, audio, player, texture);
    }
}

void GameStateManager::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
    if (!gameStates.empty()) {
        gameStates.top()->Render(directx, audio, player, texture);
    }
}
