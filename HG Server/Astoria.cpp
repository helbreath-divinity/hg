#include "hg.h"
#include "Astoria.h"
#include "char\Npc.h"
#include "map\Map.h"

extern class CGame *   g_game;
extern class CMap	**	g_mapList;
extern class CNpc **	g_npcList;
extern class CClient **	g_clientList;

CAstoria::CAstoria(const EventType type) : _eventType(type)
{
	for(int i=0; i < MAXSIDES; i++)
	{
		_sideStats[i].deaths = 0;
		_sideStats[i].kills = 0;
	}

	_relic = NULL;
	_relicHolder = NULL;
	_relicOwnedSide = NEUTRAL;
	_relicOwnedTime = 0;
	m_relicHolderSteps = 0;

	for(int i=0; i < MAXALTARS; i++)
	{
		_shields[i] = -1;
	}

	g_game->ShuffleAstoriaBasePos();

	switch(_eventType)
	{
	case ET_CAPTURE:
		_CaptureStart();
		break;
	case ET_DESTROY_SHIELD:
		_DestroyShieldStart();
		break;
	}

	g_game->CreateAstoriaFlags();

	m_beginTime = timeGetTime();
}

CAstoria::~CAstoria(void)
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		_CaptureEnd();
		break;
	case ET_DESTROY_SHIELD:
		_DestroyShieldEnd();
		break;
	}

	g_game->DeleteFlags();
}

void CAstoria::PlayerGetRelic(CClient * player)
{ 
	_relicHolder = player;
	_relicHolder->SetStatusFlag(STATUS_RELICHOLDER, true);
	_relicHolder->RemoveMagicEffect(MAGICTYPE_INVISIBILITY);

	g_game->NotifyRelicGrabbed(_relicHolder);
}

void CAstoria::PlayerDropRelic(CClient * player)
{ 
	player->SetStatusFlag(STATUS_RELICHOLDER, false);
	_relicHolder = NULL;

	_relicPos.x = player->m_sX;
	_relicPos.y = player->m_sY;

	m_relicHolderSteps = 0;

	if(_IsRelicInAltar())
	{
		_relicOwnedTime = timeGetTime();
		g_game->NotifyRelicInAltar(_relicOwnedSide);
	}
}

bool CAstoria::CheckVictory()
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		if(_IsRelicInAltar() && timeGetTime() - _relicOwnedTime > RELICVICTORYTIME)
		{
			return true;
		}
		break;
	case ET_DESTROY_SHIELD:
		uint32 shields = 0;

		for(int i=0; i < MAXALTARS; i++)
		{
			if(!g_npcList[ _shields[i] ]->IsDead()) shields++;
		}

		if(shields < 2)
			return true;

		break;
	}
	return false;
}

Side CAstoria::GetVictoriousSide() const
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		return _relicOwnedSide;
	case ET_DESTROY_SHIELD:
		for(int i=0; i < MAXALTARS; i++)
		{
			CNpc * shield = g_npcList[ _shields[i] ];
			if(shield && !shield->IsDead() && shield->m_sType == NPC_AS)
				return (Side)shield->m_side;
		}
		break;
	}
	return NEUTRAL;
}

bool CAstoria::_IsRelicInAltar()
{
	if(_relicHolder) return false;

	for(int i = 0; i < MAXALTARS; i++)
	{
		if(_relicPos == altarPos[i])
		{
			_relicOwnedSide = g_game->m_astoriaBasePos[i];
			return true;
		}
	}
	return false;
}

void CAstoria::_CaptureStart()
{
	_relic = new CItem(); 
	_relic->InitItemAttr(ITEM_RELIC);
	_relicPos = relicStartPos;

	g_mapList[g_game->m_iAstoriaMapIndex]->bSetItem(_relicPos.x, _relicPos.y, _relic);
	g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_SETITEM, g_game->m_iAstoriaMapIndex,
		_relicPos.x, _relicPos.y, _relic->m_sSprite, _relic->m_sSpriteFrame, _relic->m_cItemColor);
}

void CAstoria::_CaptureEnd()
{
	if(_relicHolder)
	{
		uint32 i = _relicHolder->HasItem(ITEM_RELIC);
		if(i != ITEM_NONE)
			g_game->DropItemHandler(_relicHolder->m_handle, i, 1, _relicHolder->m_pItemList[i]->m_cName, false);
	}

	short nextItemSprite, nextItemSpriteFrame;
	char  nextItemColor;

	g_mapList[g_game->m_iAstoriaMapIndex]->pGetItem(_relicPos.x, _relicPos.y, &nextItemSprite, &nextItemSpriteFrame, &nextItemColor);

	g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_SETITEM, g_game->m_iAstoriaMapIndex,
		_relicPos.x, _relicPos.y, nextItemSprite, nextItemSpriteFrame, nextItemColor);

	if(_relic)
		delete _relic;
}

void CAstoria::PlayerKill(CClient * killer, CClient * victim)
{
	if(killer->m_side != victim->m_side)
		_sideStats[killer->m_side].kills++;
	_sideStats[victim->m_side].deaths++;

	g_game->NotifyEventStats(_sideStats);
}

void CAstoria::_DestroyShieldStart()
{
	Point nationAltars[MAXSIDES];

	for(int i=0; i < MAXALTARS; i++)
	{
		nationAltars[ g_game->m_astoriaBasePos[i] ] = altarPos[ i ];
	}

	char cNpcWayPoint[11];
	ZeroMemory(cNpcWayPoint, sizeof(cNpcWayPoint));

	CMap * map = g_mapList[g_game->m_iAstoriaMapIndex];

	int x,y;

	x = nationAltars[ARESDEN].x;
	y = nationAltars[ARESDEN].y;
	if(!g_game->CreateNpc("AG-Aresden", g_game->m_iAstoriaMapIndex, 0, MOVETYPE_RANDOM, 
		&x, &y, (Side)-1, cNpcWayPoint, NULL, NULL)) 
	{
		ERR("Failed to create Astoria Shield");
	}

	x = nationAltars[ELVINE].x;
	y = nationAltars[ELVINE].y;
	if(!g_game->CreateNpc("AG-Elvine", g_game->m_iAstoriaMapIndex, 0, MOVETYPE_RANDOM, 
		&x, &y, (Side)-1, cNpcWayPoint, NULL, NULL)) 
	{
		ERR("Failed to create Astoria Shield");
	}
		
	uint32 shields = 0;
	for(int i = 0; i < MAXNPCS; i++)
	{
		CNpc * npc = g_npcList[i];
		if(npc && npc->m_cMapIndex == g_game->m_iAstoriaMapIndex && npc->m_sType == NPC_AS)
		{
			_shields[ shields ] = i;
			shields++;
		}
	}
}

void CAstoria::_DestroyShieldEnd() const
{
	for (int i = 0; i < MAXALTARS; i++)
	{
		if(_shields[i] != -1)
			g_game->DeleteNpc( g_npcList[ _shields[i] ]->m_handle );
	}
}

void CAstoria::NotifyShieldHP(CNpc * npc) const
{
	for(int i = 1; i < MAXCLIENTS; i++) 
	{	
		if (g_clientList[i] && g_clientList[i]->m_cMapIndex == g_game->m_iAstoriaMapIndex) 
		{	
			g_clientList[i]->Notify(NULL, NOTIFY_SHIELDHP, npc->m_side, npc->m_iHP);
		}	
	}
}

uint32 CAstoria::GetShieldHP(Side side) const
{
	for(int i = 0; i < MAXALTARS; i++) 
	{	
		if(_shields[i] != -1 && g_npcList[ _shields[i] ]->m_side == side)
			return g_npcList[ _shields[i] ]->m_iHP;
	}
	
	return 0;
}