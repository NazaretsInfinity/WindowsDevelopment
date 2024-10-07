#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "first", "list", "box" };

BOOL DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		case IDC_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ADDITEM), hwnd, (DLGPROC)DlgProcAdd, 0);
			break;
			//GetModuleHAndle(NULL) - returns the hInstance of launched programm

		case IDC_DELETEITEM:
			{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_DELETESTRING, i, 0);
			}break;
		case IDOK:
		{
			HWND hLB = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hLB, LB_GETCURSEL, 0, 0);
			CHAR buffer[256]{};
			SendMessage(hLB, LB_GETTEXT, i, (LPARAM)buffer);
			CHAR message[256] = "You haven't choosen anything";

			if (i != LB_ERR)
				sprintf_s(message, "You chose ¹%i with value \"%s\"", i, buffer);
			MessageBox(hwnd, message, "Info", MB_OK);
		}break;

		case IDCANCEL:
		{
			EndDialog(hwnd, 0);
		}break;

		}
	}break;
	case WM_CLOSE:
	{
		EndDialog(hwnd, 0);
		break;
	}
	break;
	}
	return FALSE;
}

BOOL DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: break;
	case WM_COMMAND:
	{
		switch LOWORD(wParam)
		{
		case IDOK:
		{
			CHAR buffer[256]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDITNAME), WM_GETTEXT, 256, (LPARAM)buffer);
			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
			if (strcmp(buffer, "") == 0)MessageBox(hwnd, "You can't add the empty cell", "Error", MB_OK | MB_ICONERROR);
			else if (SendMessage(hListBox, LB_FINDSTRING, -1, (LPARAM)buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
			else
				MessageBox(hwnd, "This currency already exists", "Info", MB_OK | MB_ICONINFORMATION);

		}break;

		case IDCANCEL:
			EndDialog(hwnd, 0);
		}break;

	}break;
	case WM_CLOSE: 
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}