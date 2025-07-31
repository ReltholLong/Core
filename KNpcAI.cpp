#include "KCore.h"
#include "KNpc.h"
#include "KNpcSet.h"
#include "KSubWorld.h"
#include "KMath.h"
#include "KObj.h"
#include "KPlayer.h"
#include "KNpcAI.h"

// flying add here, to use math lib
#include <math.h>
extern int GetRandomNumber(int nMin, int nMax);

#define		MAX_FOLLOW_DISTANCE		48
#define		FOLLOW_WALK_DISTANCE	100

KNpcAI NpcAI;

KNpcAI::KNpcAI()
{
	m_nIndex = 0;
	m_bActivate = TRUE;
}

// flying modified this function.
// Jun.4.2003
void KNpcAI::Activate(int nIndex)
{
	m_nIndex = nIndex;	
	if (Npc[m_nIndex].IsPlayer())
	{
		// ÐÂÔöµÄPlayer AIÔÚÕâÀïµ÷ÓÃÊµÏÖ¡£
		ProcessPlayer();
		return;
	}
#ifdef _SERVER
	if (Npc[m_nIndex].m_CurrentLifeMax == 0)
		return;
	int nCurTime = SubWorld[Npc[m_nIndex].m_SubWorldIndex].m_dwCurrentTime;
	if (/*Npc[m_nIndex].m_nPeopleIdx ||*/Npc[m_nIndex].m_NextAITime <= nCurTime)
	{
		Npc[m_nIndex].m_NextAITime = nCurTime + Npc[m_nIndex].m_AIMAXTime;
		switch(Npc[m_nIndex].m_AiMode)
		{
		case 1:
			ProcessAIType01();
			break;
		case 2:
			ProcessAIType02();
			break;
		case 3:
			ProcessAIType03();
			break;
		case 4:
			ProcessAIType04();
			break;
		case 5:
			ProcessAIType05();
			break;
		case 6:
			ProcessAIType06();
			break;
/*		case 7:
			ProcessAIType7();
			break;
		case 8:
			ProcessAIType8();
			break;
		case 9:
			ProcessAIType9();
			break;
		case 10:
			ProcessAIType10();
			break;*/
		default:
			break;
		}
	}
// flying add the code for the macro such as "_CLIENT".
// because this code only run at client.
#else
	if (Npc[m_nIndex].m_Kind > 3 && Npc[m_nIndex].m_AiMode > 10)
	{
		if (CanShowNpc())
		{
			// ÈÃNPCËæ»úÐÝÏ¢Ò»ÏÂ£¬ÊÇ¸öºÃ½¨Òé¡£
			if (GetRandomNumber(0, 1))	
			{
				Npc[m_nIndex].m_AiParam[5] = 0;
				Npc[m_nIndex].m_AiParam[4] = 5;
				return;
			}
			if (!KeepActiveRange())
				ProcessShowNpc();
		}
	}
#endif
}
//---------------------------------------------------------------------
// flying add these functions
// Run at client.
#ifndef _SERVER
// ½ö½öÓÐ»­ÃæÐ§¹ûµÄNPC
int KNpcAI::ProcessShowNpc()
{
    int nResult  = false;
    int nRetCode = false;

	switch (Npc[m_nIndex].m_AiMode)
	{
	// ·ÉÄñÐÍ
	case 11:
		nRetCode = ShowNpcType11();
        if (!nRetCode)
            goto Exit0;
		break;
	// òßòÑÐÍ
	case 12:
		nRetCode = ShowNpcType12();
        if (!nRetCode)
            goto Exit0;
		break;
	// ÓãÀàÐÍ
	case 13:
		nRetCode = ShowNpcType13();
        if (!nRetCode)
            goto Exit0;
		break;
	// ÀÏÊóÐÍ
	case 14:
		nRetCode = ShowNpcType14();
        if (!nRetCode)
            goto Exit0;
		break;
	// ¼¦È®ÐÍ
	case 15:
		nRetCode = ShowNpcType15();
        if (!nRetCode)
            goto Exit0;
		break;
	// ÍÃ×ÓÐÍ
	case 16:
		nRetCode = ShowNpcType16();
        if (!nRetCode)
            goto Exit0;
		break;
	// ºûµûÐÍ
	case 17:
		nRetCode = ShowNpcType17();
        if (!nRetCode)
            goto Exit0;
		break;
	default:
		break;
	}

    nResult = true;
Exit0:
	return nResult;
}

// ·ÉÄñÐÍ
int KNpcAI::ShowNpcType11()
{
    int nResult = false;
    int nRetCode = false;

	KNpc& aNpc = Npc[m_nIndex];
	// Go the distance between P1 to P2	
	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	
	// Ð§¹û¼ÓÇ¿ Ëæ»úµ÷Õû¸ß¶È
	aNpc.m_Height = GetRandomNumber(aNpc.m_AiParam[6] - 4, aNpc.m_AiParam[6]);

	aNpc.GetMpsPos(&nCurX, &nCurY);

	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	
    if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	
    nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);

	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	//if (KeepActiveShowRange())
	//	aNpc.m_Dir += 32;
	aNpc.m_Dir += nOffsetDir;
	if (aNpc.m_Dir < 0)
		aNpc.m_Dir += 64;
	else
		aNpc.m_Dir %= 64;
	
    // ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
    if (!nRetCode)
        goto Exit0;

	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);	

    nResult = true;
Exit0:
	return nResult;
}

// òßòÑÐÍ
// done
int KNpcAI::ShowNpcType12()
{
    int nResult = false;
    int nRetCode = false;

	// Go the distance between P1 to P2	
	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	KNpc& aNpc = Npc[m_nIndex];

	// Ð§¹û¼ÓÇ¿ Ëæ»úµ÷Õû¸ß¶È
	aNpc.m_Height = GetRandomNumber(aNpc.m_AiParam[6] - 4, aNpc.m_AiParam[6]);

	aNpc.GetMpsPos(&nCurX, &nCurY);
		
	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);

	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}
	aNpc.m_Dir += nOffsetDir;
	if (aNpc.m_Dir < 0)
		aNpc.m_Dir += 64;
	else
		aNpc.m_Dir %= 64;

	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	if (!nRetCode)
		goto Exit0;
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);

	nResult = true;
Exit0:
	return nResult;
}

// ÓãÀàÐÍ
// done
int KNpcAI::ShowNpcType13()
{
	int nResult  = false;
	int nRetCode = false;
	// Go the distance between P1 to P2	
	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	int nIndex = 0;
	KNpc& aNpc = Npc[m_nIndex];

	aNpc.GetMpsPos(&nCurX, &nCurY);

	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);

	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}
	//if (KeepActiveShowRange())
	//	aNpc.m_Dir += 32;
	// ¸½½üÓÐÍæ¼Ò
	nIndex = IsPlayerCome();
	if (nIndex > 0)
	{
		// do flee
		DoShowFlee(nIndex);
		goto Exit0;
	}
	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);

	nResult = true;
Exit0:
	return nResult;
}

// ÀÏÊóÐÍ
// done
int KNpcAI::ShowNpcType14()
{
	int nResult  = false;
	int nRetCode = false;

	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nRandom = 0;
	int nOffsetDir = 0;
	KNpc& aNpc = Npc[m_nIndex];

	nRandom = GetRandomNumber(1, 10);
	// µôÍ·¾ÍÅÜ
	if (nRandom < 4)
		nDistance = -nDistance;
	// à»à»·¢´ô
	else if (nRandom < 7)
	{
		aNpc.SendCommand(do_stand);
		goto Exit0;
	}
	aNpc.GetMpsPos(&nCurX, &nCurY);
	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);
	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}

	aNpc.m_Dir += nOffsetDir;
	if (aNpc.m_Dir < 0)
		aNpc.m_Dir += 64;
	else
		aNpc.m_Dir %= 64;
	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	if (!nRetCode)
		goto Exit0;
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);

	nResult = true;
Exit0:
	return nResult;
}

// ¼¦È®ÐÍ
int KNpcAI::ShowNpcType15()
{
	int nResult  = false;
	int nRetCode = false;
	// Go the distance between P1 to P2	
	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	int nIndex = 0;
	KNpc& aNpc = Npc[m_nIndex];

	aNpc.GetMpsPos(&nCurX, &nCurY);

	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);

	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}
	//if (KeepActiveShowRange())
	//	aNpc.m_Dir += 32;
	// ¸½½üÓÐÍæ¼Ò
	nIndex = IsPlayerCome();
	if (nIndex > 0)
	{
		// do flee
		DoShowFlee(nIndex);
		goto Exit0;
	}
	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);

	nResult = true;
Exit0:
	return nResult;
}

// ÍÃ×ÓÐÍ
int KNpcAI::ShowNpcType16()
{
	int nResult  = false;
	int nRetCode = false;

	// Go the distance between P1 to P2
	register int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	int nIndex = 0;
	KNpc& aNpc = Npc[m_nIndex];

	aNpc.GetMpsPos(&nCurX, &nCurY);

	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);
	// ¸½½üÓÐÍæ¼Ò
	nIndex = IsPlayerCome();
	if (nIndex > 0)
	{
		// do flee
		nRetCode = DoShowFlee(nIndex);
		if (!nRetCode)
			goto Exit0;		
		goto Exit1;
	}

	// ¼ÆËã¾àÀë
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}

	// ¼ÆËãÐÂ½Ç¶È
	//if (KeepActiveShowRange())
	//	aNpc.m_Dir += 32;
	aNpc.m_Dir += GetRandomNumber(0, 6);
	aNpc.m_Dir %= 64;
	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	if (!nRetCode)
		goto Exit0;
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);

Exit1:	
	nResult = true;
Exit0:
	return nResult;
}

// ºûµûÐÍ
int KNpcAI::ShowNpcType17()
{
	int nResult  = false;
	int nRetCode = false;

	// Go the distance between P1 to P2
	int nDistance = 0;
	int nDesX = 0;
	int nDesY = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nOffX = 0;
	int nOffY = 0;
	int nOffsetDir = 0;
	KNpc& aNpc = Npc[m_nIndex];

	// Ð§¹û¼ÓÇ¿ Ëæ»úµ÷Õû¸ß¶È
	aNpc.m_Height = GetRandomNumber(aNpc.m_AiParam[6] - 4, aNpc.m_AiParam[6]);

	aNpc.GetMpsPos(&nCurX, &nCurY);
		
	// ¼ÆËãÐÂ½Ç¶È ºÍ ¾àÀë
	if (aNpc.m_AiParam[3] > 0)
		nOffsetDir = GetRandomNumber(aNpc.m_AiParam[3], aNpc.m_AiParam[2]);
	else
		nOffsetDir = aNpc.m_AiParam[2];
	if (GetRandomNumber(0, 1))
		nOffsetDir = -nOffsetDir;
	nDistance = GetRandomNumber(aNpc.m_AiParam[0] - aNpc.m_AiParam[1], aNpc.m_AiParam[0]);	

	// È¡µÃÔË¶¯ËùÐèµÄÊ±¼ä£¬±£´æÔÚ²ÎÊý±íÖÐ
	if (aNpc.m_CurrentWalkSpeed > 0)
	{
		aNpc.m_AiParam[4] = (int) nDistance / aNpc.m_CurrentWalkSpeed;
		aNpc.m_AiParam[5] = 0;
	}
	else
	{
		aNpc.m_AiParam[4] = 0;
		aNpc.m_AiParam[5] = 0;
	}
	if (KeepActiveRange())
	{
		//aNpc.SendCommand(do_walk, aNpc.m_OriginX, aNpc.m_OriginY);
		goto Exit0;
		//aNpc.m_Dir += 32;
	}
	aNpc.m_Dir += nOffsetDir;
	//aNpc.m_Dir += GetRandomNumber(32, 64);
	if (aNpc.m_Dir < 0)
		aNpc.m_Dir += 64;
	else
		aNpc.m_Dir %= 64;
	// ¸ù¾ÝÈý½Çº¯Êý¼ÆËãÆ«ÒÆµÄX¡¢YÊýÖµ
	nRetCode = GetNpcMoveOffset(aNpc.m_Dir, nDistance, &nOffX, &nOffY);
	if (!nRetCode)
		goto Exit0;
	// »ñÈ¡Ä¿±ê×ø±ê
	nDesX = nCurX + nOffX;
	nDesY = nCurY + nOffY;
	aNpc.SendCommand(do_walk, nDesX, nDesY);
	
	nResult = true;
Exit0:
	return nResult;
}
#endif
//---------------------------------------------------------------------
// Player AI add here.
// flying comment
void KNpcAI::ProcessPlayer()
{
#ifdef _SERVER
	TriggerObjectTrap();
	TriggerMapTrap();
#else
	int i = Npc[m_nIndex].m_nPeopleIdx;
	if (i > 0)
	{
		FollowPeople(i);
	}
	i = Npc[m_nIndex].m_nObjectIdx;
	if (i > 0)
	{
		FollowObject(i);
	}
#endif
}

#ifndef _SERVER
void KNpcAI::FollowObject(int nIdx)
{
	int nX1, nY1, nX2, nY2;
	Npc[m_nIndex].GetMpsPos(&nX1, &nY1);
	Object[nIdx].GetMpsPos(&nX2, &nY2);

	if ((nX1 - nX2) * (nX1 - nX2) + (nY1 - nY2) * (nY1 - nY2) < PLAYER_PICKUP_CLIENT_DISTANCE * PLAYER_PICKUP_CLIENT_DISTANCE)
	{
//#ifndef _SERVER
		Player[CLIENT_PLAYER_INDEX].CheckObject(nIdx);
//#endif
	}
}
#endif

#ifndef _SERVER
void KNpcAI::FollowPeople(int nIdx)
{
	if (Npc[nIdx].m_Doing == do_death || Npc[nIdx].m_Doing == do_revive)
	{
		Npc[m_nIndex].m_nPeopleIdx = 0;
		return;
	}

	// È¡µÃµ½Ä¿±êµÄ¾àÀë
	int distance = NpcSet.GetDistance(nIdx, m_nIndex);
	int	nRelation = NpcSet.GetRelation(m_nIndex, nIdx);

	// Ð¡ÓÚ¶Ô»°°ë¾¶¾Í¿ªÊ¼¶Ô»°
	if ((Npc[nIdx].m_Kind == kind_dialoger))
	{
		if (distance <= Npc[nIdx].m_DialogRadius)
		{
			int x, y;
			SubWorld[Npc[m_nIndex].m_SubWorldIndex].Map2Mps(Npc[m_nIndex].m_RegionIndex, Npc[m_nIndex].m_MapX, Npc[m_nIndex].m_MapY, Npc[m_nIndex].m_OffX, Npc[m_nIndex].m_OffY, &x, &y);
			Npc[m_nIndex].SendCommand(do_walk, x,y);
			
			// Send Command to Server
			SendClientCmdWalk(x, y);
			Player[CLIENT_PLAYER_INDEX].DialogNpc(nIdx);
			Npc[Player[CLIENT_PLAYER_INDEX].m_nIndex].m_nPeopleIdx = 0;
			Npc[nIdx].TurnTo(Player[CLIENT_PLAYER_INDEX].m_nIndex);
			
			return;
		}
	}

	// ¾àÀëÐ¡ÓÚ¹¥»÷·¶Î§¾Í¿ªÊ¼¹¥»÷
	if (nRelation == relation_enemy)
	{
		if (distance <= Npc[m_nIndex].m_CurrentAttackRadius)
		{
			Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, nIdx);

			// Send to Server
			SendClientCmdSkill(Npc[m_nIndex].m_ActiveSkillID, -1, Npc[nIdx].m_dwID);
		}
		// à»à»×·
		else
		{
			int nDesX, nDesY;
			Npc[nIdx].GetMpsPos(&nDesX, &nDesY);
			// modify by spe 2003/06/13
			if (Player[CLIENT_PLAYER_INDEX].m_RunStatus)
			{
				Npc[m_nIndex].SendCommand(do_run, nDesX, nDesY);			
				SendClientCmdRun(nDesX, nDesY);
			}
			else
			{
				Npc[m_nIndex].SendCommand(do_walk, nDesX, nDesY);
				SendClientCmdWalk(nDesX, nDesY);
			}
		}
		return;
	}
	// ¸úËæ
	if (Npc[nIdx].m_Kind == kind_player)
	{
		// flow
		int nDesX, nDesY;
		if (distance < MAX_FOLLOW_DISTANCE)
		{
			Npc[this->m_nIndex].GetMpsPos(&nDesX, &nDesY);
			Npc[m_nIndex].SendCommand(do_walk, nDesX, nDesY);
			SendClientCmdWalk(nDesX, nDesY);
		}
		else
		{
			Npc[nIdx].GetMpsPos(&nDesX, &nDesY);
			if (distance < FOLLOW_WALK_DISTANCE ||
				!Player[CLIENT_PLAYER_INDEX].m_RunStatus)
			{
				Npc[m_nIndex].SendCommand(do_walk, nDesX, nDesY);
				SendClientCmdWalk(nDesX, nDesY);
			}
			else
			{
				Npc[m_nIndex].SendCommand(do_run, nDesX, nDesY);			
				SendClientCmdRun(nDesX, nDesY);
			}
		}
	}
	return;
}
#endif

void KNpcAI::TriggerMapTrap()
{
	// Luu fight mode tru?c khi check
	int oldFightMode = (m_nIndex > 0) ? Npc[m_nIndex].m_FightMode : 0;

	Npc[m_nIndex].CheckTrap();

	// CH? LOG KHI FIGHT MODE THAY Ð?I
	if (m_nIndex > 0 && Npc[m_nIndex].IsPlayer())
	{
		int newFightMode = Npc[m_nIndex].m_FightMode;
		if (oldFightMode != newFightMode)
		{
			int x, y;
			Npc[m_nIndex].GetMpsPos(&x, &y);

			g_DebugLog("[FIGHT_MODE_CHANGE] Player:%s %d->%d at (%d,%d) Trap:%d",
				Npc[m_nIndex].Name, oldFightMode, newFightMode,
				x / 32, y / 32, Npc[m_nIndex].m_TrapScriptID);

			// Ð?m combat mode changes
			static int combatChanges = 0;
			static DWORD firstChangeTime = 0;
			DWORD currentTime = GetCurrentTime();

			if (firstChangeTime == 0)
				firstChangeTime = currentTime;

			combatChanges++;

			// C?nh báo n?u quá nhi?u
			if (combatChanges > 10 && (currentTime - firstChangeTime < 30000)) // 10 l?n trong 30 giây
			{
				g_DebugLog("[BOT_COMBAT_TOGGLE] Player:%s %d combat changes in 30 seconds",
					Npc[m_nIndex].Name, combatChanges);
			}

			// Reset counter m?i phút
			if (currentTime - firstChangeTime > 60000)
			{
				combatChanges = 0;
				firstChangeTime = currentTime;
			}
		}
	}
}

void KNpcAI::TriggerObjectTrap()
{
	return;
}

int KNpcAI::GetNearestNpc(int nRelation)
{
	int nRangeX = Npc[m_nIndex].m_VisionRadius;
	int	nRangeY = nRangeX;
	int	nSubWorld = Npc[m_nIndex].m_SubWorldIndex;
	int	nRegion = Npc[m_nIndex].m_RegionIndex;
	int	nMapX = Npc[m_nIndex].m_MapX;
	int	nMapY = Npc[m_nIndex].m_MapY;
	int	nRet;
	int	nRMx, nRMy, nSearchRegion;

	nRangeX = nRangeX / SubWorld[nSubWorld].m_nCellWidth;
	nRangeY = nRangeY / SubWorld[nSubWorld].m_nCellHeight;	

	// ¼ì²éÊÓÒ°·¶Î§ÄÚµÄ¸ñ×ÓÀïµÄNPC
	for (int i = 0; i < nRangeX; i++)	// i, jÓÉ0¿ªÊ¼¶ø²»ÊÇ´Ó-range¿ªÊ¼ÊÇÒª±£Ö¤Nearest
	{
		for (int j = 0; j < nRangeY; j++)
		{
			// È¥µô±ß½Ç¼¸¸ö¸ñ×Ó£¬±£Ö¤ÊÓÒ°ÊÇÍÖÔ²ÐÎ
			if ((i * i + j * j) > nRangeX * nRangeX)
				continue;

			// È·¶¨Ä¿±ê¸ñ×ÓÊµ¼ÊµÄREGIONºÍ×ø±êÈ·¶¨
			nRMx = nMapX + i;
			nRMy = nMapY + j;
			nSearchRegion = nRegion;
			if (nRMx < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[2];
				nRMx += SubWorld[nSubWorld].m_nRegionWidth;
			}
			else if (nRMx >= SubWorld[nSubWorld].m_nRegionWidth)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[6];
				nRMx -= SubWorld[nSubWorld].m_nRegionWidth;
			}
			if (nSearchRegion == -1)
				continue;
			if (nRMy < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[4];
				nRMy += SubWorld[nSubWorld].m_nRegionHeight;
			}
			else if (nRMy >= SubWorld[nSubWorld].m_nRegionHeight)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[0];
				nRMy -= SubWorld[nSubWorld].m_nRegionHeight;
			}
			if (nSearchRegion == -1)
				continue;
			// ´ÓREGIONµÄNPCÁÐ±íÖÐ²éÕÒÂú×ãÌõ¼þµÄNPC			
			nRet = SubWorld[nSubWorld].m_Region[nSearchRegion].FindNpc(nRMx, nRMy, m_nIndex, nRelation);
			if (nRet > 0)
				return nRet;
			
			// È·¶¨Ä¿±ê¸ñ×ÓÊµ¼ÊµÄREGIONºÍ×ø±êÈ·¶¨
			nRMx = nMapX - i;
			nRMy = nMapY + j;
			nSearchRegion = nRegion;
			if (nRMx < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[2];
				nRMx += SubWorld[nSubWorld].m_nRegionWidth;
			}
			else if (nRMx >= SubWorld[nSubWorld].m_nRegionWidth)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[6];
				nRMx -= SubWorld[nSubWorld].m_nRegionWidth;
			}
			if (nSearchRegion == -1)
				continue;
			if (nRMy < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[4];
				nRMy += SubWorld[nSubWorld].m_nRegionHeight;
			}
			else if (nRMy >= SubWorld[nSubWorld].m_nRegionHeight)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[0];
				nRMy -= SubWorld[nSubWorld].m_nRegionHeight;
			}
			if (nSearchRegion == -1)
				continue;
			// ´ÓREGIONµÄNPCÁÐ±íÖÐ²éÕÒÂú×ãÌõ¼þµÄNPC			
			nRet = SubWorld[nSubWorld].m_Region[nSearchRegion].FindNpc(nRMx, nRMy, m_nIndex, nRelation);
			if (nRet > 0)
				return nRet;

			// È·¶¨Ä¿±ê¸ñ×ÓÊµ¼ÊµÄREGIONºÍ×ø±êÈ·¶¨
			nRMx = nMapX - i;
			nRMy = nMapY - j;
			nSearchRegion = nRegion;
			if (nRMx < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[2];
				nRMx += SubWorld[nSubWorld].m_nRegionWidth;
			}
			else if (nRMx >= SubWorld[nSubWorld].m_nRegionWidth)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[6];
				nRMx -= SubWorld[nSubWorld].m_nRegionWidth;
			}
			if (nSearchRegion == -1)
				continue;
			if (nRMy < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[4];
				nRMy += SubWorld[nSubWorld].m_nRegionHeight;
			}
			else if (nRMy >= SubWorld[nSubWorld].m_nRegionHeight)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[0];
				nRMy -= SubWorld[nSubWorld].m_nRegionHeight;
			}
			if (nSearchRegion == -1)
				continue;
			// ´ÓREGIONµÄNPCÁÐ±íÖÐ²éÕÒÂú×ãÌõ¼þµÄNPC			
			nRet = SubWorld[nSubWorld].m_Region[nSearchRegion].FindNpc(nRMx, nRMy, m_nIndex, nRelation);
			if (nRet > 0)
				return nRet;

			// È·¶¨Ä¿±ê¸ñ×ÓÊµ¼ÊµÄREGIONºÍ×ø±êÈ·¶¨
			nRMx = nMapX + i;
			nRMy = nMapY - j;
			nSearchRegion = nRegion;			
			if (nRMx < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[2];
				nRMx += SubWorld[nSubWorld].m_nRegionWidth;
			}
			else if (nRMx >= SubWorld[nSubWorld].m_nRegionWidth)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[6];
				nRMx -= SubWorld[nSubWorld].m_nRegionWidth;
			}
			if (nSearchRegion == -1)
				continue;
			if (nRMy < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[4];
				nRMy += SubWorld[nSubWorld].m_nRegionHeight;
			}
			else if (nRMy >= SubWorld[nSubWorld].m_nRegionHeight)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[0];
				nRMy -= SubWorld[nSubWorld].m_nRegionHeight;
			}
			if (nSearchRegion == -1)
				continue;
			// ´ÓREGIONµÄNPCÁÐ±íÖÐ²éÕÒÂú×ãÌõ¼þµÄNPC
			nRet = SubWorld[nSubWorld].m_Region[nSearchRegion].FindNpc(nRMx, nRMy, m_nIndex, nRelation);
			if (nRet > 0)
				return nRet;
		}
	}
	return 0;
}

#ifndef _SERVER
// flying add this
// ²éÕÒÀëÄ³¸öNPC×î½üµÄÍæ¼Ò
int KNpcAI::IsPlayerCome()
{
	int nResult = 0;
	int nPlayer = 0;
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;
	int nDistance = 0;

	nPlayer = Player[CLIENT_PLAYER_INDEX].m_nIndex;
	nDistance = NpcSet.GetDistance(nPlayer, m_nIndex);
	// ¼¦¿´µÄµ½µÄÍæ¼Ò
	if (nDistance < Npc[m_nIndex].m_VisionRadius)
	{
		// ·Ö±ð´¦Àí×ßºÍÅÜ
		if (Player[CLIENT_PLAYER_INDEX].m_RunStatus ||
			Npc[m_nIndex].m_CurrentVisionRadius > nDistance * 4)
		{
			nResult = nPlayer;
		}
	}
	return nResult;
}
#endif

int KNpcAI::GetNpcNumber(int nRelation)
{
	int nRangeX = Npc[m_nIndex].m_VisionRadius;
	int	nRangeY = nRangeX;
	int	nSubWorld = Npc[m_nIndex].m_SubWorldIndex;
	int	nRegion = Npc[m_nIndex].m_RegionIndex;
	int	nMapX = Npc[m_nIndex].m_MapX;
	int	nMapY = Npc[m_nIndex].m_MapY;
	int	nRet = 0;
	int	nRMx, nRMy, nSearchRegion;

	nRangeX = nRangeX / SubWorld[nSubWorld].m_nCellWidth;
	nRangeY = nRangeY / SubWorld[nSubWorld].m_nCellHeight;

	// ¼ì²éÊÓÒ°·¶Î§ÄÚµÄ¸ñ×ÓÀïµÄNPC
	for (int i = -nRangeX; i < nRangeX; i++)
	{
		for (int j = -nRangeY; j < nRangeY; j++)
		{
			// È¥µô±ß½Ç¼¸¸ö¸ñ×Ó£¬±£Ö¤ÊÓÒ°ÊÇÍÖÔ²ÐÎ
			if ((i * i + j * j) > nRangeX * nRangeX)
				continue;

			// È·¶¨Ä¿±ê¸ñ×ÓÊµ¼ÊµÄREGIONºÍ×ø±êÈ·¶¨
			nRMx = nMapX + i;
			nRMy = nMapY + j;
			nSearchRegion = nRegion;
			if (nRMx < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[2];
				nRMx += SubWorld[nSubWorld].m_nRegionWidth;
			}
			else if (nRMx >= SubWorld[nSubWorld].m_nRegionWidth)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[6];
				nRMx -= SubWorld[nSubWorld].m_nRegionWidth;
			}
			if (nSearchRegion == -1)
				continue;
			if (nRMy < 0)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[4];
				nRMy += SubWorld[nSubWorld].m_nRegionHeight;
			}
			else if (nRMy >= SubWorld[nSubWorld].m_nRegionHeight)
			{
				nSearchRegion = SubWorld[nSubWorld].m_Region[nSearchRegion].m_nConnectRegion[0];
				nRMy -= SubWorld[nSubWorld].m_nRegionHeight;
			}
			if (nSearchRegion == -1)
				continue;
			// ´ÓREGIONµÄNPCÁÐ±íÖÐ²éÕÒÂú×ãÌõ¼þµÄNPC			
			int nNpcIdx = SubWorld[nSubWorld].m_Region[nSearchRegion].FindNpc(nRMx, nRMy, m_nIndex, nRelation);
			if (nNpcIdx > 0)
				nRet++;
		}
	}
	return nRet;
}

void KNpcAI::KeepAttackRange(int nEnemy, int nRange)
{
	int nX1, nY1, nX2, nY2, nDir, nWantX, nWantY;

	Npc[m_nIndex].GetMpsPos(&nX1, &nY1);
	Npc[nEnemy].GetMpsPos(&nX2, &nY2);
	nDir = g_GetDirIndex(nX1, nY1, nX2, nY2);

	nWantX = nX2 - ((nRange * g_DirCos(nDir, 64)) >> 10);
	nWantY = nY2 - ((nRange * g_DirSin(nDir, 64)) >> 10);

	Npc[m_nIndex].SendCommand(do_walk, nWantX, nWantY);
}

void KNpcAI::FollowAttack(int i)
{
	if ( Npc[i].m_RegionIndex < 0 )
		return;

	int distance = NpcSet.GetDistance(m_nIndex, i);

#define	MINI_ATTACK_RANGE	32

	if (distance <= MINI_ATTACK_RANGE)
	{
		KeepAttackRange(i, MINI_ATTACK_RANGE);
		return;
	}
	// Attack Enemy
	if (distance <= Npc[m_nIndex].m_CurrentAttackRadius && InEyeshot(i))
	{
		Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, i);
		return;
	}

	// Move to Enemy
	int x, y;
	Npc[i].GetMpsPos(&x, &y);

	Npc[m_nIndex].SendCommand(do_walk, x, y);
}

BOOL KNpcAI::InEyeshot(int nIdx)
{
	int distance = NpcSet.GetDistance(nIdx, m_nIndex);

	return (Npc[m_nIndex].m_VisionRadius > distance);
}

void KNpcAI::CommonAction()
{
	// Èç¹ûÊÇ¶Ô»°ÀàµÄNPC£¬¾ÍÔ­µØ²»¶¯
	if (Npc[m_nIndex].m_Kind == kind_dialoger)
	{
		Npc[m_nIndex].SendCommand(do_stand);
		return;
	}
	int	nOffX, nOffY;
	if (g_RandPercent(80))
	{
		nOffX = 0;
		nOffY = 0;
	}
	else
	{
		
		nOffX = g_Random(Npc[m_nIndex].m_CurrentActiveRadius / 2);
		nOffY = g_Random(Npc[m_nIndex].m_CurrentActiveRadius / 2);
		if (nOffX & 1)
		{
			nOffX = - nOffX;
		}
		if (nOffY & 1)
		{
			nOffY = - nOffY;
		}
	}
	Npc[m_nIndex].SendCommand(do_walk, Npc[m_nIndex].m_OriginX + nOffX, Npc[m_nIndex].m_OriginY + nOffY);
}

BOOL KNpcAI::KeepActiveRange()
{
	int x, y;
	
	Npc[m_nIndex].GetMpsPos(&x, &y);
	int	nRange = g_GetDistance(Npc[m_nIndex].m_OriginX, Npc[m_nIndex].m_OriginY, x, y);

	// ·¢ÏÖ³¬³ö»î¶¯·¶Î§£¬°Ñµ±Ç°»î¶¯·¶Î§ËõÐ¡£¬±ÜÃâÔÚ»î¶¯·¶Î§±ßÔµÀ´»Ø»Î¡£
	if (Npc[m_nIndex].m_ActiveRadius < nRange)
	{
		Npc[m_nIndex].m_CurrentActiveRadius = Npc[m_nIndex].m_ActiveRadius / 2;
	}

	// ·¢ÏÖ³¬³öµ±Ç°»î¶¯·¶Î§£¬Íù»Ø×ß
	if (Npc[m_nIndex].m_CurrentActiveRadius < nRange)
	{
		Npc[m_nIndex].SendCommand(do_walk, Npc[m_nIndex].m_OriginX, Npc[m_nIndex].m_OriginY);
		return TRUE;
	}
	else	// ÔÚµ±Ç°»î¶¯·¶Î§ÄÚ£¬»Ö¸´µ±Ç°»î¶¯·¶Î§´óÐ¡¡£
	{
		Npc[m_nIndex].m_CurrentActiveRadius = Npc[m_nIndex].m_ActiveRadius;
		return FALSE;
	}
}

#ifndef _SERVER
// 15/16 AiMode NPCµÄÌÓÒÝ¶¯×÷
int KNpcAI::DoShowFlee(int nIdx)
{
	int nResult  = false;
	int nRetCode = false;
	
	int x1, y1, x2, y2;
	int nDistance = Npc[m_nIndex].m_AiParam[6];

	Npc[m_nIndex].GetMpsPos(&x1, &y1);
	//Npc[nIdx].GetMpsPos(&x2, &y2);
	Npc[m_nIndex].m_Dir = Npc[nIdx].m_Dir;
	nRetCode = GetNpcMoveOffset(Npc[m_nIndex].m_Dir, nDistance, &x2, &y2);
	if (!nRetCode)
		goto Exit0;
	Npc[m_nIndex].m_AiParam[4] = (int) nDistance / Npc[m_nIndex].m_WalkSpeed;
	Npc[m_nIndex].m_AiParam[5] = 0;
	Npc[m_nIndex].SendCommand(do_walk, x1 + x2, y1 + y2);

	nResult = true;
Exit0:
	return nResult;
}

#endif

// ÌÓÀëNpc[nIdx]
void KNpcAI::Flee(int nIdx)
{
	int x1, y1, x2, y2;

	Npc[m_nIndex].GetMpsPos(&x1, &y1);
	Npc[nIdx].GetMpsPos(&x2, &y2);

	x1 = x1 * 2 - x2;
	y1 = y1 * 2 - y2;

	Npc[m_nIndex].SendCommand(do_walk, x1, y1);
}

//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨Ö÷¶¯Àà1
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1¡¢2¡¢3¡¢4] ËÄÖÖ¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ1 2 3 4
//	m_AiParam[5¡¢6] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType01()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;
	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// Èç¹ûÔ­±¾Ã»ÓÐËø¶¨µÐÈË»òÕßÕâ¸öµÐÈËÅÜÌ«Ô¶£¬ÖØÐÂËø¶¨µÐÈË
	if (nEnemyIdx <= 0 || Npc[nEnemyIdx].m_dwID <= 0 || !InEyeshot(nEnemyIdx) )
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}

	// ÖÜÎ§Ã»ÓÐµÐÈË£¬Ò»¶¨¸ÅÂÊ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[5])	// ´ý»ú
			return;
		if (nRand < pAIParam[5] + pAIParam[6])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[1])
	{
		if (!Npc[m_nIndex].SetActiveSkill(1))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2] + pAIParam[3])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2] + pAIParam[3] + pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}

	FollowAttack(nEnemyIdx);
}


//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨Ö÷¶¯Àà2
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1] Ê£ÓàÉúÃüµÍÓÚÕâ¸ö°Ù·Ö±ÈµÄÊ±ºòÖ´ÐÐÏàÓ¦´¦Àí
//	m_AiParam[2] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖµÄÊ±ºòÊÇ·ñÖ´ÐÐÏàÓ¦´¦ÀíµÄ¸ÅÂÊ
//	m_AiParam[3] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖ²¢¾ö¶¨ÒªÖ´ÐÐÏàÓ¦´¦Àí£¬Ê¹ÓÃ»Ø¸´¼¼ÄÜµÄ¸ÅÂÊ ¶ÔÓ¦SkillListÀïÃæµÄ¼¼ÄÜ 1
//	m_AiParam[4¡¢5¡¢6] ÈýÖÖ¹¥»÷¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ 2 3 4
//	m_AiParam[7¡¢8] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType02()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;
	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// Èç¹ûÔ­±¾Ã»ÓÐËø¶¨µÐÈË»òÕßÕâ¸öµÐÈËÅÜÌ«Ô¶£¬ÖØÐÂËø¶¨µÐÈË
	if (nEnemyIdx <= 0 || Npc[nEnemyIdx].m_dwID <= 0 || !InEyeshot(nEnemyIdx) )
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}

	// ÖÜÎ§Ã»ÓÐµÐÈË£¬Ò»¶¨¸ÅÂÊ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// ¼ì²âÊ£ÓàÉúÃüÊÇ·ñ·ûºÏÌõ¼þ£¬ÉúÃüÌ«ÉÙÒ»¶¨¸ÅÂÊÊ¹ÓÃ²¹Ñª¼¼ÄÜ»òÌÓÅÜ
	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[1])
	{
		if (g_RandPercent(pAIParam[2]))	// ÊÇ·ñÊ¹ÓÃ²¹Ñª¼¼ÄÜ»òÌÓÅÜ
		{
			if (Npc[m_nIndex].m_AiAddLifeTime < pAIParam[9] && g_RandPercent(pAIParam[3]))	// Ê¹ÓÃ²¹Ñª¼¼ÄÜ
			{
				Npc[m_nIndex].SetActiveSkill(1);
				Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, m_nIndex);
				Npc[m_nIndex].m_AiAddLifeTime++;
				return;
			}
			else	// ÌÓÅÜ
			{
				Flee(nEnemyIdx);
				return;
			}
		}
	}

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[7])	// ´ý»ú
			return;
		if (nRand < pAIParam[7] + pAIParam[8])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5] + pAIParam[6])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}
	FollowAttack(nEnemyIdx);
}

//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨Ö÷¶¯Àà3
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1] Ê£ÓàÉúÃüµÍÓÚÕâ¸ö°Ù·Ö±ÈµÄÊ±ºòÖ´ÐÐÏàÓ¦´¦Àí
//	m_AiParam[2] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖµÄÊ±ºòÊÇ·ñÖ´ÐÐÏàÓ¦´¦ÀíµÄ¸ÅÂÊ
//	m_AiParam[3] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖ²¢¾ö¶¨ÒªÖ´ÐÐÏàÓ¦´¦Àí£¬Ê¹ÓÃ¹¥»÷¼¼ÄÜµÄ¸ÅÂÊ ¶ÔÓ¦SkillListÀïÃæµÄ¼¼ÄÜ 1
//	m_AiParam[4¡¢5¡¢6] ÈýÖÖ¹¥»÷¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ 2 3 4
//	m_AiParam[7¡¢8] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType03()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;
	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// Èç¹ûÔ­±¾Ã»ÓÐËø¶¨µÐÈË»òÕßÕâ¸öµÐÈËÅÜÌ«Ô¶£¬ÖØÐÂËø¶¨µÐÈË
	if (nEnemyIdx <= 0 || Npc[nEnemyIdx].m_dwID <= 0 || !InEyeshot(nEnemyIdx) )
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}

	// ÖÜÎ§Ã»ÓÐµÐÈË£¬Ò»¶¨¸ÅÂÊ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// ¼ì²âÊ£ÓàÉúÃüÊÇ·ñ·ûºÏÌõ¼þ£¬ÉúÃüÌ«ÉÙÒ»¶¨¸ÅÂÊÊ¹ÓÃ¹¥»÷¼¼ÄÜ»òÌÓÅÜ
	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[1])
	{
		if (g_RandPercent(pAIParam[2]))	// ÊÇ·ñÊ¹ÓÃ¹¥»÷¼¼ÄÜ»òÌÓÅÜ
		{
			if (g_RandPercent(pAIParam[3]))	// Ê¹ÓÃ¹¥»÷¼¼ÄÜ
			{
				Npc[m_nIndex].SetActiveSkill(1);
				FollowAttack(nEnemyIdx);
				return;
			}
			else	// ÌÓÅÜ
			{
				Flee(nEnemyIdx);
				return;
			}
		}
	}

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[7])	// ´ý»ú
			return;
		if (nRand < pAIParam[7] + pAIParam[8])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5] + pAIParam[6])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}
	FollowAttack(nEnemyIdx);
}

//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨±»¶¯Àà1
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1¡¢2¡¢3¡¢4] ËÄÖÖ¹¥»÷¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ 1 2 3 4
//	m_AiParam[5¡¢6] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType04()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// ÊÇ·ñÊÜµ½¹¥»÷£¬·ñ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[5])	// ´ý»ú
			return;
		if (nRand < pAIParam[5] + pAIParam[6])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[1])
	{
		if (!Npc[m_nIndex].SetActiveSkill(1))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2] + pAIParam[3])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[1] + pAIParam[2] + pAIParam[3] + pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}
	FollowAttack(nEnemyIdx);
}

//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨±»¶¯Àà2
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1] Ê£ÓàÉúÃüµÍÓÚÕâ¸ö°Ù·Ö±ÈµÄÊ±ºòÖ´ÐÐÏàÓ¦´¦Àí
//	m_AiParam[2] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖµÄÊ±ºòÊÇ·ñÖ´ÐÐÏàÓ¦´¦ÀíµÄ¸ÅÂÊ
//	m_AiParam[3] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖ²¢¾ö¶¨ÒªÖ´ÐÐÏàÓ¦´¦Àí£¬Ê¹ÓÃ»Ø¸´¼¼ÄÜµÄ¸ÅÂÊ ¶ÔÓ¦SkillListÀïÃæµÄ¼¼ÄÜ 1
//	m_AiParam[4¡¢5¡¢6] ÈýÖÖ¹¥»÷¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ 2 3 4
//	m_AiParam[7¡¢8] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType05()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// ÊÇ·ñÊÜµ½¹¥»÷£¬·ñ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	// ¼ì²âÊ£ÓàÉúÃüÊÇ·ñ·ûºÏÌõ¼þ£¬ÉúÃüÌ«ÉÙÒ»¶¨¸ÅÂÊÊ¹ÓÃ²¹Ñª¼¼ÄÜ»òÌÓÅÜ
	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[1])
	{
		if (g_RandPercent(pAIParam[2]))	// ÊÇ·ñÊ¹ÓÃ²¹Ñª¼¼ÄÜ»òÌÓÅÜ
		{
			if (Npc[m_nIndex].m_AiAddLifeTime < pAIParam[9] && g_RandPercent(pAIParam[3]))	// Ê¹ÓÃ²¹Ñª¼¼ÄÜ
			{
				Npc[m_nIndex].m_AiAddLifeTime++;
				Npc[m_nIndex].SetActiveSkill(1);
				Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, m_nIndex);
				return;
			}
			else	// ÌÓÅÜ
			{
				Flee(nEnemyIdx);
				return;
			}
		}
	}

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[7])	// ´ý»ú
			return;
		if (nRand < pAIParam[7] + pAIParam[8])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5] + pAIParam[6])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}
	FollowAttack(nEnemyIdx);
}

//------------------------------------------------------------------------------
//	¹¦ÄÜ£ºÆÕÍ¨±»¶¯Àà3
//	m_AiParam[0] ÎÞµÐÈËÊ±ºòµÄÑ²Âß¸ÅÂÊ
//	m_AiParam[1] Ê£ÓàÉúÃüµÍÓÚÕâ¸ö°Ù·Ö±ÈµÄÊ±ºòÖ´ÐÐÏàÓ¦´¦Àí
//	m_AiParam[2] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖµÄÊ±ºòÊÇ·ñÖ´ÐÐÏàÓ¦´¦ÀíµÄ¸ÅÂÊ
//	m_AiParam[3] ÔÚm_AiParam[1]µÄÇé¿ö³öÏÖ²¢¾ö¶¨ÒªÖ´ÐÐÏàÓ¦´¦Àí£¬Ê¹ÓÃ¹¥»÷¼¼ÄÜµÄ¸ÅÂÊ ¶ÔÓ¦SkillListÀïÃæµÄ¼¼ÄÜ 1
//	m_AiParam[4¡¢5¡¢6] ÈýÖÖ¹¥»÷¼¼ÄÜµÄÊ¹ÓÃ¸ÅÂÊ£¬·Ö±ð¶ÔÓ¦SkillListÀïµÄ¼¼ÄÜ 2 3 4
//	m_AiParam[7¡¢8] ¿´¼ûµÐÈËµ«±È½ÏÔ¶Ê±£¬´ý»ú¡¢Ñ²ÂßµÄ¸ÅÂÊ
//------------------------------------------------------------------------------
void	KNpcAI::ProcessAIType06()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	// ÊÇ·ñÊÜµ½¹¥»÷£¬·ñ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß
	if (nEnemyIdx <= 0)
	{
		// pAIParam[0]:Ñ²Âß¸ÅÂÊ
		if (pAIParam[0] > 0 && g_RandPercent(pAIParam[0]))
		{	// Ñ²Âß
			CommonAction();
		}
		return;
	}

	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	// ¼ì²âÊ£ÓàÉúÃüÊÇ·ñ·ûºÏÌõ¼þ£¬ÉúÃüÌ«ÉÙÒ»¶¨¸ÅÂÊÊ¹ÓÃ¹¥»÷¼¼ÄÜ»òÌÓÅÜ
	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[1])
	{
		if (g_RandPercent(pAIParam[2]))	// ÊÇ·ñÊ¹ÓÃ¹¥»÷¼¼ÄÜ»òÌÓÅÜ
		{
			if (g_RandPercent(pAIParam[3]))	// Ê¹ÓÃ¹¥»÷¼¼ÄÜ
			{
				Npc[m_nIndex].SetActiveSkill(1);
				FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
				return;
			}
			else	// ÌÓÅÜ
			{
				Flee(nEnemyIdx);
				return;
			}
		}
	}

	// Èç¹ûµÐÈËÔÚËùÓÐ¼¼ÄÜ¹¥»÷·¶Î§Ö®Íâ£¬Ò»¶¨¸ÅÂÊÑ¡Ôñ´ý»ú/Ñ²Âß/ÏòµÐÈË¿¿½ü
	if (KNpcSet::GetDistanceSquare(m_nIndex, nEnemyIdx) > pAIParam[MAX_AI_PARAM - 1])
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[7])	// ´ý»ú
			return;
		if (nRand < pAIParam[7] + pAIParam[8])	// Ñ²Âß
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);	// ÏòµÐÈË¿¿½ü
		return;
	}

	// µÐÈËÔÚ×î´ó¼¼ÄÜ¹¥»÷·¶Î§Ö®ÄÚ£¬Ñ¡ÔñÒ»ÖÖ¼¼ÄÜ¹¥»÷
	int		nRand;
	nRand = g_Random(100);
	if (nRand < pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[4] + pAIParam[5] + pAIParam[6])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}
	else	// ´ý»ú
	{
		return;
	}
	FollowAttack(nEnemyIdx);
}

/*
// Ò»°ãÖ÷¶¯ÐÍ
void KNpcAI::ProcessAIType1()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;
	// ÊÇ·ñÒÑ³¬¹ý»î¶¯°ë¾¶
	if (KeepActiveRange())
		return;

	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Npc[m_nIndex].SetActiveSkill(1);
			Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, m_nIndex);
			return;
		}
	}

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	
	if (nEnemyIdx <= 0 || Npc[nEnemyIdx].m_dwID <= 0 || !InEyeshot(nEnemyIdx) )
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}
	
	

	if (nEnemyIdx > 0)
	{
		int		nRand;
		nRand = g_Random(100);
		if (nRand < pAIParam[2])
		{
			if (!Npc[m_nIndex].SetActiveSkill(2))
			{
				CommonAction();
				return;
			}
		}
		else if (nRand < pAIParam[2] + pAIParam[3])
		{
			if (!Npc[m_nIndex].SetActiveSkill(3))
			{
				CommonAction();
				return;
			}
		}
		else if (nRand < pAIParam[2] + pAIParam[3] + pAIParam[4])
		{
			if (!Npc[m_nIndex].SetActiveSkill(4))
			{
				CommonAction();
				return;
			}
		}

//		if (g_RandPercent(pAIParam[2]))
//		{
//			Npc[m_nIndex].SetActiveSkill(2);
//		}
//		else if (g_RandPercent(pAIParam[3]))
//		{
//			Npc[m_nIndex].SetActiveSkill(3);
//		}
//		else if (g_RandPercent(pAIParam[4]))
//		{
//			Npc[m_nIndex].SetActiveSkill(4);
//		}
		else
		{
			CommonAction();
			return;
		}
		FollowAttack(nEnemyIdx);
		return;
	}
	CommonAction();
}
*/

/*
// Ò»°ã±»¶¯ÐÍ
void KNpcAI::ProcessAIType2()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Npc[m_nIndex].SetActiveSkill(1);
			Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, m_nIndex);
			return;
		}
	}

	int nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;
	if (nEnemyIdx <= 0 || !InEyeshot(nEnemyIdx))
		return;

	int		nRand;
	nRand = g_Random(100);

	if (nRand < pAIParam[2])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[2] + pAIParam[3])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[2] + pAIParam[3] + pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(4))
		{
			CommonAction();
			return;
		}
	}

//	if (g_RandPercent(pAIParam[2]))
//	{
//		Npc[m_nIndex].SetActiveSkill(2);
//	}
//	else if (g_RandPercent(pAIParam[3]))
//	{
//		Npc[m_nIndex].SetActiveSkill(3);
//	}
//	else if (g_RandPercent(pAIParam[4]))
//	{
//		Npc[m_nIndex].SetActiveSkill(4);
//	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(nEnemyIdx);

	return;
}
*/

/*
// Ò»°ãÌÓÅÜÐÍ
void KNpcAI::ProcessAIType3()
{
	int* pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int	nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;

	if (nEnemyIdx <= 0 || !InEyeshot(nEnemyIdx))
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}

	if (nEnemyIdx <= 0)
	{
		CommonAction();
		return;
	}
	
	if (Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Flee(nEnemyIdx);
			return;
		}
	}

	int		nRand;
	nRand = g_Random(100);

	if (nRand < pAIParam[2])
	{
		if (!Npc[m_nIndex].SetActiveSkill(1))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[2] + pAIParam[3])
	{
		if (!Npc[m_nIndex].SetActiveSkill(2))
		{
			CommonAction();
			return;
		}
	}
	else if (nRand < pAIParam[2] + pAIParam[3] + pAIParam[4])
	{
		if (!Npc[m_nIndex].SetActiveSkill(3))
		{
			CommonAction();
			return;
		}
	}

//	if (g_RandPercent(pAIParam[2]))
///	{
//		Npc[m_nIndex].SetActiveSkill(1);
//	}
//	else if (g_RandPercent(pAIParam[3]))
//	{
//		Npc[m_nIndex].SetActiveSkill(2);
//	}
//	else if (g_RandPercent(pAIParam[4]))
//	{
//		Npc[m_nIndex].SetActiveSkill(3);
//	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(nEnemyIdx);
	return;
}
*/

/*
// ÌÓÅÜ¼ÓÇ¿ÐÍ
void KNpcAI::ProcessAIType4()
{
	int*	pAIParam = Npc[m_nIndex].m_AiParam;
	
	if (KeepActiveRange())
		return;

	int	nEnemyIdx = Npc[m_nIndex].m_nPeopleIdx;

	if (nEnemyIdx <= 0 || !InEyeshot(nEnemyIdx))
	{
		nEnemyIdx = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = nEnemyIdx;
	}

	if (nEnemyIdx <= 0)
	{
		CommonAction();
		return;
	}
	
	int nLifePercent = Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax;
	if (nLifePercent < pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Flee(nEnemyIdx);
			return;
		}
	}
	if (nLifePercent < pAIParam[2])
	{
		if (g_RandPercent(pAIParam[3]))
		{
			Npc[m_nIndex].SetActiveSkill(1);
			Npc[m_nIndex].SendCommand(do_skill, Npc[m_nIndex].m_ActiveSkillID, -1, m_nIndex);
			return;
		}
	}

	if (g_RandPercent(pAIParam[4]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else if (g_RandPercent(pAIParam[5]))
	{
		Npc[m_nIndex].SetActiveSkill(3);
	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(nEnemyIdx);
	return;
}
*/

/*
//	ÈË¶à¾ÍÅÜÐÍ
void KNpcAI::ProcessAIType5()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;

	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}

	int nEnemyNumber = GetNpcNumber(relation_enemy);
	if (nEnemyNumber > pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Flee(i);
			return;
		}
	}

	if (g_RandPercent(pAIParam[2]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (nEnemyNumber <= pAIParam[3] && g_RandPercent(pAIParam[4]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else
	{
		CommonAction();
		return;
	}

	FollowAttack(i);
	return;
}
*/

/*
//	³ÉÈº½á¶ÓÐÍ
void KNpcAI::ProcessAIType6()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;
	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}

	int nAllyNumber = GetNpcNumber(relation_none);
	if (nAllyNumber <= pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			Flee(i);
			return;
		}
	}
	
	if (g_RandPercent(pAIParam[2]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (nAllyNumber > pAIParam[3] && g_RandPercent(pAIParam[4]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else
	{
		CommonAction();
		return;
	}

	FollowAttack(i);
	return;
}
*/

/*
// °¤´ò¾Û¶ÑÐÍ
void KNpcAI::ProcessAIType7()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;
	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}

	int j = GetNearestNpc(relation_ally);

	if (j && Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax < pAIParam[0])
	{
		if (g_RandPercent(pAIParam[1]))
		{
			int x, y;
			Npc[j].GetMpsPos(&x, &y);
			Npc[m_nIndex].SendCommand(do_walk, x, y);
			return;
		}
	}

	if (g_RandPercent(pAIParam[2]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (g_RandPercent(pAIParam[3]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else if (g_RandPercent(pAIParam[4]))
	{
		Npc[m_nIndex].SetActiveSkill(3);
	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(i);
	return;
}
*/

/*
//	Ö÷¶¯ËÍËÀÐÍ
void KNpcAI::ProcessAIType8()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;

	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}
	
	if (g_RandPercent(pAIParam[0]))
	{
		int x, y;

		Npc[i].GetMpsPos(&x, &y);
		Npc[m_nIndex].SendCommand(do_walk, x, y);
	}
	else if (g_RandPercent(pAIParam[1]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (g_RandPercent(pAIParam[2]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else if (g_RandPercent(pAIParam[3]))
	{
		Npc[m_nIndex].SetActiveSkill(3);
	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(i);
	return;
}
*/

/*
//	Ô½Õ½Ô½ÓÂÐÍ
void KNpcAI::ProcessAIType9()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;

	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}
	
	int nLifePercent = Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax;

	if (g_RandPercent(pAIParam[0]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (nLifePercent < pAIParam[1] && g_RandPercent(pAIParam[2]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else if (nLifePercent < pAIParam[3] && g_RandPercent(pAIParam[4]))
	{
		Npc[m_nIndex].SetActiveSkill(3);
	}
	else
	{
		CommonAction();
		return;
	}
	FollowAttack(i);
	return;
}
*/

/*
//	ÌÓÅÜ²»µôÐÍ
void KNpcAI::ProcessAIType10()
{
	int *pAIParam = Npc[m_nIndex].m_AiParam;

	if (KeepActiveRange())
		return;

	int i = Npc[m_nIndex].m_nPeopleIdx;

	if (!i || !InEyeshot(i))
	{
		i = GetNearestNpc(relation_enemy);
		Npc[m_nIndex].m_nPeopleIdx = i;
	}

	if (!i)
	{
		CommonAction();
		return;
	}
	
	int nLifePercent = Npc[m_nIndex].m_CurrentLife * 100 / Npc[m_nIndex].m_CurrentLifeMax;

	if (nLifePercent < pAIParam[0] && g_RandPercent(pAIParam[1]))
	{
		Npc[m_nIndex].SetActiveSkill(1);
	}
	else if (nLifePercent < pAIParam[2] && g_RandPercent(pAIParam[3]))
	{
		Npc[m_nIndex].SetActiveSkill(2);
	}
	else if (nLifePercent < pAIParam[4] && g_RandPercent(pAIParam[5]))
	{
		Flee(i);
		return;
	}
	else
	{
		CommonAction();
		return;
	}

	FollowAttack(i);
	return;
}
*/
