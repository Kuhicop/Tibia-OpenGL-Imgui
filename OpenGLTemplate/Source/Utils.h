#pragma once
#include "Includes.h"

extern HWND tmp_window;
extern BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
extern HWND GetProcessWindow();
extern void WriteLine(std::string input, ...);
extern std::string DwordToHex(DWORD input);
extern void Nop(BYTE* dst, unsigned int size);
extern void Patch(BYTE* dst, BYTE* src, unsigned int size);
extern bool Detour32(char* src, char* dst, const intptr_t len);
extern char* TrampHook32(char* src, char* dst, const intptr_t len);