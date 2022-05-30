#include "Source/Includes.h"

DWORD BattleHookGateway, battle_list;

#pragma region InitHooks
void InitHooks() {
    // get battle list hook
    BattleHookGateway = (DWORD)TrampHook32((char*)BattleListHook, (char*)BattleHook, 5);
}
#pragma endregion

#pragma region Target
DWORD __fastcall BattleHook(DWORD* pThis, DWORD battleList, DWORD localplayer) {
    WriteLine("Hooked :D");
    battle_list = (DWORD)pThis;
    Targeting();    
    return ((_BattleListHook)BattleHookGateway)(battleList, localplayer);
}
#pragma endregion