// PETool.cpp: implementation of the PETool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PETool.h"

//////////////////////////////////////////////////////////////////////
// 加载、处理 PE
//////////////////////////////////////////////////////////////////////

PETool::PETool()
{

}	//TODO

PETool::~PETool()
{
	if(this->imageTable.FileBuffer != NULL)
		free(this->imageTable.FileBuffer);
	if(this->imageTable.ImageBuffer != NULL)
		free(this->imageTable.ImageBuffer);
}		

void PETool::analysis(_IMAGE_ADR_TABLE &imageTable)
{
	//解析PE
	imageTable.lpDosHeader = ( _IMAGE_DOS_HEADER *)imageTable.FileBuffer;
	imageTable.Signature = *(DWORD*)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew);
	imageTable.lpFileHeader = (_IMAGE_FILE_HEADER *)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew + sizeof(DWORD));
	imageTable.lpOptionHeader = (_IMAGE_OPTIONAL_HEADER *)((CHAR*)imageTable.lpFileHeader + sizeof(_IMAGE_FILE_HEADER));
	/*
	#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
	#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b
	*/
	//TODO
	/*
	if(imageTable.lpOptionHeader->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)//如果打开的文件是64位文件
	{
		imageTable.lpOptionHeader64 = (_IMAGE_OPTIONAL_HEADER64 *)((CHAR*)imageTable.lpFileHeader + sizeof(_IMAGE_FILE_HEADER));
		imageTable.lpOptionHeader = NULL;
	}*/
	imageTable.lpSectionHeader = (_IMAGE_SECTION_HEADER *)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew + sizeof(DWORD) + sizeof(_IMAGE_FILE_HEADER) + imageTable.lpFileHeader->SizeOfOptionalHeader);
}

void PETool::newPEImageTable(_IMAGE_ADR_TABLE &newImageTable)
{
	//创建_IMAGE_ADR_TABLE副本
	analysis(newImageTable);
}

//rva转换为foa
void* PETool::rvaToFoa(DWORD rva)
{
	DWORD foa;
	_IMAGE_SECTION_HEADER *lpSectionHeader = this->imageTable.lpSectionHeader;

	if(rva <= this->imageTable.lpOptionHeader->SizeOfHeaders)
	{
		foa = rva + (DWORD)this->imageTable.FileBuffer;//RVA在pe头里
		return (VOID *)foa;
	}

	for(int i = 0; i < this->imageTable.lpFileHeader->NumberOfSections; i++)
	{
		if((DWORD)rva - (DWORD)(lpSectionHeader + i)->VirtualAddress <= (lpSectionHeader + i)->Misc.VirtualSize)
		{
			//foa = fileBuffer + rva - va + raw;
			foa = (DWORD)this->imageTable.FileBuffer  + rva - (lpSectionHeader + i)->VirtualAddress + (lpSectionHeader + i)->PointerToRawData;
			return (VOID *)foa;
		}
	}
}

void* PETool::foaToRva(DWORD foa)
{
	//foa转换为rva
	return 0;
}