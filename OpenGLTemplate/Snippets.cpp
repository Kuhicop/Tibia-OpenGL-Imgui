// Init modules
/*
// modules
std::cout << "moduleBase: " << std::hex << moduleBase << std::endl;
std::cout << "map: " << map << std::endl;
std::cout << "protocolGame: " << protocolGame << std::endl;
std::cout << "protocolGamePointer: " << protocolGamePointer << std::endl;

// get localplayer
DWORD LocalPlayerPointer = (DWORD)((moduleBase + dwLocalPlayer));
DWORD LocalPlayerAddress = *(DWORD*)LocalPlayerPointer;
// enable after testing when moving to loop: if (LocalPlayer == 0 || LocalPlayerPointer == 0) continue;
std::cout << "LocalPlayerPointer: " << LocalPlayerPointer << std::endl;
std::cout << "LocalPlayerAddress: " << LocalPlayerAddress << std::endl;
*/

// stop follow
/*
cancelFollow(LocalPlayerPointer);
std::cout << "Stopped follow" << std::endl;
*/

// sendinput
/*
SendMsg(WM_KEYDOWN, VK_F1);
SendMsg(WM_KEYUP, VK_F1);
*/

// get target
/*
DWORD attacking = isAttacking(LocalPlayerPointer);
DWORD buffer;
getAttackingCreature(LocalPlayer, &buffer);
std::cout << "buffer: " << buffer << std::endl;
*/

// get tiles
/*
TileList tiles;
getTiles(map, &tiles, 7);
for (TilePtr t : tiles) {
    DWORD tile = (DWORD)t;
    DWORD tilebase = (tile + offset_tilebase);
    DWORD first_stack_pointer = *(DWORD*)(tilebase);
    DWORD first_stack = *(DWORD*)(first_stack_pointer);
    DWORD tileid = *(DWORD*)(first_stack + offset_id);
}
*/

// getTopCreature
/*
DWORD creature;
getTopCreature(tile, &creature);
// check if creature isLocalPlayer
if (creature != 0 && creature != LocalPlayerAddress)
*/

// findItemInContainers
/*
DWORD item = 0;
uintptr_t itemid = 3198; //hmm
findItemInContainers(LocalPlayerPointer, &item, itemid, 1);
if (item != 0) {
    std::cout << "Item " << std::dec << itemid << " found: " << std::hex << item << std::endl;
}
else {
    std::cout << "Item " << itemid << " not found: " << std::dec << itemid << std::endl;
}
*/

// shoot
/*
useWith(protocolGamePointer, (DWORD)&item, (DWORD)&first_stack);
*/

// read inventory
/*
for (int i = 0; i <= Const::InventorySlot::LastInventorySlot; i++) {
    DWORD buffer = 0, itemId = 0, itemCount = 0;
    getInventoryItem(LocalPlayerAddress, &buffer, i);
    if (buffer != 0) {
        itemId = *(DWORD*)(buffer + offset_id);
        itemCount = *(DWORD*)(buffer + offset_itemCount);
    }
    if (itemId != 0) {
        std::cout << "Item" << i << ": " << std::hex << buffer << std::endl;
        std::cout << "ID: " << std::dec << itemId << " x" << itemCount << std::endl;
    }
}
*/


// manatrainer        
/*
double mana = getMana(LocalPlayerAddress);
std::cout << "Mana: " << std::dec << mana << std::endl;
if (mana > MANA_TO_RUNE) {
    talkChannel(LocalPlayerPointer, 1, 0, SPELL_TO_USE);
    Sleep(3000);
    // useItem
    DWORD buffer = 0, itemId = 0, itemCount = 0;
    getInventoryItem(LocalPlayerAddress, &buffer, Const::InventorySlot::InventorySlotAmmo);
    if (buffer != 0) {
        std::cout << "sending useItem()" << std::endl;
        itemId = *(DWORD*)(buffer + offset_id);
        itemCount = *(DWORD*)(buffer + offset_itemCount);
        useItem(LocalPlayerPointer, &buffer);
    }
}
*/

// targeting first attempt (didn't work)
/*
// get player floor
int floor = *(int*)(LocalPlayerAddress + offset_playerZ);
// check around creatures
TileList tiles;
getTiles(map, &tiles, floor);
// loop tiles
for (TilePtr tile : tiles) {
    DWORD creature = 0;
    DWORD creature_pointer = getTopCreature((DWORD)tile, &creature);
    // check if there is a creature
    if (creature != 0)
    {
        // check if creature isLocalPlayer
        if (creature != LocalPlayerAddress) {
            WriteLine("Creature: " + DwordToHex(creature));
            // check if creature is monster
            if (isMonster(creature)) {
                // attack
                attack(LocalPlayerPointer, creature);
                break;
            }
        }
    }
}
WriteLine("Finished reading tiles");
*/

// get angles
/*
WriteLine(("Battle list: " + DwordToHex(battle_list)));
int creatureX = *(int*)(battle_list + offset_creatureX);
int creatureY = *(int*)(battle_list + offset_creatureY);
int creatureZ = *(int*)(battle_list + offset_creatureZ);
WriteLine(("Creature X: " + std::to_string(creatureX)));
WriteLine(("Creature Y: " + std::to_string(creatureY)));
WriteLine(("Creature Z: " + std::to_string(creatureZ)));
WriteLine(("Player X: " + std::to_string(playerX)));
WriteLine(("Player Y: " + std::to_string(playerY)));
WriteLine(("Player Z: " + std::to_string(playerZ)));
WriteLine("");

// check if floor is invalid
if (creatureZ != playerZ) return;

// calculate direction
int Xangle = creatureX - playerX;
int Yangle = creatureY - playerY;

// vertical
if (abs(Xangle) == 1) {
    if (Xangle > 0) {
        WriteLine("Norte");
    }
    else {
        WriteLine("Sud");
    }
}
// horizontal
else if (abs(Yangle) == 1)
{
    if (Yangle > 0) {
        WriteLine("Este");
    }
    else {
        WriteLine("Oeste");
    }
}
*/