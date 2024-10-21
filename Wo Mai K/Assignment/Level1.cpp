#include "Level1.h"

Level1::Level1(GameStateManager& _gameStateManager, DirectX& _directx, Audio& _audio, Player& _player, Texture& _texture) : gameStateManager(_gameStateManager), directx(_directx), audio(_audio), player(_player), texture(_texture) {}

void Level1::Initialize(DirectX& directx, Audio& audio, Player& player, Texture& texture) {

	player.playerPosition = { 0, 984 };
	texture.InitializePlatformLevel1();
	audio.LoadSoundLv1();

	texture.CreateBackground(directx);
	texture.CreatePortal(directx);
	texture.CreateRockPlatform(directx);
	player.CreatePlayerTexture(directx);
}

void Level1::Update(Window& window, FrameTimer& frameTimer, Audio& audio, Player& player, Texture& texture) {
	
	audio.PlayingBGM();
	if (!audio.bgmIsPlaying) {
		audio.PlayBGM(audio.bgmVolume);
	}

	for (int i = 0; i < frameTimer.framesToUpdate(); i++)
	{
		player.PlayerInput(audio);
		player.PlayerCollisionRect();
		player.PlayerCollisionTarget(texture);

		texture.PortalRect(texture.portalPosition);

		if (player.PlayerCollisionDetection(player.playerCollisionRect, texture.portalRect)) {
			cout << "change game state to level 2 here" << endl;
			audio.ClearSound();
			gameStateManager.ChangeState(new Level2(gameStateManager, directx, audio, player, texture));
		}

		if (player.PlayerCollisionDetection(player.playerCollisionRect, texture.platformRect)) {
			player.PlayerCollision(texture);
		}
		else player.onPlatform = false;


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

void Level1::Render(DirectX& directx, Audio& audio, Player& player, Texture& texture) {
	directx.directXGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 192, 203), 1.0f, 0);
	directx.directXGPU->BeginScene();
	directx.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	texture.DrawBackground(texture.backgroundPosition1,directx);
	texture.DrawPortal(texture.portalPosition, directx);
	player.DrawPlayerTexture(directx);
	texture.DrawPlatform(texture.platformPosition0, texture.baseScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition1, texture.platformScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition2, texture.platformScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition3, texture.platformScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition4, texture.platformScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition5, texture.platformScaling, texture.rockPlatformTexture, directx);
	texture.DrawPlatform(texture.platformPosition6, texture.platformScaling, texture.rockPlatformTexture, directx);

	directx.spriteBrush->End();
	directx.directXGPU->EndScene();
	directx.directXGPU->Present(NULL, NULL, NULL, NULL);
}

void Level1::Clear(Player& player, Texture& texture) {
	texture.ClearRockPlatform();
	texture.ClearBackground();
	player.ClearPlayerTexture();
}





