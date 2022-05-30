#include <Windows.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <string>
#include <cstdint>
#include "Utils.h"
#include "Hook/Minhook/include/MinHook.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_win32.h"
#include "functions/functions.h"
#include "../Declarations.h"
#include "../Constants.h"
#include "../Offsets.h"
#include <chrono>
#include <sstream>
#include "../hooks.h"
#include "../targeting.h"

#pragma region OpenGL
#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

#define GLEW_STATIC
#if defined _M_X64
#include "Hook/GLx64/glew.h"
#pragma comment(lib, "Source/Hook/GLx64/glew32s.lib")
#elif defined _M_IX86
#include "Hook/GLx86/glew.h"
#pragma comment(lib, "Source/Hook/GLx86/glew32s.lib")
#endif
#include <gl/gl.h> 
#pragma comment(lib,"opengl32.lib")
#pragma endregion
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef BOOL(__stdcall* twglSwapBuffers) (_In_ HDC hDc);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);