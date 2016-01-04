// Util.cpp: implementation of the Util class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Util.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Util::Util()
{

}

Util::~Util()
{

}


void Util::OutputDebugPtf(const char *format,...)
{
    va_list vlArgs;
	char *strBuffer = (char*)GlobalAlloc(GPTR, 4096);

	va_start(vlArgs, format);
	_vsnprintf(strBuffer, 4096 - 1, format, vlArgs);
	va_end(vlArgs);
	strcat(strBuffer, "\n");
	OutputDebugStringA(strBuffer);
	GlobalFree(strBuffer);
	return ;
}

void Util::OpenFileWindow(LPOPENFILENAME stOpenFile, HWND hwndDlg)
{
		TCHAR szPeFileExt[100] = "*.exe;*.dll;*.sys";
		TCHAR szFileName[1024];
		memset(szFileName, 0, 256);
		memset(stOpenFile, 0, sizeof(OPENFILENAME));
		stOpenFile->lStructSize = sizeof(OPENFILENAME);
		stOpenFile->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
		stOpenFile->hwndOwner = hwndDlg;
		stOpenFile->lpstrFilter = szPeFileExt;
		stOpenFile->lpstrFile = szFileName;
		stOpenFile->nMaxFile = MAX_PATH;
		GetOpenFileName(stOpenFile);
		MessageBox(NULL, stOpenFile->lpstrFile, TEXT("PID"), MB_OK);
}

void Util::GetError()
{
	OutputDebugPtf("%d", GetLastError());
}

int Util::ReadFileToMemory(DWORD **fileBuffer, DWORD &fileSize, TCHAR *filePath)
{
	char mz_check[3] = {0};
	FILE *fp = NULL;

	fp = fopen(filePath, "rb"); //打开文件
	if(fp == NULL)//打开文件失败
		return FILE_OPEN_ERROR;

	/*计算文件的长度*/
	fseek(fp, 0, SEEK_END); //文件指针移到文件尾 
	fileSize = ftell(fp);  //得到当前指针位置, 即是文件的长度
	rewind(fp);    //文件指针恢复到文件头位置

	*fileBuffer = (DWORD*)malloc(fileSize);
	if(*fileBuffer == NULL)//文件缓冲区为空
		return FILE_BUFFER_IS_NULL;
	memset(*fileBuffer, 0, fileSize);//清零

	if(!fread(*fileBuffer, sizeof(char), fileSize, fp))//将文件读入申请的内存
		return FILE_READ_ERROR;//读取文件失败

	return FILE_OPEN_SECCESS;
}

/*

	memcpy(mz_check, fileBuff, 2);//获取程序标记
	if(strcmp(mz_check,"MZ"))//判断文件是否为可执行文件
	{
		printf("文件不是可执行程序！\n");
		exit(0);
	}

	return fileBuff;



  */