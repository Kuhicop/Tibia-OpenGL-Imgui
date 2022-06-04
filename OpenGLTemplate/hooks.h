#pragma once
#include "Source/Includes.h"

void InitHooks();

extern DWORD BattleHookGateway;
extern DWORD __fastcall BattleHook(DWORD* pThis, void* ecx, DWORD battleList);

extern DWORD CheckPlayerGateway;
extern DWORD __fastcall CheckPlayer(DWORD* pThis, void* ecx, DWORD lparam, DWORD rparam);