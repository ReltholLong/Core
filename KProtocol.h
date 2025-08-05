#ifndef KPROTOCOL_H
#define KPROTOCOL_H

#ifndef __linux
#ifdef _STANDALONE
#include "GameDataDef.h"
#else
#include "../Sources/Core/src/GameDataDef.h"
#endif
#else
#include "GameDataDef.h"
#include <string.h>
#endif

#include "KProtocolDef.h"
#include "KRelayProtocol.h"

#pragma pack(push, enter_protocol)
#pragma	pack(1)

#define	PROTOCOL_MSG_TYPE	BYTE
#define PROTOCOL_MSG_SIZE	(sizeof(PROTOCOL_MSG_TYPE))
#define	MAX_PROTOCOL_NUM	200

typedef struct
{
	BYTE	ProtocolType;
	BYTE	WalkSpeed;
	BYTE	RunSpeed;
	BYTE	AttackSpeed;
	BYTE	CastSpeed;
	BYTE	HelmType;
	BYTE	ArmorType;
	BYTE	WeaponType;
	BYTE	HorseType;
	BYTE	RankID;
	DWORD	ID;
	BYTE	m_btSomeFlag;	// 0x01 PKFlag 0x02 FightModeFlag 0x04 SleepModeFlag
//	BYTE	m_btPKFlag;
//	BYTE	m_btFightMode;
//	BYTE	m_SleepMode;
//	char	Name[32];	
} PLAYER_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	BYTE	WalkSpeed;			// ÊÇ·ñÖ»Òª´«Ò»·Ý¾Í¹»ÁË£¨Ö»¸Ä±äÒ»¸ö»òÊÇÍ¬Ê±¸Ä±ä£©
	BYTE	RunSpeed;
	BYTE	AttackSpeed;
	BYTE	CastSpeed;			// ÊÇ·ñ¿¼ÂÇ²»¸Ä±äÊ©·¨ËÙ¶È£¬»òÊ©·¨ËÙ¶ÈµÈÓÚ¹¥»÷ËÙ¶È
	BYTE	HelmType;
	BYTE	ArmorType;
	BYTE	WeaponType;
	BYTE	HorseType;
	BYTE	RankID;
	BYTE	m_btSomeFlag;	// 0x01 PKFlag 0x02 FightModeFlag 0x04 SleepModeFlag 0x08 TongOpenFlag
//	BYTE	FightMode;
//	BYTE	m_btPKFlag;
//	BYTE	m_btSleepMode;
} PLAYER_NORMAL_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	Camp;				// ÕóÓª
	BYTE	CurrentCamp;		// µ±Ç°ÕóÓª
	BYTE	m_bySeries;			// ÎåÐÐÏµ
	BYTE	LifePerCent;		// ÉúÃü°Ù·Ö±È
	BYTE	m_btMenuState;		// ×é¶Ó¡¢½»Ò×µÈ×´Ì¬
	BYTE	m_Doing;			// ÐÐÎª
	BYTE	m_btKind;			// npcÀàÐÍ
	DWORD	MapX;				// Î»ÖÃÐÅÏ¢
	DWORD	MapY;				// Î»ÖÃÐÅÏ¢
	DWORD	ID;					// NpcµÄÎ¨Ò»ID
	int		NpcSettingIdx;		// ¿Í»§¶ËÓÃÓÚ¼ÓÔØÍæ¼Ò×ÊÔ´¼°»ù´¡ÊýÖµÉè¶¨
	WORD	NpcEnchant;			// ¼ÓÇ¿µÄNPC£¨ºóÃæµÄbit±íÊ¾¼ÓÇ¿ÀàÐÍ£¬Ãû×ÖÊÇ·ñ½ðÉ«Ö®ÀàµÄÓÉ¼ÓÇ¿µÄÊýÄ¿ÔÚ¿Í»§¶ËÈ·¶¨£©
	char	m_szName[32];		// Ãû×Ö
} NPC_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	DWORD	MapX;
	DWORD	MapY;
	BYTE	Camp;
	BYTE	LifePerCent;
	BYTE	Doing;
	BYTE	State;
} NPC_NORMAL_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	//int		m_nRegionID;
	DWORD	m_dwNpcID;
	DWORD	m_dwMapX;
	DWORD	m_dwMapY;
	WORD	m_wOffX;
	WORD	m_wOffY;
	BYTE	m_byDoing;
	BYTE	m_btCamp;
	BYTE	m_btLifePerCent;	
} NPC_PLAYER_TYPE_NORMAL_SYNC;
                 
typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
} NPC_REMOVE_SYNC, NPC_SIT_SYNC, NPC_DEATH_SYNC, NPC_REQUEST_COMMAND, NPC_REQUEST_FAIL;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	int		nMpsX;
	int		nMpsY;
} NPC_WALK_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	BYTE	Type;
} NPC_REVIVE_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	int		nMpsX;
	int		nMpsY;
} NPC_JUMP_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	int		nMpsX;
	int		nMpsY;
} NPC_RUN_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	int		nFrames;
	int		nX;
	int		nY;
} NPC_HURT_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	BYTE	Camp;
} NPC_CHGCURCAMP_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	BYTE	Camp;
} NPC_CHGCAMP_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	ID;
	int		nSkillID;
	int		nSkillLevel;
	int		nMpsX;
	int		nMpsY;
} NPC_SKILL_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	int		nSkillID;
	int		nMpsX;
	int		nMpsY;
} NPC_SKILL_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	int		nMpsX;
	int		nMpsY;
} NPC_WALK_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
//	BYTE	ReviveType;
} NPC_REVIVE_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	int		nMpsX;
	int		nMpsY;
} NPC_RUN_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	int		nShopIndex;
} SALE_BOX_SYNC;

typedef struct 
{
	BYTE	ProtocolType;
	int		nNpcId;
} PLAYER_DIALOG_NPC_COMMAND; //Ö÷½ÇÓënNpcId¶Ô»°µÄÇëÇó

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	int		m_nExp;				// µ±Ç°¾­Ñé
} PLAYER_EXP_SYNC;				// Íæ¼ÒÍ¬²½¾­Ñé

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
} PLAYER_APPLY_CREATE_TEAM;		// ¿Í»§¶ËÍæ¼Ò´´½¨¶ÓÎé£¬Ïò·þÎñÆ÷·¢ÇëÇó

struct PLAYER_SEND_CREATE_TEAM_SUCCESS
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	nTeamServerID;		// ¶ÓÎéÔÚ·þÎñÆ÷ÉÏµÄÎ¨Ò»±êÊ¶
	PLAYER_SEND_CREATE_TEAM_SUCCESS() {nTeamServerID = -1;}
};	// ·þÎñÆ÷Í¨ÖªÍæ¼Ò¶ÓÎé´´½¨³É¹¦

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btErrorID;		// ¶ÓÎé´´½¨²»³É¹¦Ô­Òò£º0 Í¬Ãû 1 Íæ¼Ò±¾ÉíÒÑ¾­ÊôÓÚÄ³Ò»Ö§¶ÓÎé 3 µ±Ç°´¦ÓÚ²»ÄÜ×é¶Ó×´Ì¬
} PLAYER_SEND_CREATE_TEAM_FALSE;// ·þÎñÆ÷Í¨Öª¿Í»§¶Ë¶ÓÎé´´½¨²»³É¹¦

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwTarNpcID;		// ²éÑ¯Ä¿±ê npc id
} PLAYER_APPLY_TEAM_INFO;		// ¿Í»§¶ËÏò·þÎñÆ÷ÉêÇë²éÑ¯Ä³¸önpcµÄ×é¶ÓÇé¿ö

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
} PLAYER_APPLY_TEAM_INFO_FALSE;	// ·þÎñÆ÷¸æÖª¿Í»§¶ËÉêÇë²éÑ¯Ä³¸önpcµÄ×é¶ÓÇé¿öÊ§°Ü

typedef struct PLAYER_SEND_TEAM_INFO_DATA
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	int		m_nCaptain;			// ¶Ó³¤ npc id
	int		m_nMember[MAX_TEAM_MEMBER];	// ËùÓÐ¶ÓÔ± npc id
	DWORD	nTeamServerID;		// ¶ÓÎéÔÚ·þÎñÆ÷ÉÏµÄÎ¨Ò»±êÊ¶
	PLAYER_SEND_TEAM_INFO_DATA() {nTeamServerID = -1;};
} PLAYER_SEND_TEAM_INFO;		// ·þÎñÆ÷Ïò¿Í»§¶Ë·¢ËÍÄ³¸ö¶ÓÎéµÄÐÅÏ¢Êý¾Ý

typedef struct PLAYER_SEND_SELF_TEAM_INFO_DATA
{
	BYTE	ProtocolType;							// Ð­ÒéÃû³Æ
	BYTE	m_btState;								// ¶ÓÎé×´Ì¬
	DWORD	m_dwNpcID[MAX_TEAM_MEMBER + 1];			// Ã¿Ãû³ÉÔ±µÄnpc id £¨¶Ó³¤·ÅÔÚµÚÒ»Î»£©
	char	m_szNpcName[MAX_TEAM_MEMBER + 1][32];	// Ã¿Ãû³ÉÔ±µÄÃû×Ö£¨¶Ó³¤·ÅÔÚµÚÒ»Î»£©
	DWORD	nTeamServerID;							// ¶ÓÎéÔÚ·þÎñÆ÷ÉÏµÄÎ¨Ò»±êÊ¶
	DWORD	m_dwLeadExp;							// Íæ¼ÒµÄÍ³ÂÊÁ¦¾­Ñé
	BYTE	m_btLevel[MAX_TEAM_MEMBER + 1];			// Ã¿Ãû³ÉÔ±µÄµÈ¼¶£¨¶Ó³¤·ÅÔÚµÚÒ»Î»£©
	PLAYER_SEND_SELF_TEAM_INFO_DATA() {memset(m_szNpcName, 0, 32 * (MAX_TEAM_MEMBER + 1)); nTeamServerID = -1;};
} PLAYER_SEND_SELF_TEAM_INFO;						// ·þÎñÆ÷Ïò¿Í»§¶Ë·¢ËÍ¿Í»§¶Ë×ÔÉí¶ÓÎéµÄÐÅÏ¢Êý¾Ý

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btOpenClose;		// ´ò¿ª»ò¹Ø±Õ
} PLAYER_TEAM_OPEN_CLOSE;		// ¶ÓÎé¶Ó³¤Ïò·þÎñÆ÷ÉêÇë¿ª·Å¡¢¹Ø±Õ¶ÓÎéÊÇ·ñÔÊÐí½ÓÊÕ³ÉÔ±×´Ì¬

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwTarNpcID;		// Ä¿±ê¶ÓÎé¶Ó³¤npc id »òÕß ÉêÇëÈË npc id
} PLAYER_APPLY_ADD_TEAM;		// Íæ¼ÒÏò·þÎñÆ÷ÉêÇë¼ÓÈëÄ³¸ö¶ÓÎé»òÕß·þÎñÆ÷ÏòÄ³¸ö¶Ó³¤×ª·¢Ä³¸öÍæ¼ÒµÄ¼ÓÈëÉêÇë

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwNpcID;			// ±»½ÓÊÜÈë¶ÓÎéµÄnpc id
} PLAYER_ACCEPT_TEAM_MEMBER;	// Íæ¼ÒÍ¨Öª·þÎñÆ÷½ÓÊÜÄ³¸öÍæ¼ÒÈë¶ÓÎé

typedef struct PLAYER_TEAM_ADD_MEMBER_DATA
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btLevel;			// ¼ÓÈëÕßµÈ¼¶
	DWORD	m_dwNpcID;			// ¼ÓÈëÕßnpc id
	char	m_szName[32];		// ¼ÓÈëÕßÐÕÃû
	PLAYER_TEAM_ADD_MEMBER_DATA() {memset(m_szName, 0, 32);};
} PLAYER_TEAM_ADD_MEMBER;		// ·þÎñÆ÷Í¨Öª¶ÓÎéÖÐµÄ¸÷¸öÍæ¼ÒÓÐÐÂ³ÉÔ±¼ÓÈë

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
} PLAYER_APPLY_LEAVE_TEAM;		// ¿Í»§¶ËÍæ¼ÒÉêÇëÀë¶Ó

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwNpcID;			// Àë¶Ónpc id
} PLAYER_LEAVE_TEAM;			// ·þÎñÆ÷Í¨Öª¸÷¶ÓÔ±Ä³ÈËÀë¶Ó

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwNpcID;			// Àë¶Ónpc id
} PLAYER_TEAM_KICK_MEMBER;		// ¶Ó³¤Ìß³ýÄ³¸ö¶ÓÔ±

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwNpcID;			// Ä¿±ênpc id
} PLAYER_APPLY_TEAM_CHANGE_CAPTAIN;// ¶Ó³¤Ïò·þÎñÆ÷ÉêÇë°Ñ×Ô¼ºµÄ¶Ó³¤Éí·Ý½»¸ø±ðµÄ¶ÓÔ±

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwCaptainID;		// ÐÂ¶Ó³¤npc id
	DWORD	m_dwMemberID;		// ÐÂ¶ÓÔ±npc id
} PLAYER_TEAM_CHANGE_CAPTAIN;	// ·þÎñÆ÷Í¨Öª¸÷¶ÓÔ±¸ü»»¶Ó³¤

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
} PLAYER_APPLY_TEAM_DISMISS;	// Ïò·þÎñÆ÷ÉêÇë½âÉ¢¶ÓÎé

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btPKFlag;			// pk ¿ª¹Ø
} PLAYER_SET_PK;				// Ïò·þÎñÆ÷ÉêÇë´ò¿ª¡¢¹Ø±ÕPK

typedef struct
{
	BYTE	ProtocolType;			// Ð­ÒéÃû³Æ
	BYTE	m_btCamp;				// ÐÂÕóÓª
	BYTE	m_btCurFaction;			// µ±Ç°ÃÅÅÉ
	BYTE	m_btFirstFaction;		// Ê×´Î¼ÓÈëÃÅÅÉ
	int		m_nAddTimes;			// ¼ÓÈëÃÅÅÉ´ÎÊý
} PLAYER_FACTION_DATA;				// ·þÎñÆ÷·¢¸ø¿Í»§¶ËÃÅÅÉÐÅÏ¢

typedef struct
{
	BYTE	ProtocolType;			// Ð­ÒéÃû³Æ
} PLAYER_LEAVE_FACTION;				// ·þÎñÆ÷Í¨ÖªÍæ¼ÒÀë¿ªÃÅÅÉ

typedef struct
{
	BYTE	ProtocolType;			// Ð­ÒéÃû³Æ
	BYTE	m_btCurFactionID;		// µ±Ç°ÃÅÅÉid
	BYTE	m_btLevel;				// ¼¼ÄÜ¿ª·ÅµÈ¼¶
} PLAYER_FACTION_SKILL_LEVEL;		// ·þÎñÆ÷Í¨ÖªÍæ¼Ò¿ª·Åµ±Ç°ÃÅÅÉ¼¼ÄÜµ½Ä³¸öµÈ¼¶

typedef struct
{
	BYTE	ProtocolType;			// Ð­ÒéÃû³Æ
} PLAYER_APPLY_FACTION_DATA;		// ¿Í»§¶ËÉêÇë¸üÐÂÃÅÅÉÊý¾Ý

typedef struct PLAYER_SEND_CHAT_DATA_COMMAND
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	WORD	m_wLength;
	BYTE	m_btCurChannel;		// µ±Ç°ÁÄÌìÆµµÀ
	BYTE	m_btType;			// MSG_G_CHAT »ò MSG_G_CMD »ò¡­¡­
	BYTE	m_btChatPrefixLen;	// ¸ñÊ½¿ØÖÆ×Ö·û³¤¶È
	WORD	m_wSentenceLen;		// ÁÄÌìÓï¾ä³¤¶È
	DWORD	m_dwTargetID;		// ÁÄÌì¶ÔÏó id
	int		m_nTargetIdx;		// ÁÄÌì¶ÔÏóÔÚ·þÎñÆ÷¶ËµÄ idx
	char	m_szSentence[MAX_SENTENCE_LENGTH + CHAT_MSG_PREFIX_MAX_LEN];	// ÁÄÌìÓï¾äÄÚÈÝ
	PLAYER_SEND_CHAT_DATA_COMMAND() {memset(m_szSentence, 0, sizeof(m_szSentence));};
} PLAYER_SEND_CHAT_COMMAND;		// ¿Í»§¶ËÁÄÌìÄÚÈÝ·¢ËÍ¸ø·þÎñÆ÷

typedef struct PLAYER_SEND_CHAT_DATA_SYNC
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	WORD	m_wLength;
	BYTE	m_btCurChannel;		// µ±Ç°ÁÄÌì×´Ì¬
	BYTE	m_btNameLen;		// Ãû×Ö³¤¶È
	BYTE	m_btChatPrefixLen;	// ¿ØÖÆ×Ö·û³¤¶È
	WORD	m_wSentenceLen;		// ÁÄÌìÓï¾ä³¤¶È
	DWORD	m_dwSourceID;		// 
	char	m_szSentence[32 + CHAT_MSG_PREFIX_MAX_LEN + MAX_SENTENCE_LENGTH];	// ÁÄÌìÓï¾äÄÚÈÝ
	PLAYER_SEND_CHAT_DATA_SYNC() { memset(m_szSentence, 0, sizeof(m_szSentence)); };
} PLAYER_SEND_CHAT_SYNC;		// ¿Í»§¶ËÁÄÌìÄÚÈÝ·¢ËÍ¸ø·þÎñÆ÷

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btState;
	int		m_nID;
	int		m_nDataID;
	int		m_nXpos;
	int		m_nYpos;
	int		m_nMoneyNum;
	int		m_nItemID;
	BYTE	m_btDir;
	BYTE	m_btItemWidth;
	WORD	m_wCurFrame;
	BYTE	m_btItemHeight;
	BYTE	m_btColorID;
	BYTE	m_btFlag;
	char	m_szName[32];
} OBJ_ADD_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	BYTE	m_btState;
	int		m_nID;
} OBJ_SYNC_STATE;

typedef struct
{
	BYTE	ProtocolType;
	BYTE	m_btDir;
	int		m_nID;
} OBJ_SYNC_DIR;

typedef struct
{
	BYTE	ProtocolType;
	int		m_nID;
	BYTE	m_btSoundFlag;
} OBJ_SYNC_REMOVE;

typedef struct
{
	BYTE	ProtocolType;
	int		m_nID;
	int		m_nTarX;
	int		m_nTarY;
} OBJ_SYNC_TRAP_ACT;

typedef struct
{
	BYTE	ProtocolType;
	int		m_nID;
} OBJ_CLIENT_SYNC_ADD;

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	DWORD	m_dwLeadExp;		// Í³ÂÊÁ¦¾­ÑéÖµ
} PLAYER_LEAD_EXP_SYNC;			// Í¬²½Í³ÂÊÁ¦¾­ÑéÖµ

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btLevel;			// µ±Ç°µÈ¼¶
	int		m_nExp;				// µ±Ç°¾­Ñé
	int		m_nAttributePoint;	// Ê£ÓàÊôÐÔµã
	int		m_nSkillPoint;		// Ê£Óà¼¼ÄÜµã
	int		m_nBaseLifeMax;		// µ±Ç°×î´óÉúÃüÖµ
	int		m_nBaseStaminaMax;	// µ±Ç°×î´óÌåÁ¦Öµ
	int		m_nBaseManaMax;		// µ±Ç°×î´óÄÚÁ¦Öµ
} PLAYER_LEVEL_UP_SYNC;			// Íæ¼ÒÉý¼¶

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btLevel;			// µ±Ç°µÈ¼¶
	DWORD	m_dwTeammateID;		// ¶ÓÓÑ npc id
} PLAYER_TEAMMATE_LEVEL_SYNC;	// Íæ¼ÒÉý¼¶µÄÊ±ºòÍ¨Öª¶ÓÓÑ

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btAttribute;		// ÊôÐÔ(0=Strength 1=Dexterity 2=Vitality 3=Engergy)
	int		m_nAddNo;			// ¼ÓµÄµãÊý
} PLAYER_ADD_BASE_ATTRIBUTE_COMMAND;	// Íæ¼ÒÌí¼Ó»ù±¾ÊôÐÔµã

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	int		m_nSkillID;			// ¼¼ÄÜid
	int		m_nAddPoint;		// Òª¼ÓµÄµãÊý
} PLAYER_ADD_SKILL_POINT_COMMAND;// Íæ¼ÒÉêÇëÔö¼ÓÄ³¸ö¼¼ÄÜµÄµãÊý

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btAttribute;		// ÊôÐÔ(0=Strength 1=Dexterity 2=Vitality 3=Engergy)
	int		m_nBasePoint;		// »ù±¾µãÊý
	int		m_nCurPoint;		// µ±Ç°µãÊý
	int		m_nLeavePoint;		// Ê£ÓàÎ´·ÖÅäÊôÐÔµã
} PLAYER_ATTRIBUTE_SYNC;		// Íæ¼ÒÍ¬²½ÊôÐÔµã

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	int		m_nSkillID;			// ¼¼ÄÜid
	int		m_nSkillLevel;		// ¼¼ÄÜµÈ¼¶
	int		m_nLeavePoint;		// Ê£ÓàÎ´·ÖÅä¼¼ÄÜµã
} PLAYER_SKILL_LEVEL_SYNC;		// Íæ¼ÒÍ¬²½¼¼ÄÜµã

//typedef struct
//{
//	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
//	int		m_nItemID;			// ÎïÆ·id
//	int		m_nSourcePos;		// À´Ô´Î»ÖÃ
//	int		m_nTargetPos;		// Ä¿µÄÎ»ÖÃ
//} PLAYER_EQUIP_ITEM_COMMAND;	// Íæ¼ÒÊó±êÓÒ¼üµã»÷Ê¹ÓÃÎïÆ·(×°±¸)

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	BYTE	m_btPlace;			// Ò©Æ·Î»ÖÃ
	BYTE	m_btX;				// Ò©Æ·Î»ÖÃ
	BYTE	m_btY;				// Ò©Æ·Î»ÖÃ
	int		m_nItemID;			// ÎïÆ·id
} PLAYER_EAT_ITEM_COMMAND;		// Íæ¼ÒÊó±êÓÒ¼üµã»÷Ê¹ÓÃÎïÆ·(³ÔÒ©)

typedef struct
{
	BYTE	ProtocolType;		// Ð­ÒéÃû³Æ
	int		m_nObjID;			// Êó±êµã»÷µÄobjµÄid
	BYTE	m_btPosType;		// Î»ÖÃÀàÐÍ
	BYTE	m_btPosX;			// ×ø±ê x
	BYTE	m_btPosY;			// ×ø±ê y
} PLAYER_PICKUP_ITEM_COMMAND;		// Íæ¼Ò»ñµÃÎïÆ·£¨Êó±êµã»÷µØÍ¼ÉÏµÄobj£©

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_ID;				// ÎïÆ·µÄID
	BYTE			m_Genre;			// ÎïÆ·µÄÀàÐÍ
	BYTE			m_Detail;			// ÎïÆ·µÄÀà±ð
	BYTE			m_Particur;			// ÎïÆ·µÄÏêÏ¸Àà±ð
	BYTE			m_Series;			// ÎïÆ·µÄÎåÐÐ
	BYTE			m_Level;			// ÎïÆ·µÄµÈ¼¶
	BYTE			m_btPlace;			// ×ø±ê
	BYTE			m_btX;				// ×ø±ê
	BYTE			m_btY;				// ×ø±ê
	BYTE			m_Luck;				// MF
	BYTE			m_MagicLevel[6];	// Éú³É²ÎÊý
	WORD			m_Version;			// ×°±¸°æ±¾
	WORD			m_Durability;		// ÄÍ¾Ã¶È
	UINT			m_RandomSeed;		// Ëæ»úÖÖ×Ó
} ITEM_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_ID;				// ÎïÆ·µÄID
} ITEM_REMOVE_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_ID;				// ÎïÆ·µÄID
} PLAYER_SELL_ITEM_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_BuyIdx;			// ÂòµÚ¼¸¸ö¶«Î÷
	BYTE			m_Place;			// ·ÅÔÚÉíÉÏÄÄ¸öµØ·½
	BYTE			m_X;				// ×ø±êX
	BYTE			m_Y;				// ×ø±êY
} PLAYER_BUY_ITEM_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nMoney1;			// ×°±¸À¸
	int				m_nMoney2;			// ÖüÎïÏä
	int				m_nMoney3;			// ½»Ò×À¸
} PLAYER_MONEY_SYNC;					// ·þÎñÆ÷Í¨Öª¿Í»§¶ËÇ®µÄÊýÁ¿

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btDownPos;
	BYTE			m_btDownX;
	BYTE			m_btDownY;
	BYTE			m_btUpPos;
	BYTE			m_btUpX;
	BYTE			m_btUpY;
} PLAYER_MOVE_ITEM_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btDownPos;
	BYTE			m_btDownX;
	BYTE			m_btDownY;
	BYTE			m_btUpPos;
	BYTE			m_btUpX;
	BYTE			m_btUpY;
} PLAYER_MOVE_ITEM_SYNC;

// s2c_ItemAutoMove
typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btSrcPos;
	BYTE			m_btSrcX;
	BYTE			m_btSrcY;
	BYTE			m_btDestPos;
	BYTE			m_btDestX;
	BYTE			m_btDestY;
} ITEM_AUTO_MOVE_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
} PLAYER_THROW_AWAY_ITEM_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	short			m_shLife;
	short			m_shStamina;
	short			m_shMana;
	short			m_shAngry;
	BYTE			m_btTeamData;
} CURPLAYER_NORMAL_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	// npc²¿·Ö
	DWORD			m_dwID;				// NpcµÄID
	BYTE			m_btLevel;			// NpcµÄµÈ¼¶
	BYTE			m_btSex;			// ÐÔ±ð
	BYTE			m_btKind;			// NpcµÄÀàÐÍ
	BYTE			m_btSeries;			// NpcµÄÎåÐÐÏµ
	WORD			m_wLifeMax;			// NpcµÄ×î´óÉúÃü
	WORD			m_wStaminaMax;		// NpcµÄ×î´óÌåÁ¦
	WORD			m_wManaMax;			// NpcµÄ×î´óÄÚÁ¦
	int				m_HeadImage;
	// player ²¿·Ö
	WORD			m_wAttributePoint;	// Î´·ÖÅäÊôÐÔµã
	WORD			m_wSkillPoint;		// Î´·ÖÅä¼¼ÄÜµã
	WORD			m_wStrength;		// Íæ¼ÒµÄ»ù±¾Á¦Á¿£¨¾ö¶¨»ù±¾ÉËº¦£©
	WORD			m_wDexterity;		// Íæ¼ÒµÄ»ù±¾Ãô½Ý£¨¾ö¶¨ÃüÖÐ¡¢ÌåÁ¦£©
	WORD			m_wVitality;		// Íæ¼ÒµÄ»ù±¾»îÁ¦£¨¾ö¶¨ÉúÃü¡¢ÌåÁ¦£©
	WORD			m_wEngergy;			// Íæ¼ÒµÄ»ù±¾¾«Á¦£¨¾ö¶¨ÄÚÁ¦£©
	WORD			m_wLucky;			// Íæ¼ÒµÄ»ù±¾ÐÒÔËÖµ
	int				m_nExp;				// µ±Ç°¾­ÑéÖµ(µ±Ç°µÈ¼¶ÔÚnpcÉíÉÏ)
	DWORD			m_dwLeadExp;		// Í³ÂÊÁ¦¾­ÑéÖµ

	// ÃÅÅÉ
	BYTE			m_btCurFaction;		// µ±Ç°ÃÅÅÉ
	BYTE			m_btFirstFaction;	// µÚÒ»´Î¼ÓÈëµÄÊÇÄÄ¸öÃÅÅÉ
	int				m_nFactionAddTimes;	// ¼ÓÈë¸÷ÖÖÃÅÅÉµÄ×Ü´ÎÊý
	
	// ÅÅÃû
	WORD			m_wWorldStat;		// ÊÀ½çÅÅÃû
	WORD			m_wSectStat;		// ÃÅÅÉÅÅÃû

	// Ç®
	int				m_nMoney1;
	int				m_nMoney2;
} CURPLAYER_SYNC;

#define MAX_SCIRPTACTION_BUFFERNUM 300

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wProtocolLong;
	BYTE	m_nOperateType;				//²Ù×÷ÀàÐÍ
	BYTE	m_bUIId, m_bOptionNum, m_bParam1, m_bParam2;// m_bParam1,Ö÷ÐÅÏ¢ÊÇÊý×Ö±êÊ¶»¹ÊÇ×Ö·û´®±êÊ¶, m_bParam2,ÊÇ·ñÊÇÓë·þÎñÆ÷½»»¥µÄÑ¡Ôñ½çÃæ
	int		m_nParam;
	int		m_nBufferLen;
	char	m_pContent[MAX_SCIRPTACTION_BUFFERNUM];				//´ø¿ØÖÆ·û
} PLAYER_SCRIPTACTION_SYNC;

typedef struct
{
	WORD	SkillId;
	BYTE	SkillLevel;
} SKILL_SEND_ALL_SYNC_DATA;

typedef struct
{
	BYTE						ProtocolType;
	WORD						m_wProtocolLong;
	SKILL_SEND_ALL_SYNC_DATA	m_sAllSkill[80];
} SKILL_SEND_ALL_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	BYTE	WeatherID;
} SYNC_WEATHER;

typedef struct defWORLD_SYNC
{
	BYTE	ProtocolType;
	int		SubWorld;
	int		Region;
	BYTE	Weather;
	DWORD	Frame;
} WORLD_SYNC;

typedef struct 
{
	BYTE	ProtocolType;
	int		nSelectIndex;
}PLAYER_SELECTUI_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwTakeChannel;	// ¶©ÔÄÆµµÀ
} CHAT_SET_CHANNEL_COMMAND;				// Éè¶¨¶©ÔÄÆµµÀ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;
	DWORD			m_dwTargetNpcID;	// Ä¿±ê npc id
	char			m_szInfo[MAX_SENTENCE_LENGTH];// ¸ø¶Ô·½µÄ»°
} CHAT_APPLY_ADD_FRIEND_COMMAND;		// ÁÄÌìÌí¼ÓºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nSrcPlayerIdx;	// À´Ô´ player idx
	char			m_szSourceName[32];	// À´Ô´Íæ¼ÒÃû×Ö
	char			m_szInfo[MAX_SENTENCE_LENGTH];// ¶Ô·½¸øµÄ»°
} CHAT_APPLY_ADD_FRIEND_SYNC;			// ÁÄÌìÌí¼ÓºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nTargetPlayerIdx;	// ±»½ÓÊÜplayer idx
} CHAT_ADD_FRIEND_COMMAND;				// Ìí¼ÓÄ³Íæ¼ÒÎªÁÄÌìºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nTargetPlayerIdx;	// ±»¾Ü¾øplayer idx
} CHAT_REFUSE_FRIEND_COMMAND;			// ¾Ü¾øÌí¼ÓÄ³Íæ¼ÒÎªÁÄÌìºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ÐÂÌí¼ÓºÃÓÑµÄ id
	int				m_nIdx;				// ÐÂÌí¼ÓºÃÓÑÔÚ player Êý×éÖÐµÄÎ»ÖÃ
	char			m_szName[32];		// ÐÂÌí¼ÓºÃÓÑµÄÃû×Ö
} CHAT_ADD_FRIEND_SYNC;					// Í¨Öª¿Í»§¶Ë³É¹¦Ìí¼ÓÒ»¸öÁÄÌìºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;
	char			m_szName[32];		// ¾Ü¾øÕßÃû×Ö
} CHAT_REFUSE_FRIEND_SYNC;				// Í¨Öª¿Í»§¶ËÌí¼ÓÁÄÌìºÃÓÑµÄÉêÇë±»¾Ü¾ø

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nTargetPlayerIdx;	// ³ö´í player idx (Ò»°ã¿ÉÄÜÊÇ´ËplayerÏÂÏß»òÕß»»·þÎñÆ÷ÁË)
} CHAT_ADD_FRIEND_FAIL_SYNC;			// Í¨Öª¿Í»§¶ËÌí¼ÓÁÄÌìºÃÓÑÊ§°Ü

typedef struct
{
	BYTE			ProtocolType;	// c2s_viewequip
	DWORD			m_dwNpcID;
} VIEW_EQUIP_COMMAND;

//´Ë½á¹¹ÒÑ¾­±»tagDBSelPlayer½á¹¹Ìæ»»
/*typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nSelect;			// 
} DB_PLAYERSELECT_COMMAND;*/

/*
 * { Add by liupeng 2003.05.10
 *
 * #pragma pack( push, 1 )
*/

/*
 * Nonstandard extension used : zero-sized array in struct/union
 */
#pragma warning(disable: 4200)

#define KSG_PASSWORD_MAX_SIZE   64

typedef struct tagKSG_PASSWORD
{
    char szPassword[KSG_PASSWORD_MAX_SIZE];    // ÏÖÔÚ²ÉÓÃMD5µÄ×Ö·û´®£¬ÓÉÓÚÊÇ32¸ö×Ö·û£¬¼ÓÉÏÄ©Î²'\0'£¬ÐèÒªÖÁÉÙ33¸ö¿Õ¼ä£¬Òò´ËÊ¹ÓÃ64
} KSG_PASSWORD;

#define _NAME_LEN	32

struct tagProtoHeader
{
	BYTE	cProtocol;
};

struct tagResult : public tagProtoHeader
{
	BYTE	cResult;
};

struct tagDBSelPlayer : public tagProtoHeader
{
	char	szRoleName[_NAME_LEN];
};

struct tagDBDelPlayer : public tagProtoHeader
{
	char	        szAccountName[_NAME_LEN];
    KSG_PASSWORD    Password;
	char	        szRoleName[_NAME_LEN];
};

//É¾³ýÓëÐÂ½¨½ÇÉ«µÄ·µ»ØÏûÏ¢´øµÄÊý¾Ý
struct tagNewDelRoleResponse : public tagDBSelPlayer
{
	bool	bSucceeded;		//ÊÇ·ñ³É¹¦
};

// 2003.05.11
struct tagDBSyncPlayerInfo : public tagProtoHeader
{
	size_t	dataLength;
	char	szData[0];
};

/*
 * 2003.06.27
 * s2c_gateway_broadcast
*/

#define	AP_WARNING_ALL_PLAYER_QUIT			1
#define	AP_NOTIFY_GAMESERVER_SAFECLOSE		2
#define	AP_NOTIFY_ALL_PLAYER				3
#define	MAX_GATEWAYBROADCAST_LEN	260
struct tagGatewayBroadCast : public tagProtoHeader
{
	UINT	uCmdType;
	char	szData[MAX_GATEWAYBROADCAST_LEN];
};

/*
 * 2003.05.22
 * s2c_syncgamesvr_roleinfo_cipher
*/
struct tagGuidableInfo : public tagProtoHeader
{
	GUID guid;
	WORD nExtPoint;			//¿ÉÓÃµÄ¸½ËÍµã
	WORD nChangePoint;		//±ä»¯µÄ¸½ËÍµã
	size_t	datalength;
	char	szData[0];

};

/*
 * c2s_permitplayerlogin
 */
struct tagPermitPlayerLogin : public tagProtoHeader
{
	GUID guid;

	BYTE szRoleName[_NAME_LEN];

	/*
	 * Succeeded : true
	 * Failed	 : false
	 */
	bool bPermit;
};

struct tagPermitPlayerExchange
{
	BYTE cProtocol;
	GUID guid;
	DWORD dwIp;
	WORD wPort;
	bool bPermit;
};
/*
 * c2s_notifyplayerlogin
 */
struct tagNotifyPlayerLogin : public tagPermitPlayerLogin
{
	UINT			nIPAddr;
	unsigned short	nPort;
};

/*
 * s2c_querymapinfo
 */
struct tagQueryMapInfo : public tagProtoHeader
{	
};

/*
 * s2c_querygameserverinfo
 */
struct tagQueryGameSvrInfo : public tagProtoHeader
{	
};

/*
 * s2c_notifysvrip
 */
struct tagNotifySvrIp : public tagProtoHeader
{
	WORD	pckgID;

	BYTE	cIPType;
	DWORD	dwMapID;

	DWORD	dwSvrIP;
};

/*
 * s2c_notifyplayerexchange
 */
struct tagNotifyPlayerExchange : public tagProtoHeader
{
	GUID			guid;
	UINT			nIPAddr;
	unsigned short	nPort;
};

/*
 * c2s_requestsvrip
 */

/*
 * BYTE	cIPType
 */
#define INTRANER_IP	0
#define INTERNET_IP 1

struct tagRequestSvrIp : public tagProtoHeader
{
	WORD	pckgID;

	BYTE	cIPType;
	DWORD	dwMapID;
};

/*
 * c2c_notifyexchange
 */
struct tagSearchWay : public tagProtoHeader
{
	int		lnID;
	int		nIndex;
	DWORD	dwPlayerID;
};

/*
 * c2s_updatemapinfo
 */
struct tagUpdateMapID : public tagProtoHeader
{
	/*
	 * For example : Are your clear older information when it 
	 *		update local informatin
	 */
	BYTE cReserve;

	BYTE cMapCount;

	BYTE szMapID[0];	// C4200 warning
};

/*
 * c2s_updategameserverinfo
 */
struct tagGameSvrInfo : public tagProtoHeader
{
	UINT			nIPAddr_Intraner;
	UINT			nIPAddr_Internet;

	unsigned short	nPort;
	WORD			wCapability;
};

/*
 * s2c_identitymapping
 */
struct tagIdentityMapping : public tagGameSvrInfo
{
	GUID guid;
};

/*
 * c2s_logiclogin
 * s2c_gmgateway2relaysvr
 * s2c_gmnotify
 */
struct tagLogicLogin : public tagProtoHeader
{
	GUID guid;
};

/*
 * s2c_logiclogout
 */
struct tagLogicLogout : public tagProtoHeader
{
	BYTE szRoleName[_NAME_LEN];
};

/*
 * c2s_registeraccount
 */
struct tagRegisterAccount : public tagProtoHeader
{
	BYTE szAccountName[_NAME_LEN];
};

/*
 * c2s_entergame
 */
struct tagEnterGame : public tagProtoHeader
{
	/*
	 * Succeeded : content is account name
	 * Failed	 : content is null
	 */

	BYTE szAccountName[_NAME_LEN];
};

struct tagEnterGame2 : public EXTEND_HEADER
{
	char szAccountName[_NAME_LEN];
	char szCharacterName[_NAME_LEN];
	DWORD	dwNameID;
	unsigned long	lnID;
};

/*
 * c2s_leavegame
 */

/*
 * BYTE cCmdType
 */
#define NORMAL_LEAVEGAME	0x0		// lock account
#define HOLDACC_LEAVEGAME	0x1A	// clear resource but don't to unlock account 

struct tagLeaveGame : public tagProtoHeader
{
	BYTE cCmdType;
	WORD nExtPoint;        //½«Òª¿Û³ýµÄ¸½ËÍµã
	/*
	 * Succeeded : content is account name
	 * Failed	 : content is null
	 */

	char szAccountName[_NAME_LEN];
};

struct tagLeaveGame2 : public EXTEND_HEADER
{
	BYTE cCmdType;
	char szAccountName[_NAME_LEN];
};
/*
*  c2s_registerfamily
*/
struct tagRegisterFamily : public tagProtoHeader
{
	BYTE bRegister;		//1 is Register, 0 is unRegister
	BYTE nFamily;
	BYTE RelayMethod;
};

/*
 * c2s_gmsvr2gateway_saverole
 */
struct tagGS2GWSaveRole : public tagProtoHeader
{
	size_t	datalength;
	BYTE	szData[0];
};

/*
 * #pragma pack( pop )
 *
 * } End of the struct define
 */

typedef struct
{
	char	szName[32];
	BYTE	Sex;
	BYTE	Series;
//	BYTE	HelmType;
//	BYTE	ArmorType;
//	BYTE	WeaponType;
	BYTE	Level;
} RoleBaseInfo/* client */, S3DBI_RoleBaseInfo /* server */;

typedef struct
{
	BYTE				ProtocolType;
	RoleBaseInfo		m_RoleList[MAX_PLAYER_IN_ACCOUNT];
} ROLE_LIST_SYNC;

//ÒÆ×ÔRoleDBManager/kroledbheader.h
//ÓÃÀ´Ìæ»»ÉÏÃæµÄROLE_LIST_SYNC,ROLE_LIST_SYNC½á¹¹²»ÔÙÐèÒªÁË
struct TProcessData
{
	unsigned char	nProtoId;
	size_t			nDataLen;//TRoleNetMsgÊ±±íÊ¾¸ÃBlockµÄÊµ¼ÊÊý¾Ý³¤¶È,TProcessDataÊ±±íÊ¾StreamµÄÊµ¼ÊÊý¾Ý³¤¶È
	unsigned long	ulIdentity;
	bool			bLeave;
	char			pDataBuffer[1];//Êµ¼ÊµÄÊý¾Ý
};

struct tagRoleEnterGame
{
	BYTE			ProtocolType;
	bool			bLock;
	char			Name[_NAME_LEN];
};

//ÐÂ½¨½ÇÉ«µÄÐÅÏ¢½á¹¹
//×¢ÊÍ£ºÐÂ½¨¾öÏûÏ¢c2s_newplayer£¬´«ËÍµÄ²ÎÊýÎªTProcessData½á¹¹ÃèÊöµÄÊý¾Ý£¬ÆäÖÐTProcessData::pDataBufferÒªÀ©Õ¹ÎªNEW_PLAYER_COMMAND
struct NEW_PLAYER_COMMAND
{
	BYTE			m_btRoleNo;			// ½ÇÉ«±àºÅ
	BYTE			m_btSeries;			// ÎåÐÐÏµ
	unsigned short	m_NativePlaceId;	//³öÉúµØID
	char			m_szName[32];		// ÐÕÃû
};


typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ºÃÓÑ id
	int				m_nPlayerIdx;		// ºÃÓÑ player index
} CHAT_LOGIN_FRIEND_NONAME_SYNC;		// Íæ¼ÒµÇÂ¼Ê±·¢ËÍÍæ¼ÒÁÄÌìºÃÓÑÊý¾Ý£¨²»´øÃû×Ö£©

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;
	DWORD			m_dwID;				// ºÃÓÑ id
	int				m_nPlayerIdx;		// ºÃÓÑ player index
	char			m_szName[32];		// ºÃÓÑÃû×Ö
} CHAT_LOGIN_FRIEND_NAME_SYNC;			// Íæ¼ÒµÇÂ¼Ê±·¢ËÍÍæ¼ÒÁÄÌìºÃÓÑÊý¾Ý£¨´øÃû×Ö£©

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
} CHAT_APPLY_RESEND_ALL_FRIEND_NAME_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ºÃÓÑ id
} CHAT_APPLY_SEND_ONE_FRIEND_NAME_COMMAND;	// ÉêÇëµÃµ½Íæ¼ÒÄ³¸öÁÄÌìºÃÓÑµÄÍêÕûÊý¾Ý

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ºÃÓÑ id
	int				m_nPlayerIdx;		// ºÃÓÑ player index
	char			m_szName[32];		// ºÃÓÑÃû×Ö
} CHAT_ONE_FRIEND_DATA_SYNC;			// ·¢ËÍÍæ¼ÒÄ³Ò»¸öÁÄÌìºÃÓÑÊý¾Ý£¨´øÃû×Ö£©

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ºÃÓÑ id
	int				m_nPlayerIdx;		// ºÃÓÑ player index
} CHAT_FRIEND_ONLINE_SYNC;				// Í¨Öª¿Í»§¶ËÓÐºÃÓÑÉÏÏß

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ±»É¾³ýid
} CHAT_DELETE_FRIEND_COMMAND;			// É¾³ýÄ³¸öÁÄÌìºÃÓÑ

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// É¾³ýid
} CHAT_DELETE_FRIEND_SYNC;				// ±»Ä³¸öÁÄÌìºÃÓÑÉ¾³ý

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ±»É¾³ýid
} CHAT_REDELETE_FRIEND_COMMAND;			// É¾³ýÄ³¸öÁÄÌìºÃÓÑ

typedef struct 
{
	BYTE			ProtocolType;
	BYTE			m_LogoutType;
} LOGOUT_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	BYTE			szAccName[32];
} LOGIN_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;				// ºÃÓÑ id
} CHAT_FRIEND_OFFLINE_SYNC;				// Í¨Öª¿Í»§¶ËÓÐºÃÓÑÏÂÏß

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;
	char			m_szSentence[MAX_SENTENCE_LENGTH];
} TRADE_APPLY_OPEN_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
} TRADE_APPLY_CLOSE_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btState;			// if == 0 close if == 1 open if == 2 trading
	DWORD			m_dwNpcID;			// Èç¹ûÊÇ¿ªÊ¼½»Ò×£¬¶Ô·½µÄ npc id
} TRADE_CHANGE_STATE_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;
	DWORD			m_dwID;
	BYTE			m_btState;
	char			m_szSentence[MAX_SENTENCE_LENGTH];
} NPC_SET_MENU_STATE_SYNC;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwID;
} TRADE_APPLY_START_COMMAND;

// ·þÎñÆ÷×ª·¢½»Ò×ÉêÇë
typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nDestIdx;			// ÉêÇëÕßÔÚ·þÎñÆ÷¶ËµÄplayer idx
	DWORD			m_dwNpcId;			// ÉêÇëÕßµÄ npc id
} TRADE_APPLY_START_SYNC;

// ½ÓÊÜ»ò¾Ü¾ø±ðÈËµÄ½»Ò×ÉêÇë
typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_bDecision;		// Í¬Òâ 1 ²»Í¬Òâ 0
	int				m_nDestIdx;			// ½»Ò×¶Ô·½ÔÚ·þÎñÆ÷¶ËµÄplayer idx
} TRADE_REPLY_START_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nMoney;
} TRADE_MOVE_MONEY_COMMAND;		// c2s_trademovemoney

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	int				m_nMoney;
} TRADE_MONEY_SYNC;				// s2c_trademoneysync

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btDecision;		// È·¶¨½»Ò× 1  ÍË³ö½»Ò× 0  È¡ÏûÈ·¶¨ 4  Ëø¶¨½»Ò× 2  È¡ÏûËø¶¨ 3
} TRADE_DECISION_COMMAND;				// ½»Ò×Ö´ÐÐ»òÈ¡Ïû c2s_tradedecision

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btDecision;		// ½»Ò×ok 1  ½»Ò×È¡Ïû 0  Ëø¶¨ 2  È¡ÏûËø¶¨ 3
} TRADE_DECISION_SYNC;					// s2c_tradedecision

typedef struct
{
	BYTE			ProtocolType;		
	BYTE			m_byDir;			// È¡Ç®µÄ·½Ïò£¨0´æ£¬1È¡£©
	DWORD			m_dwMoney;			// Ç®Êý
} STORE_MONEY_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;			// ³¤¶È
	BYTE			m_btError;			// ´íÎóÀàÐÍ	0 ¶Ô·½¹Ø±ÕÁË´ËÆµµÀ£¬1 ÕÒ²»µ½¶Ô·½
	char			m_szName[32];		// ¶Ô·½Ãû×Ö
} CHAT_SCREENSINGLE_ERROR_SYNC;

typedef struct 
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	BYTE			m_btStateInfo[MAX_NPC_RECORDER_STATE];
	DWORD			m_ID;				// NpcµÄGID
}	NPC_SYNC_STATEINFO;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	DWORD			m_dwNpcID;
} TEAM_INVITE_ADD_COMMAND;

typedef struct
{
	BYTE			ProtocolType;		// Ð­ÒéÀàÐÍ
	WORD			m_wLength;			// ³¤¶È
	int				m_nIdx;
	char			m_szName[32];
} TEAM_INVITE_ADD_SYNC;

typedef struct
{
	BYTE			ProtocolType;		//
	int				m_nAuraSkill;
} SKILL_CHANGEAURASKILL_COMMAND;		//¸ü»»¹â»·¼¼ÄÜ

typedef struct
{
	BYTE			ProtocolType;
	BYTE			m_btResult;
	int				m_nIndex;
} TEAM_REPLY_INVITE_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	BYTE			m_btSelfLock;
	BYTE			m_btDestLock;
	BYTE			m_btSelfOk;
	BYTE			m_btDestOk;
} TRADE_STATE_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	WORD			m_wLength;
	DWORD			m_dwSkillID;		// ¼¼ÄÜ
	int				m_nLevel;
	int				m_nTime;			// Ê±¼ä
	KMagicAttrib	m_MagicAttrib[MAX_SKILL_STATE];
} STATE_EFFECT_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	DWORD			m_dwTime;
} PING_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	DWORD			m_dwReplyServerTime;
	DWORD			m_dwClientTime;
} PING_CLIENTREPLY_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	BYTE			m_btSitFlag;
} NPC_SIT_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	int				nMpsX;
	int				nMpsY;
} NPC_JUMP_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	int				m_dwRegionID;
	int				m_nObjID;
} OBJ_MOUSE_CLICK_SYNC;

typedef struct tagSHOW_MSG_SYNC
{
	BYTE			ProtocolType;
	WORD			m_wLength;
	WORD			m_wMsgID;
	LPVOID			m_lpBuf;
	tagSHOW_MSG_SYNC() {m_lpBuf = NULL;};
	~tagSHOW_MSG_SYNC() {Release();}
	void	Release() {if (m_lpBuf) delete []m_lpBuf; m_lpBuf = NULL;}
} SHOW_MSG_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	BYTE			m_btFlag;
} PK_APPLY_NORMAL_FLAG_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	BYTE			m_btFlag;
} PK_NORMAL_FLAG_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	DWORD			m_dwNpcID;
} PK_APPLY_ENMITY_COMMAND;

typedef struct
{
	BYTE			ProtocolType;
	WORD			m_wLength;
	BYTE			m_btState;
	DWORD			m_dwNpcID;
	char			m_szName[32];
} PK_ENMITY_STATE_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	WORD			m_wLength;
	BYTE			m_btState;
	DWORD			m_dwNpcID;
	char			m_szName[32];
} PK_EXERCISE_STATE_SYNC;

typedef struct
{
	BYTE			ProtocolType;
	int				m_nPKValue;
} PK_VALUE_SYNC;

typedef struct
{
	int		m_nID;				// ÎïÆ·µÄID
	BYTE	m_btGenre;			// ÎïÆ·µÄÀàÐÍ
	BYTE	m_btDetail;			// ÎïÆ·µÄÀà±ð
	BYTE	m_btParticur;		// ÎïÆ·µÄÏêÏ¸Àà±ð
	BYTE	m_btSeries;			// ÎïÆ·µÄÎåÐÐ
	BYTE	m_btLevel;			// ÎïÆ·µÄµÈ¼¶
	BYTE	m_btLuck;			// MF
	BYTE	m_btMagicLevel[6];	// Éú³É²ÎÊý
	WORD	m_wVersion;			// ×°±¸°æ±¾
	DWORD	m_dwRandomSeed;		// Ëæ»úÖÖ×Ó
} SViewItemInfo;

typedef struct
{
	BYTE			ProtocolType;
	DWORD			m_dwNpcID;
	SViewItemInfo	m_sInfo[itempart_num];
} VIEW_EQUIP_SYNC;				// s2c_viewequip

typedef struct//¸Ã½á¹¹ÊÇËùÍ³¼ÆµÄÍæ¼ÒµÄ»ù±¾Êý¾Ý
{
	char	Name[20];
	int		nValue;
	BYTE	bySort;
}TRoleList;

// ÓÎÏ·Í³¼Æ½á¹¹
typedef struct
{
	TRoleList MoneyStat[10];			//½ðÇ®×î¶àÅÅÃûÁÐ±í£¨Ê®¸öÍæ¼Ò£¬×î¶à¿É´ïµ½100¸ö£©
	TRoleList LevelStat[10];			//¼¶±ð×î¶àÅÅÃûÁÐ±í£¨Ê®¸öÍæ¼Ò£¬×î¶à¿É´ïµ½100¸ö£©
	TRoleList KillerStat[10];			//É±ÈË×î¶àÅÅÃûÁÐ±í
	
	//[ÃÅÅÉºÅ][Íæ¼ÒÊý]£¬ÆäÖÐ[0]ÊÇÃ»ÓÐ¼ÓÈëÃÅÅÉµÄÍæ¼Ò
	TRoleList MoneyStatBySect[11][10];	//¸÷ÃÅÅÉ½ðÇ®×î¶àÅÅÃûÁÐ±í
	TRoleList LevelStatBySect[11][10];	//¸÷ÃÅÅÉ¼¶±ð×î¶àÅÅÃûÁÐ±í

	//[ÃÅÅÉºÅ]£¬ÆäÖÐ[0]ÊÇÃ»ÓÐ¼ÓÈëÃÅÅÉµÄÍæ¼Ò
	int SectPlayerNum[11];				//¸÷¸öÃÅÅÉµÄÍæ¼ÒÊý
	int SectMoneyMost[11];				//²Æ¸»ÅÅÃûÇ°Ò»°ÙÍæ¼ÒÖÐ¸÷ÃÅÅÉËùÕ¼±ÈÀýÊý
	int SectLevelMost[11];				//¼¶±ðÅÅÃûÇ°Ò»°ÙÍæ¼ÒÖÐ¸÷ÃÅÅÉËùÕ¼±ÈÀýÊý
}  TGAME_STAT_DATA;

typedef struct
{
	BYTE	ProtocolType;
	BYTE	bSleep;
	DWORD	NpcID;
} NPC_SLEEP_SYNC;

//////////////
//ÅÅÃûÏà¹Ø
typedef struct
{
	BYTE		ProtocolType;
	DWORD		dwLadderID;
	TRoleList	StatData[10];
} LADDER_DATA;

typedef struct
{
	BYTE		ProtocolType;
	WORD		wSize;
	int			nCount;
	DWORD		dwLadderID[0];
} LADDER_LIST;

typedef struct
{
	BYTE		ProtocolType;
	DWORD		dwLadderID;
} LADDER_QUERY;


///////////////////
//chat Ïà¹Ø

typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	DWORD	packageID;
	char	someone[_NAME_LEN];
	BYTE	sentlen;
} CHAT_SOMEONECHAT_CMD, CHAT_SOMEONECHAT_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	DWORD	packageID;
	BYTE	filter;
	DWORD	channelid;
	BYTE	cost;	//0: ÎÞÏÞÖÆ£¬1: 10Ôª/¾ä£¬2: <10Lv ? ²»ÄÜËµ : MaxMana/2/¾ä, 3: MaxMana/10/¾ä,4: <20Lv ? ²»ÄÜËµ : MaxMana*4/5/¾ä
	BYTE	sentlen;
} CHAT_CHANNELCHAT_CMD;

typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	DWORD	packageID;
	char	someone[_NAME_LEN];
	DWORD	channelid;
	BYTE	sentlen;
} CHAT_CHANNELCHAT_SYNC;

enum {codeSucc, codeFail, codeStore};
typedef struct
{
	BYTE	ProtocolType;
	DWORD	packageID;
	BYTE	code;
} CHAT_FEEDBACK;

typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	WORD	wChatLength;
} CHAT_EVERYONE;


typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	WORD	wChatLength;
	BYTE	byHasIdentify;
	WORD	wPlayerCount;
} CHAT_GROUPMAN;


typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	DWORD	nameid;
	unsigned long lnID;
	WORD	wChatLength;
} CHAT_SPECMAN;


enum { tgtcls_team, tgtcls_fac, tgtcls_tong, tgtcls_scrn, tgtcls_bc};
typedef struct
{
	BYTE	ProtocolType;
	WORD	wSize;
	DWORD	nFromIP;
	DWORD	nFromRelayID;
	DWORD	channelid;
	BYTE	TargetCls;
	DWORD	TargetID;
	WORD	routeDateLength;
} CHAT_RELEGATE;


///////////////////////////////////////
// tong Ïà¹Ø

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
} S2C_TONG_HEAD;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
} STONG_PROTOCOL_HEAD;

typedef struct
{
	int		m_nPlayerIdx;
	int		m_nCamp;
	char	m_szTongName[defTONG_NAME_MAX_LENGTH + 1];
} STONG_SERVER_TO_CORE_APPLY_CREATE;

typedef struct
{
	int		m_nPlayerIdx;
	DWORD	m_dwNpcID;
} STONG_SERVER_TO_CORE_APPLY_ADD;

typedef struct
{
	int		m_nSelfIdx;
	int		m_nTargetIdx;
	DWORD	m_dwNameID;
} STONG_SERVER_TO_CORE_CHECK_ADD_CONDITION;

typedef struct
{
	int		m_nCamp;
	int		m_nPlayerIdx;
	DWORD	m_dwPlayerNameID;
	char	m_szTongName[64];
} STONG_SERVER_TO_CORE_CREATE_SUCCESS;

typedef struct
{
	int		m_nSelfIdx;
	int		m_nTargetIdx;
	DWORD	m_dwNameID;
} STONG_SERVER_TO_CORE_REFUSE_ADD;

typedef struct
{
	int		m_nSelfIdx;
	int		m_nInfoID;
	int		m_nParam1;
	int		m_nParam2;
	int		m_nParam3;
	char	m_szName[32];
} STONG_SERVER_TO_CORE_GET_INFO;

typedef struct
{
	int		m_nCamp;
	int		m_nPlayerIdx;
	DWORD	m_dwPlayerNameID;
	char	m_szTongName[32];
	char	m_szMasterName[32];
	char	m_szTitleName[32];
} STONG_SERVER_TO_CORE_ADD_SUCCESS;

typedef struct
{
	int		m_nPlayerIdx;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szTitle[32];
	char	m_szName[32];
} STONG_SERVER_TO_CORE_BE_INSTATED;

typedef struct
{
	int		m_nPlayerIdx;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szName[32];
} STONG_SERVER_TO_CORE_BE_KICKED;

typedef struct
{
	int		m_nPlayerIdx;
	BOOL	m_bSuccessFlag;
	char	m_szName[32];
} STONG_SERVER_TO_CORE_LEAVE;

typedef struct
{
	int		m_nPlayerIdx;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	DWORD	m_dwTongNameID;
	char	m_szName[32];
} STONG_SERVER_TO_CORE_CHECK_GET_MASTER_POWER;

typedef struct
{
	int		m_nPlayerIdx;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	DWORD	m_dwTongNameID;
	char	m_szTitle[32];
	char	m_szName[32];
} STONG_SERVER_TO_CORE_CHANGE_AS;

typedef struct
{
	DWORD	m_dwTongNameID;
	char	m_szName[32];
} STONG_SERVER_TO_CORE_CHANGE_MASTER;

typedef struct
{
	DWORD	m_dwParam;
	int		m_nFlag;
	int		m_nCamp;
	int		m_nFigure;
	int		m_nPos;
	char	m_szTongName[32];
	char	m_szTitle[32];
	char	m_szMaster[32];
	char	m_szName[32];
} STONG_SERVER_TO_CORE_LOGIN;

// Íæ¼ÒÉêÇë½¨Á¢°ï»á ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	BYTE	m_btCamp;
	char	m_szName[defTONG_NAME_MAX_LENGTH + 1];
} TONG_APPLY_CREATE_COMMAND;

// Íæ¼ÒÉêÇë¼ÓÈë°ï»á ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwNpcID;
} TONG_APPLY_ADD_COMMAND;

// Íæ¼ÒÉêÇë¼ÓÈë°ï»á ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btCurFigure;
	BYTE	m_btCurPos;
	BYTE	m_btNewFigure;
	BYTE	m_btNewPos;
	char	m_szName[32];
} TONG_APPLY_INSTATE_COMMAND;

// °ï»á½¨Á¢Ê§°Ü À©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	BYTE	m_btFailId;
} TONG_CREATE_FAIL_SYNC;

// ×ª·¢¼ÓÈë°ï»áÉêÇë À©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	int		m_nPlayerIdx;
	char	m_szName[32];
} TONG_APPLY_ADD_SYNC;

// Í¨ÖªÍæ¼Ò½¨Á¢°ï»á³É¹¦ ÓÃÆÕÍ¨Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	BYTE	m_btCamp;
	char	m_szName[defTONG_NAME_MAX_LENGTH + 1];
} TONG_CREATE_SYNC;

// Í¨ÖªÍæ¼Ò¼ÓÈë°ï»á ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	BYTE	m_btCamp;
	char	m_szTongName[32];
	char	m_szTitle[32];
	char	m_szMaster[32];
} TONG_Add_SYNC;

// Íæ¼ÒÉêÇë½âÉ¢°ï»á ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
} TONG_APPLY_DISMISS_COMMAND;

// Íæ¼Ò°ï»á±»½âÉ¢ ÓÃÆÕÍ¨Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
} TONG_DISMISS_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	int		m_nPlayerIdx;
	DWORD	m_dwNameID;
	BYTE	m_btFlag;			// ÊÇ·ñ½ÓÊÜ TRUE ½ÓÊÜ FALSE ²»½ÓÊÜ
} TONG_ACCEPT_MEMBER_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	BYTE	m_btInfoID;
	int		m_nParam1;
	int		m_nParam2;
	int		m_nParam3;
	char	m_szBuf[64];
} TONG_APPLY_INFO_COMMAND;

typedef struct
{
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szTitle[32];
	char	m_szName[32];
} TONG_ONE_LEADER_INFO;

typedef struct
{
	char	m_szName[32];
} TONG_ONE_MEMBER_INFO;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwNpcID;
	DWORD	m_dwMoney;
	int		m_nCredit;
	BYTE	m_btCamp;
	BYTE	m_btLevel;
	BYTE	m_btDirectorNum;
	BYTE	m_btManagerNum;
	DWORD	m_dwMemberNum;
	char	m_szTongName[32];
	TONG_ONE_LEADER_INFO	m_sMember[1 + defTONG_MAX_DIRECTOR];
} TONG_HEAD_INFO_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwMoney;
	int		m_nCredit;
	BYTE	m_btCamp;
	BYTE	m_btLevel;
	BYTE	m_btDirectorNum;
	BYTE	m_btManagerNum;
	DWORD	m_dwMemberNum;
	BYTE	m_btStateNo;
	BYTE	m_btCurNum;
	char	m_szTongName[32];
	TONG_ONE_LEADER_INFO	m_sMember[defTONG_ONE_PAGE_MAX_NUM];
} TONG_MANAGER_INFO_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwMoney;
	int		m_nCredit;
	BYTE	m_btCamp;
	BYTE	m_btLevel;
	BYTE	m_btDirectorNum;
	BYTE	m_btManagerNum;
	DWORD	m_dwMemberNum;
	BYTE	m_btStateNo;
	BYTE	m_btCurNum;
	char	m_szTitle[32];
	char	m_szTongName[32];
	TONG_ONE_MEMBER_INFO	m_sMember[defTONG_ONE_PAGE_MAX_NUM];
} TONG_MEMBER_INFO_SYNC;

// Íæ¼Ò×ÔÉíÔÚ°ï»áÖÐµÄÐÅÏ¢ ÓÃÀ©Õ¹Ð­Òé
typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	BYTE	m_btJoinFlag;
	BYTE	m_btFigure;
	BYTE	m_btCamp;
	char	m_szTongName[32];
	char	m_szTitle[32];
	char	m_szMaster[32];
} TONG_SELF_INFO_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btSuccessFlag;
	BYTE	m_btOldFigure;
	BYTE	m_btOldPos;
	BYTE	m_btNewFigure;
	BYTE	m_btNewPos;
	char	m_szTitle[32];
	char	m_szName[32];
} TONG_INSTATE_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szName[32];
} TONG_APPLY_KICK_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btSuccessFlag;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szName[32];
} TONG_KICK_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szName[32];
} TONG_APPLY_LEAVE_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btFigure;
	BYTE	m_btPos;
	char	m_szName[32];
} TONG_APPLY_CHANGE_MASTER_COMMAND;

typedef struct
{
	BYTE	ProtocolType;
	WORD	m_wLength;
	BYTE	m_btMsgId;
	DWORD	m_dwTongNameID;
	BYTE	m_btFailID;
	char	m_szName[32];
} TONG_CHANGE_MASTER_FAIL_SYNC;

// tong Ïà¹Ø end
typedef struct
{
	BYTE	ProtocolType;
	DWORD	m_dwNpcID;
	WORD	m_wGoldFlag;
} NPC_GOLD_CHANGE_SYNC;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	dwItemID;
	int		nChange;
} ITEM_DURABILITY_CHANGE;

typedef struct
{
	BYTE	ProtocolType;
	DWORD	dwItemID;
} ITEM_REPAIR;

// ÔÚµ÷ÓÃÕâÖ§º¯ÊýÖ®Ç°±ØÐëÅÐ¶ÏÊÇ·ñ´¦ÓÚ½»Ò××´Ì¬£¬Èç¹ûÕýÔÚ½»Ò×£¬²»ÄÜµ÷ÓÃÕâÖ§º¯Êý
void SendClientCmdSell(int nID);
// ÔÚµ÷ÓÃÕâÖ§º¯ÊýÖ®Ç°±ØÐëÅÐ¶ÏÊÇ·ñ´¦ÓÚ½»Ò××´Ì¬£¬Èç¹ûÕýÔÚ½»Ò×£¬²»ÄÜµ÷ÓÃÕâÖ§º¯Êý
void SendClientCmdBuy(int nBuyIdx, int nPlace, int nX, int nY);
// ÔÚµ÷ÓÃÕâÖ§º¯ÊýÖ®Ç°±ØÐëÅÐ¶ÏÊÇ·ñ´¦ÓÚ½»Ò××´Ì¬£¬Èç¹ûÕýÔÚ½»Ò×£¬²»ÄÜµ÷ÓÃÕâÖ§º¯Êý
void SendClientCmdRun(int nX, int nY);
// ÔÚµ÷ÓÃÕâÖ§º¯ÊýÖ®Ç°±ØÐëÅÐ¶ÏÊÇ·ñ´¦ÓÚ½»Ò××´Ì¬£¬Èç¹ûÕýÔÚ½»Ò×£¬²»ÄÜµ÷ÓÃÕâÖ§º¯Êý
void SendClientCmdWalk(int nX, int nY);
// ÔÚµ÷ÓÃÕâÖ§º¯ÊýÖ®Ç°±ØÐëÅÐ¶ÏÊÇ·ñ´¦ÓÚ½»Ò××´Ì¬£¬Èç¹ûÕýÔÚ½»Ò×£¬²»ÄÜµ÷ÓÃÕâÖ§º¯Êý
void SendClientCmdSkill(int nSkillID, int nX, int nY);
//void SendClientCmdPing();
void SendClientCmdSit(int nSitFlag);
void SendClientCmdMoveItem(void* pDownPos, void* pUpPos);
void SendClientCmdQueryLadder(DWORD	dwLadderID);
void SendClientCmdRequestNpc(int nID);
void SendClientCmdJump(int nX, int nY);
void SendClientCmdStoreMoney(int nDir, int nMoney);
//void SendClientCmdRevive(int nReviveType);
void SendClientCmdRevive();
void SendObjMouseClick(int nObjID, DWORD dwRegionID);
void SendClientCmdRepair(DWORD dwID);

extern	int	g_nProtocolSize[MAX_PROTOCOL_NUM];
#pragma pack(pop, enter_protocol)
#endif
