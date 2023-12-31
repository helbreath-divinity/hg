// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\..\Shared\TypeDefs.h"

#define MSGFROM_CLIENT		1
#define MSGFROM_LOGSERVER	2

class CMsg  								 
{
public:

	void Get(char * pFrom, char * pData, uint32 * pSize, int * pIndex, char * pKey);
	bool bPut(char cFrom, char * pData, uint32 dwSize, int iIndex, char cKey);
	CMsg();
	virtual ~CMsg();

	char   m_cFrom;

	char * m_pData;
	uint32  m_dwSize;

	int    m_iIndex;
	char   m_cKey;   
};

#endif // !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
