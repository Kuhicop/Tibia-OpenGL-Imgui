#include "Source/Includes.h"

void ExoriVisTarget() {
    //else {
    //    if (target != 0) {
    //        // find rune
    //        DWORD item = 0;
    //        uintptr_t itemid = 3198; //hmm
    //        findItemInContainers(LocalPlayerPointer, &item, itemid, 1);
    //        if (item != 0) {
    //            // shoot target
    //            //useWith(protocolGamePointer, (DWORD)&item, (DWORD)&target);
    //        }    
    //    }            
    //}
}

void Targeting() {
    if (LocalPlayerPointer == 0) return;
    if (battle_list == 0) return;

    DWORD attacking = isAttacking(LocalPlayerPointer);
    if (attacking == 0) {
        WriteLine("Calling attack with battle_list: " + DwordToHex(battle_list));
        //attack(LocalPlayerPointer, battle_list, 256);
        return;
    }
    else {     
        DWORD item = 0;        
        findItemInContainers(LocalPlayerPointer, &item, rune_to_shoot, 1);
        if (item != 0) {
            useWith(LocalPlayerPointer, (DWORD)&item, (DWORD)&battle_list);
        }
    }
}