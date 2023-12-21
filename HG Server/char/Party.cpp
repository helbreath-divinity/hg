#include <windows.h>
#include "party.h"
#include "..\..\shared\buffer.h"

extern char packet[500];
extern char g_cTxt[512];

CParty::CParty(uint32 id) : _id(id)
{
}

CParty::~CParty()
{	
	while(CClient * member = GetMembers())
	{
		member->Notify(NULL, NOTIFY_PARTY, 2, 0, NULL, NULL);
		member->SetParty( NULL );
	}
}

void CParty::AddPlayer(CClient * player)
{
	_players.push_front( player );

	NotifyMemberList( player );

	player->SetParty( this );

	while(CClient * member = GetMembers())
	{
		member->Notify(NULL, NOTIFY_PARTY, 4, 1, NULL, player->m_cCharName);

		if(member == player || player->m_cMapIndex != member->m_cMapIndex)
			continue;
			
		member->Notify( player->m_handle, NOTIFY_PARTY_COORDS, 
			player->m_sX, player->m_sY, NULL, player->m_cCharName );
	}

	UpdateGuildBonuses();
}

bool CParty::WithdrawPlayer(CClient * player)
{
	while(CClient * member = GetMembers())
	{
		member->Notify(NULL, NOTIFY_PARTY, 6, 1, NULL, player->m_cCharName);
	}

	_RemovePlayer(player);
	
	if(_players.size() == 1)
	{
		ClientListIter iter = _players.begin();
		CClient * solePlayer = *iter;
		_RemovePlayer(solePlayer);

		solePlayer->Notify(NULL, NOTIFY_PARTY, 2, 0, NULL, NULL);
	} else {
		UpdateGuildBonuses();
	}

	return _players.empty();
}

void CParty::_RemovePlayer(CClient * player)
{
	_players.remove( player );
	player->SetParty( NULL );
}

void CParty::NotifyMemberList(CClient * player) const
{
	char * index = packet;

	while(CClient * member = GetMembers())
	{
		if(member == player)
			continue;
		Push(index, member->m_cCharName, 11);
	}
	player->Notify(NULL, NOTIFY_PARTY, 5, 1, _players.size() - 1, packet);
}

void CParty::UpdateMemberCoords(CClient * player) const
{
	if(player->m_partyCoordSteps >= 4)
	{
		player->m_partyCoordSteps = 0;
		
		while(CClient * member = GetMembers())
		{
			if(member == player || player->m_cMapIndex != member->m_cMapIndex)
				continue;

			member->Notify(player->m_handle, NOTIFY_PARTY_COORDS, 
					player->m_sX, player->m_sY, NULL, player->m_cCharName);
		}
	}
	
	player->m_partyCoordSteps++;
}

void CParty::UpdateMemberMap(CClient * player) const
{
	while(CClient * member = GetMembers())
	{
		if(member == player)
			continue;

		// debug tests
		ASSERT(member->m_pXSock);
		if(!member->m_pXSock)
		{
			sprintf(g_cTxt, "m_pXSock == NULL Player(%s) Party Size(%u) SameParty(%u) PartyStatus(%u) Map(%s %u-%u)", 
				member->m_cCharName, GetPlayerCnt(), member->GetParty() == this, member->GetPartyStatus(), 
				member->m_cMapName, member->m_sX, member->m_sY);
			ERR(g_cTxt);
			continue;
		}

		if(player->m_cMapIndex == member->m_cMapIndex)
		{
			player->Notify(member->m_handle, NOTIFY_PARTY_COORDS, 
				member->m_sX, member->m_sY, NULL, member->m_cCharName);
			member->Notify(player->m_handle, NOTIFY_PARTY_COORDS, 
				player->m_sX, player->m_sY, NULL, player->m_cCharName);
		}
		else
		{
			member->Notify(player->m_handle, NOTIFY_PARTY_COORDS, 0, 0, NULL, player->m_cCharName);
		}
	}
}

void CParty::UpdateGuildBonuses()
{	
	_gldHuntmasters.clear();
	_gldRaidmasters.clear();

	while(CClient * player = GetMembers())
	{
		if(!player->m_guild) continue;

		switch( player->m_iGuildRank )
		{
		case GUILDRANK_RAIDMASTER:
			_gldRaidmasters[ player->m_guild ].push_front( player );
			break;

		case GUILDRANK_HUNTMASTER:
			_gldHuntmasters[ player->m_guild ].push_front( player );
			break;

		default:
			continue;
		}
	}
}

uint32 CParty::GetAlivePlayerCnt() const
{ 
	uint32 n = 0;

	for(ClientListCIter iter = _players.begin();
		iter != _players.end();
		++iter)
	{
		if( !(*iter)->IsDead() )
			n++;
	}

	return n; 
}

CClient * CParty::GetMembers() const
{
	static bool getting = false;
	static ClientListCIter iter;

	if(getting)
	{
		if(iter == _players.end())
		{
			getting = false;
			return NULL;
		}

		return (*iter++);
	}
	else
	{
		iter = _players.begin();

		if(iter == _players.end())
			return NULL;

		getting = true;
		return (*iter++);
	}
}

CClient * CParty::GetHuntmasters(CGuild * guild)
{
	static bool getting = false;
	static ClientListCIter iter, end;
	
	if(_gldHuntmasters.count(guild) == 0)
		return NULL;

	if(getting)
	{
		if(iter == end)
		{
			getting = false;
			return NULL;
		}

		return (*iter++);
	}
	else
	{
		iter = _gldHuntmasters[guild].begin();
		end = _gldHuntmasters[guild].end();

		if(iter == end)
			return NULL;

		getting = true;
		return (*iter++);
	}
}

CClient * CParty::GetRaidmasters(CGuild * guild)
{
	static bool getting = false;
	static ClientListCIter iter, end;

	if(_gldRaidmasters.count(guild) == 0)
		return NULL;

	if(getting)
	{
		if(iter == end)
		{
			getting = false;
			return NULL;
		}

		return (*iter++);
	}
	else
	{
		iter = _gldRaidmasters[guild].begin();
		end = _gldRaidmasters[guild].end();

		if(iter == end)
			return NULL;

		getting = true;
		return (*iter++);
	}
}

void CParty::PingMap(const CClient * pinger, int16 x, int16 y, uint32 pinguid) const
{
	foreach(it, _players)
	{
		CClient * player = *it;
		if(player == pinger || player->m_cMapIndex != pinger->m_cMapIndex || player->m_pinguid == pinguid)
			continue;

		player->Notify( NULL, NOTIFY_PINGMAP, PINGMAP_PARTY, x, y); 
		player->m_pinguid = pinguid;
	}
}