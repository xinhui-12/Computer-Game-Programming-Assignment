//Define//
#define WIN32_LEAN_AND_MEAN
#define PI 3.142
#define GRAVITY 10

//Include Library//
#include <sstream> 
#include <cmath>
#include <stack>

//Class//
#include "Window.h"
#include "DirectX.h"
#include "DirectInput.h"
#include "FrameTimer.h"
#include "Texture.h"
#include "Player.h"
#include "Audio.h"

//Level Class//
#include "MainMenu.h"
#include "Loading.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Win.h"

#include "GameState.h"
#include "GameStateManager.h"

//Main Programme//
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //WinMain
{
	Window window;
	DirectX directx;
	DirectInput directInput;
	FrameTimer frameTimer;
	Audio audio;
	Player player;
	Texture texture;

	// Stack data structure
	std::stack<GameState*> level;
	GameStateManager gameStateManager(directx, audio, player, texture);


	// Initialize Level
	MainMenu mainMenu(gameStateManager, directx, audio, player, texture);
	Level1 level1(gameStateManager, directx, audio, player, texture);
	Level2 level2(gameStateManager, directx, audio, player, texture);
	Level3 level3(gameStateManager, directx, audio, player, texture);
	Win win(gameStateManager, directx, audio, player, texture);

	// Push Level
	gameStateManager.PushState(&mainMenu);                             // Push Main Menu as top element in the stack

	// Get Top of the stack
	GameState* currentState = gameStateManager.GetCurrentState();      // Get the top element of the stack

	// CreateMyBruh
	window.CreateMyWindow();                                           // Create Window
	directx.CreateDirectX(window);                                     // Create DirectX
	directInput.CreateDInput(window);                                  // Create Direct Input
	directx.CreateSpriteBrush();                                       // Create Sprite Brush
	directx.CreateLine();                                              // Create Line
	directx.CreateFont();                                              // Create Font
	audio.InitialiseAudio();                                           // Initialize Audio File
	         
	frameTimer.init(60);                                               // Initialize FPS ( Frame Per Second )

	currentState->Initialize(directx, audio, player, texture);
	while (window.WindowIsRunning())
	{
		directInput.GetInput(player, mainMenu, win);

		// Get current state
		GameState* currentState = gameStateManager.GetCurrentState();
		currentState->Update(window, frameTimer, audio, player, texture);

		// Get current state
		currentState = gameStateManager.GetCurrentState();
		currentState->Render(directx, audio, player, texture);
	
	}
	// Get current state to clear
	currentState->Clear(player, texture);

	directx.ClearSpriteBrush();
	directInput.CleanUpDInput();
	directx.CleanUpDirectX();
	window.CleanUpWindow();

	return 0;
}


