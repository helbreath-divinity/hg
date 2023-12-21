#ifndef OBJECTMGR_H
#define OBJECTMGR_H
#pragma once

#include "..\..\shared\common.h"
#include "..\char\Unit.h"
#include "..\char\Client.h"
#include "..\char\Npc.h"

class CObjectMgr
{
public:
	CObjectMgr(void);
	~CObjectMgr(void);
	
	void Add(Unit * unit);
	void Remove(Unit * unit);

	CClient * FindPlayer(CharID id) const;
	CClient * FindPlayer(string name) const;
	CClient * GetPlayers() const;
	

	uint32 GetPlayersCnt()		const { return _playersByCharID.size(); }

protected:
	HashMap<CharID, CClient*> _playersByCharID;
	HashMap<string, CClient*> _playersByName;

	CClient * _playerDummy;
	CNpc * _npcDummy;
	Unit * _unitDummy;
};


#endif