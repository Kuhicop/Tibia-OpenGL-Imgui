#pragma once
#include "Source/Includes.h"

// static addresses
constexpr ptrdiff_t dwLocalPlayer = 0x982C10;
constexpr ptrdiff_t dwMap = 0x982D40; // took from getTiles, this* parameter constains address of gmap
constexpr ptrdiff_t m_protocolGame = 0x9561BC; // took from useWith function when it divides into 2
constexpr ptrdiff_t dwLightNopFirstAddress = 0x16445F; // took from light address using torch on/off (Cheat engine see what writes to this address)
constexpr ptrdiff_t dwLightNopSecondAddress = 0x1724DF; // took from light address going up/down stairs (Cheat engine see what writes to this address)
constexpr ptrdiff_t dwLightNopThirdAddress = 0x1724FF; // this address is 4 opcodes below dwLightNopSecondAddress https://imgur.com/Wz00MnB
constexpr int dwLightBytesToNop = 6;

// offsets
constexpr ptrdiff_t offset_id = 0x2C;
constexpr ptrdiff_t offset_itemCount = 0x30;
constexpr ptrdiff_t offset_creatureX = 0x2B;
constexpr ptrdiff_t offset_creatureY = 0x2F;
constexpr ptrdiff_t offset_creatureZ = 0x33;
constexpr ptrdiff_t offset_playerX = 0x0C;
constexpr ptrdiff_t offset_playerY = 0x10;
constexpr ptrdiff_t offset_playerZ = 0x14;
constexpr ptrdiff_t offset_tilex = 0x30;
constexpr ptrdiff_t offset_tiley = 0x34;
constexpr ptrdiff_t offset_tilebase = 0x24;
constexpr ptrdiff_t offset_light = 0xA8;