#include<Windows.h>
#include"resource.h"
#include<cstdio>
CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";
CONST INT g_BUTTON_SIZE = 50;
CONST INT g_INTERVAL = 5;
CONST INT gX = 10;
CONST INT gY = 10;
CONST INT g_DISPLAY_WIDTH = g_BUTTON_SIZE*5+ g_INTERVAL*4;
CONST INT g_DISPLAY_HEIGHT = 25; // THIS ERROR
CONST INT g_BUTTON_START_X = gX;
CONST INT g_BUTTON_START_Y = gY + g_DISPLAY_HEIGHT + g_INTERVAL;
CONST INT g_OPERATIONS_START_X = gX + (g_BUTTON_SIZE + g_INTERVAL) * 3;
CONST INT g_OPERATIONS_START_Y = g_BUTTON_START_Y;

CONST INT g_CONTROL_BUTTONS_START_X = gX+ (g_BUTTON_SIZE + g_INTERVAL) * 4;
CONST INT g_CONTROL_BUTTONS_START_Y = g_BUTTON_START_Y;

CONST CHAR g_OPERATIONS[] = "+-*/";


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
		WS_SYSMENU, 
		CW_USEDEFAULT,CW_USEDEFAULT,
		g_DISPLAY_WIDTH + g_BUTTON_START_X*2+16,
		g_DISPLAY_HEIGHT + (g_BUTTON_SIZE + g_INTERVAL) * 4 + gY * 2 + 16 + 23, // FIX HERE
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
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
			gX, gY,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,  
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);


		CHAR buffer[2]{};
			for (int i = 6; i >= 0; i -= 3)
            {
				for (int j = 0; j < 3; ++j)
				{
		     
					buffer[0] = i + j + 49;

					//sprintf_s(buffer, "%i", IDC_BUTTON_0+j+i-999);
					CreateWindowEx(
					NULL, "Button", buffer,
					WS_CHILD | WS_VISIBLE, 
					g_BUTTON_START_X+(g_BUTTON_SIZE + g_INTERVAL)*j, g_BUTTON_START_Y+ (g_BUTTON_SIZE+g_INTERVAL)*(2-i/3),
					g_BUTTON_SIZE,g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1+i+j),
					GetModuleHandle(NULL),
					NULL
					);
				}
    		}

			CreateWindowEx(
				NULL, "Button", "0",
				WS_CHILD | WS_VISIBLE,
				g_BUTTON_START_X, g_BUTTON_START_Y +(g_BUTTON_SIZE + g_INTERVAL)*3, 
				g_BUTTON_SIZE*2, g_BUTTON_SIZE, 
				hwnd,
				(HMENU)IDC_BUTTON_0,
				GetModuleHandle(NULL),
				NULL
			);

			CreateWindowEx(
				NULL, "Button", ".",
				WS_CHILD | WS_VISIBLE , 
				g_BUTTON_START_X+ g_BUTTON_SIZE*2 + g_INTERVAL,
				g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL)*3, 
				g_BUTTON_SIZE, g_BUTTON_SIZE, 
				hwnd, 
				(HMENU)IDC_BUTTON_POINT,
				GetModuleHandle(NULL),
				NULL
			);

			CHAR operation[2]{};
			for (int i = 0; i < 4; ++i)
			{
				operation[0] = g_OPERATIONS[i];
				CreateWindowEx(
					NULL, "Button", operation,
					WS_CHILD | WS_VISIBLE,
					g_OPERATIONS_START_X, g_OPERATIONS_START_Y+ (g_BUTTON_SIZE + g_INTERVAL) * i,
					g_BUTTON_SIZE, g_BUTTON_SIZE, 
					hwnd, 
					(HMENU)(IDC_BUTTON_PLUS+i),
					GetModuleHandle(NULL),
					NULL
					);
			}

			//Creating control buttons

			CreateWindowEx(
				NULL, "Button", "<-",
				WS_CHILD | WS_VISIBLE,
				g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y + g_BUTTON_SIZE + g_INTERVAL,
				g_BUTTON_SIZE, g_BUTTON_SIZE,
				hwnd,
				(HMENU)IDC_BUTTON_BSP,
				GetModuleHandle(NULL),
				NULL
			);

			CreateWindowEx(
				NULL, "Button", "C",
				WS_CHILD | WS_VISIBLE,
				g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y,
				g_BUTTON_SIZE, g_BUTTON_SIZE,
				hwnd,
				(HMENU)IDC_BUTTON_CLEAR,
				GetModuleHandle(NULL),
				NULL
			);

			CreateWindowEx(
				NULL, "Button", "=",
				WS_CHILD | WS_VISIBLE,
				g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y +(g_BUTTON_SIZE + g_INTERVAL)* 2, 
				g_BUTTON_SIZE, g_BUTTON_SIZE, 
				hwnd,
				(HMENU)IDC_BUTTON_EQUAL ,
				GetModuleHandle(NULL),
				NULL
			);
	}break;
	case WM_COMMAND:
	{
		CHAR display[256]{};
		CHAR digit[2]{};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)display);
			if (display[0] == '0' && display[1] != '.')display[0] = 0;

			strcat_s(display, digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)display);
			if (strchr(display, '.'))break;
			strcat(display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)display);

			if (strlen(display) == 1)display[0] = '0';
			else display[strlen(display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			display[0] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)display);
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam)), WM_GETTEXT, 2, (LPARAM)digit);
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)display);

			if (display[0] == 0 || strpbrk(display, g_OPERATIONS)!=0)break;
			strcat_s(display, digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)display);

		}

	}break;

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