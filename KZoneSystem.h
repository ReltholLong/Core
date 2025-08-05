// KZoneSystem.h
#ifndef K_ZONE_SYSTEM_H
#define K_ZONE_SYSTEM_H

#include "KCore.h"
#include "LuaFuns.h"

struct KZone
{
    int m_nSubWorldId;
    int m_nMapX;
    int m_nMapY;
    int m_nRadius;          // Bán kính chính (để tương thích code cũ)
    int m_nRadius8[8];      // 8 hướng: N, NE, E, SE, S, SW, W, NW
    bool m_bUse8Direction;  // Có sử dụng 8 hướng không
    int m_nFightState;
    bool m_bActive;
    char m_szName[32];
};

// Khai báo biến và hàm toàn cục (extern)
#define MAX_ZONE 100
extern KZone g_Zones[MAX_ZONE];
extern int g_nZoneCount;

// Khai báo các hàm
void CheckPlayerZoneState(int nPlayerIndex);
int LuaAddZone(Lua_State* L);
int LuaAddObj(Lua_State* L);

#endif // K_ZONE_SYSTEM_H