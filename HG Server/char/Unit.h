#ifndef UNIT_H
#define UNIT_H
#pragma once

#include "magic.h"
#include "..\\..\\shared\\common.h"

class CClient;

enum OwnerType{
	OWNERTYPE_NONE,
	OWNERTYPE_PLAYER,
	OWNERTYPE_NPC,
	OWNERTYPE_PLAYER_INDIRECT,
	OWNERTYPE_NPC_INDIRECT
};

class Unit
{
public:
	Unit(void);
	virtual ~Unit(void);
	void SetStatusFlag(long flag, bool enabled);
	void ToggleStatusFlag(long flag);
	bool GetStatusFlag(long flag) const;
	void SetMagicFlag(short magicType, bool enabled);
	bool AddMagicEffect(short magicType, long effectTime, char kind = 1);
	bool RemoveMagicEffect(char magicType);
	void SetSideFlag(Side side);

	bool IsDead()			const { return (m_iHP > 0) ? false : true; }
	bool IsBerserked()	const { return m_cMagicEffectStatus[MAGICTYPE_BERSERK] ? true : false; }
	bool IsInvisible()	const { return m_cMagicEffectStatus[MAGICTYPE_INVISIBILITY] ? true : false; }

	bool IsPlayer()	const	{ return (m_ownerType == OWNERTYPE_PLAYER) ? true : false; }
	bool IsNPC() 		const	{ return (m_ownerType == OWNERTYPE_NPC) ? true : false; }
	bool IsNeutral()	const	{ return (m_side == NEUTRAL) ? true : false; }
	bool IsAres()		const	{ return (m_side == ARESDEN) ? true : false; }
	bool IsElv()		const	{ return (m_side == ELVINE) ? true : false; }

	CClient * GetKiller() const;
	virtual float GetDropFactor()		const { return 1.0f; }



	short m_handle;
	
	short m_sX, m_sY;
	int  m_iHP;
	int  m_iMP;
	int  m_iExp;
	Side m_side;
	uint32 m_iStatus;
	bool m_bIsKilled;
	long m_killerh;
	char  m_cMapIndex;

	char  m_cDir;
	short m_sType;
	short m_sOriginalType;
	short m_ownerType;

	char  m_cMagicEffectStatus[MAXMAGICEFFECTS];

	int   m_iGuildGUID;

	typedef uint64 UID;
	UID m_uid;
	static UID GenUID(){
		static UID uids = 0;
		return uids++;
	}
};
#endif
