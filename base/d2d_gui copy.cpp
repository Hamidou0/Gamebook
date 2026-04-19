#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <sstream>
#include <living.hpp>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

template <class T> void SafeRelease(T **ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class CharacterApp {
private:
    HWND hwnd;
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pTextBrush;
    ID2D1SolidColorBrush* pHeaderBrush;
    IDWriteFactory* pWriteFactory;
    IDWriteTextFormat* pTextFormat;
    IDWriteTextFormat* pHeaderFormat;

    Living character;
    float currentY;

    HRESULT CreateDeviceIndependentResources() {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
        if (SUCCEEDED(hr)) {
            hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory));
        }
        if (SUCCEEDED(hr)) {
            hr = pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us", &pTextFormat);
        }
        if (SUCCEEDED(hr)) {
            hr = pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16.0f, L"en-us", &pHeaderFormat);
        }
        return hr;
    }

    HRESULT CreateDeviceResources() {
        HRESULT hr = S_OK;
        if (!pRenderTarget) {
            RECT rc;
            GetClientRect(hwnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
            hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, size), &pRenderTarget);
            if (SUCCEEDED(hr)) {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pTextBrush);
            }
            if (SUCCEEDED(hr)) {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkBlue), &pHeaderBrush);
            }
        }
        return hr;
    }

    void DiscardDeviceResources() {
        SafeRelease(&pRenderTarget);
        SafeRelease(&pTextBrush);
        SafeRelease(&pHeaderBrush);
    }

    std::wstring to_wstring_with_precision(double val, int precision = 2) {
        std::wstringstream ss;
        ss.precision(precision);
        ss << std::fixed << val;
        return ss.str();
    }

    void DrawRow(const std::wstring& label, const std::wstring& value, bool isHeader = false) {
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        D2D1_RECT_F layoutRect = D2D1::RectF(20.0f, currentY, size.width - 20.0f, currentY + 20.0f);
        
        std::wstring fullText = label + L" " + value;
        pRenderTarget->DrawText(fullText.c_str(), (UINT32)fullText.length(), isHeader ? pHeaderFormat : pTextFormat, layoutRect, isHeader ? pHeaderBrush : pTextBrush);
        currentY += isHeader ? 25.0f : 20.0f;
    }

public:
    CharacterApp() : hwnd(NULL), pFactory(NULL), pRenderTarget(NULL), pTextBrush(NULL), pHeaderBrush(NULL), pWriteFactory(NULL), pTextFormat(NULL), pHeaderFormat(NULL) {
        NameGenerator generator;
        character.setName(generator.getRandomName());
        character.genAll();
    }

    ~CharacterApp() {
        DiscardDeviceResources();
        SafeRelease(&pFactory);
        SafeRelease(&pWriteFactory);
        SafeRelease(&pTextFormat);
        SafeRelease(&pHeaderFormat);
    }

    HRESULT Initialize() {
        HRESULT hr = CreateDeviceIndependentResources();
        if (FAILED(hr)) return hr;

        WNDCLASS wc = { };
        wc.lpfnWndProc = CharacterApp::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"CharacterAppClass";
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);

        RegisterClass(&wc);

        hwnd = CreateWindowEx(0, L"CharacterAppClass", L"Direct2D Character Attributes", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 800, NULL, NULL, GetModuleHandle(NULL), this);
        
        return hwnd ? S_OK : E_FAIL;
    }

    void RunMessageLoop() {
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        CharacterApp* pApp = NULL;
        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pApp = reinterpret_cast<CharacterApp*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp));
        } else {
            pApp = reinterpret_cast<CharacterApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pApp) {
            switch (uMsg) {
            case WM_PAINT:
                pApp->OnRender();
                ValidateRect(hwnd, NULL);
                return 0;
            case WM_SIZE:
                pApp->OnResize(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void OnRender() {
        if (SUCCEEDED(CreateDeviceResources())) {
            pRenderTarget->BeginDraw();
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
            currentY = 20.0f;

            HRESULT hr = pRenderTarget->EndDraw();
            if (hr == D2DERR_RECREATE_TARGET) {
                DiscardDeviceResources();
            }
        }
    }

    void OnResize(UINT width, UINT height) {
        if (pRenderTarget) {
            pRenderTarget->Resize(D2D1::SizeU(width, height));
        }
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    if (SUCCEEDED(CoInitialize(NULL))) {
        {
            CharacterApp app;
            if (SUCCEEDED(app.Initialize())) {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }
    return 0;
}
