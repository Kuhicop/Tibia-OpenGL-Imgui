#pragma once
#include "Source/Includes.h"

void InitHooks();
extern DWORD BattleHookGateway;
extern DWORD __fastcall BattleHook(DWORD* pThis, DWORD battleList, DWORD localplayer);