// Item.h: interface for the CItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>
#include "..\..\..\shared\common.h"
#include "..\..\..\shared\maths.h"
#include "..\..\..\shared\items.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum ItemStat{
	ITEMSTAT_NONE,
	ITEMSTAT_CRITICAL,
	ITEMSTAT_POISONING,
	ITEMSTAT_RIGHTEOUS,
	ITEMSTAT_UNUSED,		// UNUSED
	ITEMSTAT_AGILE,
	ITEMSTAT_LIGHT,
	ITEMSTAT_SHARP,
	ITEMSTAT_STRONG,
	ITEMSTAT_ANCIENT,
	ITEMSTAT_CASTPROB,
	ITEMSTAT_MANACONV,
	ITEMSTAT_CRITICAL2
};

enum ItemStat2{
	ITEMSTAT2_NONE,
	ITEMSTAT2_PSNRES,
	ITEMSTAT2_HITPROB,
	ITEMSTAT2_DEF,
	ITEMSTAT2_HPREC,
	ITEMSTAT2_SPREC,
	ITEMSTAT2_MPREC,
	ITEMSTAT2_MR,
	ITEMSTAT2_PA,
	ITEMSTAT2_MA,
	ITEMSTAT2_CAD,
	ITEMSTAT2_EXP,
	ITEMSTAT2_GOLD
};

const struct ItemStats2{
	char * desc;
	uint32 mult;
} itemStats2[] = {
	{"",0},
	{"PSN", 7},
	{"HIT", 7},
	{"DF", 7},
	{"HP", 7},
	{"SP", 7},
	{"MP", 7},
	{"MR", 7},
	{"PA", 3},
	{"MA", 3},
	{"CAD", 1},
	{"XP", 10},
	{"GOLD", 10},
	{"",0}
};

#define MAXITEMEQUIPPOS		15
#define EQUIPPOS_NONE		0
#define EQUIPPOS_HEAD		1
#define EQUIPPOS_BODY		2
#define EQUIPPOS_ARMS		3
#define EQUIPPOS_PANTS		4
#define EQUIPPOS_BOOTS		5
#define EQUIPPOS_NECK		6
#define EQUIPPOS_LHAND		7
#define EQUIPPOS_RHAND		8
#define EQUIPPOS_TWOHAND	9
#define EQUIPPOS_RFINGER	10
#define EQUIPPOS_LFINGER	11
#define EQUIPPOS_BACK		12
#define EQUIPPOS_FULLBODY	13     

enum ItemTypes
{
	ITEMTYPE_NOTUSED = -1,
	ITEMTYPE_NONE,				// 0
	ITEMTYPE_EQUIP,			// 1
	ITEMTYPE_APPLY,			// 2
	ITEMTYPE_USE_DEPLETE,	// 3
	ITEMTYPE_INSTALL,			// 4
	ITEMTYPE_CONSUME,			// 5
	ITEMTYPE_ARROW,			// 6
	ITEMTYPE_EAT,				// 7
	ITEMTYPE_USE_SKILL,		// 8
	ITEMTYPE_USE_PERM,		// 9
	ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX,	// 10
	ITEMTYPE_USE_DEPLETE_DEST,				// 11
	ITEMTYPE_MATERIAL,		// 12
	ITEMTYPE_RELIC				// 13
};


#define ITEMEFFECTTYPE_NONE				0
#define ITEMEFFECTTYPE_ATTACK			1
#define ITEMEFFECTTYPE_DEFENSE			2
#define ITEMEFFECTTYPE_ATTACK_ARROW		3
#define ITEMEFFECTTYPE_HP   		    4
#define ITEMEFFECTTYPE_MP   		    5
#define ITEMEFFECTTYPE_SP   		    6
#define ITEMEFFECTTYPE_HPSTOCK 		    7
#define ITEMEFFECTTYPE_GET			    8
#define ITEMEFFECTTYPE_STUDYSKILL		9
#define ITEMEFFECTTYPE_SHOWLOCATION		10
#define ITEMEFFECTTYPE_MAGIC			11
#define ITEMEFFECTTYPE_CHANGEATTR		12
#define ITEMEFFECTTYPE_ATTACK_MANASAVE	13
#define ITEMEFFECTTYPE_ADDEFFECT	    14
#define ITEMEFFECTTYPE_MAGICDAMAGESAVE	15
#define ITEMEFFECTTYPE_OCCUPYFLAG		16
#define ITEMEFFECTTYPE_DYE				17
#define ITEMEFFECTTYPE_STUDYMAGIC		18
#define ITEMEFFECTTYPE_ATTACK_MAXHPDOWN	19
#define ITEMEFFECTTYPE_ATTACK_DEFENSE	20
#define ITEMEFFECTTYPE_MATERIAL_ATTR	21
#define ITEMEFFECTTYPE_FIRMSTAMINAR		22
#define ITEMEFFECTTYPE_LOTTERY			23

#define ITEMEFFECTTYPE_ATTACK_SPECABLTY		24
#define ITEMEFFECTTYPE_DEFENSE_SPECABLTY	25
#define ITEMEFFECTTYPE_ALTERITEMDROP		26

#define ITEMEFFECTTYPE_CONSTRUCTIONKIT		27
#define ITEMEFFECTTYPE_WARM					28
#define ITEMEFFECTTYPE_DEFENSE_ANTIMINE		29
#define ITEMEFFECTTYPE_ITEMFARM				30  
#define ITEMEFFECTTYPE_SLATES			31
#define ITEMEFFECTTYPE_JEWELRY			32
#define ITEMEFFECTTYPE_SOCKET			33
#define ITEMEFFECTTYPE_VARIABLEADD			34

enum WandEffectTypes{
	WET_NONE,
	WET_ADDMAGICDMGPCT
};

enum SocketGems : uint8{
	SG_NONE = (uint8)ITEM_NONE,
	SG_REJUGEM7 = 1,
	SG_REJUGEM14,
	SG_REJUGEM21,
	SG_BLOODGEM7,
	SG_BLOODGEM14,
	SG_BLOODGEM21,
	SG_MINDGEM7,
	SG_MINDGEM14,
	SG_MINDGEM21,
	SG_ARMORGEM7,
	SG_ARMORGEM14,
	SG_ARMORGEM21,
	SG_ENCHANTEDGEM2,
	SG_ENCHANTEDGEM4,
	SG_ENCHANTEDGEM6,
	SG_TACTICALGEM3,
	SG_TACTICALGEM5,
	SG_TACTICALGEM7,
	SG_VORTEXGEM,
	SG_MAX
};

const ItemID SocketGems[SG_MAX] = {
	ITEM_NONE,
	ITEM_REJUGEM7,
	ITEM_REJUGEM14,
	ITEM_REJUGEM21,
	ITEM_BLOODGEM7,
	ITEM_BLOODGEM14,
	ITEM_BLOODGEM21,
	ITEM_MINDGEM7,
	ITEM_MINDGEM14,
	ITEM_MINDGEM21,
	ITEM_ARMORGEM7,
	ITEM_ARMORGEM14,
	ITEM_ARMORGEM21,
	ITEM_ENCHANTEDGEM2,
	ITEM_ENCHANTEDGEM4,
	ITEM_ENCHANTEDGEM6,
	ITEM_TACTICALGEM3,
	ITEM_TACTICALGEM5,
	ITEM_TACTICALGEM7,
	ITEM_VORTEXGEM
};

#define ITET_UNIQUE_OWNER			1
#define ITET_ID						2
#define ITET_DATE						3
#define ITET_GM_MADE					4

class CItem  
{
public:

	CItem(uint32 count = 1);
	CItem(ItemID itemID, uint32 count = 1);
	CItem(char * itemName, uint32 count = 1);
	virtual ~CItem();
	
	void Init();

	uint32 GetWeight(int count) const;
	uint32 GetWeight()			const { return GetWeight( m_dwCount ); }
	uint32 GetBaseWeight()		const { return GetWeight(1); }
	uint32 GetManuCompletion()	const { return m_sItemSpecEffectValue2 + 100; }
	bool IsValid()		const { return (m_sIDnum != ITEM_INVALID); }
	bool IsLogged() 	const;
	bool IsManued()	const;
	bool IsVortexed()	const { return m_sockets[0] == SG_VORTEXGEM; }
	uint32 GetMaxSockets() const;
	bool AddSocket(CItem * gem);

	bool InitItemAttr(const char * pItemName);
	bool InitItemAttr(ItemID iItemID);
	void InitStats(int iGenLevel);
	void AdjustByStat();
	string Dump() const;


	char  m_cName[21];

	ItemID m_sIDnum;
	char  m_cItemType;
	char  m_cEquipPos;
	short m_sItemEffectType;
	short m_sItemEffectValue1, m_sItemEffectValue2, m_sItemEffectValue3;
	short m_sItemEffectValue4, m_sItemEffectValue5, m_sItemEffectValue6;
	ItemUID ItemUniqueID;
	uint16  m_wMaxLifeSpan;
	short m_sSpecialEffect;
	short m_sSpecialEffectValue1, m_sSpecialEffectValue2;

	short m_sSprite;
	short m_sSpriteFrame;

	char  m_cApprValue;
	char  m_cSpeed;

	uint32 m_wPrice;
	uint16  m_wWeight;
	short m_sLevelLimit;
	char  m_cGenderLimit;

	short m_sRelatedSkill;

	char  m_cCategory;
	bool  m_bIsForSale;
	bool m_isLogged;
	
	uint32 m_dwCount;
	short m_sTouchEffectType;
	short m_sTouchEffectValue1, m_sTouchEffectValue2, m_sTouchEffectValue3;
	char  m_cItemColor; 
	short m_sItemSpecEffectValue1, m_sItemSpecEffectValue2, m_sItemSpecEffectValue3;

	int  m_wCurLifeSpan;
	uint32 m_dwAttribute;
	uint8 m_sockets[MAXITEMSOCKETS];

	bool m_disabled;
};

typedef List<CItem*> ItemList;
typedef List<CItem*>::iterator ItemListIter;
typedef List<CItem*>::const_iterator ItemListCIter;

#endif // !defined(AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_)
