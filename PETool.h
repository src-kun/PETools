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
		DWORD *FileBuffer;							//文件缓冲
		DWORD *ImageBuffer;							//内存缓冲
		_IMAGE_DOS_HEADER *lpDosHeader;				//dos头指针
		DWORD Signature;
		IMAGE_FILE_HEADER *lpFileHeader;
		_IMAGE_OPTIONAL_HEADER *lpOptionHeader;		//TODO 智能识别文件的位数	
		_IMAGE_OPTIONAL_HEADER64 *lpOptionHeader64;	//TODO 智能识别文件的位数	
		PIMAGE_SECTION_HEADER lpSectionHeader;		//节表头指针
	}IMAGE_ADDRESS_TABLE, *PIMAGE_ADDRESS_TABLE;

public:
	_IMAGE_ADR_TABLE imageTable;					//文件缓冲区与PE结构
	_IMAGE_ADR_TABLE imageTableCpy;					//缓冲区副本 修改文件时用


public:
	PETool();
	virtual ~PETool();


public:
	void initBuffer(DWORD size);
	void analysis(_IMAGE_ADR_TABLE &imageTable);								//解析PE
	void newPEImageTable(_IMAGE_ADR_TABLE &newImageTable);
	void *PETool::rvaToFoa(DWORD rva);								//rva转换为foa
	void *PETool::foaToRva(DWORD foa);								//foa转换为rva
};


#endif // !defined(AFX_PETOOL_H__1D946039_7EF9_4D3B_85DD_745DD480D2EA__INCLUDED_)
