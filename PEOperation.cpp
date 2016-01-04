// PEOperation.cpp: implementation of the PEOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEOperation.h"

//////////////////////////////////////////////////////////////////////
// pe�鿴����
//////////////////////////////////////////////////////////////////////


static PETool peTool;
static PEOperation peOperation;
static Util util;
static CHAR filePath[2048];

//�ص����� <-> IDD_DIALOG_PEVIEW
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
	case WM_COMMAND://�Ӵ��ڻص�
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
					//�򿪽ڱ���ͼ
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
	CHAR MZ_FLAG[3] = {0};//MZ���
	
	util.ReadFileToMemory(&peTool.imageTable.FileBuffer, peTool.imageTable.FileSize, filePath);

	memcpy(MZ_FLAG, peTool.imageTable.FileBuffer, 2);
	if(strcmp("MZ", MZ_FLAG))
	{
		TCHAR* msg = filePath;
		strcat(msg, TEXT("���ǿ�ִ���ļ���"));
		MessageBox(0, msg, TEXT("��ʾ :)"), 0);
		//EndDialog(hwndDlg, 0);
		return ;
	}
	//TODO ��һ��дPE����
	peTool.analysis();
	TCHAR szBuffer[128] = {0};
	memcpy(szBuffer, "00410000", 128);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_ENTRY_POINT,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
}
