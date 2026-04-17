#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <living.hpp>

std::wstring stringToWstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    
    // Calculate size needed
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstr[0], size_needed);
    
    return wstr;
}

// Helper to convert double to string with precision
std::wstring to_wstring_with_precision(double val, int precision = 2) {
    std::wstringstream ss;
    ss.precision(precision);
    ss << std::fixed << val;
    return ss.str();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND field1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"LivingCharacterWindow";
    
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Living Character Attributes",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );


    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    //UpdateWindow(hwnd);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static Living character;
    static bool initialized = false;

    if (!initialized) {
        NameGenerator generator;
        character.setName(generator.getRandomName());
        initialized = true;
    }

    switch (uMsg) {
    case WM_CREATE: {
        field1 = CreateWindow(L"STATIC", L"It works", WS_VISIBLE | WS_CHILD, 0, 0, 
            0,0, hwnd, NULL, NULL, NULL);
        
        SetTimer(hwnd, 1, 1000, NULL); // Update every second
        return 0;
    }

    case WM_SIZE: {
        int windowWidth = LOWORD(lParam);
        int editWidth = 150;  // Define how wide you want the text field
        int editHeight = 25;  // Define how tall you want it
        int padding = 10;     // Space from the right edge

        // MoveWindow(handle, x, y, width, height, redraw)
        // x = (Total Width) - (Edit Width) - (Padding)
        MoveWindow(field1, windowWidth - editWidth - padding, 10, editWidth, editHeight, TRUE);
        break;
    }

    case WM_TIMER: {
        std::wstring cc = stringToWstring(character.return_stat());
        std::wstring w = stringToWstring(character.getName()); 
        std::wstring ww = stringToWstring(character.getMagicClassName());
        std::wstring displayText = L"Name: " + w + L"\n" +
                                   L"Strength: " + to_wstring_with_precision(character.getStrength()) + L"\n" +
                                   L"Durability: " + to_wstring_with_precision(character.getDurability()) + L"\n" +
                                   L"Speed: " + to_wstring_with_precision(character.getSpeed()) + L"\n" +
                                   L"Stamina: " + to_wstring_with_precision(character.getStamina()) + L"\n" +
                                   L"Recovery: " + to_wstring_with_precision(character.getRecovery()) + L"\n" +
                                   L"Reflexes: " + to_wstring_with_precision(character.getReflexes()) + L"\n" +
                                   L"Thinking: " + to_wstring_with_precision(character.getThinking()) + L"\n" +
                                   L"Magic Class: " + ww + L"\n" +
                                   L"Magical Strength: " + to_wstring_with_precision(character.getMagicalStrength()) + L"\n" +
                                   L"Magical Casting Speed: " + to_wstring_with_precision(character.getMagicalCastingSpeed()) + L"\n" +
                                   L"Magical Recovery: " + to_wstring_with_precision(character.getMagicalRecovery()) + L"\n";

        SetWindowText(field1, cc.c_str());
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
