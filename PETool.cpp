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

}

PETool::~PETool()
{
	if(this->imageTable.FileBuffer != NULL)
		free(this->imageTable.FileBuffer);
	if(this->imageTable.ImageBuffer != NULL)
		free(this->imageTable.ImageBuffer);
	if(this->imageTable.NewBuffer != NULL)
		free(this->imageTable.NewBuffer);
}		

void PETool::analysis(_IMAGE_ADR_TABLE &imageTable)
{
	//解析PE
	imageTable.lpDosHeader = ( _IMAGE_DOS_HEADER *)imageTable.FileBuffer;
	imageTable.Signature = *(DWORD*)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew);
	imageTable.lpFileHeader = (_IMAGE_FILE_HEADER *)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew + sizeof(DWORD));
	memcpy(&imageTable.optionHeader, ((CHAR*)imageTable.lpFileHeader + sizeof(_IMAGE_FILE_HEADER)), imageTable.lpFileHeader->SizeOfOptionalHeader);
	imageTable.lpSectionHeader = (_IMAGE_SECTION_HEADER *)((CHAR*)this->imageTable.FileBuffer + imageTable.lpDosHeader->e_lfanew + sizeof(DWORD) + sizeof(_IMAGE_FILE_HEADER) + imageTable.lpFileHeader->SizeOfOptionalHeader);
}

void PETool::rvaToFoa(DWORD &rva, DWORD* foa)
{
	//rva转换为foa
}

void PETool::foaToRva(DWORD &foa, DWORD* rva)
{
	//foa转换为rva
}