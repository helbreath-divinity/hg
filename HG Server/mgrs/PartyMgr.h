#ifndef PARTYMGR_H
#define PARTYMGR_H
#pragma once

#include "..\..\shared\common.h"
#include "..\char\client.h"
#include "..\char\party.h"

class CPartyMgr
{
public:
	CPartyMgr(void);
	~CPartyMgr(void);

	CParty * CreateParty(CClient * player = NULL, CClient * player2 = NULL);
	CParty * GetParty(uint32 id)		{ return _parties[id]; }
	void RemoveFromParty(CClient * player);
	void DeleteParty(uint32 id);

	bool PartyExists(uint32 id)	const { return ( _parties.find( id ) != _parties.end() ); }
protected:
	PartyMap _parties;

	uint32 _idCnt;
	uint32 _GetNewID() { return ++_idCnt; }
};


#endif