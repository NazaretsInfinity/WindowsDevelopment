#include<Windows.h>
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
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEMS[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
		//CB - Combo box
		//CB_SETCURSEL - set current selection

	}break;
	case WM_COMMAND:
	{


	}break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}