#include "Window.h"

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}

void Window::CreateMyWindow() {

	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "Assignment Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	

	//	Register the window.
	RegisterClass(&wndClass);

	//	GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Wo Mai K", WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
	ShowCursor(true);

}

bool Window::WindowIsRunning() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void Window::CleanUpWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

