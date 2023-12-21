// Item.cpp: implementation of the CItem class.
//
//////////////////////////////////////////////////////////////////////
#include "..\\..\\GlobalDef.h"

#ifdef LOG_ARMORSTATS
	#include "..\\..\\hg.h"

	extern char            g_cTxt[512];
#else
	#include "Item.h"
#endif

extern class CItem ** g_itemConfigList;
extern HashMap<ItemID, uint8> g_socketMap;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem::CItem(uint32 count) : m_dwCount(count)
{
	Init();
}

CItem::CItem(ItemID itemID, uint32 count) : m_dwCount(count)
{
	Init();
	InitItemAttr(itemID);
}

CItem::CItem(char * itemName, uint32 count) : m_dwCount(count)
{
	Init();
	InitItemAttr(itemName);
}

void CItem::Init()
{
	ZeroMemory(m_cName, sizeof(m_cName));
	m_sSprite = 0;
	m_sSpriteFrame = 0;
											  
	m_sItemEffectValue1 = 0;
	m_sItemEffectValue2 = 0;
	m_sItemEffectValue3 = 0; 

	m_sItemEffectValue4 = 0;
	m_sItemEffectValue5 = 0;
	m_sItemEffectValue6 = 0; 

	m_sTouchEffectType   = 0;
	m_sTouchEffectValue1 = 0;
	m_sTouchEffectValue2 = 0;
	m_sTouchEffectValue3 = 0;

	m_cItemColor = 0;
	m_sItemSpecEffectValue1 = 0;
	m_sItemSpecEffectValue2 = 0;
	m_sItemSpecEffectValue3 = 0;

	m_sSpecialEffectValue1 = 0;
	m_sSpecialEffectValue2 = 0;

	m_wCurLifeSpan = 0;
	m_dwAttribute   = 0;

	for(int i = 0; i < MAXITEMSOCKETS; i++)
		m_sockets[i] = ITEM_NONE;

	m_cCategory = NULL;
	m_sIDnum    = ITEM_INVALID;

	m_bIsForSale = false;
	ItemUniqueID = 0;

	m_disabled = false;
}

CItem::~CItem()
{

}

string CItem::Dump() const
{
	char txt[256];

	sprintf(txt, "Item: %u %s %u %i,%i,%i | "
					"%u %i,%i,%i %u | "
					"%u %i,%i,%i %I64u", 
					m_dwCount, m_cName, m_sTouchEffectType, m_sTouchEffectValue1, m_sTouchEffectValue2, m_sTouchEffectValue3,
					m_cItemColor, m_sItemSpecEffectValue1, m_sItemSpecEffectValue2, m_sItemSpecEffectValue3, m_wCurLifeSpan,
					m_dwAttribute, m_sockets[0], m_sockets[1], m_sockets[2], ItemUniqueID
					);

	return txt;
}

uint32 CItem::GetWeight(int count) const
{
	if(count < 0) count = 1;

	uint32 weight = m_wWeight * count;

	if(m_sIDnum == ITEM_GOLD)
		weight /= 20;

	return (weight <= 0) ? 1 : weight;
}

bool CItem::IsLogged() const
{
	if(m_sIDnum == ITEM_GOLD && m_isLogged)
		return (m_dwCount > 10000) ? true : false;

	return m_isLogged;
}

bool CItem::InitItemAttr(ItemID itemID)
{
	if(itemID == ITEM_NONE || itemID == ITEM_INVALID)
		return false;

	for(int i = 0; i < MAXITEMTYPES; i++) 
	{
		if (g_itemConfigList[i] != NULL) {
			if (itemID ==  g_itemConfigList[i]->m_sIDnum) {

				ZeroMemory(m_cName, sizeof(m_cName));
				strcpy(m_cName, g_itemConfigList[i]->m_cName);
				m_cItemType         = g_itemConfigList[i]->m_cItemType;
				m_cEquipPos         = g_itemConfigList[i]->m_cEquipPos;
				m_sItemEffectType   = g_itemConfigList[i]->m_sItemEffectType;
				m_sItemEffectValue1 = g_itemConfigList[i]->m_sItemEffectValue1;
				m_sItemEffectValue2 = g_itemConfigList[i]->m_sItemEffectValue2;
				m_sItemEffectValue3 = g_itemConfigList[i]->m_sItemEffectValue3;
				m_sItemEffectValue4 = g_itemConfigList[i]->m_sItemEffectValue4;
				m_sItemEffectValue5 = g_itemConfigList[i]->m_sItemEffectValue5;
				m_sItemEffectValue6 = g_itemConfigList[i]->m_sItemEffectValue6;
				m_wMaxLifeSpan      = g_itemConfigList[i]->m_wMaxLifeSpan;
				m_wCurLifeSpan	   = m_wMaxLifeSpan;
				m_sSpecialEffect    = g_itemConfigList[i]->m_sSpecialEffect;

				m_sSprite           = g_itemConfigList[i]->m_sSprite;
				m_sSpriteFrame      = g_itemConfigList[i]->m_sSpriteFrame;
				m_wPrice            = g_itemConfigList[i]->m_wPrice;
				m_wWeight           = g_itemConfigList[i]->m_wWeight;
				m_cApprValue        = g_itemConfigList[i]->m_cApprValue;
				m_cSpeed            = g_itemConfigList[i]->m_cSpeed;
				m_sLevelLimit       = g_itemConfigList[i]->m_sLevelLimit;
				m_cGenderLimit      = g_itemConfigList[i]->m_cGenderLimit;

				m_sSpecialEffectValue1 = g_itemConfigList[i]->m_sSpecialEffectValue1;
				m_sSpecialEffectValue2 = g_itemConfigList[i]->m_sSpecialEffectValue2;

				m_sRelatedSkill     = g_itemConfigList[i]->m_sRelatedSkill;
				m_cCategory         = g_itemConfigList[i]->m_cCategory;
				m_sIDnum			   = g_itemConfigList[i]->m_sIDnum;

				m_bIsForSale	       = g_itemConfigList[i]->m_bIsForSale;
				m_cItemColor        = g_itemConfigList[i]->m_cItemColor;
				m_isLogged			= g_itemConfigList[i]->m_isLogged;
				return true;
			}
		}
	}

	return false;
}

bool CItem::InitItemAttr(const char * pItemName)
{
	char cTmpName[22];

	if (strlen(pItemName) > 21) return false;

	ZeroMemory(cTmpName, sizeof(cTmpName));
	strcpy(cTmpName, pItemName);

	for(int i = 0; i < MAXITEMTYPES; i++) 
	{
		if (g_itemConfigList[i] != NULL) {
			if (memcmp(cTmpName, g_itemConfigList[i]->m_cName, 20) == 0) {

				ZeroMemory(m_cName, sizeof(m_cName));
				strcpy(m_cName, g_itemConfigList[i]->m_cName);
				m_cItemType         = g_itemConfigList[i]->m_cItemType;
				m_cEquipPos         = g_itemConfigList[i]->m_cEquipPos;
				m_sItemEffectType   = g_itemConfigList[i]->m_sItemEffectType;
				m_sItemEffectValue1 = g_itemConfigList[i]->m_sItemEffectValue1;
				m_sItemEffectValue2 = g_itemConfigList[i]->m_sItemEffectValue2;
				m_sItemEffectValue3 = g_itemConfigList[i]->m_sItemEffectValue3;
				m_sItemEffectValue4 = g_itemConfigList[i]->m_sItemEffectValue4;
				m_sItemEffectValue5 = g_itemConfigList[i]->m_sItemEffectValue5;
				m_sItemEffectValue6 = g_itemConfigList[i]->m_sItemEffectValue6;
				m_wMaxLifeSpan      = g_itemConfigList[i]->m_wMaxLifeSpan;
				m_wCurLifeSpan	   = m_wMaxLifeSpan;
				m_sSpecialEffect    = g_itemConfigList[i]->m_sSpecialEffect;

				m_sSprite           = g_itemConfigList[i]->m_sSprite;
				m_sSpriteFrame      = g_itemConfigList[i]->m_sSpriteFrame;
				m_wPrice            = g_itemConfigList[i]->m_wPrice;
				m_wWeight           = g_itemConfigList[i]->m_wWeight;
				m_cApprValue        = g_itemConfigList[i]->m_cApprValue;
				m_cSpeed            = g_itemConfigList[i]->m_cSpeed;
				m_sLevelLimit       = g_itemConfigList[i]->m_sLevelLimit;
				m_cGenderLimit      = g_itemConfigList[i]->m_cGenderLimit;

				m_sSpecialEffectValue1 = g_itemConfigList[i]->m_sSpecialEffectValue1;
				m_sSpecialEffectValue2 = g_itemConfigList[i]->m_sSpecialEffectValue2;

				m_sRelatedSkill     = g_itemConfigList[i]->m_sRelatedSkill;
				m_cCategory         = g_itemConfigList[i]->m_cCategory;
				m_sIDnum			   = g_itemConfigList[i]->m_sIDnum;

				m_bIsForSale	       = g_itemConfigList[i]->m_bIsForSale;
				m_cItemColor        = g_itemConfigList[i]->m_cItemColor;
				m_isLogged			= g_itemConfigList[i]->m_isLogged;
				return true;
			}
		}
	}

	return false;
}

void CItem::InitStats(int iGenLevel)
{
	uint32 statType, statValue, stat2Type, stat2Value;
	int iResult;

	switch(m_sItemEffectType)
	{
	default:
		return;
	case ITEMEFFECTTYPE_ATTACK_MANASAVE:
	case ITEMEFFECTTYPE_ATTACK:
		if(m_sItemEffectType == ITEMEFFECTTYPE_ATTACK_MANASAVE)
		{
			statType = ITEMSTAT_CASTPROB;
			m_cItemColor = 5;
		}else
		{
			iResult = dice(1,10000);
			if ((iResult >= 1) && (iResult <= 299)) {
				statType = ITEMSTAT_LIGHT; 
				m_cItemColor = 2; 
			}
			else if ((iResult >= 300) && (iResult <= 999)) {
				statType = ITEMSTAT_STRONG; 
				m_cItemColor = 3;
			}
			else if ((iResult >= 1000) && (iResult <= 2499)) {
				statType = ITEMSTAT_CRITICAL;
				m_cItemColor = 5;
			}
			else if ((iResult >= 2500) && (iResult <= 4499)) {
				statType = ITEMSTAT_AGILE;
				m_cItemColor = 1;
			}
			else if ((iResult >= 4500) && (iResult <= 6499)) {
				statType = ITEMSTAT_RIGHTEOUS;
				m_cItemColor = 7;
			}
			else if ((iResult >= 6500) && (iResult <= 8099)) {
				statType = ITEMSTAT_POISONING;
				m_cItemColor = 4;
			}
			else if ((iResult >= 8100) && (iResult <= 9699)) {
				statType = ITEMSTAT_SHARP;
				m_cItemColor = 6;
			}
			else if ((iResult >= 9700) && (iResult <= 10000)) {
				statType = ITEMSTAT_ANCIENT;
				m_cItemColor = 8;
			}
		}

		iResult = dice(1, 30000);
		if ((iResult >= 1) && (iResult < 10000))           statValue = 1;  // 10000/29348 = 34%
		else if ((iResult >= 10000) && (iResult < 17400))  statValue = 2;  // 6600/29348 = 22.4%
		else if ((iResult >= 17400) && (iResult < 22400))  statValue = 3;  // 4356/29348 = 14.8%
		else if ((iResult >= 22400) && (iResult < 25400))  statValue = 4;  // 2874/29348 = 9.7%
		else if ((iResult >= 25400) && (iResult < 27400))  statValue = 5;  // 1897/29348 = 6.4%
		else if ((iResult >= 27400) && (iResult < 28400))  statValue = 6;  // 1252/29348 = 4.2%
		else if ((iResult >= 28400) && (iResult < 28900))  statValue = 7;  // 826/29348 = 2.8%
		else if ((iResult >= 28900) && (iResult < 29300))  statValue = 8;  // 545/29348 = 1.85%
		else if ((iResult >= 29300) && (iResult < 29600))  statValue = 9;  // 360/29348 = 1.2%
		else if ((iResult >= 29600) && (iResult < 29800))  statValue = 10; // 237/29348 = 0.8%
		else if ((iResult >= 29800) && (iResult < 29900))  statValue = 11; // 156/29348 = 0.5%
		else if ((iResult >= 29900) && (iResult < 29970))  statValue = 12; // 103/29348 = 0.3%
		else if ((iResult >= 29970) && (iResult <= 30000))  statValue = 13; // 68/29348 = 0.1%
		else statValue = 1; 

		switch (statType) 
		{
		case ITEMSTAT_CRITICAL: 						
			if (statValue <= 5) statValue = 5;
			break; 
		case ITEMSTAT_POISONING: 
			if (statValue <= 4) statValue = 4;
			break; 
		case ITEMSTAT_LIGHT: 
			if (statValue <= 4) statValue = 4;
			break; 
		case ITEMSTAT_STRONG: 						
			if (statValue <= 2) statValue = 2;
			break; 
		}

		if ((iGenLevel <= 2) && (statValue > 7)) statValue = 7;

		SetNibble(m_dwAttribute, 5, statType);
		SetNibble(m_dwAttribute, 4, statValue);


		if (dice(1,10000) >= 6000) {
			iResult = dice(1,10000);
			if ((iResult >= 1) && (iResult <= 4999))          stat2Type = ITEMSTAT2_HITPROB;
			else if ((iResult >= 5000) && (iResult <= 8499))  stat2Type = ITEMSTAT2_CAD;
			else if ((iResult >= 8500) && (iResult <= 9499))  stat2Type = ITEMSTAT2_GOLD;
			else if ((iResult >= 9500) && (iResult <= 10000)) stat2Type = ITEMSTAT2_EXP;


			iResult = dice(1, 30000);
			if ((iResult >= 1) && (iResult < 10000)) stat2Value = 1; // 33.33%
			else if ((iResult >= 10000) && (iResult < 17400)) stat2Value = 2; // 24.67%
			else if ((iResult >= 17400) && (iResult < 22400)) stat2Value = 3; // 16.67%
			else if ((iResult >= 22400) && (iResult < 25400)) stat2Value = 4; // 10.00%
			else if ((iResult >= 25400) && (iResult < 27100)) stat2Value = 5; // 5.67%
			else if ((iResult >= 27100) && (iResult < 28200)) stat2Value = 6; // 3.67%
			else if ((iResult >= 28200) && (iResult < 28900)) stat2Value = 7; // 2.34%
			else if ((iResult >= 28900) && (iResult < 29400)) stat2Value = 8; // 1.67%
			else if ((iResult >= 29400) && (iResult < 29720)) stat2Value = 9; // 1.07%
			else if ((iResult >= 29720) && (iResult < 29900)) stat2Value = 10; // 0.60%
			else if ((iResult >= 29900) && (iResult < 29970)) stat2Value = 11; // 0.24%
			else if ((iResult >= 29970) && (iResult < 29994)) stat2Value = 12; // 0.08%
			else if ((iResult >= 29994) && (iResult <= 30000)) stat2Value = 13; // 0.02% 
			else stat2Value = 1; 

			switch (stat2Type) 
			{
			case 2: 
				if (stat2Value <= 3) stat2Value = 3;
				break; 
			case 10: 							
				if (stat2Value > 7) stat2Value = 7; 
				break; 
			case 11: 
				stat2Value = 2;
				break; 
			case 12: 
				stat2Value = 5;
				break; 
			}

			if ((iGenLevel <= 2) && (stat2Value > 7)) stat2Value = 7;

			SetNibble(m_dwAttribute, 3, stat2Type);
			SetNibble(m_dwAttribute, 2, stat2Value);
		}
		break;

	case ITEMEFFECTTYPE_DEFENSE:
		iResult = dice(1,10000);
		if ((iResult >= 1) && (iResult <= 5999))          statType = ITEMSTAT_STRONG;
		else if ((iResult >= 6000) && (iResult <= 8999))  statType = ITEMSTAT_LIGHT;
		else if ((iResult >= 9000) && (iResult <= 9554))  statType = ITEMSTAT_MANACONV;
		else if ((iResult >= 9555) && (iResult <= 10000)) statType = ITEMSTAT_CRITICAL2;

		iResult = dice(1, 30000);
		if ((iResult >= 1) && (iResult < 10000)) statValue = 1;
		else if ((iResult >= 10000) && (iResult < 17400)) statValue = 2;
		else if ((iResult >= 17400) && (iResult < 22400)) statValue = 3;
		else if ((iResult >= 22400) && (iResult < 25400)) statValue = 4;
		else if ((iResult >= 25400) && (iResult < 27400)) statValue = 5;
		else if ((iResult >= 27400) && (iResult < 28400)) statValue = 6;
		else if ((iResult >= 28400) && (iResult < 28900)) statValue = 7;
		else if ((iResult >= 28900) && (iResult < 29300)) statValue = 8;
		else if ((iResult >= 29300) && (iResult < 29600)) statValue = 9;
		else if ((iResult >= 29600) && (iResult < 29800)) statValue = 10;
		else if ((iResult >= 29800) && (iResult < 29900)) statValue = 11;
		else if ((iResult >= 29900) && (iResult < 29970)) statValue = 12;
		else if ((iResult >= 29970) && (iResult <= 30000)) statValue = 13;
		else statValue = 1; 

		switch (statType) 
		{
		case ITEMSTAT_LIGHT: 
			if (statValue <= 4) statValue = 4;
			break; 
		case ITEMSTAT_STRONG: 						
			if (statValue <= 2) statValue = 2;
			break; 
		case ITEMSTAT_MANACONV:
		case ITEMSTAT_CRITICAL2:
			statValue = (statValue+1) / 2;
			if (statValue < 1) statValue = 1;
			if ((iGenLevel <= 3) && (statValue > 2)) statValue = 2;
			break;
		}

		if ((iGenLevel <= 2) && (statValue > 7)) statValue = 7;

		SetNibble(m_dwAttribute, 5, statType);
		SetNibble(m_dwAttribute, 4, statValue);

		if (dice(1,10000) <= 8500) {
			iResult = dice(1,10000);
			if (iResult <= 1000)       stat2Type = ITEMSTAT2_PSNRES;	// 10
			else if (iResult <= 2200) stat2Type = ITEMSTAT2_DEF; // 12
			else if (iResult <= 3800) stat2Type = ITEMSTAT2_SPREC; // 16
			else if (iResult <= 6100) stat2Type = ITEMSTAT2_HPREC; // 23
			else if (iResult <= 8400) stat2Type = ITEMSTAT2_MPREC; // 23 
			else if (iResult <= 9600)  stat2Type = ITEMSTAT2_MR;		// 12
			else if (iResult <= 9900)  stat2Type = ITEMSTAT2_PA;		// 3
			else if (iResult <= 10000) stat2Type = ITEMSTAT2_MA;		// 1

			iResult = dice(1, 30017);
			if (iResult <= 8500) stat2Value = 1;
			else if (iResult <= 16000) stat2Value = 2;
			else if (iResult <= 23000) stat2Value = 3;
			else if (iResult <= 27000) stat2Value = 4;
			else if (iResult <= 28500) stat2Value = 5;
			else if (iResult <= 29250) stat2Value = 6;
			else if (iResult <= 29650) stat2Value = 7;
			else if (iResult <= 29850) stat2Value = 8;
			else if (iResult <= 29950) stat2Value = 9;
			else if (iResult <= 29995) stat2Value = 10;
			else if (iResult <= 30011) stat2Value = 11;
			else if (iResult <= 30016) stat2Value = 12;
			else if (iResult <= 30017) stat2Value = 13; 
			else stat2Value = 1; 

			switch (stat2Type) 
			{
			case ITEMSTAT2_PSNRES:
			case ITEMSTAT2_DEF:
			case ITEMSTAT2_MR:
			case ITEMSTAT2_PA:
			case ITEMSTAT2_MA:
				if (stat2Value <= 3) stat2Value = 3;
				break; 
			}

			if ((iGenLevel <= 2) && (stat2Value > 7)) stat2Value = 7;

			SetNibble(m_dwAttribute, 3, stat2Type);
			SetNibble(m_dwAttribute, 2, stat2Value);
#ifdef LOG_ARMORSTATS
			wsprintf(g_cTxt, "[I] Armor Drop: %s %s+%u (%u)", 
				m_cName, itemStats2[stat2Type].desc, stat2Value * itemStats2[stat2Type].mult, stat2Value);
			PutLogList(g_cTxt);
#endif
		}
		break;

	case ITEMEFFECTTYPE_JEWELRY:
		iResult = dice(1,10000);
		if ((iResult >= 1) && (iResult <= 4999))  statType = ITEMSTAT_LIGHT;
		else if ((iResult >= 5000) && (iResult <= 7999))  statType = ITEMSTAT_MANACONV;
		else if ((iResult >= 8000) && (iResult <= 10000)) statType = ITEMSTAT_CRITICAL2;


		uint32 bonus = m_sItemEffectValue1;

		iResult = dice(1, 30000-bonus) + bonus;
		if ((iResult >= 1) && (iResult < 10000))           statValue = 1;
		else if ((iResult >= 10000) && (iResult < 17400))  statValue = 2; 
		else if ((iResult >= 17400) && (iResult < 22400))  statValue = 3;
		else if ((iResult >= 22400) && (iResult < 25400))  statValue = 4;
		else if ((iResult >= 25400) && (iResult < 27400))  statValue = 5;
		else if ((iResult >= 27400) && (iResult < 28400))  statValue = 6;
		else if ((iResult >= 28400) && (iResult < 28900))  statValue = 7;
		else if ((iResult >= 28900) && (iResult < 29300))  statValue = 8;
		else if ((iResult >= 29300) && (iResult < 29600))  statValue = 9;
		else if ((iResult >= 29600) && (iResult < 29800))  statValue = 10;
		else if ((iResult >= 29800) && (iResult < 29900))  statValue = 11;
		else if ((iResult >= 29900) && (iResult < 29970))  statValue = 12;
		else if ((iResult >= 29970) && (iResult <= 30000))  statValue = 13;
		else statValue = 1; 

		switch (statType) 
		{
		case ITEMSTAT_LIGHT: 
			if (statValue <= 4) statValue = 4;
			break; 
		case ITEMSTAT_STRONG: 						
			if (statValue <= 2) statValue = 2;
			break; 
		case ITEMSTAT_MANACONV:
		case ITEMSTAT_CRITICAL2:
			statValue = (statValue+1) / 2;
			if (statValue < 1) statValue = 1;
			if ((iGenLevel <= 3) && (statValue > 2)) statValue = 2;
			break;
		}

		if ((iGenLevel <= 2) && (statValue > 7)) statValue = 7;

		SetNibble(m_dwAttribute, 5, statType);
		SetNibble(m_dwAttribute, 4, statValue);

		if (dice(1,10000) <= 8000) {
			iResult = dice(1,13000);
			if (iResult <= 1000)       stat2Type = ITEMSTAT2_PSNRES;	// 10
			else if (iResult <= 2000)  stat2Type = ITEMSTAT2_DEF;		// 10
			else if (iResult <= 3000)  stat2Type = ITEMSTAT2_SPREC;	// 16
			else if (iResult <= 5400)  stat2Type = ITEMSTAT2_HPREC;	// 24
			else if (iResult <= 7800)  stat2Type = ITEMSTAT2_MPREC;	// 24
			else if (iResult <= 9000)  stat2Type = ITEMSTAT2_MR;		// 12
			else if (iResult <= 11000)  stat2Type = ITEMSTAT2_EXP;
			else if (iResult <= 13000)  stat2Type = ITEMSTAT2_GOLD;

			iResult = dice(1, 29980 - bonus) + bonus;
			if ((iResult >= 1) && (iResult < 15000))           stat2Value = 1; 
			else if ((iResult >= 15000) && (iResult < 22400))  stat2Value = 2; 
			else if ((iResult >= 23000) && (iResult < 26100))  stat2Value = 3; 
			else if ((iResult >= 26100) && (iResult < 27700))  stat2Value = 4;  
			else if ((iResult >= 27700) && (iResult < 28700))  stat2Value = 5; 
			else if ((iResult >= 28700) && (iResult < 29200))  stat2Value = 6;  
			else if ((iResult >= 29200) && (iResult < 29450))  stat2Value = 7;  
			else if ((iResult >= 29450) && (iResult < 29649))  stat2Value = 8; 
			else if ((iResult >= 29649) && (iResult < 29793))  stat2Value = 9; 
			else if ((iResult >= 29793) && (iResult < 29888))  stat2Value = 10;
			else if ((iResult >= 29888) && (iResult < 29935))  stat2Value = 11; 
			else if ((iResult >= 29935) && (iResult < 29967))  stat2Value = 12;
			else if ((iResult >= 29967) && (iResult <= 29980))  stat2Value = 13;
			else stat2Value = 1;

			switch (stat2Type) 
			{
			case ITEMSTAT2_PSNRES:
			case ITEMSTAT2_DEF:
			case ITEMSTAT2_MR:
				if (stat2Value <= 3) stat2Value = 3;
				break; 
			}

			if (iGenLevel <= 2 && stat2Value > 7) stat2Value = 7;

			SetNibble(m_dwAttribute, 3, stat2Type);
			SetNibble(m_dwAttribute, 2, stat2Value);
		}
		break;
	}

	AdjustByStat();
}

void CItem::AdjustByStat()
{
	uint32 dwSWEType, dwSWEValue;
	double dV1, dV2, dV3;

	dwSWEType = GetNibble(m_dwAttribute, 5);
	dwSWEValue = GetNibble(m_dwAttribute, 4);

	switch (dwSWEType)
	{
	case ITEMSTAT_AGILE: 			
		m_cSpeed--;
		if (m_cSpeed < 0) m_cSpeed = 0;
		break;

	case ITEMSTAT_LIGHT: 
		dV2 = (double)m_wWeight;
		dV3 = (double)(dwSWEValue*4);
		dV1 = (dV3/100.0f)*dV2;
		m_wWeight -= (int)dV1;

		if (m_wWeight < 1) m_wWeight = 1;
		break;

	case ITEMSTAT_STRONG: 
	case ITEMSTAT_ANCIENT: 
		dV2 = (double)m_wMaxLifeSpan;
		dV3 = (double)(dwSWEValue*7);
		dV1 = (dV3/100.0f)*dV2;
		m_wMaxLifeSpan += (int)dV1;
		break;
	}
}

uint32 CItem::GetMaxSockets() const
{
	if(IsVortexed())
	{
		return 2;
	}
	else if(!IsManued())
	{
		return 0;
	}

	switch(m_cEquipPos)
	{
	case EQUIPPOS_BODY:
		if(GetManuCompletion() < 50)
			return 1;
		else if(GetManuCompletion() < 100)
			return 2;
		else if(GetManuCompletion() >= 100)
			return 3;
		break;
		
	case EQUIPPOS_ARMS:
	case EQUIPPOS_PANTS:
		if(GetManuCompletion() >= 50 && GetManuCompletion() < 100)
			return 1;
		else if(GetManuCompletion() >= 100)
			return 2;
		break;

	case EQUIPPOS_HEAD:
		if(GetManuCompletion() >= 50)
			return 1;
		break;
	}

	return 0;
}

bool CItem::AddSocket(CItem * gem)
{
	uint32 sockets = GetMaxSockets();

	if(gem->m_sIDnum == ITEM_VORTEXGEM)
	{
		if(sockets == 0 && 
			(m_cEquipPos == EQUIPPOS_BODY || m_cEquipPos == EQUIPPOS_ARMS || 
			m_cEquipPos == EQUIPPOS_PANTS || m_cEquipPos == EQUIPPOS_HEAD) &&
			GetNibble(m_dwAttribute, 5) )
		{
				m_sockets[0] = SG_VORTEXGEM;
				m_cItemColor = 10; // blue
				return true;
		} else {
			return false;
		}
	}

	int socket = -1;
	for(int i = 0; i < sockets; i++)
	{
		if(m_sockets[i] == SG_NONE)
		{
			socket = i;
			break;
		}
	}

	if(socket == -1)
	{
		// no free sockets
		return false;
	}

	m_sockets[socket] = g_socketMap[ gem->m_sIDnum ];

	return true;
}

bool CItem::IsManued() const
{
	 return (m_dwAttribute & 1) && m_sItemEffectType != ITEMEFFECTTYPE_VARIABLEADD;
}