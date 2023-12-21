#ifndef LGNSVCS_H
#define LGNSVCS_H
#include "NetMessages.h"

enum lgnSvcsCmds{
	CMD_LGNSVC_MAGEHAT,
	CMD_LGNSVC_BMAGEHAT,
	CMD_LGNSVC_WARRIORHELM,
	CMD_LGNSVC_BMAGEHELM,
	CMD_LGNSVC_TOARE,
	CMD_LGNSVC_TOELV,
	CMD_LGNSVC_MAJ2,
	CMD_LGNSVC_MAJ20,
	CMD_LGNSVC_GOLD10,
	CMD_LGNSVC_GOLD100,
	CMD_LGNSVC_REP10,
	CMD_LGNSVC_REP100,
	CMD_LGNSVC_XPSLATE,
	CMD_LGNSVC_ZERKSLATE,
	CMD_LGNSVC_MPSLATE,
	CMD_LGNSVC_HPSLATE,
	CMD_LGNSVC_ZEM,
	CMD_LGNSVC_SOM,
	CMD_LGNSVC_SOX,
	// tokens start
	CMD_LGNSVC_TOKEN1,
	CMD_LGNSVC_TOKEN10,
	CMD_LGNSVC_TOKEN100,
	CMD_LGNSVC_TRADETOKEN1,
	CMD_LGNSVC_TRADETOKEN10,
	CMD_LGNSVC_TRADETOKEN100,
	// tokens end
	// spells start
	CMD_LGNSVC_TRADECANCEL,
	CMD_LGNSVC_TRADEIMC,
	CMD_LGNSVC_TRADEICESTORM,
	CMD_LGNSVC_TRADEMFS,
	CMD_LGNSVC_TRADEBS,
	CMD_LGNSVC_TRADEESW,
	// spells end
	CMD_LGNSVC_MAX
};

const struct lgnPtsSvc{
	char * desc;
	char * name;
	unsigned long price;
	unsigned short cmd;
} lgnPtsSvcs[] = {
	{"MP14 Indestr. Golden Wizard Hat", "LegionHat MP14", 25, CMD_LGNSVC_MAGEHAT},
	{"HP14 Indestr. Golden Wizard Hat", "LegionHat HP14", 25, CMD_LGNSVC_BMAGEHAT},
	{"HP14 Indestr. Golden Winged Helm", "LegionHelm HP14", 25, CMD_LGNSVC_WARRIORHELM},
	{"MP14 Indestr. Golden Winged Helm", "LegionHelm MP14", 25, CMD_LGNSVC_BMAGEHELM},
	{"Town Change (to Aresden)", "TC(Are)", 10, CMD_LGNSVC_TOARE},
	{"Town Change (to Elvine)", "TC(Elv)", 10, CMD_LGNSVC_TOELV},
	{"2 Majestic points", "2 Maj", 1, CMD_LGNSVC_MAJ2},
	{"20 Majestic points", "20 Maj", 10, CMD_LGNSVC_MAJ20},
	{"10,000 Gold", "10k Gold", 1, CMD_LGNSVC_GOLD10},
	{"100,000 Gold", "100k Gold", 10, CMD_LGNSVC_GOLD100},
	{"10 Reputations points", "10 Rep", 1, CMD_LGNSVC_REP10},
	{"100 Reputations points", "100 Rep", 10, CMD_LGNSVC_REP100},
	{"Experience Slate", "XP Slate", 2, CMD_LGNSVC_XPSLATE},
	{"Berserk Slate", "Zerk Slate", 2, CMD_LGNSVC_ZERKSLATE},
	{"Mana Slate", "MP Slate", 4, CMD_LGNSVC_MPSLATE},
	{"Health Slate", "HP Slate", 6, CMD_LGNSVC_HPSLATE},
	{"Zemstone of Sacrifice", "Zem", 2, CMD_LGNSVC_ZEM},
	{"Stone of Merien", "SoM", 2, CMD_LGNSVC_SOM},
	{"Stone of Xelima", "SoX", 2, CMD_LGNSVC_SOX},
	{"Take 1 Legion Token", "1 Legion Token", 1, CMD_LGNSVC_TOKEN1},
	{"Take 10 Legion Token", "10 Legion Token", 10, CMD_LGNSVC_TOKEN10},
	{"Take 100 Legion Token", "100 Legion Token", 100, CMD_LGNSVC_TOKEN100},
	{"Trade Back 1 Legion Token", "Trade 1 Legion Token Back", 1, CMD_LGNSVC_TRADETOKEN1},
	{"Trade Back 10 Legion Token", "Trade 10 Legion Token Back", 10, CMD_LGNSVC_TRADETOKEN10},
	{"Trade Back 100 Legion Token", "Trade 100 Legion Token Back", 100, CMD_LGNSVC_TRADETOKEN100},
	{"Unlearn Cancel. and convert to manual", "Unlearn Cancel", 10, CMD_LGNSVC_TRADECANCEL},
	{"Unlearn I.M.C and convert to manual", "Unlearn I.M.C", 10, CMD_LGNSVC_TRADEIMC},
	{"Unlearn I.S and convert to manual", "Unlearn IceStorm", 10, CMD_LGNSVC_TRADEICESTORM},
	{"Unlearn M.F.S and convert to manual", "Unlearn MassFireStrike", 10, CMD_LGNSVC_TRADEMFS},
	{"Unlearn B.S.W and convert to manual", "Unlearn BloodyShockW", 10, CMD_LGNSVC_TRADEBS},
	{"Unlearn E.S.W and convert to manual", "Unlearn E.S.W", 10, CMD_LGNSVC_TRADEESW},
	{"","",0,0}
};

#endif // LGNSVCS_H
