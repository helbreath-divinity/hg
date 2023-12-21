// Teleport.cpp: implementation of the CTeleport class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\shared\typedefs.h"
#include "Teleport.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTeleport::CTeleport()
{
	memset(m_cNpcname, 0, sizeof(m_cNpcname));
	memset(m_cSourceMap, 0, sizeof(m_cSourceMap));
	memset(m_cTargetMap, 0, sizeof(m_cTargetMap));

	m_iX = m_iY = -5;
	m_cost		= 0;
	m_iMinLvl	= 0;
	m_iMaxLvl	= 0;
	m_iSide		= 0;
	m_bNetural	= true;
	m_bCriminal	= true;
	m_adminCreated = false;
	m_donateEvent = false;
}

CTeleport::~CTeleport()
{

}
