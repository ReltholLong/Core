#ifndef	KProtocolDefH
#define	KProtocolDefH


// Add by Freeway chen in 2003.7.1
// ¶¨ÒåÐ­Òé¼æÈÝµÄ°æ±¾£¬Èç¹ûÐÞ¸ÄµÄÐ­Òé£¬µ¼ÖÂÔ­ÓÐ°æ±¾ÎÞ·¨Ê¹ÓÃ£¬ÐèÒªÐÞ¸ÄÏÂÃæµÄÖµ

#define USE_KPROTOCOL_VERSION   1
//#undef USE_KPROTOCOL_VERSION

#define KPROTOCOL_VERSION   1
/*
 *
 */

/*
 * It was to judge a package type that 
 * it is a larger package or it is a small package
 */
const UINT g_nGlobalProtocolType = 31;

enum s2c_PROTOCOL
{
	s2c_roleserver_getroleinfo_result = 10,
	s2c_syncgamesvr_roleinfo_cipher,
	s2c_gamestatistic_bigpackage,

	/*
	 * This value must be equal to c2s_micropackbegin
	 */
	s2c_micropackbegin = g_nGlobalProtocolType,

	s2c_accountbegin = 32,
	s2c_accountlogin,
	s2c_gamelogin,
	s2c_accountlogout,
	s2c_gatewayverify,		//ÓÃÓÚÁ¬½ÓºóµÚÒ»¸ö°ü
	s2c_gatewayverifyagain,		//ÓÃÓÚÖØÁ¬ºóµÚÒ»¸ö°ü
	s2c_gatewayinfo,

	s2c_multiserverbegin = 48,
	s2c_querymapinfo,
	s2c_querygameserverinfo,
	s2c_identitymapping,
	s2c_notifyplayerlogin,
	s2c_notifyplayerexchange,
	s2c_notifysvrip,
	
	s2c_roleserver_getrolelist_result,
	s2c_roleserver_saverole_result,
	s2c_roleserver_createrole_result,
	s2c_roleserver_deleterole_result,
	s2c_logiclogout,
	s2c_gateway_broadcast,
	s2c_gamestatistic,
	
	s2c_clientbegin = 64,
	s2c_login,		//ref: ../../S3Client/Login/LoginDef.h
	s2c_logout,
	s2c_syncend,
	s2c_synccurplayer,
	s2c_synccurplayerskill,
	s2c_synccurplayernormal,
	s2c_newplayer,
	s2c_removeplayer,
	s2c_syncworld,
	s2c_syncplayer,
	s2c_syncplayermin,
	s2c_syncnpc,
	s2c_syncnpcmin,
	s2c_syncnpcminplayer,
	s2c_objadd,
	s2c_syncobjstate,
	s2c_syncobjdir,
	s2c_objremove,
	s2c_objTrapAct,
	s2c_npcremove,
	s2c_npcwalk,
	s2c_npcrun,
	s2c_npcattack,
	s2c_npcmagic,
	s2c_npcjump,
	s2c_npctalk,
	s2c_npchurt,
	s2c_npcdeath,
	s2c_npcchgcurcamp,
	s2c_npcchgcamp,
	s2c_skillcast,
	s2c_playertalk,
	s2c_playerexp,
	s2c_teaminfo,
	s2c_teamselfinfo,
	s2c_teamapplyinfofalse,
	s2c_teamcreatesuccess,
	s2c_teamcreatefalse,
	s2c_teamopenclose,
	s2c_teamgetapply,
	s2c_teamaddmember,
	s2c_teamleave,
	s2c_teamchangecaptain,
	s2c_playerfactiondata,
	s2c_playerleavefaction,
	s2c_playerfactionskilllevel,
	s2c_playersendchat,
	s2c_playersyncleadexp,
	s2c_playerlevelup,
	s2c_teammatelevel,
	s2c_playersyncattribute,
	s2c_playerskilllevel,
	s2c_syncitem,
	s2c_removeitem,
	s2c_syncmoney,
	s2c_playermoveitem,
	s2c_scriptaction,
	s2c_chatapplyaddfriend,
	s2c_chataddfriend,
	s2c_chatrefusefriend,
	s2c_chataddfriendfail,
	s2c_chatloginfriendnoname,
	s2c_chatloginfriendname,
	s2c_chatonefrienddata,
	s2c_chatfriendonline,
	s2c_chatdeletefriend,
	s2c_chatfriendoffline,
	s2c_syncrolelist,
	s2c_tradechangestate,
	s2c_npcsetmenustate,
	s2c_trademoneysync,
	s2c_tradedecision,
	s2c_chatscreensingleerror,
	s2c_syncnpcstate,
	s2c_teaminviteadd,
	s2c_tradepressoksync,
	s2c_ping,
	s2c_npcsit,
	s2c_opensalebox,
	s2c_castskilldirectly,
	s2c_msgshow,
	s2c_syncstateeffect,
	s2c_openstorebox,
	s2c_playerrevive,

	s2c_requestnpcfail,
	s2c_tradeapplystart,
	
	s2c_rolenewdelresponse,	//ÐÂ½¨ÓëÉ¾³ý½ÇÉ«µÄ½á¹û·µ»Ø,Ëù´øÊý¾ÝÎª½á¹¹tagNewDelRoleResponse
	s2c_ItemAutoMove,
	s2c_itemexchangefinish,
	s2c_changeweather,
	s2c_pksyncnormalflag,
	s2c_pksyncenmitystate,
	s2c_pksyncexercisestate,
	s2c_pksyncpkvalue,
	s2c_npcsleepmode,
	s2c_viewequip,

	s2c_ladderresult,
	s2c_ladderlist,

	s2c_tongcreate,

	s2c_replyclientping,

	s2c_npcgoldchange,

	s2c_itemdurabilitychange,

//	s2c_gmgateway2relaysvr,		//GMµÇÂ½ºóÍø¹ØÍ¨ÖªÖÐ×ª·þÎñÆ÷ÓÐºÏ·¨Á¬½ÓµÄÐ­Òé

	s2c_extend = 250,
	s2c_extendchat = 251,
	s2c_extendfriend = 252,
	s2c_extendtong = 253,
	s2c_end,
};

enum c2s_PROTOCOL
{
	c2s_roleserver_saveroleinfo = 10,
	c2s_roleserver_createroleinfo,
	
	c2s_gmsvr2gateway_saverole,

	/*
	 * This value must be equal to s2c_micropackbegin
	 */
	c2s_micropackbegin = g_nGlobalProtocolType,

	c2s_accountbegin = 32,
	c2s_accountlogin,
	c2s_gamelogin,
	c2s_accountlogout,
	c2s_gatewayverify,
	c2s_gatewayverifyagain,
	c2s_gatewayinfo,

	c2s_multiserverbegin = 48,
	c2s_permitplayerlogin,
	c2s_updatemapinfo,
	c2s_updategameserverinfo,
	c2s_entergame,
	c2s_leavegame,
	c2s_registeraccount,

	c2s_requestsvrip,

	c2s_roleserver_getrolelist,
	c2s_roleserver_getroleinfo,
	c2s_roleserver_deleteplayer,
	c2s_gamestatistic,
	c2s_roleserver_lock,
	
	c2s_gameserverbegin = 64,
/*65 */ c2s_login,
/*66 */ c2s_logiclogin,
/*67 */ c2s_syncend,
/*68 */ c2s_loadplayer,
/*69 */ c2s_newplayer,
/*70 */ c2s_removeplayer,
/*71 */ c2s_requestworld,
/*72 */ c2s_requestplayer,
/*73 */ c2s_requestnpc,
/*74 */ c2s_requestobj,
/*75 */ c2s_npcwalk,
/*76 */ c2s_npcrun,
/*77 */ c2s_npcskill,
/*78 */ c2s_npcjump,
/*79 */ c2s_npctalk,
/*80 */ c2s_npchurt,
/*81 */ c2s_npcdeath,
/*82 */ c2s_playertalk,
/*83 */ c2s_teamapplyinfo,
/*84 */ c2s_teamapplycreate,
/*85 */ c2s_teamapplyopenclose,
/*86 */ c2s_teamapplyadd,
/*87 */ c2s_teamacceptmember,
/*88 */ c2s_teamapplyleave,
/*89 */ c2s_teamapplykickmember,
/*90 */ c2s_teamapplychangecaptain,
/*91 */ c2s_teamapplydismiss,
/*92 */ c2s_playerapplysetpk,
/*93 */ c2s_playerapplyfactiondata,
/*94 */ c2s_playersendchat,
/*95 */ c2s_playeraddbaseattribute,
/*96 */ c2s_playerapplyaddskillpoint,
/*97 */ c2s_playereatitem,
/*98 */ c2s_playerpickupitem,
/*99 */ c2s_playermoveitem,
/*100*/ c2s_playersellitem,
/*101*/ c2s_playerbuyitem,
/*102*/ c2s_playerthrowawayitem,
/*103*/ c2s_playerselui,
/*104*/ c2s_chatsetchannel,
/*105*/ c2s_chatapplyaddfriend,
/*106*/ c2s_chataddfriend,
/*107*/ c2s_chatrefusefriend,
/*108*/ c2s_dbplayerselect,
/*109*/ c2s_chatapplyresendallfriendname,
/*110*/ c2s_chatapplysendonefriendname,
/*111*/ c2s_chatdeletefriend,
/*112*/ c2s_chatredeletefriend,
/*113*/ c2s_tradeapplystateopen,
/*114*/ c2s_tradeapplystateclose,
/*115*/ c2s_tradeapplystart,
/*116*/ c2s_trademovemoney,
/*117*/ c2s_tradedecision,
/*118*/ c2s_dialognpc,
/*119*/ c2s_teaminviteadd,
/*120*/ c2s_changeauraskill,
/*121*/ c2s_teamreplyinvite,
/*122*/ c2s_ping,
/*123*/ c2s_npcsit,
/*124*/ c2s_objmouseclick,
/*125*/ c2s_storemoney,
/*126*/ c2s_playerrevive,
/*127*/ c2s_tradereplystart,
/*128*/ c2s_pkapplychangenormalflag,
/*129*/ c2s_pkapplyenmity,
/*130*/ c2s_viewequip,
//	c2s_gmlogin,		//¹¦Ð§Í¬c2s_login
	c2s_ladderquery,
	c2s_repairitem,

	_c2s_begin_relay = 250,
	c2s_extend = _c2s_begin_relay,
	c2s_extendchat,
	c2s_extendfriend,
	_c2s_end_relay = c2s_extendfriend,
	c2s_extendtong,
	c2s_end,
};

enum c2c_PROTOCOL		//¸ÃÐ­Òé×å½öÓÃÓÚserverºÍserverÖ®¼ä
{
	c2c_transferroleinfo = 14,
	c2c_micropackbegin = g_nGlobalProtocolType,
	c2c_protocolbegin = 32,
	c2c_permitplayerexchangeout = 64,
	c2c_permitplayerexchangein,
	c2c_notifyexchange,

	s2s_broadcast = 96,		//ÓÃÓÚ´ÓRelayµ½ÓÎÏ·ÊÀ½çµÄ¹ã²¥
	s2s_execute = 97,		//ÓÃÓÚ´ÓRelayµ½ÓÎÏ·ÊÀ½çµÄÖ´ÐÐ½Å±¾

	c2c_end,
};

//ÒÔÏÂÐ­ÒéÎªc2s_extendÐ­ÒéµÄÅÉÉúÐ­Òé£¬²Î¼ûKRelayProtocol.h
//À©Õ¹Ð­Òé±ØÐëÒÔEXTEND_HEADER´òÍ·

enum gm_PROTOCOL		//¸ÃÐ­Òé×å½öÓÃÓÚgmºÍserverÖ®¼ä
{
	gm_begin = 32,
	gm_c2s_execute,				//ÒÔÏÂÐ­ÒéÓÉGM¿Í»§¶ËÒÔrelay_c2c_askwaydata×ª·¢¸øÓÎÏ·ÊÀ½ç
	gm_c2s_disable,
	gm_c2s_enable,
	gm_c2s_tracking,
	gm_c2s_setrole,
	gm_c2s_getrole,	
	gm_c2s_findplayer,
	gm_c2s_unlock,
	gm_c2s_getrolelist,
	gm_c2s_broadcast_chat,

	gm_s2c_tracking,			//ÒÔÏÂÐ­ÒéÓÉÓÎÏ·ÊÀ½çÒÔrelay_c2c_data×ª·¢¸øGM¿Í»§¶Ë
	gm_s2c_getrole,
	gm_s2c_findplayer,
	gm_s2c_getrolelist,

	gm_end,
};


enum relay_PROTOCOL		//¸ÃÐ­Òé×å½öÓÃÓÚserverºÍrelayÖ®¼ä
{
	relay_begin = 32,

	relay_c2c_data,

	relay_c2c_askwaydata,

	relay_s2c_loseway,

	relay_end,
};

enum chat_PROTOCOL
{
	chat_micropackbegin = g_nGlobalProtocolType,

	chat_someonechat,
	chat_channelchat,
	chat_feedback,

	chat_everyone,

	chat_groupman,
	chat_specman,

	chat_relegate,
	chat_filterplayer,
};

enum playercomm_PROTOCOL		//¸ÃÐ­Òé×å½öÓÃÓÚserverºÍclientÖ®¼ä,µ«ÊÇserver¿ÉÒÔ×ª·¢¸ørelay´¦Àí£¬ÒòÎªrelay³Ðµ£ÁË²¿·ÖserverµÄ¹¦ÄÜ
{
	playercomm_begin = 32,

	playercomm_c2s_querychannelid,
	playercomm_s2c_notifychannelid,
	playercomm_c2s_freechannelid,

	playercomm_c2s_subscribe,
	
	playercomm_s2c_relegate,
	playercomm_c2s_rollback,

	playercomm_s2c_gmquerychannelid,
	playercomm_s2c_gmfreechannelid,
	playercomm_s2c_gmsubscribe,

	playercomm_c2s_someoneact,
	playercomm_c2s_channelact,

	playercomm_someonechat,
	playercomm_channelchat,
};

// game server ·¢¸ø s3client °ï»áÀ©Õ¹Ð­Òé id
enum
{
	enumTONG_SYNC_ID_CREATE_FAIL = 0,
	enumTONG_SYNC_ID_TRANSFER_ADD_APPLY,
	enumTONG_SYNC_ID_ADD,
	enumTONG_SYNC_ID_HEAD_INFO,
	enumTONG_SYNC_ID_SELF_INFO,
	enumTONG_SYNC_ID_MANAGER_INFO,
	enumTONG_SYNC_ID_MEMBER_INFO,
	enumTONG_SYNC_ID_INSTATE,
	enumTONG_SYNC_ID_KICK,
	enumTONG_SYNC_ID_CHANGE_MASTER_FAIL,

	enumTONG_SYNC_ID_NUM,
};

// s3client ·¢¸ø game server °ï»áÀ©Õ¹Ð­Òé id
enum
{
	enumTONG_COMMAND_ID_START = 0,
	enumTONG_COMMAND_ID_APPLY_CREATE,
	enumTONG_COMMAND_ID_APPLY_ADD,
	enumTONG_COMMAND_ID_ACCEPT_ADD,
	enumTONG_COMMAND_ID_APPLY_INFO,
	enumTONG_COMMAND_ID_APPLY_INSTATE,
	enumTONG_COMMAND_ID_APPLY_KICK,
	enumTONG_COMMAND_ID_APPLY_LEAVE,
	enumTONG_COMMAND_ID_APPLY_CHANGE_MASTER,

	enumTONG_COMMAND_ID_NUM,
};


#endif
