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

	fp = fopen(filePath, "rb"); //���ļ�
	if(fp == NULL)//���ļ�ʧ��
		return FILE_OPEN_ERROR;

	/*�����ļ��ĳ���*/
	fseek(fp, 0, SEEK_END); //�ļ�ָ���Ƶ��ļ�β 
	fileSize = ftell(fp);  //�õ���ǰָ��λ��, �����ļ��ĳ���
	rewind(fp);    //�ļ�ָ��ָ����ļ�ͷλ��

	*fileBuffer = (DWORD*)malloc(fileSize);
	if(*fileBuffer == NULL)//�ļ�������Ϊ��
		return FILE_BUFFER_IS_NULL;
	memset(*fileBuffer, 0, fileSize);//����

	if(!fread(*fileBuffer, sizeof(char), fileSize, fp))//���ļ�����������ڴ�
		return FILE_READ_ERROR;//��ȡ�ļ�ʧ��

	return FILE_OPEN_SECCESS;
}

/*

	memcpy(mz_check, fileBuff, 2);//��ȡ������
	if(strcmp(mz_check,"MZ"))//�ж��ļ��Ƿ�Ϊ��ִ���ļ�
	{
		printf("�ļ����ǿ�ִ�г���\n");
		exit(0);
	}

	return fileBuff;



  */