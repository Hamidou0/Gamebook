#ifndef UNICODE
#define UNICODE
#endif 

#include "BaseWindow.hpp"
#include <living.hpp>
#include <fight.hpp>
#include <techniques_list.hpp>

class GameApp : public BaseWindow<GameApp> {
    // Game Logic
    Living char1 = Living();
    Living char2 = Living();
    Fight fight = Fight(&char1, &char2);

    ID2D1SolidColorBrush* pRedBrush = nullptr;
    ID2D1SolidColorBrush* pGreenBrush = nullptr;
    ID2D1SolidColorBrush* pOutlineBrush = nullptr;

    // Direct2D Resources
    ID2D1Factory* pFactory = nullptr;
    ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    ID2D1SolidColorBrush* pBrush = nullptr;
    IDWriteFactory* pWriteFactory = nullptr;
    IDWriteTextFormat* pTextFormat = nullptr;

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

void DrawHealthBar(float x, float y, float width, float height, float current, float max) {
    // 1. Calculate the fill ratio
    float healthRatio = current / max;
    if (healthRatio < 0) healthRatio = 0;

    // 2. Define the rectangles
    D2D1_RECT_F fullBar = D2D1::RectF(x, y, x + width, y + height);
    D2D1_RECT_F healthFill = D2D1::RectF(x, y, x + (width * healthRatio), y + height);

    // 3. Draw Background (Red)
    pRenderTarget->FillRectangle(fullBar, pRedBrush);

    // 4. Draw Foreground (Green)
    pRenderTarget->FillRectangle(healthFill, pGreenBrush);

    // 5. Draw Outline (Gray)
    pRenderTarget->DrawRectangle(fullBar, pOutlineBrush, 1.5f);
}

void DrawVerticalHealthBar(float x, float y, float width, float height, float current, float max) {
    float healthRatio = current / max;
    if (healthRatio < 0) healthRatio = 0;
    if (healthRatio > 1) healthRatio = 1;

    // The background (Red)
    D2D1_RECT_F backgroundRect = D2D1::RectF(x, y, x + width, y + height);
    
    // The foreground (Green) - Filling from bottom to top
    // Top = Bottom - (Total Height * Ratio)
    float fillTop = (y + height) - (height * healthRatio);
    D2D1_RECT_F foregroundRect = D2D1::RectF(x, fillTop, x + width, y + height);

    pRenderTarget->FillRectangle(backgroundRect, pRedBrush);
    pRenderTarget->FillRectangle(foregroundRect, pGreenBrush);
    pRenderTarget->DrawRectangle(backgroundRect, pOutlineBrush, 1.0f);
}

template <class T> void SafeRelease(T **ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = NULL;
    }
}



    void CreateGraphicsResources() {
        if (!pRenderTarget) {
            RECT rc;
            GetClientRect(m_hwnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
            pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), 
                D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);
            pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);

pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pRedBrush);
pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LimeGreen), &pGreenBrush);
pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DimGray), &pOutlineBrush);
    

            // Text Setup
            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFactory), (IUnknown**)&pWriteFactory);
            pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"", &pTextFormat);
        }
    }

    void OnPaint() {
        CreateGraphicsResources();
        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        D2D1_SIZE_F size = pRenderTarget->GetSize();
        float columnWidth = size.width / 3.0f;
        float barH = 20.0f; // Height of health bar



double colW = 400.0f;
double gap = 10.0f;
double barWidth = 20.0f;
double barHeight = 200.0f;

// --- Player 1 (Left) ---
    // Assuming char1 has methods like getHealth() and getMaxHealth()
    DrawVerticalHealthBar(colW - barWidth - gap, 10, barWidth, barHeight, char1.getHealth(), char1.getMaxHealth());
    
    std::wstring stats1 = stringToWstring(char1.return_char());
    pRenderTarget->DrawText(stats1.c_str(), stats1.length(), pTextFormat,
        D2D1::RectF(10, 10 + barH + 5, colW - 10, size.height), pBrush);

    // --- Fight Log (Middle) ---
    std::wstring logs = stringToWstring(fight.getLog_clear());
    pRenderTarget->DrawText(logs.c_str(), logs.length(), pTextFormat,
        D2D1::RectF(colW, 10, colW * 2 - 10, size.height), pBrush);

    // --- Player 2 (Right) ---
    DrawHealthBar(colW * 2 + 10, 10, colW - 20, barH, char2.getHealth(), char2.getMaxHealth());
    
    std::wstring stats2 = stringToWstring(char2.return_char());
    pRenderTarget->DrawText(stats2.c_str(), stats2.length(), pTextFormat,
        D2D1::RectF(colW * 2 + 10, 10 + barH + 5, size.width - 10, size.height), pBrush);

        pRenderTarget->EndDraw();
    }

public:
    GameApp() {
            NameGenerator gen;
        char1.setName(gen.getRandomName());
        char2.setName(gen.getRandomName());
        char1.genAll(); char2.genAll();
        char1.addTechnique(2, fistPunch);
        char2.addTechnique(2, legKick);
        
        fight.simulate(1,0);
    }

    virtual ~GameApp() {
        SafeRelease(&pFactory);
        SafeRelease(&pRenderTarget);
        SafeRelease(&pBrush);
        SafeRelease(&pWriteFactory);
        SafeRelease(&pTextFormat);
        SafeRelease(&pRedBrush);
        SafeRelease(&pGreenBrush);
        SafeRelease(&pOutlineBrush);
    }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CREATE:
            SetTimer(m_hwnd, 1, 1000, NULL);
            return 0;

        case WM_TIMER:
            fight.nextTurn();
            InvalidateRect(m_hwnd, NULL, FALSE); // Trigger OnPaint
            return 0;

        case WM_PAINT:
            OnPaint();
            ValidateRect(m_hwnd, NULL);
            return 0;

        case WM_SIZE: {
            if (pRenderTarget) {
                D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));
                pRenderTarget->Resize(size);
            }
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR, int nCmdShow) {
    GameApp app;

    WNDCLASS wc = { };
    wc.lpfnWndProc = GameApp::WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"GameWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, L"GameWindowClass", L"OOP Direct2D RPG", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800, 
        NULL, NULL, hInst, &app);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}