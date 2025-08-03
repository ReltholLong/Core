//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
//
// File:	KCore.h  
// Date:	2000.08.08
// Code:	Daphnis Wang
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef KCore_H
#define KCore_H
#pragma warning(disable : 4244)

// === TÁCH BIỆT SERVER VÀ CLIENT BUILD ===
#ifdef _MSC_VER
#if _MSC_VER >= 1900

#pragma warning(disable: 4996 5208 4267 4305 4018 4800)

#ifdef _SERVER
    // Server: Block DirectDraw
#ifndef __DDRAW_INCLUDED__
#define __DDRAW_INCLUDED__
#endif
#ifndef _DDRAW_H
#define _DDRAW_H
#endif

#define WINDOWS_IGNORE_PACKING_MISMATCH
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCKAPI_
#include <windows.h>
#undef _WINSOCKAPI_
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCKAPI_

#else
    // Client: Include DirectDraw after KWin32.h
#define WINDOWS_IGNORE_PACKING_MISMATCH
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCKAPI_

// FORCE DirectDraw include after
#include <winsock2.h>
#include <windows.h>
#include <ddraw.h>        // ← CRITICAL
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "ddraw.lib")

#undef _WINSOCKAPI_
#endif

#else
// VC 6.0
#include <windows.h>
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")
#ifndef _SERVER
#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#endif
#endif
#endif

//---------------------------------------------------------------------------
#include "KWin32.h"    // ← Include befont Befont DirectDraw

// Rest của file...
//---------------------------------------------------------------------------
#ifdef _STANDALONE
#define CORE_API
#else
#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#endif
//---------------------------------------------------------------------------
#define	DIR_DOWN		0
#define	DIR_LEFTDOWN	1
#define	DIR_LEFT		2
#define	DIR_LEFTUP		3
#define	DIR_UP			4
#define	DIR_RIGHTUP		5
#define	DIR_RIGHT		6
#define	DIR_RIGHTDOWN	7
//---------------------------------------------------------------------------
#include "KWin32.h"
#include "KDebug.h"
#include "KMemBase.h"
#include "KStrBase.h"

#ifndef _SERVER
#include "KSpriteCache.h"
#include "KFont.h"
#endif

#include "KTabFile.h"
#include "KProtocol.h"
#include "KEngine.h"
#include "KScriptList.h"
#include "KScriptCache.h"
#include "KSkillManager.h"
#include "MyAssert.H"
class ISkill;
#ifdef _SERVER
#ifdef _STANDALONE
#include "IServer.h"
#else
#include "../../Headers/IServer.h"
#endif
#else
#include "../../Headers/IClient.h"
#include "KMusic.h"
#include "KSoundCache.h"
#endif

#pragma warning (disable: 4512)
#pragma warning (disable: 4786)
#define TASKCONTENT
//#define		BMPMAPDEBUG
//---------------------------------------------------------------------------
#ifdef TOOLVERSION
extern CORE_API int g_ScreenX;
extern CORE_API int g_ScreenY;
#endif

#define ITOA(NUMBER)  #NUMBER

#define __TEXT_LINE__(LINE) ITOA(LINE)

//#ifdef _DEBUG
#define ATTENTION(MSG) __FILE__"("__TEXT_LINE__(__LINE__)") : ЎпATTENTIONЎп Ўъ "#MSG
//#else
//#define ATTENTION(MSG) __FILE__"("__TEXT_LINE__(__LINE__)") : ATTENTION!! error: "#MSG
//#endif

#define	NET_DEBUG
extern CORE_API	KTabFile		g_OrdinSkillsSetting, g_MisslesSetting;
extern CORE_API	KTabFile		g_SkillLevelSetting;
extern CORE_API	KTabFile		g_NpcSetting;
extern CORE_API	KTabFile		g_NpcImageSetting;
extern KTabFile					g_RankTabSetting;

#ifdef TOOLVERSION
#ifndef __linux
extern CORE_API	KSpriteCache	g_SpriteCache;
#endif
#endif
#ifndef _SERVER
extern KSoundCache		g_SoundCache;

extern KMusic* g_pMusic;

extern unsigned int* g_pAdjustColorTab;
extern unsigned int g_ulAdjustColorCount;
#endif

//#ifdef _DEBUG
extern CORE_API BOOL			g_bDebugScript;
//#endif
extern KTabFile		g_NpcKindFile; //јЗВјNpcИЛОпАаРНОДјю

#ifndef _SERVER
extern BOOL g_bUISelIntelActiveWithServer;//µ±З°СЎФсїтКЗ·сУл·юОсЖч¶ЛЅ»»Ґ
extern BOOL g_bUISpeakActiveWithServer;
extern int g_bUISelLastSelCount;
#endif

#ifdef _SERVER

enum DBMESSAGE
{
	DBMSG_PUSH,
	DBMSG_POP,
};

enum DBI_COMMAND
{
	DBI_PLAYERSAVE,  // ІОКэ1 КЗ·сїЙТФРВЅЁЅЗЉ«
	DBI_PLAYERLOAD,
	DBI_PLAYERDELETE,
	DBI_GETPLAYERLISTFROMACCOUNT,
};
BOOL CORE_API g_AccessDBMsgList(DBMESSAGE Msg, int* pnPlayerIndex, DBI_COMMAND* pnDBICommand, void** ppParam1, void** ppParam2);
extern KLuaScript g_WorldScript;
extern KList g_DBMsgList;

class KDBMsgNode :public KNode
{
public:
	void* pParam1;
	void* pParam2;
	int	   nPlayerIndex;
	DBI_COMMAND Command;
	KDBMsgNode() { pParam1 = pParam2 = NULL; nPlayerIndex = 0;	Command = DBI_PLAYERSAVE; };
};

#endif

#ifndef _SERVER
class KImageNode : public KNode
{
public:
	char	m_szFile[32];
	int		m_nFrame;
	int		m_nXpos;
	int		m_nYpos;
};
#endif

#ifndef _SERVER
extern char* g_GetStringRes(int nStringID, char* szString, int nMaxLen);
#endif

BOOL InitSkillSetting();
BOOL InitMissleSetting();
BOOL InitNpcSetting();
void g_ReleaseCore();
inline int GetRandomNumber(int nMin, int nMax)
{
	return g_Random(nMax - nMin + 1) + nMin;
}
#ifdef _SERVER
void g_SetServer(LPVOID pServer);
extern IServer* g_pServer;
#else
void g_SetClient(LPVOID pClient);
extern IClient* g_pClient;
//extern BOOL	g_bPingReply;
#endif
//---------------------------------------------------------------------------

#include "KPathFix.h"

#ifdef _WIN32
#undef fopen
#define fopen(path, mode) KPathFix::SafeFOpen(path, mode)

#undef _fopen
#define _fopen(path, mode) KPathFix::SafeFOpen(path, mode)
#endif

#endif // KCore_H