#include "../Includes.h"

uintptr_t moduleBase;
uintptr_t map;
uintptr_t protocolGame;
DWORD protocolGamePointer;

_getHealth getHealth;
_getHealthMax getHealthMax;
_getMana getMana;
_getManaMax getManaMax;
_isAttacking isAttacking;
_getInventoryItem getInventoryItem;
_findItemInContainers findItemInContainers;
_talkChannel talkChannel;
_useWith useWith;
_useItem useItem;
_attack attack;
_isMonster isMonster;
_getCreatureById getCreatureById;
_turn turn;
_canPerformGameAction canPerformGameAction;
_isOnline isOnline;
// hooks
_BattleListHook BattleListHook;
_CheckPlayerHook CheckPlayerHook;

void InitFunctions(){
	// get base address
	moduleBase = (uintptr_t)GetModuleHandle("NewHorizon_OpenGL.exe");
	getHealth = (_getHealth)(moduleBase + 0x93EB0);
	getHealthMax = (_getHealthMax)(moduleBase + 0x93EC0);
	getMana = (_getMana)(moduleBase + 0x5A830);
	getManaMax = (_getManaMax)(moduleBase + 0x5A840);
	isAttacking = (_isAttacking)(moduleBase + 0x734A0);
	getInventoryItem = (_getInventoryItem)(moduleBase + 0x93F90);
	findItemInContainers = (_findItemInContainers)(moduleBase + 0x78710);
	talkChannel = (_talkChannel)(moduleBase + 0x79340);
	useWith = (_useWith)(moduleBase + 0x78220); //protocolgame->usewith 0x17ED50
	useItem = (_useItem)(moduleBase + 0x77E60);
	attack = (_attack)(moduleBase + 0x78D60);
	isMonster = (_isMonster)(moduleBase + 0x13EEF0);
	getCreatureById = (_getCreatureById)(moduleBase + 0x142680);
	turn = (_turn)(moduleBase + 0x770D0);
	canPerformGameAction = (_canPerformGameAction)(moduleBase + 0x7E030);
	isOnline = (_isOnline)(moduleBase + 0x73490);

	// HOOKS:
	BattleListHook = (_BattleListHook)(moduleBase + 0x600E0);
	CheckPlayerHook = (_CheckPlayerHook)(moduleBase + 0x14FE80);

	map = (uintptr_t)((moduleBase + dwMap));
	protocolGame = (uintptr_t)((moduleBase + m_protocolGame));
	protocolGamePointer = *(DWORD*)protocolGame;
}