// KZoneSystem.cpp
#include "KCore.h"
#include "KZoneSystem.h"
#include "KPlayer.h"
#include "KNpc.h"
#include "KSubWorld.h"
#include "KPlayerChat.h"
#include "KObjSet.h"        // ← THÊM DÒNG NÀY
#include "KObj.h"           // ← THÊM DÒNG NÀY (nếu chưa có)
// Định nghĩa các biến toàn cục
KZone g_Zones[MAX_ZONE];
int g_nZoneCount = 0;

int LuaAddZone(Lua_State* L)
{
    int nParamCount = Lua_GetTopIndex(L);
    if (nParamCount < 3)
    {
        Lua_PushNumber(L, 0);
        return 1;
    }

    if (g_nZoneCount >= MAX_ZONE)
    {
        Lua_PushNumber(L, 0);
        return 1;
    }

    int nZoneIndex = g_nZoneCount;

    // Đọc tham số bắt buộc
    g_Zones[nZoneIndex].m_nSubWorldId = (int)Lua_ValueToNumber(L, 1);
    g_Zones[nZoneIndex].m_nMapX = (int)Lua_ValueToNumber(L, 2);
    g_Zones[nZoneIndex].m_nMapY = (int)Lua_ValueToNumber(L, 3);

    // Bán kính
    g_Zones[nZoneIndex].m_nRadius = 10;
    if (nParamCount >= 4)
    {
        g_Zones[nZoneIndex].m_nRadius = (int)Lua_ValueToNumber(L, 4);
    }

    // FightState
    g_Zones[nZoneIndex].m_nFightState = 0;
    if (nParamCount >= 5)
    {
        g_Zones[nZoneIndex].m_nFightState = (int)Lua_ValueToNumber(L, 5);
    }

    // Tên zone
    if (nParamCount >= 6 && Lua_IsString(L, 6))
    {
        const char* szName = Lua_ValueToString(L, 6);
        strncpy(g_Zones[nZoneIndex].m_szName, szName, sizeof(g_Zones[nZoneIndex].m_szName) - 1);
        g_Zones[nZoneIndex].m_szName[sizeof(g_Zones[nZoneIndex].m_szName) - 1] = '\0';
    }
    else
    {
        sprintf(g_Zones[nZoneIndex].m_szName, "Zone_%d", nZoneIndex);
    }

    // Xử lý các loại zone
    if (nParamCount == 8) // Hình chữ nhật với hướng và độ rộng
    {
        int nHuong = (int)Lua_ValueToNumber(L, 7);
        int nDoRong = (int)Lua_ValueToNumber(L, 8);

        // Giới hạn tham số - 6 HƯỚNG
        if (nHuong < 1 || nHuong > 6) nHuong = 1;
        if (nDoRong < 1 || nDoRong > 5) nDoRong = 1;

        g_Zones[nZoneIndex].m_bUse8Direction = true;

        int nBaseRadius = g_Zones[nZoneIndex].m_nRadius;
        int nLongRadius = nBaseRadius + 5; // Tăng thêm 5 ô cho 2 đầu
        int nShortRadius = nDoRong;

        // Khởi tạo tất cả hướng với độ rộng
        for (int i = 0; i < 8; i++)
        {
            g_Zones[nZoneIndex].m_nRadius8[i] = nShortRadius;
        }

        // Thiết lập hướng dài - 6 HƯỚNG ĐỐI XỨNG
        switch (nHuong)
        {
        case 1: // 6h-12h (S-N)
            g_Zones[nZoneIndex].m_nRadius8[0] = nLongRadius; // N (12h)
            g_Zones[nZoneIndex].m_nRadius8[4] = nLongRadius; // S (6h)
            break;

        case 2: // 7h-1h (SW-NE)
            g_Zones[nZoneIndex].m_nRadius8[1] = nLongRadius; // NE (1h)
            g_Zones[nZoneIndex].m_nRadius8[5] = nLongRadius; // SW (7h)
            break;

        case 3: // 8h-2h (W-E xiên)
            g_Zones[nZoneIndex].m_nRadius8[1] = nLongRadius; // NE (2h gần)
            g_Zones[nZoneIndex].m_nRadius8[5] = nLongRadius; // SW (8h gần)
            break;

        case 4: // 9h-3h (W-E)
            g_Zones[nZoneIndex].m_nRadius8[2] = nLongRadius; // E (3h)
            g_Zones[nZoneIndex].m_nRadius8[6] = nLongRadius; // W (9h)
            break;

        case 5: // 10h-4h (NW-SE)
            g_Zones[nZoneIndex].m_nRadius8[3] = nLongRadius; // SE (4h)
            g_Zones[nZoneIndex].m_nRadius8[7] = nLongRadius; // NW (10h)
            break;

        case 6: // 11h-5h (NW-SE xiên)
            g_Zones[nZoneIndex].m_nRadius8[3] = nLongRadius; // SE (5h gần)
            g_Zones[nZoneIndex].m_nRadius8[7] = nLongRadius; // NW (11h gần)
            break;
        }
    }
    else if (nParamCount == 7) // Zone oval với 1 hướng nhọn
    {
        int nHuongGio = (int)Lua_ValueToNumber(L, 7);
        g_Zones[nZoneIndex].m_bUse8Direction = true;

        int nBaseRadius = g_Zones[nZoneIndex].m_nRadius;
        int nShortRadius = nBaseRadius * 0.4f;
        int nLongRadius = nBaseRadius * 2.0f;

        // Khởi tạo tất cả hướng với bán kính gốc
        for (int i = 0; i < 8; i++)
        {
            g_Zones[nZoneIndex].m_nRadius8[i] = nBaseRadius;
        }

        // Thiết lập hướng nhọn - 6 HƯỚNG
        switch (nHuongGio)
        {
        case 1: // 6h-12h (S-N)
            g_Zones[nZoneIndex].m_nRadius8[0] = nLongRadius;  // N
            g_Zones[nZoneIndex].m_nRadius8[4] = nLongRadius;  // S
            g_Zones[nZoneIndex].m_nRadius8[2] = nShortRadius; // E
            g_Zones[nZoneIndex].m_nRadius8[6] = nShortRadius; // W
            break;

        case 2: // 7h-1h (SW-NE)
            g_Zones[nZoneIndex].m_nRadius8[1] = nLongRadius;  // NE
            g_Zones[nZoneIndex].m_nRadius8[5] = nLongRadius;  // SW
            g_Zones[nZoneIndex].m_nRadius8[3] = nShortRadius; // SE
            g_Zones[nZoneIndex].m_nRadius8[7] = nShortRadius; // NW
            break;

        case 3: // 8h-2h 
            g_Zones[nZoneIndex].m_nRadius8[1] = nLongRadius;  // NE
            g_Zones[nZoneIndex].m_nRadius8[5] = nLongRadius;  // SW
            g_Zones[nZoneIndex].m_nRadius8[0] = nShortRadius; // N
            g_Zones[nZoneIndex].m_nRadius8[4] = nShortRadius; // S
            break;

        case 4: // 9h-3h (W-E)
            g_Zones[nZoneIndex].m_nRadius8[2] = nLongRadius;  // E
            g_Zones[nZoneIndex].m_nRadius8[6] = nLongRadius;  // W
            g_Zones[nZoneIndex].m_nRadius8[0] = nShortRadius; // N
            g_Zones[nZoneIndex].m_nRadius8[4] = nShortRadius; // S
            break;

        case 5: // 10h-4h (NW-SE)
            g_Zones[nZoneIndex].m_nRadius8[3] = nLongRadius;  // SE
            g_Zones[nZoneIndex].m_nRadius8[7] = nLongRadius;  // NW
            g_Zones[nZoneIndex].m_nRadius8[1] = nShortRadius; // NE
            g_Zones[nZoneIndex].m_nRadius8[5] = nShortRadius; // SW
            break;

        case 6: // 11h-5h
            g_Zones[nZoneIndex].m_nRadius8[3] = nLongRadius;  // SE
            g_Zones[nZoneIndex].m_nRadius8[7] = nLongRadius;  // NW
            g_Zones[nZoneIndex].m_nRadius8[2] = nShortRadius; // E
            g_Zones[nZoneIndex].m_nRadius8[6] = nShortRadius; // W
            break;

        default:
            g_Zones[nZoneIndex].m_bUse8Direction = false;
            for (int i = 0; i < 8; i++)
            {
                g_Zones[nZoneIndex].m_nRadius8[i] = nBaseRadius;
            }
            break;
        }
    }
    else
    {
        // Zone tròn thông thường
        g_Zones[nZoneIndex].m_bUse8Direction = false;
        for (int i = 0; i < 8; i++)
        {
            g_Zones[nZoneIndex].m_nRadius8[i] = g_Zones[nZoneIndex].m_nRadius;
        }
    }

    g_Zones[nZoneIndex].m_bActive = true;
    g_nZoneCount++;

    Lua_PushNumber(L, nZoneIndex + 1);
    return 1;
}

void CheckPlayerZoneState(int nPlayerIndex)
{
    if (nPlayerIndex <= 0 || nPlayerIndex >= MAX_PLAYER)
        return;

    if (Player[nPlayerIndex].m_nIndex <= 0)
        return;

    // Lấy thông tin vị trí người chơi
    int nPlayerX, nPlayerY;
    Npc[Player[nPlayerIndex].m_nIndex].GetMpsPos(&nPlayerX, &nPlayerY);

    // Chuyển đổi từ đơn vị điểm sang đơn vị ô
    nPlayerX = nPlayerX / 32;
    nPlayerY = nPlayerY / 32;

    int nSubWorldIdx = Npc[Player[nPlayerIndex].m_nIndex].m_SubWorldIndex;
    if (nSubWorldIdx < 0 || nSubWorldIdx >= MAX_SUBWORLD)
        return;

    int nSubWorldID = SubWorld[nSubWorldIdx].m_SubWorldID;

    // Kiểm tra từng zone
    for (int i = 0; i < g_nZoneCount; i++)
    {
        if (!g_Zones[i].m_bActive)
            continue;

        if (g_Zones[i].m_nSubWorldId != nSubWorldID)
            continue;

        bool bInZone = false;

        if (g_Zones[i].m_bUse8Direction)
        {
            // Sử dụng thuật toán 8 hướng
            float dx = (float)(nPlayerX - g_Zones[i].m_nMapX);
            float dy = (float)(nPlayerY - g_Zones[i].m_nMapY);

            float distance = sqrt(dx * dx + dy * dy);

            if (distance <= 0.1f)
            {
                bInZone = true;
            }
            else
            {
                float angle = atan2(dx, -dy) * 180.0f / 3.14159f;
                if (angle < 0) angle += 360.0f;

                int dir1 = (int)(angle / 45.0f) % 8;
                int dir2 = (dir1 + 1) % 8;

                float remainderAngle = angle - (dir1 * 45.0f);
                float t = remainderAngle / 45.0f;

                float interpolatedRadius = g_Zones[i].m_nRadius8[dir1] * (1.0f - t) +
                    g_Zones[i].m_nRadius8[dir2] * t;

                bInZone = (distance <= interpolatedRadius);
            }
        }
        else
        {
            // Sử dụng hình tròn thông thường
            int nDeltaX = nPlayerX - g_Zones[i].m_nMapX;
            int nDeltaY = nPlayerY - g_Zones[i].m_nMapY;
            int nDistanceSquared = nDeltaX * nDeltaX + nDeltaY * nDeltaY;
            int nRadiusSquared = g_Zones[i].m_nRadius * g_Zones[i].m_nRadius;
            bInZone = (nDistanceSquared <= nRadiusSquared);
        }

        if (bInZone)
        {
            int nCurrentFightState = Npc[Player[nPlayerIndex].m_nIndex].m_FightMode;
            int nNewFightState = g_Zones[i].m_nFightState;

            if (nCurrentFightState != nNewFightState)
            {
                Npc[Player[nPlayerIndex].m_nIndex].SetFightMode(nNewFightState != 0);

                char szMsg[128];
                if (nNewFightState == 1)
                {
                    sprintf(szMsg, "Bạn đã vào vùng nguy hiểm: %s", g_Zones[i].m_szName);
                }
                else if (nNewFightState == 0)
                {
                    sprintf(szMsg, "Bạn đã vào vùng an toàn: %s", g_Zones[i].m_szName);
                }
                else
                {
                    sprintf(szMsg, "Bạn đã vào vùng đặc biệt: %s", g_Zones[i].m_szName);
                }

#ifdef _SERVER
                // Server: sử dụng static function với đầy đủ tham số
                KPlayerChat::SendSystemInfo(1, nPlayerIndex, "System", szMsg, strlen(szMsg));
#else
                // Client: không cần gửi message (server sẽ gửi)
#endif
            }

            return;
        }
    }
}

int LuaAddObj(Lua_State* L)
{
    int nParamCount = Lua_GetTopIndex(L);
    if (nParamCount < 4)
    {
        printf("[AddObj] Thieu tham so!\n");
        Lua_PushNumber(L, 0);
        return 1;
    }
#ifdef _SERVER
    int nObjDataID = (int)Lua_ValueToNumber(L, 1);
    int nSubWorldID = (int)Lua_ValueToNumber(L, 2);  // Đây là ID, không phải Index
    int nMapX = (int)Lua_ValueToNumber(L, 3);
    int nMapY = (int)Lua_ValueToNumber(L, 4);

    // **QUAN TRỌNG: Chuyển đổi SubWorld ID thành SubWorld Index**
    int nSubWorldIndex = g_SubWorldSet.SearchWorld(nSubWorldID);
    if (nSubWorldIndex < 0) {
        printf("[AddObj] SubWorld ID %d khong tim thay!\n", nSubWorldID);
        Lua_PushNumber(L, 0);
        return 1;
    }

    // Validation SubWorld Index
    if (nSubWorldIndex >= MAX_SUBWORLD) {
        printf("[AddObj] SubWorld Index khong hop le: %d (tu ID: %d)\n", nSubWorldIndex, nSubWorldID);
        Lua_PushNumber(L, 0);
        return 1;
    }

    printf("[AddObj] Tao object: DataID=%d, SubWorldID=%d->Index=%d, X=%d, Y=%d\n",
        nObjDataID, nSubWorldID, nSubWorldIndex, nMapX, nMapY);

    const char* szScript = "";
    if (nParamCount >= 5 && Lua_IsString(L, 5))
        szScript = Lua_ValueToString(L, 5);

    // Tạo KMapPos - SỬ DỤNG SubWorld Index (đã chuyển đổi)
    KMapPos mapPos;
    mapPos.nSubWorld = nSubWorldIndex;  // Sử dụng Index, không phải ID
    SubWorld[nSubWorldIndex].Mps2Map(nMapX, nMapY,  // Sử dụng Index
        &mapPos.nRegion,
        &mapPos.nMapX,
        &mapPos.nMapY,
        &mapPos.nOffX,
        &mapPos.nOffY);

    if (mapPos.nRegion < 0)
    {
        printf("[AddObj] Region khong hop le!\n");
        Lua_PushNumber(L, 0);
        return 1;
    }

    // Tạo KObjItemInfo 
    KObjItemInfo itemInfo;
    itemInfo.m_nItemID = 0;
    itemInfo.m_nItemWidth = 0;
    itemInfo.m_nItemHeight = 0;
    itemInfo.m_nMoneyNum = 0;
    itemInfo.m_nColorID = 0;
    itemInfo.m_szName[0] = 0;
    itemInfo.m_nMovieFlag = 0;
    itemInfo.m_nSoundFlag = 1;

    // SỬ DỤNG HÀM Add CỦA ObjSet (nhận KMapPos và KObjItemInfo)
    int nObjIndex = ObjSet.Add(nObjDataID, mapPos, itemInfo);
    if (nObjIndex <= 0)
    {
        printf("[AddObj] Khong the tao object tu DataID %d\n", nObjDataID);
        Lua_PushNumber(L, 0);
        return 1;
    }

    // Thiết lập script nếu có
    if (strlen(szScript) > 0)
    {
        Object[nObjIndex].SetScriptFile((char*)szScript);
        printf("[AddObj] Thiet lap script: %s\n", szScript);
    }

    printf("[AddObj] Thanh cong tao object %d (SubWorldID:%d->Index:%d)\n",
        nObjIndex, nSubWorldID, nSubWorldIndex);
    Lua_PushNumber(L, nObjIndex);
#else
    printf("[AddObj] Client khong tao object\n");
    Lua_PushNumber(L, 0);
#endif
    return 1;
}
