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

void PETool::analysis()
{
	this->imageTable.lpDosHeader = ( _IMAGE_DOS_HEADER *)this->imageTable.FileBuffer;
	this->imageTable.lpFileHeader = ( _IMAGE_FILE_HEADER *)(this->imageTable.lpDosHeader->e_lfanew + (DWORD)this->imageTable.FileBuffer);
	//this->
	//解析PE
}

void PETool::rvaToFoa(DWORD &rva, DWORD* foa)
{
	//rva转换为foa
}

void PETool::foaToRva(DWORD &foa, DWORD* rva)
{
	//foa转换为rva
}