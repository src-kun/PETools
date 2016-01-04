// PEDosHeader.h: interface for the PEDosHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEDOSHEADER_H__53FAFB4A_A358_458B_9FFB_6551EC6B4CC2__INCLUDED_)
#define AFX_PEDOSHEADER_H__53FAFB4A_A358_458B_9FFB_6551EC6B4CC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PEDosHeader  
{
public:
	PEDosHeader();
	virtual ~PEDosHeader();

public:
	void DosParsing(DWORD* fileBuffer);

};

#endif // !defined(AFX_PEDOSHEADER_H__53FAFB4A_A358_458B_9FFB_6551EC6B4CC2__INCLUDED_)
