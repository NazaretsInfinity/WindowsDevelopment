#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//hwnd - Handler to Window - дескриптор окна -  число, при помощи которого можно обратится к окну.
//uMsg - сообщение, которое отправляется окну
//wParam, lParam - параметры сообщения, у каждого сообщения свой набор параметров. 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// caption  - заголовок

	/*MessageBox
	(NULL, 
		"WE RA #! \"S HERE ;)))))\nShall we start?", 
		"tITLE UWU",  
		MB_YESNO | MB_HELP| MB_DEFBUTTON1 |
		MB_ICONWARNING |
		MB_TASKMODAL
	);*/
	//W - means WHITESTRING. 
	//wchar_t  - 2 bytes (unicode)
	//char - 1 Byte(ASCII)
	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG: // this message send only 1 time during window initialization
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetWindowText(hEditLogin, "Enter username");
	}
		break;
	case WM_COMMAND: //process the pushing of buttons and other user's acts 
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Was pushed \"OK\" button", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd,0);break;
		case IDC_COPY:
		{
			//create buffer
			char sz_buffer[256]{}; //sz - string zero(NULL Terminated Line - C-String)

			// get deskriptors of text lines.
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

			//read the contents of 'Login' and save it to buffer.
			SendMessage(hEditLogin, WM_GETTEXT, 256, (LPARAM)sz_buffer);

			//load text we got in text field 'password'
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;

		case IDC_EDIT_LOGIN:
		{
			if (GetFocus() == (GetDlgItem(hwnd, IDC_EDIT_LOGIN)))
			{
			   /* HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				if (GetWindowTextLength(hEditLogin) > 14)
				{
					SendMessage(hEditLogin, EM_SETSEL, 0, 15);
					SendMessage(hEditLogin, WM_CLEAR, 0, 0);
				}*/
			}
			else if (GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT_LOGIN)) == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"Enter username");
			
		}
		break;
		}
		break;


	case WM_CLOSE: //send when the button 'close' is pushed. (X)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}