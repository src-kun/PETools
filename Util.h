// Util.h: interface for the Util class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__A1CB2496_6393_4BE9_90EE_AEBED27DD5B0__INCLUDED_)
#define AFX_UTIL_H__A1CB2496_6393_4BE9_90EE_AEBED27DD5B0__INCLUDED_

#include <string>
#include <commctrl.h>
#include <windows.h>
#include <commdlg.h>

#pragma comment(lib, "comdlg32.lib")

#define FILE_OPEN_SECCESS						  0x0		//未知错误
#define FILE_BUFFER_IS_NULL                       0x1		//fileBuffer为null
#define FILE_OPEN_ERROR							  0x2		//打开文件失败
#define FILE_READ_ERROR							  0x3		//读取文件失败
#define FILE_UNKOWN_ERROR						  0x4		//未知错误

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Util  
{
public:
	Util();
	virtual ~Util();

public:
	void OutputDebugPtf(const char *format,...);											//输出debug信息
	void OpenFileWindow(LPOPENFILENAME stOpenFile, HWND hwndDlg);							//打开文件列表窗口
	void GetError();																		//输出最后系统错误
	int ReadFileToMemory(DWORD **fileBuffer, DWORD &fileSize, TCHAR *filePath);								//将文件读取到内存中

};

#endif // !defined(AFX_UTIL_H__A1CB2496_6393_4BE9_90EE_AEBED27DD5B0__INCLUDED_)
