// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\..\Shared\common.h"

class CItem;

class CTile  
{												  
public:
	CTile();
	virtual ~CTile();

	bool IsBuild()		const { return (m_attribute & 0x10) ? true : false; }
	bool IsFarm()		const { return (m_attribute & 0x20) ? true : false; }
	bool IsTele()		const { return (m_attribute & 0x40) ? true : false; }
	bool IsMovable()	const { return (m_attribute & 0x80 || !m_bIsTempMoveAllowed) ? false : true; }

	char  m_cOwnerClass;		// OT_PLAYER / OT_NPC
	short m_sOwner;

	char  m_cDeadOwnerClass;	
	short m_sDeadOwner;

	CItem * m_pItem[ITEMS_PER_TILE];
	char  m_cTotalItem;

	uint16  m_wDynamicObjectID;
	short m_sDynamicObjectType;
	uint32 m_dwDynamicObjectRegisterTime;

	bool  m_bIsMoveAllowed, m_bIsTeleport, m_bIsWater, m_bIsTempMoveAllowed;
	bool  m_bIsFarmingAllowed; 


	int   m_iOccupyStatus;    
	int   m_iOccupyFlagIndex; 
	// Crusade
	uint8	  m_attribute;		  

};

#endif // !defined(AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
