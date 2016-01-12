// PESectionHeader.cpp: implementation of the PESectionHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PESectionHeader.h"

//////////////////////////////////////////////////////////////////////
// CONSTruction/Destruction
//////////////////////////////////////////////////////////////////////
 _IMAGE_SECTION_HEADER *lpSectionHeader ;
static PESectionHeader sectionHeaderOpt;
static DWORD number;

BOOL CALLBACK SectionViewProc(
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
				sectionHeaderOpt.SetSectionInfoDlg(hwndDlg, lpSectionHeader, number);
				break;
			}
		case WM_CLOSE:
			{
				EndDialog(hwndDlg,0);
				break;
			}
		}
	return FALSE;
}

PESectionHeader::PESectionHeader()
{

}

PESectionHeader::~PESectionHeader()
{

}

void PESectionHeader::ShowSectionView(HINSTANCE hInstance, HWND hwndDlg, CONST _IMAGE_SECTION_HEADER *lpSection, DWORD numberOfSections)
{
	lpSectionHeader = (_IMAGE_SECTION_HEADER *)lpSection;
	number = numberOfSections;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_SECTION_VIEW), hwndDlg, SectionViewProc);
}

void PESectionHeader::SetSectionInfoDlg(HWND hwndDlg, CONST _IMAGE_SECTION_HEADER *lpSectionHeader, DWORD numberOfSections)
{
	_IMAGE_SECTION_HEADER* section = (_IMAGE_SECTION_HEADER*)lpSectionHeader;
	TCHAR szBuffer[9 * 4096] = {0};
	TCHAR Name[0x9] = {0};
	int len = 0;
	CHAR* sectionContent[0xA] = {
								"Name:\t\t\t",
								"VirtualSize:\t\t",
								"VirtualAddress:\t\t",
								"SizeOfRawData:\t\t",
								"PointerToRawData:\t\t",
								"PointerToRelocations:\t",
								"PointerToLinenumbers:\t",
								"NumberOfRelocations:\t",
								"NumberOfLinenumbers:\t",
								"Characteristics:\t\t", };
	for(DWORD i = 0; i < numberOfSections; i++)
	{

		memset(Name, 0, 0x9);
		//节名
		memcpy(Name, section->Name, 0x8);

		len += sprintf(szBuffer + len,"%s%s\r\n", 
				sectionContent[0], Name
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[1], section->Misc.VirtualSize  
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[2], section->VirtualAddress
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[3], section->SizeOfRawData
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[4], section->PointerToRawData
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[5], section->PointerToRelocations
				);
		
		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[6], section->PointerToLinenumbers
				);

		len += sprintf(szBuffer + len ,"%s%04x\r\n", 
				sectionContent[7], section->NumberOfRelocations
				);

		len += sprintf(szBuffer + len ,"%s%04x\r\n", 
				sectionContent[8], section->NumberOfLinenumbers
				);

		len += sprintf(szBuffer + len ,"%s%08x\r\n", 
				sectionContent[9], section->Characteristics
				);

		len += sprintf(szBuffer + len ,"%s\r\n", "--------------------------------------"
				);
		section++;
	}

	//,
	//	sectionContent[2], sectionHeader.VirtualAddress
	SendDlgItemMessage(hwndDlg,
				   IDC_TEST,
				   WM_SETTEXT,
				   0,
				   (DWORD)szBuffer);

	HDC hdc = ::GetDC(hwndDlg);

	::TextOutA(hdc,0,0,"文本内容",strlen("文本内容"));
	
}