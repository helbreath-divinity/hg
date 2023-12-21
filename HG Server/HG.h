#ifndef HG_H
#define HG_H
#pragma once

#include <windows.h>
//#include <winbase.h>
//#include <process.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <direct.h>
//#include <algorithm>

#include "..\shared\common.h"
#include "..\Shared\npcType.h"

#include "GlobalDef.h"
#include "map\TeleportLoc.h"

class CMap;
class CBuildItem;
class CItem;
class CTile;
class CMagic;
class CNpc;
class CClient;
class Unit;
class XSocket;
class DropManager;
class CDynamicObject;
class CDelayEvent;
class CMsg;
class CSkill;
class CQuest;
class CCrafting;
class CTeleport;
class CFish;
class CPortion;
class CMineral;
class CIni;

#define SERVERSOCKETBLOCKLIMIT	300

#define MAXCLIENTS			200
#define MAXNPCS				15000
#define MAXMAPS				120
#define MAXBUILDITEMS		300
#define CLIENTTIMEOUT		18 _s
#define AUTOSAVETIME		3 _m
#define HPUPTIME			15 _s
#define MPUPTIME			20 _s
#define SPUPTIME			10 _s

#define HUNGERTIME			1 _m
#define POISONTIME			12 _s
#define SUMMONTIME			5 _m
#define NOTICETIME			80 _s
#define PLANTTIME			5 _m

#define EXPSTOCKTIME		10 _s
#define MSGQUENESIZE		100000
#define AUTOEXPTIME			6 _m



#define TOTALLEVELUPPOINT	3

#define MAXDYNAMICOBJECTS	60000
#define MAXDELAYEVENTS		60000

#define SSN_LIMIT_MULTIPLY_VALUE	2

#define MAXNOTIFYMSGS		1000
#define NIGHTTIME			40

#define CHARPOINTLIMIT		200
#define RAGPROTECTIONTIME	7000
#define MAXREWARDGOLD		99999999

#define ATTACKAI_NORMAL				1
#define ATTACKAI_EXCHANGEATTACK		2
#define ATTACKAI_TWOBYONEATTACK		3

#define MAXFISHS					200
#define MAXMINERALS					200
#define MAXENGAGINGFISH				30
#define MAXPORTIONTYPES				500 
#define MAXCRAFTING					120

#define MOBEVENTTIME				5 _m
#define MAXQUESTTYPE				200

#define MAXSUBLOGSOCK				5

#define ITEMLOG_GIVE				1
#define ITEMLOG_DROP				2
#define ITEMLOG_GET					3
#define ITEMLOG_DEPLETE				4
#define ITEMLOG_NEWGENDROP			5
#define ITEMLOG_DUPITEMID			6
#define ITEMLOG_BUY					7        
#define ITEMLOG_SELL				8     
#define ITEMLOG_RETRIEVE			9
#define ITEMLOG_DEPOSIT				10
#define ITEMLOG_EXCHANGE			11
#define ITEMLOG_MAGICLEARN			12
#define ITEMLOG_MAKE				13
#define ITEMLOG_SUMMONMONSTER		14
#define ITEMLOG_POISONED			15
#define ITEMLOG_SKILLLEARN			16
#define ITEMLOG_REPAIR				17
#define ITEMLOG_JOINGUILD           18
#define ITEMLOG_BANGUILD            19
#define ITEMLOG_RESERVEFIGZONE      20	//  "
#define ITEMLOG_APPLY               21	//  "
#define ITEMLOG_SHUTUP              22	//  "
#define ITEMLOG_CLOSECONN			23	//  "
#define ITEMLOG_SPELLFIELD			24	//  "
#define ITEMLOG_CREATEGUILD			25	//  "
#define ITEMLOG_GUILDDISMISS		26	//  "
#define ITEMLOG_SUMMONPLAYER        27	//  "
#define ITEMLOG_CREATE				28	//  "
#define ITEMLOG_UPGRADEFAIL         29
#define ITEMLOG_UPGRADESUCCESS      30
#define ITEMLOG_MAILRETRIEVE			31
#define ITEMLOG_MAILSEND				32
#define ITEMLOG_GWHDEPOSIT				33
#define ITEMLOG_GWHRETRIEVE			34


#define ITEMSPREAD_RANDOM			1
#define ITEMSPREAD_FIXED			2
#define MAX_NPCITEMDROP				95


#define CRUSADELOG_ENDCRUSADE       1
#define CRUSADELOG_STARTCRUSADE     2
#define CRUSADELOG_SELECTDUTY       3
#define CRUSADELOG_GETEXP           4
#define CRUSADELOG_APOCALYPSE		5

#define PKLOG_BYPLAYER				1
#define PKLOG_BYPK					2
#define PKLOG_BYENERMY				3
#define PKLOG_BYNPC					4
#define PKLOG_BYOTHER				5
#define PKLOG_REDUCECRIMINAL        6


#define MAXDUPITEMID				100

#define MAXGUILDS					1000
#define MAXONESERVERUSERS			800	 
#define MAXGATESERVERSTOCKMSGSIZE	30000


#define MAXCONSTRUCTNUM			20//raised from 10 to 20 to in corporate 4mana stones

#define MAXSCHEDULE					10



#define MAXFIGHTZONE 10 

//============================
// #define LEVELLIMIT		130
#define LEVELLIMIT		50
//============================

//============================
#define MINIMUMHITRATIO 15
//============================

//============================
#define MAXIMUMHITRATIO	99
//============================

//============================
#define PLAYERMAXLEVEL	180
//============================

//============================
#define GMGMANACONSUMEUNIT	15
//============================

#define MAXCONSTRUCTIONPOINT 30000

#define MAXWARCONTRIBUTION	 500000

#define MAXPARTYNUM			200


#define ALLSIDES			100
#define ATTACKER			101
#define DEFENDER			102

//v2.19 2002-11-19 
#define PK					0
#define NONPK				1
#define NEVERNONPK			2  

#define MAX_CRUSADESUMMONMOB	100

#define CRUSADELOG_ENDHELDENIAN		11
#define CRUSADELOG_STARTHELDENIAN	12
#define CRUSADELOG_GETHELDENIANEXP	14
#define CRUSADELOG_HELDENIANVICTORY	15
#define CRUSADELOG_HELDENIANWARNOW	16

#define MAX_HELDENIANTOWER			200
#define MAXHELDENIAN				10
#define MAXHELDENIANSUMMONPOINT		12000	

class CGame  
{
public:

	void UpdateSoccerEvent() const;
	void SoccerEventWon(Side side, int MapIndex);
	void CreateSoccerFile(int Winner) const;
	bool ReadSoccerFile(char * cFn);

	void StartHeldenianMode(int iClientH = -1);
	bool bReadHeldenianGUIDFile(char * cFn);
	void _CreateHeldenianGUID(uint32 m_dwHeldenianGUID, int m_iHeldenianType1Winner, int m_iHeldenianType2Winner, int m_iHeldenianType) const;
	bool SetHeldenianFlag(char cMapIndex, int dX, int dY, int iSide, int iEKNum, int iClientH, int code);
	void UpdateHeldenianStatus() const;	
	void HeldenianEndWarNow(int m_iHeldenianType, Side side);
	void CheckHeldenianResultCalculation(int iClientH) const;
	void RequestHeldenianScroll(int iClientH, char * pData, uint32 dwMsgSize);
	void HeldenianPlayerKill(CClient * killer, CClient * victim);

	void Apocalypse_MonsterCount(int iClientH);
	void DoAbaddonThunderDamageHandler(char cMapIndex);
	void SendThunder(int iClient, short sX, short sY, short sV3, short sV4);
	void LocalEndApocalypse();
	void LocalStartApocalypse();
	void GlobalEndApocalypseMode(int iClientH);
	void GlobalStartApocalypseMode(int iClientH = NULL);
	void GenerateApocalypseBoss(int MapIndex);
	void Notify_ApocalypseGateState(int iClientH);
	void Use_ApocalypseGate(int iClientH);
	void Open_EmptyMap_Gate(int MapIndex);
	void GenerateSlime(int MapIndex);

	int  iSetSide(int iClientH); 
	bool _bCrusadeLog(int iAction,int iClientH,int iData, char * cName);
	void SetForceRecallTime(int iClientH) ; 
	bool bCheckClientMoveFrequency(int iClientH, bool running);
	bool bCheckClientMagicFrequency(int iClientH);
	bool bCheckClientAttackFrequency(int iClientH); 
	void RequestGuildNameHandler(int iClientH, int iObjectID, int iIndex); 
	void ArmorLifeDecrement(int iClientH, int sTargetH, char cOwnerType, int iValue);
	bool bCheckIsItemUpgradeSuccess(int iClientH, int iItemIndex, int iSomH,bool bBonus = false) ;
	void RequestItemUpgradeHandler(int iClientH, int iItemIndex);
	void GetExp(int iClientH, int iExp, bool bIsAttackerOwn = false);
	void RequestAcceptJoinPartyHandler(int iClientH, int iResult);
	void RequestDismissPartyHandler(int iClientH);
	void ResurrectPlayer(int iClientH);
	void AdminOrder_GetFightzoneTicket(int iClientH);
	void KillCrusadeObjects();
	void AdminOrder_CheckRep(int iClientH, char * pData,uint32 dwMsgSize);
	void AdminOrder_CleanMap(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_Ethereal(int iClientH);

	void RequestUpdateFriendsHandler(int iClientH, char *pData, uint32 dwMsgSize);
	void GSM_RequestFindFriend(uint16 reqServerID, uint16 reqClientH, char * requesterName, char * names, uint16 nameSize);

	bool bReadSchedulerConfigFile(char * pFn);
	void Scheduler();
	bool bCopyItemContents(CItem * pOriginal, CItem * pCopy);

	int  iGetMapLocationSide(char * pMapName);
	void WriteItemData(char * &cp, CItem * pItem) const;
	bool WriteTileData(char * buffer, int & sizeWritten, int iClientH, CTile * srcTile, int ix, int iy);

	void ManualEndCrusadeMode(int m_iCrusadeWinnerSide);
	void ChatMsgHandlerGSM(int iMsgType, int iV1, char * pName, char * pData, uint32 dwMsgSize);
	bool bReadCrusadeGUIDFile(char * cFn);
	void _CreateCrusadeGUID(uint32 dwCrusadeGUID, int m_iCrusadeWinnerSide);
	void RemoveClientShortCut(int iClientH);
	bool bAddClientShortCut(int iClientH);
	void RequestSetGuildConstructLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void GSM_SetGuildConstructLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void GSM_ConstructionPoint(int iGuildGUID, int iPoint);
	void CheckCommanderConstructionPoint(int iClientH);
	void GlobalStartCrusadeMode();
	void GSM_SetGuildTeleportLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void SyncMiddlelandMapInfo();
	void _GrandMagicLaunchMsgSend(int iType, char cAttackerSide);

	void GrandMagicResultHandler(char * cMapName, int iCrashedStructureNum, int iStructureDamageAmount, int iCasualities, int iActiveStructure, int iSTCount,char * pData);
	void CalcMeteorStrikeEffectHandler(int iMapIndex);
	void DoMeteorStrikeDamageHandler(int iMapIndex);
	void GSM_RequestFindCharacter(uint16 wReqServerID, uint16 wReqClientH, char * pName,char * cCharName);

	void GSM_RequestShutupPlayer(char * cName,uint16 wReqServerID, uint16 wReqClientH, uint16 wV1,char * cTemp); 
	void ServerStockMsgHandler(char * pData);
	void SendStockMsgToGateServer();
	bool bStockMsgToGateServer(char * pData, uint32 dwSize);
	
	void ReqCreateCraftingHandler(int iClientH, char *pData);
	bool _bDecodeCraftingConfigFileContents(char * pData, uint32 dwMsgSize);

	void _SendMapStatus(int iClientH);
	void MapStatusHandler(int iClientH, int iMode, char * pMapName);
	void SelectCrusadeDutyHandler(int iClientH, int iDuty);

	void CheckConnectionHandler(int iClientH, char *pData);
	void RequestSummonWarUnitHandler(int iClientH, int dX, int dY, char cType, char cNum, char cMode);
	void RequestGuildTeleportHandler(int iClientH);
	void RequestSetGuildTeleportLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void MeteorStrikeHandler(int iMapIndex);
	void _LinkStrikePointMapIndex();
	void MeteorStrikeMsgHandler(char cAttackerSide);
	void SendCollectedMana();
	void CreateCrusadeStructures();

	bool bReadCrusadeStructureConfigFile(char * cFn);
	void SaveOccupyFlagData();
	void LocalEndCrusadeMode(int crusadeWinnerSide);
	void LocalStartCrusadeMode(uint32 dwGuildGUID);
	void CheckCrusadeResultCalculation(int iClientH);

	bool __bSetConstructionKit(int iMapIndex, int dX, int dY, int iType, int iTimeCost, int iClientH);
	bool __bSetAgricultureItem(int iMapIndex, int dX, int dY, int iType, int iSsn,int iClientH);   
	bool bCropsItemDrop(int iClientH, short iTargetH,bool bMobDropPos = false);
	void AgingMapSectorInfo();
	void UpdateMapSectorInfo();

	bool bGetItemNameWhenDeleteNpc(int & iItemID, short sNpcType, int iItemprobability);

	void CancelQuestHandler(int iClientH);
	void ActivateSpecialAbilityHandler(int iClientH);
	void EnergySphereProcessor(bool bIsAdminCreate = false, int iClientH = NULL);
	bool bCheckEnergySphereDestination(int iNpcH, short sAttackerH, char cAttackerType);
	void JoinPartyHandler(int iClientH, int iV1, char * pMemberName);
	void DeleteOccupyFlags(int iMapIndex);
	void RequestSellItemListHandler(int iClientH, char * pData);
	void AdminOrder_CreateItem(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_SetWeather(int iClientH, char * pData, uint32 dwMsgSize);
	void RequestRestartHandler(int iClientH);
	void AdminOrder_SetObserverMode(int iClientH);
	int iRequestPanningMapDataRequest(int iClientH, char * pData);
	void GetMagicAbilityHandler(int iClientH);
	void _TamingHandler(int iClientH, int iSkillNum, char cMapIndex, int dX, int dY);
	void RequestCheckAccountPasswordHandler(char * pData, uint32 dwMsgSize);
	int _iTalkToNpcResult_Guard(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	void _bDecodeNoticementFileContents(char * pData, uint32 dwMsgSize);
	void RequestNoticementHandler(int iClientH, char * pData);
	bool _bCheckDupItemID(CItem * pItem);
	bool _bDecodeDupItemIDFileContents(char * pData, uint32 dwMsgSize);
	void NpcDeadItemGenerator(int iNpcH, short sAttackerH, char cAttackerType);
	uint32 RollMultiple(CNpc * npc, int iItemSpreadType, int iSpreadRange, int *iItemIDs, Point *BasePos);
	void AdminOrder_DisconnectAll(int iClientH);
	void AdminOrder_Summon(int iClientH, char * pData, uint32 dwMsgSize);

	void AdminOrder_SummonPlayer(int iClientH, char * pData, uint32 dwMsgSize);


	char _cGetSpecialAbility(int iKindSA);
	void AdminOrder_UnsummonBoss(int iClientH);
	void AdminOrder_UnsummonAll(int iClientH);
	void AdminOrder_SetAttackMode(int iClientH, char * pData, uint32 dwMsgSize);

	void AdminOrder_ToggleInvincible(int iClientH);
	void AdminOrder_ToggleNoAggro(int iClientH);
	void AdminOrder_ToggleEthereal(int iClientH);

	void AdminOrder_SetForceRecallTime(int iClientH, char * pData, uint32 dwMsgSize);

	void AdminOrder_EventSpell(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventArmor(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventSheild(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventChat(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventParty(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventReset(int iClientH);
	void AdminOrder_EventTP(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_EventIllusion(int iClientH, char * pData, uint32 dwMsgSize);

	void BuildItemHandler(int iClientH, char * pData);
	bool _bDecodeBuildItemConfigFileContents(char * pData, uint32 dwMsgSize);
	bool _bCheckSubLogSocketIndex();

	bool _bItemLog(int iAction, int iGiveH, int iRecvH, CItem * pItem, bool bForceItemLog = false) ;
	bool _bItemLog(int iAction, int iClientH, char * cName, CItem * pItem);

	bool _bPKLog(int iAction, int iAttackerH, int iVictumH, char * cNPC) ;

	void OnSubLogRead(int iIndex);
	void OnSubLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void _CheckStrategicPointOccupyStatus(char cMapIndex);
	void GetMapInitialPoint(int iMapIndex, short * pX, short * pY, char * pPlayerLocation = NULL);
	void _ClearQuestStatus(int iClientH);
	bool _bCheckItemReceiveCondition(int iClientH, CItem * pItem);
	void SendItemNotifyMsg(int iClientH, uint16 wMsgType, CItem * pItem, int iV1, bool deleteOnError);

	int _iTalkToNpcResult_WTower(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_WHouse(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_BSmith(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GShop(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GuildHall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	bool _bCheckIsQuestCompleted(int iClientH);
	void _CheckQuestEnvironment(int iClientH);
	void _SendQuestContents(int iClientH);
	bool _bDecodeQuestConfigFileContents(char * pData, uint32 dwMsgSize);
	void CancelExchangeItem(int iClientH);
	bool bAddItem(int iClientH, CItem * pItem);
	void ConfirmExchangeItem(int iClientH);
	void SetExchangeItem(int iClientH, int iItemIndex, int iAmount);
	void ExchangeItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, uint16 wObjectID, char * pItemName);


	void _Manager_Init(int iClientH, char * pData);
	void _Manager_Shutdown(int iClientH, char * pData);


	void CheckUniqueItemEquipment(int iClientH);
	void _SetItemPos(int iClientH, char * pData);
	void GetHeroMantleHandler(int iClientH,int iItemID,char * pString);

	bool _bDecodeOccupyFlagSaveFileContents(char * pData, uint32 dwMsgSize);
	void GetOccupyFlagHandler(int iClientH);
	int  _iComposeFlagStatusContents(char * pData);
	void SetSummonMobAction(int iClientH, int iMode, uint32 dwMsgSize, char * pData = NULL);
	bool __bSetOccupyFlag(char cMapIndex, int dX, int dY, int iSide, int iEKNum, int iClientH, bool bAdminFlag);
	bool _bDepleteDestTypeItemUseEffect(int iClientH, int dX, int dY, short sItemIndex, short sDestItemID);
	void SetDownSkillIndexHandler(int iClientH, int iSkillIndex);
	int iGetComboAttackBonus(int iSkill, int iComboCount);
	int  _iGetWeaponSkillType(int iClientH);
	//void AdminOrder_GetNpcStatus(int iClientH, char * pData, uint32 dwMsgSize);
	void CheckFireBluring(char cMapIndex, int sX, int sY);
	void NpcTalkHandler(int iClientH, int iWho);
	bool bDeleteMineral(int iIndex);
	void DeleteFlags();
	void _CheckMiningAction(int iClientH, int dX, int dY);
	int iCreateMineral(char cMapIndex, int tX, int tY, char cLevel);
	void MineralGenerator();
	void LocalSavePlayerData(int iClientH);
	bool _bDecodePortionConfigFileContents(char * pData, uint32 dwMsgSize);
	void ReqCreatePortionHandler(int iClientH, char * pData);
	void _CheckAttackType(int iClientH, short * spType);
	bool bOnClose();
	void AdminOrder_SetInvi(int iClientH);
	void AdminOrder_SetHP(int iClientH, uint32 val);
	void AdminOrder_SetMP(int iClientH, uint32 val);
	void AdminOrder_SetMag(int iClientH, uint32 val);
	void AdminOrder_Polymorph(int iClientH, char * pData, uint32 dwMsgSize);
	void ForceDisconnectAccount(char * pAccountName, uint16 wCount);
	void NpcRequestAssistance(int iNpcH);
	void ToggleSafeAttackModeHandler(int iClientH);
	void AdminOrder_CheckIP(int iClientH, char * pData, uint32 dwMsgSize);
	void SpecialEventHandler();
	int _iForcePlayerDisconect(int iNum);
	void AdminOrder_Teleport(int iClientH, char * pData, uint32 dwMsgSize);
	int iGetMapIndex(char * pMapName);
	int iGetWeatherMagicBonusEffect(CMagic * spell, Weather weather);
	void WeatherProcessor();
	int getPlayerNum(char cMapIndex, short dX, short dY, char cRadius);
	void FishGenerator();
	void ReqGetFishThisTimeHandler(int iClientH);
	void AdminOrder_CreateFish(int iClientH, char * pData, uint32 dwMsgSize);
	void FishProcessor();
	int iCheckFish(int iClientH, char cMapIndex, short dX, short dY);
	bool bDeleteFish(int iHandle, int iDelMode);
	int  iCreateFish(char cMapIndex, short sX, short sY, short sDifficulty, CItem * pItem, int iDifficulty, uint32 dwLastTime);
	void UserCommand_DissmissGuild(int iClientH, char * pData, uint32 dwMsgSize);

	void UserCommand_BanGuildsman(int iClientH, char * pData, uint32 dwMsgSize);

	void AdminOrder_ReserveFightzone(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_CloseConn(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_CallGuard(int iClientH, char * pData, uint32 dwMsgSize);
	int iGetExpLevel(int iExp);
	void CalcExpStock(int iClientH);
	void ResponseSavePlayerDataReplyHandler(char * pData, uint32 dwMsgSize);
	void NoticeHandler();
	bool bReadNotifyMsgListFile(char * cFn);
	void SetPlayerReputation(int iClientH, char * pMsg, char cValue, uint32 dwMsgSize);
	void ShutUpPlayer(int iClientH, char * pMsg, uint32 dwMsgSize);
	void CheckDayOrNightMode();
	void PoisonEffect(int iClientH, int iV1);
	bool _bGetIsPlayerHostile(int iClientH, int sOwnerH);
	bool bAnalyzeCriminalAction(int iClientH, short dX, short dY, bool bIsCheck = false);
	void CalcTotalItemEffect(int iClientH, int iEquipItemID, bool bNotify = true);
	void GetPlayerProfile(int iClientH, char * pMsg, uint32 dwMsgSize);
	void SetPlayerProfile(int iClientH, char * pMsg, uint32 dwMsgSize);
	void ToggleWhisperPlayer(int iClientH, char * pMsg, uint32 dwMsgSize);
	void CheckAndNotifyPlayerConnection(int iClientH, char * pMsg, uint32 dwSize);
	int iCalcTotalWeight(int iClientH);
	void ReqRepairAll(int iClientH);
	void ReqRepairAllConfirmHandler(int iClientH, int quotedPrice);
	void ReqRepairItemCofirmHandler(int iClientH, char cItemID, char * pString);
	void ReqRepairItemHandler(int iClientH, char cItemID, char cRepairWhom, char * pString);
	void ReqSellItemConfirmHandler(int iClientH, char cItemID, int iNum, char * pString);
	void ReqSellItemHandler(int iClientH, char cItemID, char cSellToWhom, int iNum, char * pItemName);
	void UseSkillHandler(int iClientH, int iV1, int iV2, int iV3);
	int  iCalculateUseSkillItemEffect(int iOwnerH, char cOwnerType, char cOwnerSkill, int iSkillNum, char cMapIndex, int dX, int dY);
	void ClearSkillUsingStatus(int iClientH);
	void DynamicObjectEffectProcessor();
	int _iGetTotalClients();
	void SendObjectMotionRejectMsg(int iClientH);
	bool RemoveFromDelayEventList(int iH, char cType, int iEffectType);
	bool RemoveFromDelayEventList(Unit * unit, int iEffectType);
	void DelayEventProcessor();
	bool RegisterDelayEvent(int iDelayType, int iEffectType, uint32 dwLastTime, int iTargetH, char cTargetType, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3);
	bool RegisterDelayEvent(int iDelayType, int iEffectType, uint32 dwLastTime, Unit * unit, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3);
	int iGetFollowerNumber(short sOwnerH, char cOwnerType);
	int  _iCalcSkillSSNpoint(int iLevel);
	void OnKeyUp(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	bool bSetItemToBankItem(int iClientH, CItem * pItem);
	void Effect_SpDown_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_HpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_Damage_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3, bool bExp, Element element = ELEMENT_NONE, CMagic * spell = NULL);
	void Effect_Damage_Spot_DamageMove(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, bool bExp, Element element = ELEMENT_NONE, CMagic * spell = NULL);
	void UseItemHandler(int iClientH, short sItemIndex, short dX, short dY, short sDestItemID);

	void ItemDepleteHandler(int iClientH, short sItemIndex, bool bIsUseItemResult, bool bIsLog = true, bool notify = true);
	int _iGetArrowItemIndex(int iClientH);
	void RequestFullObjectData(int iClientH, char * pData, int objectID = -1);
	void DeleteNpc(int iNpcH);
	void nextWaypointDest(int iNpcH);
	void MobGenerator();
	void CheckDynamicObjectList();
	int  iAddDynamicObjectList(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, uint32 dwLastTime, int iV1 = NULL);
	int _iCalcMaxLoad(int iClientH);
	void GetRewardMoneyHandler(int iClientH);
	void EnemyKillRewardHandler(int iAttackerH, int iClientH);
	void PK_KillRewardHandler(short sAttackerH, short sVictimH);
	void RequestRetrieveItemHandler(int iClientH, char * pData);
	void RequestRetrieveGuildItem(CClient * player, char * data);
	void HandlePingMap(const CClient * player, char * data) const;
	void RequestCivilRightHandler(int iClientH, char * pData);
	bool bCheckLimitedUser(int iClientH);
	void LevelUpSettingsHandler(int iClientH, char * pData, uint32 dwMsgSize);

	void FightzoneReserveHandler(int iClientH, char * pData, uint32 dwMsgSize);
	bool bCheckLevelUp(int iClientH);
	int iGetLevelExp(int iLevel);
	void TimeManaPointsUp(int iClientH);
	void TimeStaminarPointsUp(int iClientH);
	void Quit();

	int  _iGetSkillNumber(char * pSkillName);
	void TrainSkillResponse(bool bSuccess, int iClientH, int iSkillNum, int iSkillLevel);
	int _iGetMagicNumber(char * pMagicName, int * pReqInt, int * pCost);
	bool RequestStudyMagicHandler(int iClientH, char * pName, bool bIsPurchase = true);
	void VariableAdd(CClient * player, CItem * item);
	bool _bDecodeSkillConfigFileContents(char * pData, uint32 dwMsgSize);
	bool _bDecodeMagicConfigFileContents(char * pData, uint32 dwMsgSize);
	void ReleaseFollowMode(short sOwnerH, char cOwnerType);
	void RequestTeleportHandler(int iClientH, char recallType, char * cMapName = NULL, int dX = -1, int dY = -1);
	void PlayerMagicHandler(int iClientH, int dX, int dY, short sType, bool bItemEffect = false, int iV1 = NULL);
	int  iClientMotion_Magic_Handler(int iClientH, short sX, short sY, char cDir);
	void ToggleCombatModeHandler(int iClientH); 
	void GuildNotifyHandler(char * pData, uint32 dwMsgSize);
	void SendGuildMsg(int iClientH, uint16 wNotifyMsgType, short sV1, short sV2, char * pString);
	void TimeHitPointsUp(int iClientH);
	void CalculateGuildEffect(int iVictimH, char cVictimType, short sAttackerH);
	void OnStartGameSignal();
	bool _binitNpcAttr(CNpc * pNpc, char * pNpcName, short sClass, char cSA);
	bool _bDecodeNpcConfigFileContents(char * pData, uint32 dwMsgSize);
	void ReleaseItemHandler(int iClientH, short sItemIndex, bool bNotice);
	int  SetItemCount(int iClientH, char * pItemName, uint32 dwCount);
	int  SetItemCount(int iClientH, int iItemIndex, uint32 dwCount);
	uint32 dwGetItemCount(int iClientH, char * pName);
	void DismissGuildRejectHandler(int iClientH, char * pName);
	void DismissGuildApproveHandler(int iClientH, char * pName);
	void JoinGuildRejectHandler(int iClientH, char * pName);			    
	void JoinGuildApproveHandler(int iClientH, char * pName);
	void SendNotifyMsg(int iFromH, int iToH, uint16 wMsgType, uint32 sV1 = NULL, uint32 sV2 = NULL, uint32 sV3 = NULL, const char * pString = NULL, 
		uint32 sV4 = NULL, uint32 sV5 = NULL, uint32 sV6 = NULL, uint32 sV7 = NULL, uint32 sV8 = NULL, 
		uint32 sV9 = NULL, char * pString2 = NULL) const;
	void GiveItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, uint16 wObjectID, char * pItemName);
	void RequestPurchaseItemHandler(int iClientH, char * pItemName, int iNum);
	void ResponseDisbandGuildHandler(char * pData, uint32 dwMsgSize);
	void RequestDisbandGuildHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void RequestCreateNewGuildHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void ResponseCreateNewGuildHandler(char * pData, uint32 dwMsgSize);
	void ResponseGuildInfo(char * data);
	int  iClientMotion_Stop_Handler(int iClientH, short sX, short sY, char cDir);

	bool bEquipItemHandler(int iClientH, short sItemIndex, bool bNotify = true);
	bool _bAddClientItemList(int iClientH, CItem * pItem, int * pDelReq);
	int  iClientMotion_GetItem_Handler(int iClientH, short sX, short sY, char cDir);
	void DropItemHandler(int iClientH, short sItemIndex, int iAmount, char * pItemName, bool bByPlayer = false);
	void ClientCommonHandler(int iClientH, char * pData);
	bool __fastcall bGetMsgQuene(char * pFrom, char * pData, uint32 * pMsgSize, int * pIndex, char * pKey);
	void MsgProcess();
	bool __fastcall bPutMsgQuene(char cFrom, char * pData, uint32 dwMsgSize, int iIndex, char cKey);
	void NpcBehavior_Flee(int iNpcH);
	void NpcBehavior_Dead(int iNpcH);
	void NpcKilledHandler(short sAttackerH, char cAttackerType, int iNpcH, short sDamage);
	void RemoveFromTarget(short sTargetH, char cTargetType, int iCode = NULL);
	void RemoveFromTarget(Unit * target, int iCode = NULL);
	bool bGetEmptyPosition(short * pX, short * pY, char cMapIndex);
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int * pError);
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int * pError, short * DOType);
	int  iClientMotion_Attack_Handler(int iClientH, short sX, short sY, short dX, short dY, short wType, char cDir, uint16 wTargetObjectID, bool bRespose = true, bool bIsDash = false);
	void ChatMsgHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void NpcProcess();
	CNpc * CreateNpc(char * pNpcName, int mapIndex, char cSA, char cMoveType, int * poX, int * poY, Side changeSide, char * pWaypointList, RECT * pArea, int iSpotMobIndex, bool bHideGenMode = false, bool bIsSummoned = false, bool bFirmBerserk = false, bool bIsMaster = false, int iGuildGUID = NULL);
	bool _bReadMapInfoFiles(int iMapIndex);

	bool _bGetIsStringIsNumber(char * pStr);

	bool bReadProgramConfigFile(char * cFn);
	void InitPlayerData(int iClientH, char * pData, uint32 dwSize);
	void ResponsePlayerDataHandler(char * pData, uint32 dwSize);
	//void RequestInitDataHandler(int iClientH);
	//void RequestInitPlayerHandler(int iClientH, char * pData, char cKey);
	void PlayerMapEntry(int iClientH, bool setRecallTime = true);


	bool bSendMsgToLS(uint32 dwMsg, int iClientH, bool bFlag = true,char * pData = NULL, uint32 v1 = 0, uint32 v2 = 0 );
	void CheckClientResponseTime();
	void OnTimer(char cType);
	int iComposeMoveMapData(short sX, short sY, int iClientH, char cDir, char * pData);
	void SendEventToNearClient_TypeB(uint32 dwMsgID, uint16 wMsgType, char cMapIndex, short sX, short sY, short sV1 = 0, short sV2 = 0, short sV3 = 0, short sV4 = 0);
	void SendEventToNearClient_TypeA(short sOwnerH, char cOwnerType, Msgid msgid, short sV1, short sV2, short sV3);
	void DeleteClient(int iClientH, bool bSave, bool bNotify, bool bCountLogout = true, bool bForceCloseConn = false);
	int  iComposeInitMapData(short sX, short sY, int iClientH, char * pData);
	int  iClientMotion_Move_Handler(int iClientH, short sX, short sY, char cDir, bool bIsRun);
	void ClientMotionHandler(int iClientH, char * pData);
	void DisplayInfo(HDC hdc);
	void OnClientRead(int iClientH);
	bool bInit();
	void OnClientSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	bool bAccept(XSocket * pXSock);
	void PlayerOrder_SetAFK(int iClientH);


	void GetFightzoneTicketHandler(int iClientH);

	void FightzoneReserveProcessor() ;

	// 2002-10-23 Item Event
	bool NpcDeadItemGeneratorWithItemEvent(int iNpcH, short sAttackerH, char cAttackerType);

	bool bCheckInItemEventList(int iItemID, int iNpcH);


	bool _bDecodeTeleportListConfigFileContents(char * pData, uint32 dwMsgSize);

	void RequestQuestListHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void RequestAcceptQuestHandler(int iClientH, char * pData, uint32 dwMsgSize);

	void RequestTeleportListHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void RequestChargedTeleportHandler(int iClientH, char *pData, uint32 dwMsgSize);
	void RequestResurrectPlayer(int iClientH, bool bResurrect);

	// -------------------- GUILD ---------------------
	void RequestGuildBank(CClient * player, char * data);
	void RequestGuildSummon(CClient * player, char * data);
	void ResponseGuildSummon(CClient * player, char * data);
	void GuildContribute(CClient * player, char * data);
	void GuildUpgrade(CClient * player, char * data) const;
	void GuildsmanChange(CClient * player, char * data) const;
	void RequestGuildBoard(CClient * player, char * data);
	void ResponseGuildBoard(char * data, uint32 size);
	void RequestGuildBoardPost(CClient * player, char * data);
	void ResponseGuildBoardPost(char * data, uint32 size);
	void RequestDeleteGuildBoardPost(CClient * player, char * data);
	void RequestPostGuildBoard(CClient * player, char * data, uint32 size);
	void ResponsePostGuildBoard(char * data, uint32 size);
	
	// -------------------- MAILBOX ---------------------
	void RequestMailbox(CClient * player, char * data);
	void ResponseMailbox(char * data, uint32 size);
	void RequestMailData(CClient * player, char * data);
	void ResponseMailData(char * data);
	void RequestSendMail(CClient * player, char * data, uint32 size);
	void ResponseSendMail(char * data);
	void RequestDeleteMail(CClient * player, char * data);
	void RequestRetrieveMailItem(CClient * player, char * data);
	void ResponseRetrieveMailItem(char * data);

	void StateChangeHandler(int iClientH, char * pData, uint32 dwMsgSize);
	bool CheckMagicInt(int iClientH);
	bool ChangeState(char cStateChange, char* cStr, char *cVit,char *cDex,char *cInt,char *cMag,char *cChar);

	void RequestSetRecallPoint(int iClientH, char * pData, uint32 dwMsgSize);

	struct 
	{
		CItem * item;
		time_t dropTime;
		short sx, sy;
		char cMapIndex;
		bool bEmpty;
	} m_stGroundNpcItem[MAXGROUNDITEMS];
	void TileCleaner();
	void AddGroundItem(CItem * pItem, short x, short y, char mapIndex, uint32 dwTime);

	// Legion point functions
	void HandleLegionService(char * data);
	bool ChangeNation(int clientH, Side side);
	void LegionCash(char * account, uint16 cmd, bool Type);
	bool GetLegionItemCount(int clientH, char * cItemName, long count);
	bool GetLegionItem(int clientH, uint16 cmd);
	bool GetLegionPoints(int clientH, uint16 cmd);
	bool GetSpellBack(int clientH, uint16 cmd);
	
	CClient * FindPlayer(CharID charid);
	uint32 FindNPC(const string npcName);
	uint32 FindItem(const string itemName);

	void EventStart(EventType eType);
	void EventEnd();
	void NotifyEventStats(const Casualties * stats) const;
	void NotifyRelicInAltar(const Side altarSide) const;
	void NotifyRelicGrabbed(const CClient * picker) const;
	void ShuffleAstoriaBasePos();
	void CreateAstoriaFlags();
	void UpdateRelicPos(int iClientH = NULL);

	void UpdateWebsiteStats();
	void OnWebSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	//=======================================================================================
	bool IsDatePast(char *Date);
	//=======================================================================================
	char CheckHeroItemEquipped(int iClientH);

	CGame(HWND hWnd);
	~CGame();

	char m_cServerName[12];
	char m_cGameServerAddr[16];
	char m_cLogServerAddr[16];
	int  m_iGameServerPort;
	int  m_iLogServerPort;
	int  m_iGateServerPort;
	int  m_iWorldLogServerPort;
	char m_cGameServerAddrExternal[16];
	int  m_iGameServerMode;
	int  m_iLimitedUserExp, m_iLevelExp51;

//private:
	bool _bDecodeItemConfigFileContents(char * pData, uint32 dwMsgSize);
	int _iComposePlayerDataFileContents(int iClientH, char * pData);
	bool _bDecodePlayerDatafileContents(int iClientH, char * pData, uint32 dwSize);
	bool _bRegisterMap(char * pName);
	
	HashMap<string, uint8> m_mapNameList;

	CClient * m_pClientList[MAXCLIENTS];
	CNpc    * m_pNpcList[MAXNPCS];
	CMap    * m_pMapList[MAXMAPS];
	CDynamicObject * m_pDynamicObjectList[MAXDYNAMICOBJECTS];
	CDelayEvent    * m_pDelayEventList[MAXDELAYEVENTS];

	CMsg    * m_pMsgQuene[MSGQUENESIZE];
	int             m_iQueneHead, m_iQueneTail;
	int             m_iTotalMaps;
	bool			m_dropsInitiated;
	bool			m_bIsGameStarted;
	bool			ReceivedAllConfig;
	bool			m_bIsGameServerRegistered;
	bool			m_bIsSocketConnected[MAXSUBLOGSOCK];
	bool			m_bIsItemAvailable, m_bIsBuildItemAvailable, m_bIsNpcAvailable, m_bIsMagicAvailable;
	bool			m_bIsSkillAvailable, m_bIsPortionAvailable, m_bIsQuestAvailable;
	CItem   * m_pItemConfigList[MAXITEMTYPES];
	CNpc    * m_npcConfigList[MAXNPCTYPES];
	CMagic  * m_pMagicConfigList[MAXMAGICTYPE];
	CSkill  * m_pSkillConfigList[MAXSKILLTYPE];
	CQuest  * m_pQuestConfigList[MAXQUESTTYPE];
	char            m_pMsgBuffer[MSGBUFFERSIZE+1];
	CCrafting * m_pCraftingConfigList[MAXCRAFTING];

	CTeleport * m_pTeleportConfigList[MAXTELEPORTLIST];

	HWND  m_hWnd;
	int   m_iTotalClients, m_iMaxClients, m_iTotalGameServerClients, m_iTotalGameServerMaxClients;

	bool  m_bF1pressed, m_bF4pressed, m_bF12pressed;
	bool  m_bOnExitProcess;
	uint32 m_dwExitProcessTime;

	uint32 m_dwWeatherTime, m_dwGameTime1, m_dwGameTime2, m_dwGameTime3, m_dwGameTime4, m_dwGameTime5, m_dwGameTime6, m_dwFishTime;

	char  m_cDayOrNight;
 	int   m_iSkillSSNpoint[102];

	CMsg * m_pNoticeMsgList[MAXNOTIFYMSGS];
	int   m_iTotalNoticeMsg, m_iPrevSendNoticeMsg;
	uint32 m_dwNoticeTime, m_dwSpecialEventTime, m_startTime;
	bool  m_bIsSpecialEventTime;
	char  m_cSpecialEventType;
	uint32 m_onlineCntAdd;

	int   m_iLevelExpTable[300];
 	CFish * m_pFish[MAXFISHS];
	CPortion * m_pPortionConfigList[MAXPORTIONTYPES];

	bool  m_bIsServerShutdowned;
	char  m_cShutDownCode;
	CMineral * m_pMineral[MAXMINERALS];

	int m_iMiddlelandMapIndex;
	int m_iAresdenMapIndex;
	int m_iElvineMapIndex;
	int m_iIstriaMapIndex;
	int m_iAstoriaMapIndex;
	Astoria m_astoria;
	Side m_astoriaBasePos[3];
	Side m_eventWinner[ET_MAX];
	CIni * m_eventsIni;

	bool	m_bIsApocalypseMode;	
	bool	m_bIsApocalypseGateOpen;
	
	bool	m_bHeldenianMode;
	uint32	m_dwHeldenianGUID;
	int	m_iHeldenianType1Winner, m_iHeldenianType2Winner;
	int	m_iHeldenianType;
	int	m_iLastHeldenianType;
	int m_iHeldenianAresdenDead, m_iHeldenianElvineDead, m_iHeldenianAresdenKill, m_iHeldenianElvineKill, m_iHeldenianAresdenFlags, m_iHeldenianElvineFlags, 
		m_iHeldenianAresdenLeftTower, m_iHeldenianElvineLeftTower;
	int	m_iBtFieldMapIndex;
	int	m_iRampartMapIndex;
	int	m_iGodHMapIndex;

	int	 m_iMaxGMGMana;
	int m_iAresdenOccupyTiles;
	int m_iElvineOccupyTiles;
	int m_iCurMsgs, m_iMaxMsgs;

	uint32 m_dwCanFightzoneReserveTime ;
	
	int  m_iFightZoneReserve[MAXFIGHTZONE] ;
	CharID m_donateEventHolder;
	uint32 m_donateEventPot;
	
	struct ConfirmedLogin 
	{
		char ip[20];
		char accName[15];
		char playerName[12];
		char accPass[12];
		uint32 timeReceived;
	};
	List<ConfirmedLogin> confirmedLogins;

	struct RecentDisconnect
	{
		RecentDisconnect(char * pN, uint32 dT)
			{strcpy(playerName,pN); disconnectTimes[0] = dT; dcCount = 1; disconnectTimes[1] = disconnectTimes[2] = 0;}
		char playerName[12];
		uint32 disconnectTimes[3];
		int dcCount;
	};
	List<RecentDisconnect> m_recentDCs;

	struct {
		uint64 iFunds;
		uint64 iCrimes;
		uint64 iWins;
	} m_stCityStatus[MAXSIDES];

	int	  m_iStrategicStatus;

	XSocket * m_pSubLogSock[MAXSUBLOGSOCK];
	int   m_iSubLogSockInitIndex;
	bool  m_bIsSubLogSockAvailable[MAXSUBLOGSOCK];
	int	  m_iCurSubLogSockIndex;
	int   m_iSubLogSockFailCount;
	int   m_iSubLogSockActiveCount;
	int   m_iAutoRebootingCount;

	CBuildItem * m_pBuildItemList[MAXBUILDITEMS];
	CItem * m_pDupItemIDList[MAXDUPITEMID];

	char * m_pNoticementData;
	uint32  m_dwNoticementDataSize;

	uint32  m_dwMapSectorInfoTime;
	int    m_iMapSectorInfoUpdateCount;



	bool   m_bIsCrusadeMode;
	struct {
		char cMapName[11];
		char cType;
		int  dX, dY;
	} m_stCrusadeStructures[MAXCRUSADESTRUCTURES];


	// 2 variables? hmm
	int m_iCollectedMana[MAXSIDES];
	int m_mana[MAXSIDES];
	// int m_iAresdenMana, m_iElvineMana;

	CTeleportLoc m_pGuildTeleportLoc[MAXGUILDS];
	//

	sBYTE  GSID;
	char  m_cGateServerStockMsg[MAXGATESERVERSTOCKMSGSIZE];
	int   m_iIndexGSS;

	struct {
		int iCrashedStructureNum;
		int iStructureDamageAmount;
		int iCasualties;
	} m_stMeteorStrikeResult;

	struct {
		char cType;
		char cSide;
		short sX, sY;
	} m_stMiddleCrusadeStructureInfo[MAXCRUSADESTRUCTURES];
	int m_iTotalMiddleCrusadeStructures;
 
		int m_iClientShortCut[MAXCLIENTS+1];

	int m_iNpcConstructionPoint[MAXNPCTYPES];
	uint32 m_dwCrusadeGUID;
	int   m_iCrusadeWinnerSide;   

	int   m_iPlayerMaxLevel;

	int   m_iWorldMaxUser;

	short m_sForceRecallTime;
	short m_sSlateSuccessRate;

	void ReqCreateSlateHandler(int iClientH, char* pData);
	void SetSlateFlag(int iClientH, short sType, bool bFlag);

	int   m_iFinalShutdownCount;

	uint32  m_schedulesCnt;

	enum EventStatus{
		ES_ANNOUNCED_ONCE,
		ES_ANNOUNCED_TWICE,
		ES_ANNOUNCED_THRICE,
		ES_STARTED,
		ES_ENDED
	};
	struct {
		int iDay;
		int iHour;
		int iMinute;
		EventStatus evStatus;
		EventType evType;
		bool operator==(SYSTEMTIME sysTime)
		{
			return (iDay == sysTime.wDayOfWeek &&
				iHour == sysTime.wHour &&
				iMinute == sysTime.wMinute)
				? true : false;
		}
	} m_schedules[MAXSCHEDULE];

	CItem * m_pGold;

	XSocket * m_webSocket;
	char m_websiteAddr[61];
	char m_websiteScriptAddr[61];
	int m_websitePort;

	bool	m_bReceivedItemList;

	bool m_SoccerMode;
	int m_SoccerAresdenGoals, m_SoccerElvineGoals, m_SoccerWinner;

	void _ClearExchangeStatus(int iClientH);	// previously private, who knows why
	void ShowClientMsg(int iClientH, char* pMsg);
	void SetAngel(short sOwnerH, char cOwnerType, int iStatus, bool notify = true);
	void GetAngelHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void GetDKItemHandler(int iClientH, char * pData, uint32 dwMsgSize);
	void AdminOrder_GoTo(int iClientH, char* pData, uint32 dwMsgSize);
	void AdminOrder_Pushplayer(int iClientH, char * pData, uint32 dwMsgSize);

private:
	int _iTalkToNpcResult_Cityhall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iGetItemSpaceLeft(int iClientH);

};

#endif // !defined(AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
