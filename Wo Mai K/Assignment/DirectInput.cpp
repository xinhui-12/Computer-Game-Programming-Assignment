#include "DirectInput.h"

void DirectInput::CreateDInput(Window& window) 
{
	//Create Direct Input Object
	hResult.hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	if (FAILED(hResult.hr))
		cout << "Failed to create Direct Input Object" << endl;

	//Create Keyboard Device
	hResult.hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FAILED(hResult.hr))
		cout << "Failed to create Direct Input Keyboard Device" << endl;

	hResult.hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hResult.hr))
		cout << "Failed to set Data Format for Keyboard" << endl;

	hResult.hr = dInputKeyboardDevice->SetCooperativeLevel(window.g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hResult.hr))
	{
		cout << "Failed to set cooperative level for keyboard device. " << endl;
	}

	//Create Mouse Device
	hResult.hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FAILED(hResult.hr))
		cout << "Failed to create Direct Input Mouse Device" << endl;

	hResult.hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hResult.hr))
	{
		cout << "Failed to set Data Format for Mouse. " << endl;
	}

	hResult.hr = dInputMouseDevice->SetCooperativeLevel(window.g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hResult.hr))
	{
		cout << "Failed to set cooperative level for Mouse. " << endl;
	}

	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
}

void DirectInput::GetInput(Player& player, MainMenu& mainMenu, Win& win)
{
	//	Acquire the device.
	if (DISCL_FOREGROUND) {
		dInputKeyboardDevice->Acquire();
		dInputMouseDevice->Acquire();
	}
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	
	if (diKeys[DIK_W] & 0x80)
	{
		player.wKeyPressed = true;
	}
	else player.wKeyPressed = false;

	if (diKeys[DIK_S] & 0x80)
	{
		player.sKeyPressed = true;
	}
	else player.sKeyPressed = false;

	if (diKeys[DIK_A] & 0x80)
	{
		player.aKeyPressed = true;
	}
	else player.aKeyPressed = false;

	if (diKeys[DIK_D] & 0x80)
	{
		player.dKeyPressed = true;
	}
	else player.dKeyPressed = false;

	if (diKeys[DIK_SPACE] & 0x80)
	{
		player.spaceKeyPressed = true;
	}
	else player.spaceKeyPressed = false;

	if (BUTTONDOWN(mouseState, 0))
	{
		mainMenu.leftMouseButton = true;
		cout << "Left Mouse Button" << endl;
	}	
	else 
		mainMenu.leftMouseButton = false;

	if (BUTTONDOWN(mouseState, 1))
	{
		mainMenu.rightMouseButton = true;
		cout << "Right Mouse Button" << endl;
	}
	else mainMenu.rightMouseButton = false;

	mainMenu.mousePosition.x += mouseState.lX;
	mainMenu.mousePosition.y += mouseState.lY;
}

void DirectInput::CleanUpDInput() {
	//	Release keyboard device.
	if (dInputKeyboardDevice) {
		dInputKeyboardDevice->Unacquire();
		dInputKeyboardDevice->Release();
		dInputKeyboardDevice = NULL;
	}
	
	//	Release mouse device.
	if (dInputMouseDevice) {
		dInputMouseDevice->Unacquire();
		dInputMouseDevice->Release();
		dInputMouseDevice = NULL;
	}

	//	Release DirectInput.
	if (dInput) {
		dInput->Release();
		dInput = NULL;
	}
}


