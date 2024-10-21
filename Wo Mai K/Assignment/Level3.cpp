#include "Level3.h"

Level3::Level3(GameStateManager& _gameStateManager, DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture) : gameStateManager(_gameStateManager), directx(_directx), audio(_audio), player(_player), texture(_texture) {}

void Level3::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
    player.CreateSpaceshipTexture(directx); 
    audio.LoadSoundLv3();
}

void Level3::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {
    player.spaceshipEngineForce.x = 0;
    player.spaceshipEngineForce.y = 0;
    player.spaceshipAcceleration.x = 0;
    player.spaceshipAcceleration.y = 0;
    player.staticSpaceshipAcceleration.x = 0;
    player.staticSpaceshipAcceleration.y = 0;
    player.SpaceshipInput();

    player.spaceshipAcceleration = player.spaceshipEngineForce / player.spaceshipMass;
    player.spaceshipVelocity += player.spaceshipAcceleration;

    random_device rd;
    mt19937 gen(rd());

    // Boundary
    if (player.spaceshipPosition.y < 0 || player.spaceshipPosition.y > window.windowHeight - (player.spaceshipSpriteHeight * player.spaceshipScalling.y)) {
        player.spaceshipVelocity.y *= -1;
    }
    if (player.spaceshipPosition.x < 0 || player.spaceshipPosition.x > window.windowWidth - (player.spaceshipSpriteWidth * player.spaceshipScalling.x)) {
        player.spaceshipVelocity.x *= -1;
    }
    // if the static spaceship out of the screen, then the position and the velocity will be reset
    if (player.staticSpaceshipPosition.x <0 || player.staticSpaceshipPosition.x>window.windowWidth - (player.spaceshipSpriteWidth * player.staticSpaceshipScalling.x) || player.staticSpaceshipPosition.y<0 || player.staticSpaceshipPosition.y>window.windowHeight - (player.spaceshipSpriteHeight * player.staticSpaceshipScalling.y)) {
        player.staticSpaceshipPosition.y = 0;
        uniform_int_distribution<int> distribution(0, window.windowWidth - player.spaceshipSpriteWidth);
        player.staticSpaceshipPosition.x = distribution(gen);
        player.staticSpaceshipVelocity = D3DXVECTOR2(0.0f, 2.0f);
    }

    // Collision
    if (player.CircleCollisionDection(player.spaceshipRadius, player.spaceshipRadius, player.spaceshipPosition, player.staticSpaceshipPosition)) {
		audio.PlayingCrash();
        audio.PlayCrashSound();
        D3DXVECTOR2 distance = player.spaceshipPosition - player.staticSpaceshipPosition;
        float radiiSum = player.spaceshipRadius + player.spaceshipRadius;
        float distanceSquared = D3DXVec2LengthSq(&distance);

        // Calculate the collision normal
        D3DXVECTOR2 collisionNormal = D3DXVECTOR2(player.spaceshipPosition - player.staticSpaceshipPosition);
        D3DXVec2Normalize(&collisionNormal, &collisionNormal);

        // Calculate relative velocity
        D3DXVECTOR2 relativeVelocity = player.spaceshipVelocity - player.staticSpaceshipVelocity;

        float overlap = radiiSum - sqrt(distanceSquared);
        overlap = max(overlap, 0.0f);
        D3DXVECTOR2 separationVector = overlap * collisionNormal;
        player.spaceshipPosition += 0.5f * separationVector;
        player.staticSpaceshipPosition -= 0.5f * separationVector;

        // Calculate the impulse along the collision normal
        float impulse = 5.0f * D3DXVec2Dot(&relativeVelocity, &collisionNormal) / (1.0f / player.spaceshipMass + 1.0f / player.staticSpaceshipMass);

        // Update the velocity of the dynamic circle (player)
        player.spaceshipAcceleration -= (impulse * collisionNormal) / player.spaceshipMass;
        player.staticSpaceshipAcceleration += (impulse * collisionNormal) / player.staticSpaceshipMass;

        if (!staticMove) {
            score += 10;
            cout << "Score: " << score <<endl;
        }
        staticMove = true;
        
        if (score >=30){
            audio.ClearSound();
            gameStateManager.ChangeState(new Win(gameStateManager, directx, audio, player, texture));
        }
    }
    else {
        staticMove = false;
    }
    player.spaceshipVelocity += player.spaceshipAcceleration;
    player.staticSpaceshipVelocity += player.staticSpaceshipAcceleration;

    player.spaceshipVelocity *= player.staticSpaceshipFiction;

    player.spaceshipPosition += player.spaceshipVelocity;
    player.staticSpaceshipPosition += player.staticSpaceshipVelocity;

    audio.UpdateSound();

}

void Level3::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
    directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    directx.directXGPU->BeginScene();
    directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

    player.DrawScore(directx, score);

    player.DrawSpaceshipTexture(directx);

    directx.spriteBrush->End();
    directx.directXGPU->EndScene();
    directx.directXGPU->Present(NULL, NULL, NULL, NULL);
}

void Level3::Clear(Player& player, Texture& texture) {
    player.ClearSpaceshipTexture();
}   