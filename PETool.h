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
		    typedef struct _IMAGE_OPTIONAL_HEADER {  
			WORD Magic ;                
			BYTE MajorLinkerVersion;         
			DWORD MinorLinkerVersion;         
			DWORD SizeOfCode;                 
			DWORD SizeOfInitializedData;      
			DWORD SizeOfUninitializedData;    
			DWORD AddressOfEntryPoint;   
			DWORD BaseOfCode;                 
			DWORD ImageBase;                  
			DWORD SectionAlignment;           
			DWORD FileAlignment;              
			WORD MajorOperatingSystemVersion;
			WORD MinorOperatingSystemVersion;
			WORD MajorImageVersion;          
			WORD MinorImageVersion;          
			WORD MajorSubsystemVersion;      
			WORD MinorSubsystemVersion;      
			DWORD Win32VersionValue;          
			DWORD SizeOfImage;                
			DWORD SizeOfHeaders;              
			DWORD CheckSum;                   
			WORD Subsystem;                  
			WORD DllCharacteristics;         
			DWORD SizeOfStackReserve;         
			DWORD SizeOfStackCommit;          
			DWORD SizeOfHeapReserve;          
			DWORD SizeOfHeapCommit;           
			DWORD LoaderFlags;                
			DWORD NumberOfRvaAndSizes;                 
			IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];  
    } ;  

	struct _IMAGE_ADR_TABLE
	{
		DWORD  FileSize;
		DWORD *FileBuffer;							//文件缓冲
		DWORD *ImageBuffer;							//内存缓冲
		DWORD *NewBuffer;							//修改后的缓冲
		_IMAGE_DOS_HEADER *lpDosHeader;				//dos头指针
		DWORD Signature;
		IMAGE_FILE_HEADER *lpFileHeader;
		_IMAGE_OPTIONAL_HEADER64 optionHeader;				
		PIMAGE_SECTION_HEADER lpSectionHeader;		//节表头指针
	}IMAGE_ADDRESS_TABLE, *PIMAGE_ADDRESS_TABLE;

public:
	_IMAGE_ADR_TABLE imageTable;


public:
	PETool();
	virtual ~PETool();


public:
	void initBuffer(DWORD size);
	void analysis(_IMAGE_ADR_TABLE &imageTable);							//解析PE
	void PETool::rvaToFoa(DWORD &rva, DWORD *foa);								//rva转换为foa
	void PETool::foaToRva(DWORD &foa, DWORD *rva);								//foa转换为rva
};


#endif // !defined(AFX_PETOOL_H__1D946039_7EF9_4D3B_85DD_745DD480D2EA__INCLUDED_)
