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

	//初始化
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
	
	//第二行
	vitem.pszText = "notepad.exe";
	vitem.iItem = 1;//修改行
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
//初始化进程list
void InitProcessListView(HWND hwndDlg)
{
	LV_COLUMN lv;
	HWND hListProcess;

	//初始化
	memset(&lv, 0, sizeof(LV_COLUMN));
	//获取IDC_LIST_PROCESS 句柄
	hListProcess = GetDlgItem(hwndDlg, IDC_LIST_PROCESS);
	//设置整行选中
	SendMessage(hListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	//第一行
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("进程");
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
	lv.pszText = TEXT("镜像基址");
	lv.cx = 80;
	lv.iSubItem = 2;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("镜像大小");
	lv.cx = 80;
	lv.iSubItem = 3;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	
	EnumProcess(hListProcess);
}

//遍历模块
void EnumMoudle(HWND hListProcess,  // handle to dialog box
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
  )
{

	DWORD dwRowId;
	TCHAR szPid[0x20];
	LV_ITEM vitem;

	//初始化
	memset(&vitem, 0, sizeof(LV_ITEM));
	memset(szPid, 0, 0x20);
	
	//获取选择行
	dwRowId = SendMessage(hListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);

	if(dwRowId == -1)
	{
		MessageBox(NULL, TEXT("请选择进程"), TEXT("出错了"), MB_OK);
		return ;
	}

	//获取PID
	vitem.iSubItem = 1;
	vitem.pszText = szPid;
	vitem.cchTextMax = 0x20;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&vitem);

	MessageBox(NULL, szPid, TEXT("PID"), MB_OK);
}

//初始化模块list
void InitMoudleListView(HWND hwndDlg)
{
	LV_COLUMN lv;
	HWND hListMoudle;

	//初始化
	memset(&lv, 0, sizeof(LV_COLUMN));
	//获取IDC_LIST_PROCESS 句柄
	hListMoudle = GetDlgItem(hwndDlg, IDC_LIST_MOUDLE);
	//设置整行选中
	SendMessage(hListMoudle, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	//第一行
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("模块名称");
	lv.cx = 142;
	lv.iSubItem = 0;
	SendMessage(hListMoudle, LVM_INSERTCOLUMN, lv.iSubItem, (DWORD)&lv);	

	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv.pszText = TEXT("模块位置");
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
	PEOperation peOption ;//PE操作
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
	case WM_COMMAND://子窗口回调
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
	case WM_NOTIFY://list触发
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
	icex.dwSize = ICC_WIN95_CLASSES ;//ICC_WIN95_CLASSES 包含多个常用控件
	InitCommonControlsEx(&icex);
	
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);

	
	return 0;
}



