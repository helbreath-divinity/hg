#include <windows.h>
#include "ObjectMgr.h"


CObjectMgr::CObjectMgr(void)
{
	_playerDummy = new CClient(-1);
	_npcDummy = new CNpc(-1);
	_unitDummy = new Unit();
}

CObjectMgr::~CObjectMgr(void)
{
}

CClient * CObjectMgr::FindPlayer(CharID id) const
{
	HashMap<CharID, CClient*>::const_iterator it;

	it = _playersByCharID.find(id);

	if(it != _playersByCharID.end())
	{
		return (*it).second;
	}
	
	return _playerDummy;
}

CClient * CObjectMgr::FindPlayer(string name) const
{
	HashMap<string, CClient*>::const_iterator it;

	it = _playersByName.find(name);

	if(it != _playersByName.end())
	{
		return (*it).second;
	}
	
	return _playerDummy;
}

void CObjectMgr::Add(Unit * unit)
{
	if(unit->IsPlayer())
	{
		CClient * player = (CClient*)unit;
		_playersByCharID[ player->m_charID ] = player;
		_playersByName[ player->m_cCharName ] = player;
	}
}

void CObjectMgr::Remove(Unit * unit)
{
	if(unit->IsPlayer())
	{
		CClient * player = (CClient*)unit;
		if(!player->m_bIsInitComplete)
			return;

		_playersByCharID.erase( _playersByCharID.find( player->m_charID ) );
		_playersByName.erase( _playersByName.find( player->m_cCharName ) );
	}
}

CClient * CObjectMgr::GetPlayers() const
{
	static bool getting = false;
	static HashMap<CharID, CClient*>::const_iterator it;

	CClient * player = NULL;

	if(getting)
	{
		if(it == _playersByCharID.end())
		{
			getting = false;
			return NULL;
		}

		player = (*it++).second;
		return player;
	}
	else
	{
		it = _playersByCharID.begin();

		if(it == _playersByCharID.end())
			return NULL;

		getting = true;
		player = (*it++).second;
		return player;
	}
}