#pragma once

#include <d3dx9.h>
#include <sstream>

#include "Window.h"
#include "DirectX.h"
#include "FrameTimer.h"
#include "Audio.h"
#include "Texture.h"

class Player
{

public:

	LPDIRECT3DTEXTURE9 playerTexture = NULL;

	//Player State
	int playerState = 0;
	int playerCounter = 0;

	//Player RECT
	RECT playerSpriteRect;
	RECT playerCollisionRect;

	int playerTextureWidth = 128;
	int playerTextureHeight = 192;
	int playerSpriteWidth = 32;
	int playerSpriteHeight = 48;
	int playerMaxFrame = 4;
	int playerRow = 4;
	int playerCol = 4;
	D3DXMATRIX playerMat;
	D3DXVECTOR2 playerScaling = D3DXVECTOR2(2.0f, 2.0f);

	bool onPlatform = true;
	bool topCollision = false;

	//Player Motion
	D3DXVECTOR2 playerPosition = D3DXVECTOR2(100.0f, 100.0f);
	D3DXVECTOR2 playerVelocity = D3DXVECTOR2(0.0f, 0.0f);
	float playerSpeed = 1.0f;
	float playerAcceleration = 1.0f;
	float playerFriction = 0.9f;
	float playerGravity = 3.0f;
	float playerJumpForce = 50.0f;

	//Player State
	bool wKeyPressed = false;
	bool aKeyPressed = false;
	bool sKeyPressed = false;
	bool dKeyPressed = false;
	bool spaceKeyPressed = false;

	//Function
	void PlayerInput(Audio& audio);

	RECT PlayerCollisionRect();
	void CreatePlayerTexture(DirectX& directx);
	void DrawPlayerTexture(DirectX& directx);

	RECT PlayerSpriteRect();
	bool PlayerCollisionDetection(RECT a, RECT b);
	RECT PlayerCollisionTarget(Texture& texture);
	void PlayerCollision(Texture& texture);
	void PlayerBoundary(Window& window, Texture& texture);

	void ClearPlayerTexture();


	//===========================================================================================================================================//
	//Black Spaceship
	LPDIRECT3DTEXTURE9 spaceshipTexture = NULL;
	D3DXVECTOR2 spaceshipPosition = D3DXVECTOR2(100.0f, 100.0f);
	int spaceshipRow = 2;
	int spaceshipCol = 2;
	int spaceshipTextureWidth = 64;
	int spaceshipTextureHeight = 64;
	int spaceshipMaxFrame = 4;
	int spaceshipSpriteWidth = spaceshipTextureWidth / spaceshipCol;
	int spaceshipSpriteHeight = spaceshipTextureHeight / spaceshipRow;
	D3DXMATRIX spaceshipMat;
	RECT spaceshipRect;
	int spaceshipSpeed = 1;
	D3DXVECTOR2 spaceshipVelocity = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 spaceshipSpriteCenter = D3DXVECTOR2(spaceshipSpriteWidth/2, spaceshipSpriteHeight/2);
	float spaceshipRotation = 0.0f;
	float spaceshipRotationSpeed = 0.05f;
	D3DXVECTOR2 spaceshipAcceleration = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 spaceshipEngineForce = D3DXVECTOR2(0.0f, 0.0f);
	int spaceshipMass = 50;
	float spaceshipRadius = spaceshipSpriteWidth / 2;
	D3DXVECTOR2 spaceshipScalling = D3DXVECTOR2(1.5f, 1.5f);

	//White Spaceship
	D3DXVECTOR2 staticSpaceshipPosition = D3DXVECTOR2(200.0f, 200.0f);
	int staticSpaceshipMass = 100;
	RECT staticSpaceshipRect;
	D3DXMATRIX staticSpaceshipMat;
	D3DXVECTOR2 staticSpaceshipVelocity = D3DXVECTOR2(0.0f, 2.0f);
	D3DXVECTOR2 staticSpaceshipAcceleration = D3DXVECTOR2(0.0f, 0.0f);
	float staticSpaceshipFiction = 0.995;
	D3DXVECTOR2 staticSpaceshipScalling = D3DXVECTOR2(1.2f, 1.2f);

	void CreateSpaceshipTexture(DirectX& directx);
	void DrawSpaceshipTexture(DirectX& directx); 
	void SpaceshipInput();
	bool CircleCollisionDection(float a, float b, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
	void ClearSpaceshipTexture();

	RECT scoreRect;
	D3DXMATRIX scoreMat;
	D3DXVECTOR2 scorePosition = D3DXVECTOR2(0.0f, 0.0f);
	void DrawScore(DirectX& directx, int score);


};

