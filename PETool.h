// PETool.h: interface for the PETool class.
//
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "PEDosHeader.h"

#if !defined(AFX_PETOOL_H__1D946039_7EF9_4D3B_85DD_745DD480D2EA__INCLUDED_)
#define AFX_PETOOL_H__1D946039_7EF9_4D3B_85DD_745DD480D2EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PETool  
{	
public:
	struct _IMAGE_ADR_TABLE
	{
		DWORD  FileSize;
		DWORD *FileBuffer;							//�ļ�����
		DWORD *ImageBuffer;							//�ڴ滺��
		DWORD *NewBuffer;							//�޸ĺ�Ļ���
		PIMAGE_DOS_HEADER lpDosHeader;				//dosͷָ��
		PIMAGE_FILE_HEADER lpFileHeader;			//�ļ�ͷָ��
		PIMAGE_SECTION_HEADER lpSectionHeader;		//�ڱ�ͷָ��
	}IMAGE_ADDRESS_TABLE, *PIMAGE_ADDRESS_TABLE;

public:
	_IMAGE_ADR_TABLE imageTable;


public:
	PETool();
	virtual ~PETool();


public:
	void initBuffer(DWORD size);
	void analysis();							//����PE
	void PETool::rvaToFoa(DWORD &rva, DWORD *foa);								//rvaת��Ϊfoa
	void PETool::foaToRva(DWORD &foa, DWORD *rva);								//foaת��Ϊrva
};


#endif // !defined(AFX_PETOOL_H__1D946039_7EF9_4D3B_85DD_745DD480D2EA__INCLUDED_)
