// PEOperation.cpp: implementation of the PEOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEOperation.h"

//////////////////////////////////////////////////////////////////////
// pe查看界面
//////////////////////////////////////////////////////////////////////


static PETool peTool;
static PEOperation peOperation;
static Util util;
static CHAR filePath[2048];

//回调函数 <-> IDD_DIALOG_PEVIEW
BOOL CALLBACK PEViewProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			peOperation.ParsingPeInfo(hwndDlg, filePath);
			break;
		}
	case WM_CLOSE:
		{
			EndDialog(hwndDlg,0);
			break;
		}
	case WM_COMMAND://子窗口回调
		{
			switch(LOWORD(wParam))
			{

			case IDC_BUTTON_PE_EXIT:
				{
					EndDialog(hwndDlg,0);
					break;
				}
			case IDC_BUTTON_SECTION:
				{
					//打开节表视图
					break;
				}
			}
		}
	}
	return FALSE;
}

PEOperation::PEOperation()
{

}

PEOperation::~PEOperation()
{

}

void PEOperation::ShowPEView(HINSTANCE hInstance, HWND hwndDlg, TCHAR *path)
{

	memcpy(filePath, path, strlen(path));
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_PEVIEW), hwndDlg, PEViewProc);
}

void PEOperation::ParsingPeInfo(HWND hwndDlg, TCHAR* filePath)
{
	CHAR MZ_FLAG[3] = {0};//MZ标记
	
	util.ReadFileToMemory(&peTool.imageTable.FileBuffer, peTool.imageTable.FileSize, filePath);

	memcpy(MZ_FLAG, peTool.imageTable.FileBuffer, 2);
	if(strcmp("MZ", MZ_FLAG))
	{
		TCHAR* msg = filePath;
		strcat(msg, TEXT("不是可执行文件！"));
		MessageBox(0, msg, TEXT("提示 :)"), 0);
		//EndDialog(hwndDlg, 0);
		return ;
	}
	//TODO 下一步写PE解析
	peTool.analysis();
	TCHAR szBuffer[128] = {0};
	memcpy(szBuffer, "00410000", 128);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_ENTRY_POINT,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
}
