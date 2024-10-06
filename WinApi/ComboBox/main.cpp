#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"Resource.h"

CONST CHAR* g_COMBO_BOX_ITEMS[] = {"This" , "is", "my", "first", "combo", "box"};
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		// SETTED ICON
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		//setted box cells
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_COMBO_BOX_ITEMS) / sizeof(g_COMBO_BOX_ITEMS[0]); ++i)
		{
			SendMessage(hCombo, CB_INSERTSTRING, i, (LPARAM)g_COMBO_BOX_ITEMS[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
		//CB - Combo box
		//CB_SETCURSEL - set current selection

	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCB = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCB, CB_GETCURSEL,0,0);
			CHAR buffer[256]{};
			SendMessage(hCB, CB_GETLBTEXT, i, (LPARAM)buffer);
			CHAR message[256]{};
			sprintf(message, "You chose ¹%i with value \"%s\"", i, buffer);
			//sprintf() - analogue of Format for strings.
			//specifiers: %i - int;    %s - string
			MessageBox(hwnd, message, "Info", MB_OK );

		}break;
		case IDCANCEL:
		{
			EndDialog(hwnd, 0);
		}break;

		}
	}break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}