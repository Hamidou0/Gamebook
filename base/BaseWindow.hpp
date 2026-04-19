#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <sstream>
#include <living.hpp>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

template <class T>
class BaseWindow {
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        T* pApp = NULL;
        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pApp = (T*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pApp);
            pApp->m_hwnd = hwnd;
        } else {
            pApp = (T*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pApp) return pApp->HandleMessage(uMsg, wParam, lParam);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    HWND m_hwnd = NULL;
};