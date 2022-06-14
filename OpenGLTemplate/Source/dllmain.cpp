#include "Includes.h"

#pragma region Variables
bool debugging = false;
twglSwapBuffers oSwapBuffers = NULL;
WNDPROC oWndProc;
static HWND Window = NULL;
int init = false;
bool show, botloaded, stopped = false;
std::chrono::steady_clock::time_point begin_eatfood, start_cast, start_manapot = std::chrono::steady_clock::now();
DWORD LocalPlayerPointer, LocalPlayerAddress;
int health, healthmax, mana, manamax, light, playerX, playerY, playerZ;
std::string SPELL_TO_MANATRAIN = "adori vita vis";
std::string SPELL_TO_AUTOHEAL = "exura vita";
#pragma endregion

void HackLoop() {
    #pragma region InitHackLoop
    if (stopped) return;
    //WriteLine("Setting now time");
    std::chrono::steady_clock::time_point end_eatfood = std::chrono::steady_clock::now();
    #pragma endregion
    
    #pragma region LocalPlayer
    //WriteLine("Setting LocalPlayer");
    LocalPlayerPointer = (DWORD)((moduleBase + dwLocalPlayer));
    //WriteLine(("LocalPlayerPointer: " + DwordToHex(LocalPlayerPointer)));
    LocalPlayerAddress = *(DWORD*)LocalPlayerPointer;
    //WriteLine(("LocalPlayerAddress: " + DwordToHex(LocalPlayerAddress)));
    if (LocalPlayerAddress == 0) return;
    #pragma endregion

    #pragma region Lighthack
    //WriteLine("Writting light");
    *(DWORD*)(LocalPlayerAddress + offset_light) = 4311;
    if (!botloaded) {        
        // nop light
        //WriteLine("Nopping light");
        Nop((BYTE*)(moduleBase + dwLightNopFirstAddress), (dwLightBytesToNop * 2)); // we're nopping 2 opcodes at once (12 bytes)
        Nop((BYTE*)(moduleBase + dwLightNopSecondAddress), dwLightBytesToNop); // every opcode is 6 bytes
        Nop((BYTE*)(moduleBase + dwLightNopThirdAddress), dwLightBytesToNop);
        botloaded = true;
    }    
    #pragma endregion
    
    #pragma region Stats
    //WriteLine("Reading stats");
    health = (int)getHealth(LocalPlayerAddress);
    //WriteLine(("health: " + std::to_string(health)));
    if (health == 0) return;
    healthmax = (int)getHealthMax(LocalPlayerAddress);
    //WriteLine(("healthmax: " + std::to_string(healthmax)));
    mana = (int)getMana(LocalPlayerAddress);
    //WriteLine(("mana: " + std::to_string(mana)));
    manamax = (int)getManaMax(LocalPlayerAddress);
    //WriteLine(("manamax: " + std::to_string(manamax)));
    playerX = *(int*)(LocalPlayerAddress + offset_playerX);
    //WriteLine(("playerX: " + std::to_string(playerX)));
    playerY = *(int*)(LocalPlayerAddress + offset_playerY);
    //WriteLine(("playerY: " + std::to_string(playerY)));
    playerZ = *(int*)(LocalPlayerAddress + offset_playerZ);
    //WriteLine(("playerZ: " + std::to_string(playerZ)));
    #pragma endregion
    
    #pragma region Autoheal
    //WriteLine("Reading autoheal");
    if (enabled_auto_heal) {
        //WriteLine("Checking autoheal");
        if (health > 0 && health <= health_to_cast_autoheal && health_to_cast_autoheal != 0 && mana >= mana_to_cast_autoheal) {
            int seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_cast).count();
            if (seconds_to_cast != 0 && seconds >= seconds_to_cast) {
                //WriteLine("Casting autoheal");
                talkChannel(LocalPlayerPointer, 1, 0, SPELL_TO_AUTOHEAL);
                start_cast = std::chrono::steady_clock::now();
            }
        }
    }
    #pragma endregion

    #pragma region Manatrain
    //WriteLine("Reading manatrain");
    if (enabled_mana_trainer) {   
        //WriteLine("Checking manatrain");
        if (mana >= mana_to_cast_manatrain && mana_to_cast_manatrain != 0) {
            int seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_cast).count();
            if (seconds_to_cast != 0 && seconds >= seconds_to_cast) {
                //WriteLine("Casting manatrain");
                if (canPerformGameAction(LocalPlayerPointer)) {
                    talkChannel(LocalPlayerPointer, 1, 0, SPELL_TO_MANATRAIN);
                    start_cast = std::chrono::steady_clock::now();
                }
            }
        }
    }
    #pragma endregion

    #pragma region Eatfood
    //WriteLine("Reading eatfood");
    if (enabled_eat_food) {
        //WriteLine("Checking eatfood");
        if (seconds_to_eat != 0 && std::chrono::duration_cast<std::chrono::seconds>(end_eatfood - begin_eatfood).count() >= seconds_to_eat) {
            // useItem
            DWORD buffer = 0;
            //WriteLine("Getting inventory item");
            getInventoryItem(LocalPlayerAddress, &buffer, Const::InventorySlot::InventorySlotAmmo);
            //WriteLine("Getting buffer");
            if (buffer != 0) {       
                //WriteLine("Using item to buffer: " + DwordToHex(buffer));
                if (canPerformGameAction(LocalPlayerPointer))
                    useItem(LocalPlayerPointer, &buffer);
                //WriteLine("Setting new time for eatfood");
                begin_eatfood = std::chrono::steady_clock::now();             
            }
        }
    }
    #pragma endregion
}

void alert() {
    while (true) {
        if (LocalPlayerPointer != 0)
            if (!isOnline(LocalPlayerPointer)) {
                Beep(523, 500);
            }                
        Sleep(3000);
    }        
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

    if ((GetAsyncKeyState(VK_INSERT) & 1) && (Window == GetFocus()))
        show = !show;

    //if (GetAsyncKeyState(VK_END) & 1) // Unload
    //{
    //    MH_DisableHook(MH_ALL_HOOKS);
    //    SetWindowLongPtr(Window, GWL_WNDPROC, (LONG_PTR)oWndProc); // Reset WndProc
    //}

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // HACK MENU
    if (show)
    {
        ImGui::Begin("Tibia OpenGL Imgui");
        ImGui::Text("Project under development for educational purposes.");
        ImGui::Separator();

        /*if (ImGui::CollapsingHeader("Addresses")) {
            ImGui::Text("LocalPlayerPointer: %X", LocalPlayerPointer);
            ImGui::Text("LocalPlayerAddress: %X", LocalPlayerAddress);
            ImGui::Text("Map: %X", map);
        }
        ImGui::Separator();*/

        if (ImGui::CollapsingHeader("Stats")) {
            ImGui::Text("Health: %d/%d", health, healthmax);
            ImGui::Text("Mana: %d/%d", mana, manamax);
        }
        ImGui::Separator();

        if (ImGui::CollapsingHeader("Healing")) {            
            ImGui::Checkbox("Enabled##Healing", &enabled_auto_heal);            
            ImGui::SliderInt("Health##Healing", &health_to_cast_autoheal, 0, healthmax);
            ImGui::InputText("Spell##Healing", &SPELL_TO_AUTOHEAL);
            ImGui::SliderInt("Mana##Healing", &mana_to_cast_autoheal, 0, manamax);

        }
        ImGui::Separator();

        /*if (ImGui::CollapsingHeader("Manapots")) {
            ImGui::Checkbox("Enabled##Manapots", &enabled_manapot);
            ImGui::SliderInt("Mana##Manapots", &mana_to_autopot, 0, manamax);

        }
        ImGui::Separator();*/

        if (ImGui::CollapsingHeader("Runemaker")) {            
            ImGui::Checkbox("Enabled##Runemaker", &enabled_mana_trainer);
            ImGui::InputText("Spell##Runemaker", &SPELL_TO_MANATRAIN);
            ImGui::SliderInt("Mana##Runemaker", &mana_to_cast_manatrain, 0, manamax);
            ImGui::Checkbox("Eat food", &enabled_eat_food);
            ImGui::SliderInt("Eat delay", &seconds_to_eat, 30, 300);
            ImGui::Text("Eating will use arrow slot MEATS.");
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

    if (show)
        return 1;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
#pragma endregion

#pragma region Initialization
DWORD WINAPI Initalization(__in  LPVOID lpParameter)
{
    InitFunctions();
    InitHooks();  

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

        // Hook SwapBuffers
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
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)alert, hModule, 0, nullptr));
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, Initalization, 0, 0, 0); 
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#pragma endregion