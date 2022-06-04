#pragma once
#include "../Includes.h"

void InitFunctions();
extern uintptr_t moduleBase;
extern uintptr_t map;
extern uintptr_t protocolGame;
extern DWORD protocolGamePointer;

#pragma region Functions
// getMana
typedef double(__thiscall* _getMana)(DWORD localplayer);
extern _getMana getMana;
// getManaMax
typedef double(__thiscall* _getManaMax)(DWORD localplayer);
extern _getManaMax getManaMax;
// getHealth
typedef double(__thiscall* _getHealth)(DWORD localplayer);
extern _getHealth getHealth;
// getHealthMax
typedef double(__thiscall* _getHealthMax)(DWORD localplayer);
extern _getHealthMax getHealthMax;
// isAttacking
typedef int(__thiscall* _isAttacking)(DWORD localplayer);
extern _isAttacking isAttacking;
// getInventoryItem
typedef DWORD(__thiscall* _getInventoryItem)(DWORD localplayer, DWORD* buffer, uintptr_t index);
extern _getInventoryItem getInventoryItem;
// cancelFollow
typedef DWORD(__thiscall* _cancelFollow)(DWORD localplayer);
extern _cancelFollow cancelFollow;
// findItemInContainers
typedef DWORD(__thiscall* _findItemInContainers)(DWORD localplayer, DWORD* buffer, uintptr_t id, uintptr_t type);
extern _findItemInContainers findItemInContainers;
// talkChannel
typedef DWORD(__thiscall* _talkChannel)(DWORD localplayer, uintptr_t mode, uintptr_t channelId, const std::string& message);
extern _talkChannel talkChannel;
// useWith
typedef void(__thiscall* _useWith)(DWORD game, DWORD fromthing, DWORD tothing);
extern _useWith useWith;
// getAttackingCreature
typedef DWORD(__thiscall* _getAttackingCreature)(DWORD localplayer, DWORD* buffer);
extern _getAttackingCreature getAttackingCreature;
// useItem    
typedef void(__thiscall* _useItem)(DWORD localplayer, DWORD* item);
extern _useItem useItem;
// getTile
typedef TilePtr& (__thiscall* _getTile)(DWORD map, DWORD tile_pos);
extern _getTile getTile;
// get tiles
typedef void(__thiscall* _getTiles)(DWORD map, TileList* buffer, uintptr_t floor);
extern _getTiles getTiles;
// getTopCreature
typedef DWORD(__thiscall* _getTopCreature)(DWORD tile, DWORD* buffer);
extern _getTopCreature getTopCreature;
// getTopThing
typedef void(__thiscall* _getTopThing)(DWORD tile, DWORD* buffer);
extern _getTopThing getTopThing;
// getThingStackPos
typedef int(__thiscall* _getThingStackPos)(DWORD thing);
extern _getThingStackPos getThingStackPos;
// getThings
typedef std::vector<DWORD>(__thiscall* _getThings)(DWORD tile);
extern _getThings getThings;
// getId 
typedef int(__thiscall* _getId)(DWORD thing);
extern _getId getId;
// attack
typedef void(__thiscall* _attack)(DWORD localplayer, DWORD creature, int unknown);
extern _attack attack;
// isMonster
typedef bool(__thiscall* _isMonster)(DWORD creature);
extern _isMonster isMonster;
// getCreatureById
typedef DWORD(__thiscall* _getCreatureById)(DWORD map, DWORD* buffer, DWORD id);
extern _getCreatureById getCreatureById;
// turn
typedef void(__thiscall* _turn)(DWORD player, int direction);
extern _turn turn;
// canPerformGameAction
typedef bool(__thiscall* _canPerformGameAction)(DWORD dwThis);
extern _canPerformGameAction canPerformGameAction;
// getSpectatorsInRangeEx
typedef std::vector<DWORD*>(__thiscall* _getSpectatorsInRangeEx)(DWORD dwThis, std::vector<int>* a2, std::vector<int> a3, DWORD a4, DWORD a5, DWORD a6);
extern _getSpectatorsInRangeEx getSpectatorsInRangeEx;
#pragma endregion

#pragma region Hooks
// BattleListHook
typedef DWORD(__thiscall* _BattleListHook)(DWORD* pthis, DWORD battleList);
extern _BattleListHook BattleListHook;
// CheckPlayer
typedef DWORD(__thiscall* _CheckPlayerHook)(DWORD* player, DWORD lparam, DWORD rparam);
extern _CheckPlayerHook CheckPlayerHook;
#pragma endregion