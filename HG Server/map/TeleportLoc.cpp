// TeleportLoc.cpp: implementation of the CTeleportLoc class.
//
//////////////////////////////////////////////////////////////////////

#include "TeleportLoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTeleportLoc::CTeleportLoc()
{

	memset(m_cDestMapName, 0, sizeof(m_cDestMapName));

	m_sSrcX   = -1;
	m_sSrcY	  = -1;
	m_sDestX  = -1;								    
	m_sDestY  = -1;
	m_sDestX2 = -1;
	m_sDestY2 = -1;

	m_iV1     = NULL;
	m_iV2     = NULL;
	m_dwTime  = NULL;
	m_dwTime2 = NULL;

	m_iNumSummonNpc = 0;
}

CTeleportLoc::~CTeleportLoc()
{

}
