// PETools.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "PEOperation.h"
#include "Util.h"

#pragma comment(lib, "comctl32.lib")
//
//OPENFILENAME

HINSTANCE hAppInstance;
static Util util;




void EnumProcess(HWND hListProcess)
{
	LV_ITEM vitem;

	//��ʼ��
	memset(&vitem, 0, sizeof(LV_ITEM));
	vitem.mask = LVIF_TEXT;

	vitem.pszText = "csrss.exe";
	vitem.iItem = 0;
	vitem.iSubItem = 0;
	ListView_InsertItem(hListProcess, &vitem);
	//SendMessage(hListProcess, LVM_INSERTITEM, 0, (DWORD)&vitem);

	vitem.pszText = TEXT("448");
	vitem.iSubItem = 1;
	ListView_SetItem(hListProcess, &vitem);

	vitem.pszText = TEXT("56000010");
	vitem.iSubItem = 2;
	ListView_SetItem(hListProcess, &vitem);

	vitem.pszText = TEXT("40001");
	vitem.iSubItem = 3;
	ListView_SetItem(hListProcess, &vitem);
	
	//�ڶ���
	vitem.pszText = "notepad.exe";
	vitem.iItem = 1;//�޸���
	vitem.iSubItem = 0;
	ListView_InsertItem(hListProcess, &vitem);
	//SendMessage(hListProcess, LVM_INSERTITEM, 0, (DWORD)&vitem);

	vitem.pszText = TEXT("125");
	vitem.iSubItem = 1;
	ListView_SetItem(hListProcess, &vitem);

	vitem.pszText = TEXT("71007000");
	vitem.iSubItem = 2;
	ListView_SetItem(hListProcess, &vitem);

	vitem.pszText = TEXT("800000");
	vitem.iSubItem = 3;
	ListView_SetItem(hListProcess, &vitem);
	
}
//��ʼ������list
void InitProcessListView(HWND hwndDlg)
{
	LV_COLUMN lv;
	HWND hListProcess;

	//��ʼ��
	memset(&lv, 0, sizeof(LV_COLUMN));
	//��ȡIDC_LIST_PROCESS ���
	hListProcess = GetDlgItem(hwndDlg, IDC_LIST_PROCESS);
	//��������ѡ��
	SendMessage(hListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	//��һ��
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("����");
	lv.cx = 172;
	lv.iSubItem = 0;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("PID");
	lv.cx = 80;
	lv.iSubItem = 1;
	//ListView_SetItem(hListProcess, &lv);
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("�����ַ");
	lv.cx = 80;
	lv.iSubItem = 2;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("�����С");
	lv.cx = 80;
	lv.iSubItem = 3;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	
	EnumProcess(hListProcess);
}

//����ģ��
void EnumMoudle(HWND hListProcess,  // handle to dialog box
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
  )
{

	DWORD dwRowId;
	TCHAR szPid[0x20];
	LV_ITEM vitem;

	//��ʼ��
	memset(&vitem, 0, sizeof(LV_ITEM));
	memset(szPid, 0, 0x20);
	
	//��ȡѡ����
	dwRowId = SendMessage(hListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);

	if(dwRowId == -1)
	{
		MessageBox(NULL, TEXT("��ѡ�����"), TEXT("������"), MB_OK);
		return ;
	}

	//��ȡPID
	vitem.iSubItem = 1;
	vitem.pszText = szPid;
	vitem.cchTextMax = 0x20;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&vitem);

	MessageBox(NULL, szPid, TEXT("PID"), MB_OK);
}

//��ʼ��ģ��list
void InitMoudleListView(HWND hwndDlg)
{
	LV_COLUMN lv;
	HWND hListMoudle;

	//��ʼ��
	memset(&lv, 0, sizeof(LV_COLUMN));
	//��ȡIDC_LIST_PROCESS ���
	hListMoudle = GetDlgItem(hwndDlg, IDC_LIST_MOUDLE);
	//��������ѡ��
	SendMessage(hListMoudle, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	//��һ��
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("ģ������");
	lv.cx = 142;
	lv.iSubItem = 0;
	SendMessage(hListMoudle, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("ģ��λ��");
	lv.cx = 270;
	lv.iSubItem = 1;
	//ListView_SetItem(hListProcess, &lv);
	SendMessage(hListMoudle, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	
}


BOOL CALLBACK DialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	PEOperation peOption ;//PE����
	OPENFILENAME stOpenFile;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			InitProcessListView(hwndDlg);
			InitMoudleListView(hwndDlg);
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

			case IDC_BUTTON_EXIT:
				{
					EndDialog(hwndDlg,0);
					return TRUE;
				}
			case IDC_BUTTON_PETOOLS:
				{
					util.OpenFileWindow(&stOpenFile ,hwndDlg);
					peOption.ShowPEView(hAppInstance, hwndDlg, stOpenFile.lpstrFile);
					break;
				}
			}
		}
	case WM_NOTIFY://list����
		{
			NMHDR *pNMHDR = (NMHDR*)lParam;
			if(wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
			{
				EnumMoudle(GetDlgItem(hwndDlg, IDC_LIST_PROCESS), wParam, lParam);
			}
			break;
		}
	}

	return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	hAppInstance = hInstance;
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = sizeof(INITCOMMONCONTROLSEX);
	icex.dwSize = ICC_WIN95_CLASSES ;//ICC_WIN95_CLASSES ����������ÿؼ�
	InitCommonControlsEx(&icex);
	
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);

	
	return 0;
}



