#include <windows.h>
#include <algorithm>
//#include "Guild.h"
#include "..\hg.h"
#include "..\..\shared\buffer.h"
#include "..\mgrs\PartyMgr.h"
#include "Guild.h"
#include "ActionID.h"


extern CGame *   g_game;
extern CPartyMgr partyMgr;
extern char	G_cData50000[50000];

extern char packet[500];

CGuild::CGuild(int16 guildID, char * name, char * data) : m_guildGUID(guildID)
{
	m_lastActive = time(NULL);
	warehouseVer = 1;
	_master = NULL;

	ZeroMemory(m_name, sizeof(m_name));
	memcpy(m_name, name, 20);

	if(data)
	{
		// Whatever is added in here must be set in ResponseCreateNewGuildHandler,
		// and CGuild::Save() and most likely CClient::NotifyGuildInfo()

		// Login doesn't iterate through gldUps, so don't change to Pop(data, guild->m_upgrades[i])
		Pop(data, m_upgrades[GU_WAREHOUSE]);
		Pop(data, m_upgrades[GU_SUMMONS]);
		Pop(data, m_upgrades[GU_CAPTAINCY]);
		Pop(data, m_upgrades[GU_RAIDMASTERS]);
		Pop(data, m_upgrades[GU_HUNTMASTERS]);

		Pop(data, _gold);
		Pop(data, _maj);
		Pop(data, _cont);

		Pop(data, _captains);
		Pop(data, _raidmasters);
		Pop(data, _huntmasters);

		LoadWarehouse(data);
	}
	else
	{
		for(int i = 0; i < GU_MAX; i++)
			m_upgrades[i] = 0;

		_gold = _maj = _cont = 0;
		_captains = _raidmasters = _huntmasters = 0;
	}
}

CGuild::~CGuild(void)
{	
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		CClient * player = *it;
		ZeroMemory(player->m_cGuildName, sizeof(player->m_cGuildName));
		memcpy(player->m_cGuildName, "NONE", 4);
		player->m_iGuildRank = GUILDRANK_NONE;					
		player->m_iGuildGUID = -1;
		player->m_guild = NULL;

		if(player->GetParty()) 
			partyMgr.RemoveFromParty( player );

		g_game->SendEventToNearClient_TypeA(player->m_handle, OWNERTYPE_PLAYER, MSGID_MOTION_NULL, NULL, NULL, NULL);
		g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_CLEARGUILDNAME,
			player->m_cMapIndex, player->m_sX, player->m_sY, 0, 0, 0);
	}
}

void CGuild::Save(bool saveWH) const
{
	char * p = G_cData50000;
	char * index = p;

	Push(index, (uint32)MSGID_SAVE_GUILDINFO);
	Push(index, (uint16)m_guildGUID);
	Push(index, (char*)m_name, 20);
	
	WriteInfo(index);

	Push(index, (uint8) saveWH);
	if(saveWH)
		WriteWarehouse_Save(index);

	g_game->bSendMsgToLS(MSGID_SAVE_GUILDINFO, NULL, false, p, index - p);
}

void CGuild::MemberLogin(CClient * player)
{			
	player->m_guild = this;
	_onlineList.push_front(player);
	if(player->m_iGuildRank == GUILDRANK_MASTER)
		_master = player;

	player->NotifyGuildInfo(true);

	// Notify guild members
	for(ClientListCIter it = _onlineList.begin(); 
		it != _onlineList.end();
		++it)
	{
		if((*it) == player)
			continue;
		(*it)->NotifyGuildsmanStatus(player);
	}
}

bool CGuild::MemberLogout(CClient * player)
{
	_onlineList.remove(player);
	if(player->m_iGuildRank == GUILDRANK_MASTER)
		_master = NULL;

	// Notify guild members
	for(ClientListCIter it = _onlineList.begin(); 
		it != _onlineList.end();
		++it)
	{
		(*it)->NotifyGuildsmanStatus(player, false);
	}

	m_lastActive = time(NULL);

	return _onlineList.empty();
}

void CGuild::MemberWithdrawal(CClient * player)
{
	switch(player->m_iGuildRank)
	{
	case GUILDRANK_CAPTAIN:
		_captains--;
		break;

	case GUILDRANK_RAIDMASTER:
		_raidmasters--;
		break;

	case GUILDRANK_HUNTMASTER:
		_huntmasters--;
		break;
	}
	
	if(player->GetParty()) 
		partyMgr.RemoveFromParty( player );

	_GuildInfoChanged();
}

void CGuild::MemberMapChanged(CClient * player) const
{
	// Notify guild members
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		if((*it) == player)
			continue;
		(*it)->NotifyGuildsmanStatus(player);
	}
}
void CGuild::_GuildInfoChanged() const
{
	Save();

	// Notify guild members
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		(*it)->NotifyGuildInfo();
	}
}
void CGuild::WriteInfo(char * &index) const
{
	for(int i=0; i < GU_MAX; i++)
		Push(index, m_upgrades[i] );

	Push(index, GetGold() );
	Push(index, GetMaj() );
	Push(index, GetCont() );
	
	Push(index, GetNCaptains() );
	Push(index, GetNRaidmasters() );
	Push(index, GetNHuntmasters() );
}
void CGuild::WriteMemberList(char * &index, CClient const * player) const
{
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		CClient const * member = *it;
		if(member == player)
			continue;

		memcpy(index, member->m_cCharName, 10);
		index += 10;
		Push(index, (uint8)member->m_iGuildRank);
		Push(index, g_game->m_mapNameList[ member->m_cMapName ]);
	}
}

void CGuild::RequestTeleport(CClient const * master, string memberName) const
{
	if((uint32)master->m_iGuildRank >= GUILDRANK_MAX || !gldRankPerm[ master->m_iGuildRank ].canSummon ||
		timeGetTime() - master->m_lastDamageTime < 10 _s || master->IsDead())
		return;

	CClient * member = FindPlayer(memberName);

	if(!member)
		return;

	time_t now = time(NULL);
	if(now - member->m_gldSummonsTime < GUILDSUMMONSTIME - 5 _s /* 5s LATENCY THRESHOLD */)
		return;

	member->m_gldSummonsTime = now;
	member->NotifyGuildSummons(master);
}

bool CGuild::CanSummon(CClient const * master, CClient const * member) const
{
	if(GetGold() < GUILDSUMMONSGOLDCOST || !master || timeGetTime() - member->m_lastDamageTime < 10 _s)
		return false;

	string map = master->m_cMapName;

	switch(m_upgrades[GU_SUMMONS])
	{
	case 1:
		if(map == "middleland")
			return true;
		else
			return false;
		
	case 2:
		if(map == "middleland" || map == "icebound")
			return true;
		else{
			return false;
		}

	case 3:
		if(map == "middleland" || map == "icebound" || map == "toh1" || map == "dglv2" ||
			(master->IsAres() && map == "aresdend1") || (master->IsElv() && map == "elvined1"))
		{
			return true;
		}else{
			return false;
		}

	case 4:
		if(map == "middleland" || map == "icebound" || map == "toh1" || map == "toh2" || map == "toh3" ||
			(master->IsAres() && map == "aresdend1") || (master->IsElv() && map == "elvined1") || 
			map == "dglv2" || map == "dglv3" || map == "dglv4")
		{
			return true;
		}else{
			return false;
		}
	default:
		return false;
	}
}

void CGuild::LoadWarehouse(char * data)
{	
	if(m_upgrades[GU_WAREHOUSE] == 0 || m_upgrades[GU_WAREHOUSE] > gldUps[GU_WAREHOUSE].maxLvl)
		return;

	uint16 itemCnt;
	Pop(data, itemCnt);

	for(size_t index = 0; index < itemCnt; index++)
	{
		char ItemName[25];
		ZeroMemory(ItemName, sizeof(ItemName));
		Pop(data, ItemName, 20);
		
		CItem * item = new CItem(ItemName);

		Pop(data, item->m_dwCount);
		if(item->m_dwCount < 0) item->m_dwCount = 1;
		Pop(data, (uint16&)item->m_sTouchEffectType);
		Pop(data, (uint16&)item->m_sTouchEffectValue1);
		Pop(data, (uint16&)item->m_sTouchEffectValue2);
		Pop(data, (uint16&)item->m_sTouchEffectValue3);
		Pop(data, (uint8&)item->m_cItemColor);
		Pop(data, (uint16&)item->m_sItemSpecEffectValue1);
		Pop(data, (uint16&)item->m_sItemSpecEffectValue2);
		Pop(data, (uint16&)item->m_sItemSpecEffectValue3);
		Pop(data, (uint32&)item->m_wCurLifeSpan);
		Pop(data, item->m_dwAttribute);
		Pop(data, item->ItemUniqueID);

		if(!item->IsValid())
		{
			ERR("INVALID ITEM");
			delete item;
			continue;
		}

		if(item->IsManued() && (item->m_sIDnum > ITEM_MAGICSAPPHIRE || item->m_sIDnum < ITEM_MAGINDIAMOND)) //Quick hack. TODO: Fix Endu for Magic jewels
			item->m_wMaxLifeSpan = item->m_sItemSpecEffectValue1;

		int iValue = (item->m_dwAttribute & 0xF0000000) >> 28;
		if(iValue > 0)
		{
			switch (item->m_cCategory) {
			case 5:
			case 6:
				item->m_wMaxLifeSpan = item->m_sItemSpecEffectValue1;
				break;
			}
		}
		item->AdjustByStat();
		if(item->m_wCurLifeSpan > item->m_wMaxLifeSpan)
			item->m_wCurLifeSpan = item->m_wMaxLifeSpan;

		_warehouse.push_back(item);
	}
}

void CGuild::WriteWarehouse_Save(char * &index) const
{
	Push(index, (uint16)_warehouse.size());
	
	for(ItemListCIter it = _warehouse.begin();
		it != _warehouse.end(); ++it)
	{
		CItem * item = *it;

		memcpy(index, item->m_cName, 20);
		index += 20;

		Push(index, item->m_dwCount);
		Push(index, (uint16)item->m_sTouchEffectType);
		Push(index, (uint16)item->m_sTouchEffectValue1);
		Push(index, (uint16)item->m_sTouchEffectValue2);
		Push(index, (uint16)item->m_sTouchEffectValue3);
		Push(index, (uint8)item->m_cItemColor);
		Push(index, (uint16)item->m_sItemSpecEffectValue1);
		Push(index, (uint16)item->m_sItemSpecEffectValue2);
		Push(index, (uint16)item->m_sItemSpecEffectValue3);
		Push(index, (uint16)item->m_wCurLifeSpan);
		Push(index, item->m_dwAttribute);
		Push(index, (uint64)item->ItemUniqueID);
	}
}

void CGuild::WriteWarehouse(char * &index) const
{
	Push(index, (uint16)_warehouse.size());
	Push(index, warehouseVer);

	for(ItemListCIter it = _warehouse.begin();
		it != _warehouse.end(); ++it)
	{
		CItem * item = *it;

		memcpy(index, item->m_cName, 20);
		index += 20;

		Push(index, item->m_dwCount);
		Push(index, (uint8)item->m_cItemType);
		Push(index, (uint8)item->m_cEquipPos);
		Push(index, (uint16)item->m_sLevelLimit);
		Push(index, (uint8)item->m_cGenderLimit);
		Push(index, (uint16)item->m_wCurLifeSpan);
		Push(index, item->m_wWeight);
		Push(index, (uint16)item->m_sSprite);
		Push(index, (uint16)item->m_sSpriteFrame);
		Push(index, (uint8)item->m_cItemColor);
		Push(index, (uint16)item->m_sItemSpecEffectValue2);
		Push(index, item->m_dwAttribute);
		for(int i = 0; i < MAXITEMSOCKETS; i++)
			Push(index, item->m_sockets[i]);
		Push(index, (uint32&)item);
	}
}

bool CGuild::AddToWarehouse(CItem * item, CClient * player)
{
	if(_warehouse.size() >= maxGWHItems[ m_upgrades[GU_WAREHOUSE] ] || 
		(player && !player->m_bIsOnWarehouse) || item->m_disabled)
		return false;

	if(item->m_sTouchEffectType != 0 &&
		item->m_sTouchEffectValue1 == player->m_sCharIDnum1 &&
		item->m_sTouchEffectValue2 == player->m_sCharIDnum2 &&
		item->m_sTouchEffectValue3 == player->m_sCharIDnum3)
		return false;

	_warehouse.push_back(item);
	
	warehouseVer++;

	if(player)
	{
		player->Notify(NULL, NOTIFY_ITEMTOGUILDBANK, (uint32)item, warehouseVer, NULL, NULL);
	}
	
	g_game->_bItemLog(ITEMLOG_GWHDEPOSIT, player->m_handle, (int)-1, item);
	return true;
}

bool CGuild::RetrieveFromWarehouse(CItem * item, CClient * player)
{
	char p[100];
	char * index = p;

	if(player->m_iGuildRank == GUILDRANK_NONE || !gldRankPerm[ player->m_iGuildRank ].canWithdrawWH ||
		item->m_disabled)
	{
		return false;
	}

	Push(index, (uint32)MSGID_RESPONSE_RETRIEVEITEM_GUILDBANK);

	ItemListIter it = find(_warehouse.begin(), _warehouse.end(), item);
	
	if(it == _warehouse.end())
	{
		Push(index, (uint16)MSGTYPE_REJECT);

		player->m_pXSock->iSendMsg(p, index - p);
		return false;
	}

	if ( item->GetWeight() + player->m_iCurWeightLoad > g_game->_iCalcMaxLoad(player->m_handle)) {
		g_game->SendItemNotifyMsg(player->m_handle, NOTIFY_CANNOTCARRYMOREITEM, NULL, NULL, true);
		return false;
	}

	if (item->m_cItemType == ITEMTYPE_CONSUME || item->m_cItemType == ITEMTYPE_ARROW) 
	{
		for (int i = 0; i < MAXITEMS; i++)
		{
			CItem *& plrItem = player->m_pItemList[i];
			if (!plrItem || player->m_pItemList[i]->m_cItemType != item->m_cItemType ||
				memcmp(player->m_pItemList[i]->m_cName, item->m_cName, 20) != 0)
			{
				continue;
			}

			g_game->SetItemCount(player->m_handle, i, plrItem->m_dwCount + item->m_dwCount);
			
			g_game->iCalcTotalWeight(player->m_handle);
			if(item->m_cItemType == ITEMTYPE_ARROW)
				player->m_cArrowIndex = g_game->_iGetArrowItemIndex(player->m_handle);
			
			warehouseVer++;

			Push(index, (uint16)MSGTYPE_CONFIRM);
			Push(index, (uint32&)item);
			Push(index, (uint8)i);
			Push(index, warehouseVer);
			
			delete item;

			_warehouse.erase(it);

			Save(true);

			switch (player->m_pXSock->iSendMsg(p, index - p)) 
			{
			case XSOCKEVENT_QUENEFULL:
			case XSOCKEVENT_SOCKETERROR:
			case XSOCKEVENT_CRITICALERROR:
			case XSOCKEVENT_SOCKETCLOSED:
				g_game->DeleteClient(player->m_handle, true, true);
			}
			return true;
		}

		goto RFW_NOQUANTITY;
	} 
	else {
RFW_NOQUANTITY:;
		for(int i = 0; i < MAXITEMS; i++)
		{
			CItem *& plrItem = player->m_pItemList[i];
			if (plrItem) continue;

			plrItem = item;

			player->m_ItemPosList[i].x = 40;
			player->m_ItemPosList[i].y = 30;
			player->m_bIsItemEquipped[i] = false;

			g_game->_bItemLog(ITEMLOG_RETRIEVE, player->m_handle, (int) -1,
				player->m_pItemList[i], (plrItem->m_sIDnum == ITEM_ZEM ));
				
			warehouseVer++;

			Push(index, (uint16)MSGTYPE_CONFIRM);
			Push(index, (uint32&)item);
			Push(index, (uint8)i);
			Push(index, warehouseVer);
			
			g_game->iCalcTotalWeight(player->m_handle);

			_warehouse.erase(it);

			Save(true);

			switch (player->m_pXSock->iSendMsg(p, index - p))
			{
			case XSOCKEVENT_QUENEFULL:
			case XSOCKEVENT_SOCKETERROR:
			case XSOCKEVENT_CRITICALERROR:
			case XSOCKEVENT_SOCKETCLOSED:
				g_game->DeleteClient(player->m_handle, true, true);
			}
			return true;
		}
		
		Push(index, (uint16)MSGTYPE_REJECT);

		player->m_pXSock->iSendMsg(p, index - p);
	}

	return false;
}

void CGuild::Broadcast(char * data, uint32 length) const
{
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		(*it)->m_pXSock->iSendMsg(data, length);
	}
}

void CGuild::Notify(uint16 wMsgType, uint32 sV1, uint32 sV2, uint32 sV3, char * pString, 
		uint32 sV4, uint32 sV5, uint32 sV6, uint32 sV7, uint32 sV8, uint32 sV9, char * pString2) const
{
	for(ClientListCIter it = _onlineList.begin();
		it != _onlineList.end();
		++it)
	{
		(*it)->Notify(NULL, wMsgType, sV1, sV2, sV3, pString, sV4, sV5, sV6, sV7, sV8, sV9, pString2);
	}
}

void CGuild::ContributeGold(CClient * player, uint32 val)
{
	uint32 goldindex = player->HasItem(ITEM_GOLD);

	if(goldindex == ITEM_NONE || player->m_pItemList[goldindex]->m_disabled)
		return;

	uint32 playerGold = player->GetItemCount(ITEM_GOLD);

	if(val > playerGold && player->IsFlooding(3))
		return;

	_gold += val;
	player->SetItemCount(ITEM_GOLD, playerGold - val, false);
	player->Notify(NULL, NOTIFY_GUILDCONTRIBUTERSP, 0, val, NULL, NULL);

	_GuildInfoChanged();
}

void CGuild::ContributeMaj(CClient * player, uint32 val)
{
	if(val > player->m_iGizonItemUpgradeLeft || player->IsFlooding(3))
		return;

	_maj += val;
	player->m_iGizonItemUpgradeLeft -= val;
	player->Notify(NULL, NOTIFY_GUILDCONTRIBUTERSP, 1, val, NULL, NULL);

	_GuildInfoChanged();
}

void CGuild::ContributeCont(CClient * player, uint32 val)
{
	if(val > player->m_iContribution || player->IsFlooding(3))
		return;

	_cont += val;
	player->m_iContribution -= val;
	player->Notify(NULL, NOTIFY_GUILDCONTRIBUTERSP, 2, val, NULL, NULL);

	_GuildInfoChanged();
}

void CGuild::GuildUpgrade(CClient * player, GuildUpgrades gu)
{
	if(player != GetMaster() || gu >= GU_MAX || m_upgrades[gu] >= gldUps[gu].maxLvl)
		return;

	uint32 costGold = gldUps[gu].costGold[ m_upgrades[gu] + 1 ];
	uint32 costMaj = gldUps[gu].costMaj[ m_upgrades[gu] + 1 ];
	uint32 costCont = gldUps[gu].costCont[ m_upgrades[gu] + 1 ];

	if(GetGold() < costGold || GetMaj() < costMaj || GetCont() < costCont)
	{
		return;
	}

	_gold -= costGold;
	_maj -= costMaj;
	_cont -= costCont;

	m_upgrades[gu]++;

	_GuildInfoChanged();
	Save();
}

void CGuild::GuildsmanChange(CClient * player, GuildRank gr, string memberName)
{
	if(gr >= GUILDRANK_MAX || player->IsFlooding(3))
		return;

	if(!gldRankPerm[ player->m_iGuildRank ].canPromote)
		return;

	CClient * member = FindPlayer(memberName);

	if(!member || member == player 
		|| player->m_iGuildRank >= gr || member->m_iGuildRank <= player->m_iGuildRank)
		return;

	switch(gr)
	{
	case GUILDRANK_CAPTAIN:
		if(_GetAvailableCaptains() == 0)
			return;

		switch(member->m_iGuildRank)
		{
		case GUILDRANK_RAIDMASTER:
			_raidmasters--;
			break;

		case GUILDRANK_HUNTMASTER:
			_huntmasters--;
			break;
		}

		_captains++;
		break;

	case GUILDRANK_RAIDMASTER:
		if(_GetAvailableRaidmasters() == 0)
			return;

		switch(member->m_iGuildRank)
		{
		case GUILDRANK_CAPTAIN:
			_captains--;
			break;

		case GUILDRANK_HUNTMASTER:
			_huntmasters--;
			break;
		}

		_raidmasters++;
		break;
		
	case GUILDRANK_HUNTMASTER:
		if(_GetAvailableHuntmasters() == 0)
			return;

		switch(member->m_iGuildRank)
		{
		case GUILDRANK_RAIDMASTER:
			_raidmasters--;
			break;
			
		case GUILDRANK_CAPTAIN:
			_captains--;
			break;
		}

		_huntmasters++;
		break;

	case GUILDRANK_RECRUIT:
	case GUILDRANK_GUILDSMAN:
		switch(member->m_iGuildRank)
		{
		case GUILDRANK_CAPTAIN:
			_captains--;
			break;

		case GUILDRANK_RAIDMASTER:
			_raidmasters--;
			break;
			
		case GUILDRANK_HUNTMASTER:
			_huntmasters--;
			break;
		}
		break;

	default:
		return;
	}

	member->m_iGuildRank = gr;
	member->Save();

	if(member->GetParty())
		member->GetParty()->UpdateGuildBonuses();

	_GuildInfoChanged();

	// Notify guild members
	for(ClientListCIter it = _onlineList.begin(); 
		it != _onlineList.end();
		++it)
	{
		(*it)->NotifyGuildsmanStatus(member);
	}

	g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_CLEARGUILDNAME, 
		member->m_cMapIndex, member->m_sX, member->m_sY, 0, 0, 0);
}

void CGuild::PingMap(const CClient * pinger, int16 x, int16 y, uint32 pinguid) const
{	
	if(pinger->m_iGuildRank == GUILDRANK_NONE || !gldRankPerm[ pinger->m_iGuildRank ].canPing)
		return;

	foreach(it, _onlineList)
	{
		CClient * player = *it;
		if(player == pinger || player->m_cMapIndex != pinger->m_cMapIndex || player->m_pinguid == pinguid)
			continue;

		player->Notify( NULL, NOTIFY_PINGMAP, PINGMAP_GUILD, x, y); 
		player->m_pinguid = pinguid;
	}
}