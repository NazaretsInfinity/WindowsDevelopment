#include<Windows.h>
#include"resource.h"
#include<cstdio>
CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";
CONST INT g_BUTTON_SIZE = 50;
CONST INT g_INTERVAL = 5;
CONST INT gX = 10;
CONST INT gY = 10;
CONST INT g_DISPLAY_WIDTH = 300;
CONST INT g_DISPLAY_HEIGHT = 25;
CONST INT g_BUTTON_START_X = gX;
CONST INT g_BUTTON_START_Y = gY + g_DISPLAY_HEIGHT + g_INTERVAL;


BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

	//REGISTER CLASS
	WNDCLASSEX wClass; 
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	//Appearance
	wClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.lpszMenuName = NULL;


	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//END REGISTER CLASS


	//CREATING OF WINDOW
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	//Launch of message loop
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
			gX, gY,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);

			for (int i = 6; i >= 0; i -= 3)
            {
				for (int j = 0; j < 3; ++j)
				{
					CHAR buffer[256];
					sprintf_s(buffer, "%i", IDC_BUTTON_0+j+i-999);
					CreateWindowEx(
					NULL, "Button", buffer,
					WS_CHILD | WS_VISIBLE, 
					g_BUTTON_START_X+(g_BUTTON_SIZE + g_INTERVAL)*j, g_BUTTON_START_Y+ (g_BUTTON_SIZE+g_INTERVAL)*(i/3),
					g_BUTTON_SIZE,g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0+i+j),
					GetModuleHandle(NULL),
					NULL
					);
				}
    		}
	}break;
	case WM_COMMAND: break;

	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}