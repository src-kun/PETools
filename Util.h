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

#define FILE_OPEN_SECCESS						  0x0		//δ֪����
#define FILE_BUFFER_IS_NULL                       0x1		//fileBufferΪnull
#define FILE_OPEN_ERROR							  0x2		//���ļ�ʧ��
#define FILE_READ_ERROR							  0x3		//��ȡ�ļ�ʧ��
#define FILE_UNKOWN_ERROR						  0x4		//δ֪����

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Util  
{
public:
	Util();
	virtual ~Util();

public:
	void OutputDebugPtf(const char *format,...);											//���debug��Ϣ
	void OpenFileWindow(LPOPENFILENAME stOpenFile, HWND hwndDlg);							//���ļ��б���
	void GetError();																		//������ϵͳ����
	int ReadFileToMemory(DWORD **fileBuffer, DWORD &fileSize, TCHAR *filePath);								//���ļ���ȡ���ڴ���

};

#endif // !defined(AFX_UTIL_H__A1CB2496_6393_4BE9_90EE_AEBED27DD5B0__INCLUDED_)
