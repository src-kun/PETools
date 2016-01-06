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
static HWND PEINFO_HWNDDLG;

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
			PEINFO_HWNDDLG = hwndDlg;
			peOperation.ParsingPeInfo(filePath);
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
	if(!*path) return;
	memcpy(filePath, path, strlen(path));
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_PEVIEW), hwndDlg, PEViewProc);
}

void PEOperation::ParsingPeInfo(TCHAR* filePath)
{
	CHAR MZ_FLAG[3] = {0};//MZ���
	
	util.ReadFileToMemory(&peTool.imageTable.FileBuffer, peTool.imageTable.FileSize, filePath);

	memcpy(MZ_FLAG, peTool.imageTable.FileBuffer, 2);
	if(strcmp("MZ", MZ_FLAG))
	{
		TCHAR* msg = filePath;
		strcat(msg, TEXT("���ǿ�ִ���ļ���"));
		MessageBox(0, msg, TEXT("��ʾ :)"), 0);
		EndDialog(PEINFO_HWNDDLG, 0);
		return ;
	}
	peTool.analysis(peTool.imageTable);
	SetPeInfoDlg(peTool.imageTable);
}

void PEOperation::SetPeInfoDlg(PETool::_IMAGE_ADR_TABLE &imageTable)
{
	TCHAR szBuffer[0XF] = {0};
	TCHAR sectionName[0x9] = {0};
	
	//��ڵ�
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.AddressOfEntryPoint);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_ENTRY_POINT,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�����ַ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.ImageBase);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_IMAGE_BASE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�����С
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.SizeOfImage);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_IMAGE_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�����ַ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.BaseOfCode);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_CODE_BASE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	
	//�ڴ����
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.SectionAlignment);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_MEMERY_ALIGNMENT,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//�ļ�����
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.FileAlignment);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_FILE_ALIGNMENT,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��־��
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.optionHeader.Magic);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_FLAGE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��ϵͳ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.optionHeader.Subsystem);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_SUBSYSTEM,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//������Ŀ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.lpFileHeader->NumberOfSections);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_NUMBER_SECTIONS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//ʱ���
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.lpFileHeader->TimeDateStamp);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_TIME_DATE_STAMP,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//PEͷ��С
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.SizeOfHeaders);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_SIZE_HEADERS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//����ֵ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.lpFileHeader->Characteristics);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_CHARACTERISTICS,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
	//У���
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%08x", imageTable.optionHeader.CheckSum);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_CHECK_SUM,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//��ѡPEͷ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.lpFileHeader->SizeOfOptionalHeader);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_SIZE_OPTIONAL,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);

	//Ŀ¼����Ŀ
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "0x%04x", imageTable.optionHeader.NumberOfRvaAndSizes);
	SendDlgItemMessage(PEINFO_HWNDDLG,
							   IDC_EDIT_NUMBER_RVA_SIZE,
							   WM_SETTEXT,
							   0,
							   (DWORD)szBuffer);
}