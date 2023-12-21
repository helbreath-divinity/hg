// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "Msg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_pData  = NULL;
	m_dwSize = NULL;
}

CMsg::~CMsg()						   
{
	if (m_pData != NULL) delete[] m_pData;
}

bool CMsg::bPut(char cFrom, char * pData, uint32 dwSize, int iIndex, char cKey)
{
	m_pData = new char [dwSize + 1];
	if (m_pData == NULL) return false;
	memset(m_pData, 0, dwSize + 1);
	memcpy(m_pData, pData, dwSize);

	m_dwSize = dwSize;
	m_cFrom  = cFrom;
	m_iIndex = iIndex;
	m_cKey   = cKey;

	return true;
}

void CMsg::Get(char * pFrom, char * pData, uint32 * pSize, int * pIndex, char * pKey)
{
	*pFrom  = m_cFrom;
	memcpy(pData, m_pData, m_dwSize);
	*pSize  = m_dwSize;
	*pIndex = m_iIndex;
	*pKey   = m_cKey;
}
