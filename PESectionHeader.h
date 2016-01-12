// PESectionHeader.h: interface for the PESectionHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PESECTIONHEADER_H__A863B3E6_9D09_4F76_9D88_5272E5069097__INCLUDED_)
#define AFX_PESECTIONHEADER_H__A863B3E6_9D09_4F76_9D88_5272E5069097__INCLUDED_

#include "resource.h"
#include "PEOperation.h"
#include <string>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PESectionHeader  
{
public:
	PESectionHeader();
	virtual ~PESectionHeader();

public:
	void ShowSectionView(HINSTANCE hInstance, HWND hwndDlg, CONST _IMAGE_SECTION_HEADER *lpSectionHeader, DWORD numberOfSections);
	void SetSectionInfoDlg(HWND hwndDlg, CONST _IMAGE_SECTION_HEADER *lpSectionHeader, DWORD numberOfSections);

};

#endif // !defined(AFX_PESECTIONHEADER_H__A863B3E6_9D09_4F76_9D88_5272E5069097__INCLUDED_)
