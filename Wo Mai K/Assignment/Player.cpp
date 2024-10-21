#include "Player.h"

void Player::PlayerInput(Audio& audio) {
	if (aKeyPressed) {
		playerState = 1;
		playerCounter++;
		playerVelocity.x -= playerSpeed;
		cout << "a" << endl;
	}

	if (dKeyPressed) {
		playerState = 2;
		playerCounter++;
		playerVelocity.x += playerSpeed;
		cout << "d" << endl;
	}
	if (spaceKeyPressed)
	{
		if (playerVelocity.y == 0) {
			cout << playerVelocity.x << "||" << playerVelocity.y << endl;
			playerVelocity.y -= playerJumpForce;
			onPlatform = false;
			audio.playJumpSound();
		}
	}

	if (!aKeyPressed && !dKeyPressed && (onPlatform = true))
	{
		playerVelocity.x = 0;
	}
}

//===========================================================================================================================================//

RECT Player::PlayerCollisionRect() {
	playerCollisionRect.top = playerPosition.y;
	playerCollisionRect.bottom = playerCollisionRect.top + playerSpriteHeight * playerScaling.x;
	playerCollisionRect.left = playerPosition.x;
	playerCollisionRect.right = playerCollisionRect.left + playerSpriteWidth * playerScaling.y;
	return playerCollisionRect;
}

void Player::CreatePlayerTexture(DirectX& directx) {
	HRESULT hr = D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/Player.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &playerTexture);

	if (FAILED(hr))
		cout << "Fail To Load Player Texture" << endl;
}

void Player::DrawPlayerTexture(DirectX& directx) {
	PlayerSpriteRect();
	D3DXMatrixTransformation2D(&playerMat, NULL, 0.0, &playerScaling, NULL, 0.0f, &playerPosition);
	directx.spriteBrush->SetTransform(&playerMat);
	directx.spriteBrush->Draw(playerTexture, &playerSpriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

//===========================================================================================================================================//
RECT Player::PlayerSpriteRect() {
	playerSpriteRect.left = playerCounter % playerMaxFrame % playerCol * playerSpriteWidth;
	playerSpriteRect.right = playerSpriteRect.left + playerSpriteWidth;
	playerSpriteRect.top = playerSpriteHeight * playerState;
	playerSpriteRect.bottom = (playerSpriteRect.top + playerSpriteHeight);
	return playerSpriteRect;
}

bool Player::PlayerCollisionDetection(RECT a, RECT b) {

	if (a.top > b.bottom)
		return false;
	if (a.bottom < b.top)
		return false;
	if (a.left > b.right)
		return false;
	if (a.right < b.left)
		return false;
	return true;

}

RECT Player::PlayerCollisionTarget(Texture& texture) {

	texture.PlatformRect(texture.platformPosition1);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

	texture.PlatformRect(texture.platformPosition2);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

	texture.PlatformRect(texture.platformPosition3);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

	texture.PlatformRect(texture.platformPosition4);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

	texture.PlatformRect(texture.platformPosition5);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

	texture.PlatformRect(texture.platformPosition6);
	if (PlayerCollisionDetection(playerCollisionRect, texture.platformRect))
		return texture.platformRect;

}

void Player::PlayerCollision(Texture& texture) {

	if (playerVelocity.y >= 0 && playerCollisionRect.top < texture.platformRect.top)//player V Rock
	{
		cout << "Top collision" << endl;
		playerCollisionRect.bottom = texture.platformRect.top - 1;
		playerPosition.y = texture.platformRect.top - playerSpriteHeight * playerScaling.y;
		onPlatform = true;
		topCollision = true;
	}
	else topCollision = false;

	if (playerVelocity.y < 0 && playerCollisionRect.bottom > texture.platformRect.bottom)//player ^ Rock
	{
		cout << "Bottom collision" << endl;
		playerCollisionRect.bottom = texture.platformRect.top + 1;
		playerPosition.y = texture.platformRect.bottom + 1;
		onPlatform = false;
	}

	if (!topCollision) {
		if (playerVelocity.x > 0 && playerCollisionRect.left < texture.platformRect.left)//player > rock
		{
			cout << "Right collision" << endl;
			playerCollisionRect.right = texture.platformRect.left - 1;
			playerPosition.x = playerCollisionRect.right - playerSpriteWidth - 1;
		}

		if (playerVelocity.x < 0 && playerCollisionRect.right > texture.platformRect.right)//player < player
		{
			cout << "Left collision" << endl;
			playerCollisionRect.left = texture.platformRect.right * playerScaling.y + 1;
			playerPosition.x = texture.platformRect.right + 1;
		}
	}

}

void Player::PlayerBoundary(Window& window, Texture& texture) {
	if (playerPosition.y > window.windowHeight - playerSpriteHeight * playerScaling.y - (window.windowHeight - texture.platformPosition0.y))
	{
		playerPosition.y = window.windowHeight - playerSpriteHeight * playerScaling.y - (window.windowHeight - texture.platformPosition0.y);
		playerVelocity.y = 0.0f;
		onPlatform = true;
	}
	if (playerPosition.y < 0)
	{
		playerPosition.y = 0;
	}
	if (playerPosition.x > window.windowWidth - playerSpriteWidth * playerScaling.x)
	{
		playerPosition.x = window.windowWidth - playerSpriteWidth * playerScaling.x;
	}
	if (playerPosition.x < 0)
	{
		playerPosition.x = 0;
	}
}

//===========================================================================================================================================//

void Player::ClearPlayerTexture() {
	playerTexture->Release();
	playerTexture = NULL;
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

void Player::DrawScore(DirectX& directx, int score) {
	SetRect(&scoreRect, 0, 0, 300, 100);
	stringstream scoreText;
	scoreText << "Score: " << score;

	D3DXMatrixTransformation2D(&scoreMat, NULL, 0.0, 0, 0, 0, &scorePosition);
	directx.spriteBrush->SetTransform(&scoreMat);

    directx.arialFont->DrawText(directx.spriteBrush, scoreText.str().c_str(), -1, &scoreRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

void Player::CreateSpaceshipTexture(DirectX& directx) {
	HRESULT hr = D3DXCreateTextureFromFileEx(directx.directXGPU, "../Texture/spaceship.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0),
		NULL, NULL, &spaceshipTexture);

	if (FAILED(hr))
		cout << "Fail To Load Spaceship Texture" << endl;
}

void Player::DrawSpaceshipTexture(DirectX& directx) {
	spaceshipRect.left = 0;
	spaceshipRect.right = spaceshipRect.left + spaceshipSpriteWidth;
	spaceshipRect.top = 0;
	spaceshipRect.bottom = spaceshipRect.top + spaceshipSpriteHeight;
	D3DXVECTOR2 scaledCenter = spaceshipSpriteCenter;
	scaledCenter.x *= spaceshipScalling.x;
	scaledCenter.y *= spaceshipScalling.y;

	D3DXMatrixTransformation2D(&spaceshipMat, NULL, 0.0, &spaceshipScalling, &scaledCenter, spaceshipRotation, &spaceshipPosition);
	directx.spriteBrush->SetTransform(&spaceshipMat);
	directx.spriteBrush->Draw(spaceshipTexture, &spaceshipRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	staticSpaceshipRect.left = spaceshipSpriteWidth;
	staticSpaceshipRect.right = staticSpaceshipRect.left + spaceshipSpriteWidth;
	staticSpaceshipRect.top = spaceshipSpriteHeight;
	staticSpaceshipRect.bottom = staticSpaceshipRect.top + spaceshipSpriteHeight;

	D3DXMatrixTransformation2D(&staticSpaceshipMat, NULL, 0.0, &staticSpaceshipScalling, NULL,0.0f, &staticSpaceshipPosition);
	directx.spriteBrush->SetTransform(&staticSpaceshipMat);
	directx.spriteBrush->Draw(spaceshipTexture, &staticSpaceshipRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Player::SpaceshipInput() {
	if (aKeyPressed) {
		spaceshipRotation -= spaceshipRotationSpeed;
	}

	if (dKeyPressed) {
		spaceshipRotation += spaceshipRotationSpeed;
	}

	if (wKeyPressed) { //forward
		spaceshipEngineForce.x = spaceshipSpeed * sin(spaceshipRotation);
		spaceshipEngineForce.y = spaceshipSpeed * -cos(spaceshipRotation);
	}

	if (sKeyPressed) { //slow down or reverse
		spaceshipEngineForce.x = -spaceshipSpeed * sin(spaceshipRotation);;
		spaceshipEngineForce.y = -spaceshipSpeed * -cos(spaceshipRotation);;
	}

}

bool Player::CircleCollisionDection(float a, float b, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB) {
	D3DXVECTOR2 distance = positionA - positionB;
	if (pow(a + b, 2) > D3DXVec2LengthSq(&distance)) 
		return true; 
	return false;
}

void Player::ClearSpaceshipTexture() {
	spaceshipTexture->Release();
	spaceshipTexture = NULL;
}