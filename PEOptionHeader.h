// PEOptionHeader.h: interface for the PEOptionHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEOPTIONHEADER_H__C2F4E306_A370_4813_886F_512594CD92F7__INCLUDED_)
#define AFX_PEOPTIONHEADER_H__C2F4E306_A370_4813_886F_512594CD92F7__INCLUDED_

#include "resource.h"
#include <string>
#include "PETool.h"



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PEOptionHeader  
{
public:
	PEOptionHeader();
	virtual ~PEOptionHeader();

public:
	void ShowDirtoryView(HINSTANCE hInstance, HWND hwndDlg, PETool *tool);
	void ParsingDirtoryInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY DataDirectory[16]);
	void ShowImportView(HWND hwndDlg);
	void ParsingImportInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY importDirectory);
	void ShowExportView(HWND hwndDlg);
	void ParsingExportInfo(HWND hwndDlg, IMAGE_DATA_DIRECTORY exportDirectory);

};

#endif // !defined(AFX_PEOPTIONHEADER_H__C2F4E306_A370_4813_886F_512594CD92F7__INCLUDED_)
