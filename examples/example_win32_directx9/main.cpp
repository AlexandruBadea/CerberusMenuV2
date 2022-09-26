// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include "imgui_shadow.h"
#include "bytes.h"
#include <math.h>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

IDirect3DTexture9* aura_image = nullptr;
IDirect3DTexture9* misc_image = nullptr;
IDirect3DTexture9* visuals_image = nullptr;
IDirect3DTexture9* settings_image = nullptr;
IDirect3DTexture9* cerberus_logo = nullptr;
IDirect3DTexture9* keyboard = nullptr;

ImFont* font = nullptr;
// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int accent_color[4] = {130, 34, 35, 255};
int selection_count = 0;
int legit_group_count = 0;

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Cerberus"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("OlympusHub Cerberus"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    font = io.Fonts->AddFontFromMemoryTTF(fonto, sizeof(fonto), 14.f);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);


    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGuiStyle& style = ImGui::GetStyle();


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {

            if (aura_image == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &aura_icon, sizeof(aura_icon),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &aura_image);
            if (misc_image == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &rage, sizeof(rage),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &misc_image);
            if (visuals_image == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &visuals, sizeof(visuals),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &visuals_image);
            if (settings_image == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &settings, sizeof(settings),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &settings_image);
            if (cerberus_logo == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &logo_png, sizeof(logo_png),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &cerberus_logo);
            if (keyboard == nullptr)D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice
                , &key_icon, sizeof(key_icon),
                20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &keyboard);

            ImGui::SetNextWindowSize(ImVec2(100, 100));
            ImGui::SetNextWindowSize(ImVec2(680, 550));
            ImGui::Begin("жопа", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
            {
                const ImVec2 pos = ImGui::GetWindowPos();
                ImDrawList* draw = ImGui::GetWindowDrawList();

                style.ScrollbarSize = 3.f;
                style.ScrollbarRounding = 12.f;
                style.WindowBorderSize = 0.f;
                style.WindowPadding = ImVec2(0, 0);

                draw->AddRectFilled(pos + ImVec2(71, 56), pos + ImVec2(680, 550), ImColor(11, 11, 11, 255), 2.f, ImDrawFlags_RoundCornersBottomRight);

                draw->AddRectFilled(pos, pos + ImVec2(70, 550), ImColor(14, 14, 14, 255), 2.f, ImDrawFlags_RoundCornersLeft);
                draw->AddLine(pos + ImVec2(70, 0), pos + ImVec2(70, 550), ImColor(24, 24, 24, 255));

                draw->AddRectFilled(pos + ImVec2(71, 0), pos + ImVec2(680, 55), ImColor(14, 14, 14, 255), 2.f, ImDrawFlags_RoundCornersTopRight);
                draw->AddLine(pos + ImVec2(71, 55), pos + ImVec2(680, 55), ImColor(24, 24, 24, 255));

               
                ImGui::AddShadow(ImVec2(0, 0), ImVec2(680, 470), 20, 4, 7, 2, 20, ImColor(0, 0, 0));

                ImGui::SetCursorPos(ImVec2(10, 123));
                ImGui::BeginGroup();
                if (ImGui::selection("esp", visuals_image, 0 == selection_count))
                    selection_count = 0;
                if (ImGui::selection("aura_esp", aura_image, 1 == selection_count))
                    selection_count = 1;
                if (ImGui::selection("misc", misc_image, 2 == selection_count))
                    selection_count = 2;
                if (ImGui::selection("keybindings", keyboard, 3 == selection_count))
                    selection_count = 3;
                if (ImGui::selection("settings", settings_image, 4 == selection_count))
                    selection_count = 4;
                ImGui::EndGroup();

                //Header
                ImGui::SetCursorPos(ImVec2(85, 20));
                    ImGui::Image(cerberus_logo, ImVec2(20, 20));
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(110, 25));
                        ImGui::Text("Cerberus - owned by Olympus and cheatBay");
                // ! Header

                ImGui::BeginGroup();
                    if (selection_count == 0)
                {
                    
                        ImGui::SetCursorPos(ImVec2(85, 70));
                        ImGui::BeginChild("ESP Text", ImVec2(282, 470));

                            static bool esp = false;
                            static bool esp_name = false;
                            static bool esp_meters = false;
                            static bool esp_obj = false;
                            static bool esp_gen = false;
                            static bool esp_escape_door = false;
                            static bool esp_totem = false;
                            static bool esp_chest = false;
                            static bool esp_hook = false;
                            static bool esp_pallet = false;
                            static bool esp_window = false;
                            static bool esp_hatch = false;
                            static bool esp_trap = false;
                            static bool esp_locker = false;
                            static bool esp_door = false;
                            static bool crosshair = false;
                            static float crosshair_color[4] = { 255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f };

                            ImGui::Checkbox("Enable Text ESP", &esp);
                            ImGui::Checkbox("ESP Name", &esp_name);
                            ImGui::Checkbox("ESP Meters", &esp_meters);
                            ImGui::Checkbox("ESP Objects", &esp_obj);
                            ImGui::Checkbox("ESP Generator", &esp_gen);
                            ImGui::Checkbox("ESP Escape door", &esp_escape_door);
                            ImGui::Checkbox("ESP Totem", &esp_totem);
                            ImGui::Checkbox("ESP Chest", &esp_chest);
                            ImGui::Checkbox("ESP Hook", &esp_hook);
                            ImGui::Checkbox("ESP Pallet", &esp_pallet);
                            ImGui::Checkbox("ESP Window", &esp_window);
                            ImGui::Checkbox("ESP Hatch", &esp_hatch);
                            ImGui::Checkbox("ESP Trap", &esp_trap);
                            ImGui::Checkbox("ESP Locker", &esp_locker);
                            ImGui::Checkbox("ESP Door", &esp_door);
                            ImGui::Checkbox("Crosshair", &crosshair);
                            if (crosshair) {
                                ImGui::ColorEdit4("Crosshair color", crosshair_color);
                            }

                        
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(382, 70));
                        ImGui::BeginChild("ESP Colors", ImVec2(282, 470));

                            static float esp_surv[4] = {0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                            static float esp_killer[4] = { 255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.f };
                            static float esp_surv_vis[4] = { 29.f / 255.f, 124.f / 255.f, 203.f / 255.f, 1.f };
                            static float esp_killer_vis[4] = { 255.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                            static float esp_breakable[4] = { 135.f / 255.f, 245.f / 255.f, 153.f / 255.f, 1.f };
                            static float esp_generator[4] = { 255.f / 255.f, 0.f / 255.f, 68.f / 255.f, 1.f };
                            static float esp_escape[4] = { 222.f / 255.f, 7.f / 255.f, 200.f / 255.f, 1.f };
                            static float esp_totems[4] = { 2.f / 255.f, 227.f / 255.f, 219.f / 255.f, 1.f };
                            static float esp_chests[4] = { 110.f / 255.f, 56.f / 255.f, 2.f / 255.f, 1.f };
                            static float esp_hooks[4] = { 255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f };
                            static float esp_pallets[4] = { 207.f / 255.f, 74.f / 255.f, 12.f / 255.f, 1.f };
                            static float esp_windows[4] = { 119.f / 255.f, 3.f / 255.f, 252.f / 255.f, 1.f };
                            static float esp_closet[4] = { 84.f / 255.f, 48.f / 255.f, 8.f / 255.f, 1.f };
                            static float hatch[4] = { 160.f / 255.f, 163.f / 255.f, 0.f / 255.f, 1.f };
                            static float esp_traps[4] = { 0.f / 255.f, 153.f / 255.f, 255.f / 255.f, 1.f };

                            ImGui::ColorEdit4("Survivor color", esp_surv);
                            ImGui::ColorEdit4("Killer color", esp_killer);
                            ImGui::ColorEdit4("Survivor visible color", esp_surv_vis);
                            ImGui::ColorEdit4("Killer visible color", esp_killer_vis);
                            ImGui::ColorEdit4("Breakable color", esp_breakable);
                            ImGui::ColorEdit4("Generator color", esp_generator);
                            ImGui::ColorEdit4("Escape door color", esp_escape);
                            ImGui::ColorEdit4("Totem color", esp_totems);
                            ImGui::ColorEdit4("Chest color", esp_chests);
                            ImGui::ColorEdit4("Hook color", esp_hooks);
                            ImGui::ColorEdit4("Pallet color", esp_pallets);
                            ImGui::ColorEdit4("Window color", esp_windows);
                            ImGui::ColorEdit4("Closet color", esp_closet);
                            ImGui::ColorEdit4("Hatch color", hatch);
                            ImGui::ColorEdit4("Trap color", esp_traps);



                        ImGui::EndChild();
                    

                }

                    if (selection_count == 1)
                {

                    ImGui::SetCursorPos(ImVec2(85, 70));
                    ImGui::BeginChild("Aura ESP", ImVec2(282, 470));

                    static bool aura_esp = false;
                    static bool aura_survivor = false;
                    static bool aura_killer = false;
                    static bool aura_breakable = false;
                    static bool aura_gen = false;
                    static bool aura_escape_door = false;
                    static bool aura_totem = false;
                    static bool aura_chest = false;
                    static bool aura_hook = false;
                    static bool aura_pallet = false;
                    static bool aura_window = false;
                    static bool aura_hatch = false;
                    static bool aura_trap = false;
                    static bool aura_locker = false;
                    static bool aura_door = false;

                    ImGui::Checkbox("Enable Aura ESP", &aura_esp);
                    ImGui::Checkbox("Survivor", &aura_survivor);
                    ImGui::Checkbox("Killer", &aura_killer);
                    ImGui::Checkbox("Breakable", &aura_breakable);
                    ImGui::Checkbox("Generator", &aura_gen);
                    ImGui::Checkbox("Escape door", &aura_escape_door);
                    ImGui::Checkbox("Totem", &aura_totem);
                    ImGui::Checkbox("Chest", &aura_chest);
                    ImGui::Checkbox("Hook", &aura_hook);
                    ImGui::Checkbox("Pallet", &aura_pallet);
                    ImGui::Checkbox("Window", &aura_window);
                    ImGui::Checkbox("Closet", &aura_hatch);
                    ImGui::Checkbox("Hatch", &aura_trap);
                    ImGui::Checkbox("Trap", &aura_locker);

                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(382, 70));
                    ImGui::BeginChild("Aura Colors", ImVec2(282, 470));

                    static float aura_surv[4] = { 0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                    static float aura_killer_outline[4] = { 255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.f };
                    static float aura_surv_vis[4] = { 29.f / 255.f, 124.f / 255.f, 203.f / 255.f, 1.f };
                    static float aura_killer_vis[4] = { 255.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                    static float aura_breakable_outline[4] = { 135.f / 255.f, 245.f / 255.f, 153.f / 255.f, 1.f };
                    static float aura_generator[4] = { 255.f / 255.f, 0.f / 255.f, 68.f / 255.f, 1.f };
                    static float aura_escape[4] = { 222.f / 255.f, 7.f / 255.f, 200.f / 255.f, 1.f };
                    static float aura_totems[4] = { 2.f / 255.f, 227.f / 255.f, 219.f / 255.f, 1.f };
                    static float aura_chests[4] = { 110.f / 255.f, 56.f / 255.f, 2.f / 255.f, 1.f };
                    static float aura_hooks[4] = { 255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f };
                    static float aura_pallets[4] = { 207.f / 255.f, 74.f / 255.f, 12.f / 255.f, 1.f };
                    static float aura_windows[4] = { 119.f / 255.f, 3.f / 255.f, 252.f / 255.f, 1.f };
                    static float aura_closet[4] = { 84.f / 255.f, 48.f / 255.f, 8.f / 255.f, 1.f };
                    static float aura_hatch_outline[4] = { 160.f / 255.f, 163.f / 255.f, 0.f / 255.f, 1.f };
                    static float aura_traps[4] = { 0.f / 255.f, 153.f / 255.f, 255.f / 255.f, 1.f };

                    ImGui::ColorEdit4("Outline Survivor color", aura_surv);
                    ImGui::ColorEdit4("Outline Killer color", aura_killer_outline);
                    ImGui::ColorEdit4("Outline Breakable color", aura_breakable_outline);
                    ImGui::ColorEdit4("Outline Generator color", aura_generator);
                    ImGui::ColorEdit4("Outline Escape door color", aura_escape);
                    ImGui::ColorEdit4("Outline Totem color", aura_totems);
                    ImGui::ColorEdit4("Outline Chest color", aura_chests);
                    ImGui::ColorEdit4("Outline Hook color", aura_hooks);
                    ImGui::ColorEdit4("Outline Pallet color", aura_pallets);
                    ImGui::ColorEdit4("Outline Window color", aura_windows);
                    ImGui::ColorEdit4("Outline Closet color", aura_closet);
                    ImGui::ColorEdit4("Outline Hatch color", aura_hatch_outline);
                    ImGui::ColorEdit4("Outline Trap color", aura_traps);

                    ImGui::Button("Apply outline color changes", ImVec2(200, 40));

                    ImGui::EndChild();
                }

                    if (selection_count == 2)
                {

                    ImGui::SetCursorPos(ImVec2(85, 70));
                    ImGui::BeginChild("Miscellaneous", ImVec2(282, 470));

                    static bool misc_jump = false;
                    static bool misc_auto_skillcheck = false;
                    static bool misc_trap_immunity = false;
                    static bool misc_hook = false;
                    static bool misc_one_hit = false;
                    static bool misc_instant_interaction = false;
                    static bool misc_fov = false;
                    static bool misc_speedhack = false;
                    static int fov_slider = 0;
                    static int speed_slider = 0;
                    static int speed_count = 0;
                    const char* misc_speed_key[2] = { "Toggle", "Hold" };

                    ImGui::Checkbox("Jump", &misc_jump);
                    ImGui::Checkbox("Auto skillcheck", &misc_auto_skillcheck);
                    ImGui::Checkbox("Trap immunity", &misc_trap_immunity);
                    ImGui::Checkbox("Hook", &misc_hook);
                    ImGui::Checkbox("One hit", &misc_one_hit);
                    ImGui::Checkbox("Instant interaction", &misc_instant_interaction);
                    ImGui::Checkbox("FOV", &misc_fov);
                    if (misc_fov) {
                        ImGui::SliderInt("Field of view:", &fov_slider, 0, 100);
                    }
                    ImGui::Checkbox("Speedhack", &misc_speedhack);
                    if (misc_speedhack) {
                        ImGui::Combo("Speed system:", &speed_count, misc_speed_key, 2);
                        ImGui::SliderInt("Speed multiplier:", &speed_slider, 0, 100);
                        ImGui::Text("Movement: W, A, S, D & SPACE");
                    }
                    

                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(382, 70));
                    ImGui::BeginChild("Others", ImVec2(282, 470));

                    ImGui::Button("Unlock all cosmetics", ImVec2(262, 40));
                    ImGui::Button("Escape the trial", ImVec2(262, 40));

                    ImGui::EndChild();
                }

                    if (selection_count == 3)
                {

                    ImGui::SetCursorPos(ImVec2(85, 70));
                    ImGui::BeginChild("Hotkeys", ImVec2(579, 470));

                        ImGui::Button("NONE##speedhack", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("Speedhack");

                        ImGui::Button("NONE##jump", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("Jump");

                        ImGui::Button("NONE##hook", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("Hook");

                        ImGui::Button("NONE##unhook", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("Unhook");

                        ImGui::Button("NONE##one_hit", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("One hit");

                        ImGui::Button("NONE##instant_interaction", ImVec2(70, 20));
                        ImGui::SameLine();
                        ImGui::Text("Instant interaction");
                    

                    ImGui::EndChild();
                }

                    if (selection_count == 4)
                {

                    ImGui::SetCursorPos(ImVec2(85, 70));
                    ImGui::BeginChild("UI Settings", ImVec2(579, 470));

                    static float color[4] = { 130.f / 255.f, 34.f / 255.f, 35.f / 255.f, 1.f };
                    if (ImGui::ColorEdit4("UI Accent Color", color))
                    {
                        accent_color[0] = color[0] * 255.f;
                        accent_color[1] = color[1] * 255.f;
                        accent_color[2] = color[2] * 255.f;

                    }

                    ImGui::EndChild();
                }

                ImGui::EndGroup();
            }
            ImGui::End();

        }


        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

// кто это читает, тот пидарас
