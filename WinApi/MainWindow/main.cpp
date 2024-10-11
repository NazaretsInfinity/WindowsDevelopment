#include<Windows.h>
#include<cstdio>
#define IDC_STATIC 1000 //1) ResourceID for child element
#define IDC_EDIT 1001
#define IDC_BUTTON 1002

// name of class window
CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window! :4"; 
CONST CHAR titlebar[] = "Main Window! Size: %ix%i, Position: X: %i Y: %i"; 


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// registing a class
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass); //cb - count bytes
	wClass.cbClsExtra = 0; //Class extra bytes
	wClass.cbWndExtra = 0;// Window extra bytes

	//Appearance:
	
	//LOAD ICON 
	
	/* Default
	
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Sm - small icon*/

	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\blackrose.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\buntrose.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);



	//LOAD CURSOR
	
	/*default
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);*/
	
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "CUR\\RegGlit.ani", IMAGE_CURSOR,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE);


	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.lpszMenuName = NULL;


	//
	wClass.hInstance = hInstance; 
	wClass.lpfnWndProc = (WNDPROC)WndProc;

	wClass.lpszClassName = g_sz_WINDOW_CLASS;

	//1) register class
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
	}


	
	//2) Create window

	HWND hwnd = CreateWindowEx(
      NULL, //Window exStyle
      g_sz_WINDOW_CLASS, // Window class name
      titlebar, //Window title
      WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU, //Windows style
	  0,0,
      CW_USEDEFAULT, CW_USEDEFAULT, //Window size
      NULL, // Parent(no parent ,'cause it's MAIN) 
      NULL , //hMenu 
	  hInstance,
      NULL
		);
	// About hMenu. for main window it's a ResourceID of main menu.
	
	/*For child window(buttons, etc...) it's and ID of resource of associated elements.
	
	For example, if we create a child window edit or static, in hMenu parameter we give (HMENU)IDC_STATIC or (HMENU)IDC_EDIT

	we defined ResourceIDs in the uppest lines for now.( where include hwindow is)

	По этому resourceID мы находим дочерний элемент окна при помощи функции GetDlgItem()*/


	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); // Задаёт режим окна
	UpdateWindow(hwnd);


   //3) Launch of loop of messages
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:// here we creates main window elements(child windows)
	{
		CreateWindowEx(
			NULL,
			"Static",
			"This is a text of the window(static text,bby)",
			WS_CHILD | WS_VISIBLE,// for child window style will start with WS_CHILD and WS_VISIBLE(Neccessity)
			100, 10,
			200, 40,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);

		CreateWindowEx(NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE,
			100, 50,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		CreateWindowEx(NULL, "Button", "AYE!",
			WS_CHILD | WS_VISIBLE,
			150, 80,
			50, 40,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL);
	}break;

	case WM_SIZE:
	{
		//UINT width = LOWORD(lParam); client area idk??? mb title bar's not included.
		//UINT height = HIWORD(lParam); differ from rect coordinates.
		


		/*RECT rect;
		CHAR title[256]{};

		GetWindowRect(hwnd, &rect);
	    INT width = rect.right - rect.left;
	    INT height = rect.bottom - rect.top;

		sprintf_s(title, titlebar, height, width, rect.left, rect.top);

		
		SetWindowText(hwnd, title);*/
		//no break, 'cause its body is similar to WM_MOVE
	}

	case WM_MOVE:
	{
		//UINT x = LOWORD(lParam);
		//UINT y = HIWORD(lParam);
		
		CHAR title[256]{};
		RECT rect;
		GetWindowRect(hwnd, &rect);
		INT width =  rect.right-rect.left;
		INT height = rect.bottom - rect.top;
		
		sprintf_s(title, titlebar, height, width  , rect.left, rect.top);
		SetWindowText(hwnd, title);

	}break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			CHAR buffer[256];
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)buffer);


			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);

		}break;
		}
	}break;

	

	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd); break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return FALSE;
}