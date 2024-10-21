#include "Level2.h"

Level2::Level2(GameStateManager& _gameStateManager, DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture) : gameStateManager(_gameStateManager), directx(_directx), audio(_audio), player(_player), texture(_texture) {}

void Level2::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {

	//texture.InitializePlatformLevel2();
	//audio.LoadSoundLv2();
	//audio.PlayBGM(0.5);

    player.playerPosition = { 0, 948 };
    texture.InitializePlatformLevel2();
    audio.LoadSoundLv2();

	texture.CreateBackground(directx);
	texture.CreatePortal(directx);
	texture.CreateCloudPlatform(directx);
	player.CreatePlayerTexture(directx);

}

void Level2::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {
    audio.PlayingBGM();
    if (!audio.bgmIsPlaying) {
        audio.PlayBGM(audio.bgmVolume);
    }

	audio.windCounter++;
	audio.WindDirectionUpdate();
	audio.Blowing();
	if (!audio.windIsPlaying) {
		audio.PlayWindSound(audio.windDirection);
	}

	for (int i = 0; i < frameTimer.framesToUpdate(); i++)
	{
		player.PlayerInput(audio);
		player.PlayerCollisionRect();
		player.PlayerCollisionTarget(texture);

        texture.PortalRect(texture.portalPosition);
        if (player.PlayerCollisionDetection(player.playerCollisionRect, texture.portalRect)) {
            cout << "change game state to level 1 here" << endl;
			audio.ClearSound();
			gameStateManager.ChangeState(new Level3(gameStateManager, directx, audio, player, texture));
        }

		if (player.PlayerCollisionDetection(player.playerCollisionRect, texture.platformRect)) {
			player.PlayerCollision(texture);
		}
		else player.onPlatform = false;

		if (audio.windDirection < 0) {
			player.playerVelocity.x += 0.7;
		}

		if (audio.windDirection > 0) {
			player.playerVelocity.x -= 0.7;
		}

		if (!player.onPlatform)
		{
			player.playerVelocity.y += player.playerGravity;
			player.onPlatform = false;
		}
		else
		{
			player.playerVelocity.y -= player.playerGravity;
			player.playerVelocity.y = 0;
		}

		player.playerVelocity *= player.playerFriction;
		player.playerPosition += player.playerVelocity;

		player.PlayerBoundary(window, texture);
	}
	audio.UpdateSound();
}

void Level2::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
	directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 192, 203), 1.0f, 0);
	directx.directXGPU->BeginScene();
	directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	texture.DrawBackground(texture.backgroundPosition2, directx);
	texture.DrawPortal(texture.portalPosition, directx);
	player.DrawPlayerTexture(directx);
	texture.DrawPlatform(texture.platformPosition0, texture.baseScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition1, texture.platformScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition2, texture.platformScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition3, texture.platformScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition4, texture.platformScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition5, texture.platformScaling, texture.cloudPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition6, texture.platformScaling, texture.cloudPlatformTexture, directx);

	directx.spriteBrush->End();
	directx.directXGPU->EndScene();
	directx.directXGPU->Present(NULL, NULL, NULL, NULL);
}

void Level2::Clear(Player& player, Texture& texture) {
	texture.ClearCloudPlatform();
	texture.ClearBackground();
	player.ClearPlayerTexture();
}
