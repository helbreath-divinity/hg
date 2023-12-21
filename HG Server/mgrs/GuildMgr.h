#ifndef GUILDMGR_H
#define GUILDMGR_H
#pragma once

#include "..\..\shared\common.h"

class CGuild;
class CClient;


class CGuildMgr
{
public:
	CGuildMgr(void);
	~CGuildMgr(void);

	CGuild * FindGuild(uint32 guildID) const;
	void Add(CGuild * guild);
	void Remove(CGuild * guild);
	void Update();
	void Empty();
	uint32 Count() const { return _guildMap.size(); }
	CGuild * Get() const;
	
	void AddPendingMember(CClient * player);
	void RemovePendingMember(CClient * player);

protected:
	void _RemoveExpired();
	void _SaveGuilds();

	GuildMap _guildMap;
	ClientList _pendingGldMbrs;
};


#endif