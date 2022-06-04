#include "Source/Includes.h"

DWORD BattleHookGateway, CheckPlayerGateway, battle_list;
std::chrono::steady_clock::time_point start_targeting;

#pragma region InitHooks
void InitHooks() {    
    //BattleHookGateway = (DWORD)TrampHook32((char*)BattleListHook, (char*)BattleHook, 5);
    CheckPlayerGateway = (DWORD)TrampHook32((char*)CheckPlayerHook, (char*)CheckPlayer, 5);
}
#pragma endregion

#pragma region BattleHook
DWORD __fastcall BattleHook(DWORD* pThis, void* ecx, DWORD battleList) {
    WriteLine("Hooked BattleHook :D");
    battle_list = (DWORD)pThis;
    start_targeting = std::chrono::steady_clock::now();
    return ((_BattleListHook)BattleHookGateway)(pThis, battleList);
}
#pragma endregion

#pragma region MainHook
DWORD __fastcall CheckPlayer(DWORD* pThis, void* ecx, DWORD lparam, DWORD rparam) {
    WriteLine("Hooked CheckPlayer :D");

    HackLoop();
    //Targeting();

    return ((_CheckPlayerHook)CheckPlayerGateway)(pThis, lparam, rparam);
}
#pragma endregion
