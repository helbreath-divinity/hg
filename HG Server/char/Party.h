#ifndef PARTY_H
#define PARTY_H
#pragma once

#include "..\..\shared\common.h"
#include "client.h"

#define GUILDPARTYBONUS_RANGE_X		FLAGRANGE_X
#define GUILDPARTYBONUS_RANGE_Y		FLAGRANGE_Y

class CParty
{
public:
	CParty(uint32 id);
	~CParty();
	
	uint32 GetPlayerCnt()	const { return _players.size(); }
	uint32 GetAlivePlayerCnt()	const;
	CClient * GetMembers() const;
	CClient * GetHuntmasters(CGuild * guild);
	CClient * GetRaidmasters(CGuild * guild);
	void AddPlayer(CClient * player);
	bool WithdrawPlayer(CClient * player);
	void NotifyMemberList(CClient * player) const;
	void UpdateMemberCoords(CClient * player) const;
	void UpdateMemberMap(CClient * player) const;
	void UpdateGuildBonuses();

	void PingMap(const CClient * pinger, int16 x, int16 y, uint32 pinguid) const;

	uint32 GetID()	const { return _id; }
private:
	void _RemovePlayer(CClient * player);

	typedef Map< CGuild*, ClientList > GuildPartyMastersMap;
	GuildPartyMastersMap _gldHuntmasters;
	GuildPartyMastersMap _gldRaidmasters;

	ClientList _players;
	uint32 _id;
};

typedef HashMap< uint32, CParty* > PartyMap;
typedef HashMap< uint32, CParty* >::const_iterator PartyMapCIter;

#endif