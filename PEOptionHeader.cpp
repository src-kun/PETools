// PEOptionHeader.cpp: implementation of the PEOptionHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PEOptionHeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HINSTANCE hAppInstance;
PEOptionHeader optionHeaderCls;
PETool *peTool;

PEOptionHeader::PEOptionHeader()
{

}

PEOptionHeader::~PEOptionHeader()
{

}

BOOL CALLBACK DirtoryViewProc(
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
			optionHeaderCls.ParsingDirtoryInfo(hwndDlg, peTool->imageTable.lpOptionHeader->DataDirectory);
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
			case IDC_BUTTON_OPEN_IMPORT_VIEW:
				{
					optionHeaderCls.ShowImportView(hwndDlg);
					break;
				}
			case IDC_BUTTON_OPEN_EXPORT_VIEW:
				{
					optionHeaderCls.ShowExportView(hwndDlg);
					break;
				}

			}
		}
	}
	return FALSE;
}


void PEOptionHeader::ShowDirtoryView(HINSTANCE hInstance, HWND hwndDlg, PETool *tool)
 {
	peTool = tool;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_DIRCTORY_VIEW), hwndDlg, DirtoryViewProc);
}

void PEOptionHeader::ParsingDirtoryInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY DataDirectory[16])
{
	CHAR szBuffer[16] = {0};
	//������
	sprintf(szBuffer, "%08x", DataDirectory[0].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_EXPORT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[0].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_EXPORT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�����
	sprintf(szBuffer, "%08x", DataDirectory[1].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_IMPORT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[1].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_IMPORT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��Դ��
	sprintf(szBuffer, "%08x", DataDirectory[2].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_RESOURCE_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[2].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_RESOURCE_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�쳣��
	sprintf(szBuffer, "%08x", DataDirectory[3].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_EXCEPTION_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[3].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_EXCEPTION_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��ȫ֤��
	sprintf(szBuffer, "%08x", DataDirectory[4].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_SECURITY_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[4].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_SECURITY_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�ض�λ��
	sprintf(szBuffer, "%08x", DataDirectory[5].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_BASERELOC_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[5].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_BASERELOC_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//������Ϣ��
	sprintf(szBuffer, "%08x", DataDirectory[6].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_DEBUG_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[6].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_DEBUG_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��Ȩ���б�
	sprintf(szBuffer, "%08x", DataDirectory[7].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_COPYRIGHT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[7].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_COPYRIGHT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//ȫ��ָ���
	sprintf(szBuffer, "%08x", DataDirectory[8].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_GLOBALPTR_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[8].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_CLOBALPTR_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//TLS��
	sprintf(szBuffer, "%08x", DataDirectory[9].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_TLSTABLE_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[9].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_TLSTABLE_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��������
	sprintf(szBuffer, "%08x", DataDirectory[10].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_LOADCONFIG_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[10].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_LOADCONFIG_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//������
	sprintf(szBuffer, "%08x", DataDirectory[11].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_BOUNDIMPORT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[11].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_BOUNDIMPORT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	//IAT
	sprintf(szBuffer, "%08x", DataDirectory[12].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_IAT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[12].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_IAT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�ӳٵ����
	sprintf(szBuffer, "%08x", DataDirectory[13].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_DELAYIMPORT_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[13].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_DELAYIMPORT_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//COM
	sprintf(szBuffer, "%08x", DataDirectory[14].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_COM_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[14].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_COM_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//����
	sprintf(szBuffer, "%08x", DataDirectory[15].VirtualAddress);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_RESERVED_VIRTUALADDRESS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	sprintf(szBuffer, "%08x",  DataDirectory[15].Size);
	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_RESERVED_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
}

BOOL CALLBACK ImportDirtoryViewProc(
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
			optionHeaderCls.ParsingImportInfo(hwndDlg, peTool->imageTable.lpOptionHeader->DataDirectory[1]);
			break;
		}
	case WM_CLOSE:
		{
			EndDialog(hwndDlg,0);
			break;
		}
	case WM_COMMAND://�Ӵ��ڻص�
		{
			//switch(LOWORD(wParam))
			//{
			

			//}
		}
	}
	return FALSE;
}


void PEOptionHeader::ShowImportView(HWND hwndDlg)
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_IMPORT_VIEW), hwndDlg, ImportDirtoryViewProc);
}

	//������
void PEOptionHeader::ParsingImportInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY directory)
{
	IMAGE_IMPORT_DESCRIPTOR *import;
	_IMAGE_IMPORT_BY_NAME *INT = {0};
	DWORD len = 0;
	import = (IMAGE_IMPORT_DESCRIPTOR *)peTool->rvaToFoa(directory.VirtualAddress);
	CHAR szBuffer[20 * 1024] = {0};

	while(import->FirstThunk)
	{
		DWORD* thunk = (DWORD*)peTool->rvaToFoa(import->OriginalFirstThunk);
		len += sprintf(szBuffer + len, "%s\r\n", "--------------------------------------------------------------------------------------");
		len += sprintf(szBuffer + len, "%s\r\n", peTool->rvaToFoa(import->Name));
		len += sprintf(szBuffer + len, "%s\r\n", "--------------------------------------------------------------------------------------");
		len += sprintf(szBuffer + len, "%s", "API Name\t\t\t\t");
		len += sprintf(szBuffer + len, "%s", "Hint\t");
		len += sprintf(szBuffer + len, "%s\r\n", "Ordinal RVA");
		while(*thunk)
		{
			if((*thunk & 0x80000000 ) - 0x80000000)
			{
				INT = (_IMAGE_IMPORT_BY_NAME *)peTool->rvaToFoa(*thunk);
				len += sprintf(szBuffer + len, "%s\t\t\t\t", INT->Name);
				len += sprintf(szBuffer + len, "%04x\t", INT->Hint);
				len += sprintf(szBuffer + len, "-\r\n", INT->Hint);
			}else{
				len += sprintf(szBuffer + len, "-\t\t\t\t", "");
				len += sprintf(szBuffer + len, "-\t", "");
				len += sprintf(szBuffer + len, "%04x\r\n", *thunk - 0x80000000);
			}
				
			thunk++;
		}
		import++;
	}


	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_IMPORT_INFO,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
}

BOOL CALLBACK ExportDirtoryViewProc(
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
			optionHeaderCls.ParsingExportInfo(hwndDlg, peTool->imageTable.lpOptionHeader->DataDirectory[0]);
			break;
		}
	case WM_CLOSE:
		{
			EndDialog(hwndDlg,0);
			break;
		}
	case WM_COMMAND://�Ӵ��ڻص�
		{
			//switch(LOWORD(wParam))
			//{
			

			//}
		}
	}
	return FALSE;
}

//�����
void PEOptionHeader::ShowExportView(HWND hwndDlg)
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_EXPORT_VIEW), hwndDlg, ExportDirtoryViewProc);
}

void PEOptionHeader::ParsingExportInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY exportDirectory)
{
	DWORD len = 0;
	CHAR szBuffer[20 * 1024] = {0};

	len += sprintf(szBuffer + len, "%s\r\n", "
	len += sprintf(szBuffer + len, "%s\r\n", "--------------------------------------------------------------------------------------");

	SendDlgItemMessage(hwndDlg,
							   IDC_EDIT_EXPORT_INFO,
							   WM_SETTEXT,
							   0,
							   (DWORD)"test");
}