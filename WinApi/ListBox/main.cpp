#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "first", "list", "box" };

BOOL DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}


BOOL DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); ++i)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
		}

	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hLB = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hLB, LB_GETCURSEL, 0, 0);
			CHAR buffer[256]{};
			SendMessage(hLB, LB_GETTEXT, i, (LPARAM)buffer);
			CHAR message[256]{};
			sprintf_s(message, "You chose ¹%i with value \"%s\"", i, buffer);
			MessageBox(hwnd, message, "Info", MB_OK);
		}break;
        
		case IDCANCEL:
		{
			EndDialog(hwnd, 0);
		}break;

		//case
		}
	}
		break;
	case WM_CLOSE:
	{
		EndDialog(hwnd, 0);
		break;
	}
	break;
	}
	return FALSE;
}

