#pragma once

#include <d3dx9.h>
#include <dinput.h>
#include <ddraw.h>

#include "Window.h"
#include "DirectX.h"
#include "MainMenu.h"
#include "Player.h"

#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)
#define DIRECTINPUT_VERSION 0x0800

class Win;

class DirectInput
{

public:
    //Initialize
    DirectX hResult;
    Window window;

    LPDIRECTINPUT8 dInput;

    //Device Manager
    LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8 dInputMouseDevice;

    DIMOUSESTATE mouseState;
    BYTE diKeys[256];

    //Function
    void CreateDInput(Window& window);
    void GetInput(Player& player, MainMenu& mainMenu, Win& win);
    void CleanUpDInput();

};

