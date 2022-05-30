#include "Includes.h"

#pragma region Variables
bool debugging = false;
twglSwapBuffers oSwapBuffers = NULL;
WNDPROC oWndProc;
static HWND Window = NULL;
int init = false;
bool show, botloaded, stopped = false;
std::chrono::steady_clock::time_point begin_eatfood = std::chrono::steady_clock::now();
DWORD LocalPlayerPointer, LocalPlayerAddress;
int health, healthmax, mana, manamax, light, playerX, playerY, playerZ;
#pragma endregion

void HackLoop() {
    #pragma region InitHackLoop
    if (stopped) return;
    //WriteLine("Running hackloop");
    std::chrono::steady_clock::time_point end_eatfood = std::chrono::steady_clock::now();
    #pragma endregion
    
    #pragma region LocalPlayer
    LocalPlayerPointer = (DWORD)((moduleBase + dwLocalPlayer));
    LocalPlayerAddress = *(DWORD*)LocalPlayerPointer;
    if (LocalPlayerAddress == 0) return;
    #pragma endregion

    #pragma region Lighthack
    *(DWORD*)(LocalPlayerAddress + offset_light) = 2263;
    if (!botloaded) {        
        // nop light
        Nop((BYTE*)(moduleBase + dwLightNopFirstAddress), (dwLightBytesToNop * 2)); // we're nopping 2 opcodes at once (12 bytes)
        Nop((BYTE*)(moduleBase + dwLightNopSecondAddress), dwLightBytesToNop); // every opcode is 6 bytes
        Nop((BYTE*)(moduleBase + dwLightNopThirdAddress), dwLightBytesToNop);
        botloaded = true;
    }    
    #pragma endregion
    
    #pragma region Stats
    health = (int)getHealth(LocalPlayerAddress);
    if (health == 0) return;
    healthmax = (int)getHealthMax(LocalPlayerAddress);
    mana = (int)getMana(LocalPlayerAddress);
    manamax = (int)getManaMax(LocalPlayerAddress);
    playerX = *(int*)(LocalPlayerAddress + offset_playerX);
    playerY = *(int*)(LocalPlayerAddress + offset_playerY);
    playerZ = *(int*)(LocalPlayerAddress + offset_playerZ);
    #pragma endregion
    
    #pragma region Autoheal
    if (enabled_auto_heal) {
        if (health > 0 && health <= health_to_heal && health_to_heal != 0 && mana >= mana_to_cast_heal) {
            talkChannel(LocalPlayerPointer, 1, 0, SPELL_TO_AUTOHEAL);
        }
    }
    #pragma endregion

    #pragma region Manatrain
    if (enabled_mana_trainer) {        
        if (mana >= mana_to_cast && mana_to_cast != 0) {
            talkChannel(LocalPlayerPointer, 1, 0, SPELL_TO_MANATRAIN);                        
        }
    }
    #pragma endregion

    #pragma region Eatfood
    if (enabled_eat_food) {
        if (seconds_to_eat != 0 && std::chrono::duration_cast<std::chrono::seconds>(end_eatfood - begin_eatfood).count() >= seconds_to_eat) {
            // useItem
            DWORD buffer = 0;
            getInventoryItem(LocalPlayerAddress, &buffer, Const::InventorySlot::InventorySlotAmmo);
            if (buffer != 0) {                
                useItem(LocalPlayerPointer, &buffer);
                try {
                    begin_eatfood = std::chrono::steady_clock::now();
                }
                catch (...) {                    
                    WriteLine("Eatfood exception");
                }                
            }
        }
        
    }
    #pragma endregion  
}

#pragma region hkSwapBuffers
BOOL __stdcall hkSwapBuffers(_In_ HDC hDc)
{
    if (init == FALSE)
    {
        glewExperimental = GL_TRUE;
        if (glewInit() == GLEW_OK)
        {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
            ImGui_ImplWin32_Init(Window);
            ImGui_ImplOpenGL3_Init();
            InitFunctions();
            init = TRUE;
        }
    }

    HackLoop();

    if (GetAsyncKeyState(VK_INSERT) & 1)
        show = !show;

    if (GetAsyncKeyState(VK_END) & 1) // Unload
    {
        MH_DisableHook(MH_ALL_HOOKS);
        SetWindowLongPtr(Window, GWL_WNDPROC, (LONG_PTR)oWndProc); // Reset WndProc
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // HACK MENU
    if (show)
    {
        ImGui::Begin("Tibia OpenGL Imgui");
        ImGui::Text("Project under development for educational purposes.");
        ImGui::Separator();

        if (ImGui::CollapsingHeader("Addresses")) {
            ImGui::Text("LocalPlayerPointer: %X", LocalPlayerPointer);
            ImGui::Text("LocalPlayerAddress: %X", LocalPlayerAddress);
            ImGui::Text("Map: %X", map);
        }
        ImGui::Separator();

        if (ImGui::CollapsingHeader("Stats")) {
            ImGui::Text("Health: %d/%d", health, healthmax);
            ImGui::Text("Mana: %d/%d", mana, manamax);
        }
        ImGui::Separator();

        if (ImGui::CollapsingHeader("Runemaker")) {
            ImGui::Checkbox("Mana trainer", &enabled_mana_trainer);
            ImGui::SliderInt("Mana to cast", &mana_to_cast, 0, manamax);
            ImGui::Checkbox("Eat food", &enabled_eat_food);
            ImGui::SliderInt("Eat interval", &seconds_to_eat, 30, 300);
            ImGui::Text("Eating will use arrow slot food.");
        }

        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return oSwapBuffers(hDc);
}
#pragma endregion

#pragma region WndProc
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
#pragma endregion

#pragma region Initialization
DWORD WINAPI Initalization(__in  LPVOID lpParameter)
{
    InitFunctions();
    //InitHooks();

    if (debugging) {        
        while (!GetAsyncKeyState(VK_END)) {
            //WriteLine("Trying to run loop");
            HackLoop();
            Sleep(10);
        }
        return false;
    }

    while (GetModuleHandle("opengl32.dll") == NULL)  { Sleep(100); }
    Sleep(100);

    HMODULE hMod = GetModuleHandle("opengl32.dll");
    if (hMod)
    {
        void* ptr = GetProcAddress(hMod, "wglSwapBuffers");
        MH_Initialize();
        MH_CreateHook(ptr, hkSwapBuffers, reinterpret_cast<void**>(&oSwapBuffers));
        MH_EnableHook(ptr);
        do
            Window = GetProcessWindow();
        while (Window == NULL);
        oWndProc = (WNDPROC)SetWindowLongPtr(Window, GWL_WNDPROC, (LONG_PTR)WndProc);
        return true;
    }
    else
        return false;
}
#pragma endregion

#pragma region DllMain
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, Initalization, 0, 0, 0); 
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#pragma endregion