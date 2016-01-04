// PEOperation.h: interface for the PEOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEOPERATION_H__9E6E7D46_727B_4AE7_9148_9489DB33FB49__INCLUDED_)
#define AFX_PEOPERATION_H__9E6E7D46_727B_4AE7_9148_9489DB33FB49__INCLUDED_

#include "resource.h"
#include <string>
#include "PETool.h"
#include "Util.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PEOperation  
{
public:
	PEOperation();
	virtual ~PEOperation();

public:					
	void ShowPEView(HINSTANCE hInstance, HWND hwndDlg, CHAR *path);
	void ParsingPeInfo(HWND hwndDlg, CHAR* filePath);							//显示PE头信息

};

BOOL CALLBACK PEViewProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);

#endif // !defined(AFX_PEOPERATION_H__9E6E7D46_727B_4AE7_9148_9489DB33FB49__INCLUDED_)
