#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
using namespace std;


class Window
{
	public:
		HWND g_hWnd = NULL;
		WNDCLASS wndClass;

		int windowWidth = 1920;//GetSystemMetrics(SM_CXSCREEN); //800; 
		int windowHeight = 1080;//GetSystemMetrics(SM_CYSCREEN); //900; 

		//Function
		void CreateMyWindow();
		bool WindowIsRunning();
		void CleanUpWindow();


};

