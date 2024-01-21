#include <windows.h>
#pragma comment(lib, "user32.lib")

#include "../IWindow.hpp"

class WindowWindows implements IWindow {
public:
    WindowWindows() : m_handle(nullptr), m_parentWindows(false) {
        initialize();
    }

    WindowWindows(LPCWSTR title, float x, float y, float width, float height, int nCmdShow, HINSTANCE hInstance)
        : m_title(title), m_posX(x), m_posY(y), m_width(width), m_height(height), m_handle(nullptr), m_parentWindows(false), m_nCmdShow(nCmdShow), m_hInstance(hInstance) {
        initialize();
    }

    ~WindowWindows() {
    }

    void setTitle(void* title) override {
        m_title = static_cast<LPCWSTR>(title);
    }

    void setSize(float width, float height) override {
        m_width = width;
        m_height = height;
    }

    void setHandle(void* handle) override {
        m_handle = static_cast<HWND>(handle);
    }

    void render() override {
        RegisterClassW(&m_wc);
        m_handle = CreateWindowW(
            m_wc.lpszClassName, 
            m_title,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            m_posX,
            m_posY,
            m_width,
            m_height,
            NULL,
            NULL,
            m_hInstance,
            NULL
        );

        ShowWindow(m_handle, m_nCmdShow);
        UpdateWindow(m_handle);
    }

    void run() {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void* getHandleInstance() override {
        return m_handle;
    }

    bool isParentWindow() override {
        return m_parentWindows;
    }

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        WindowWindows* pWindow = nullptr;

        if (msg == WM_NCCREATE) {
            CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            pWindow = static_cast<WindowWindows*>(pCreateStruct->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        } else {
            pWindow = reinterpret_cast<WindowWindows*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pWindow) {
            switch (msg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }
        }

        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    void initialize() {
        m_wc.style          = CS_HREDRAW | CS_VREDRAW;
        m_wc.cbClsExtra     = 0;
        m_wc.cbWndExtra     = sizeof(LONG_PTR);
        m_wc.lpszClassName  = L"MyWindowClass";
        m_wc.hInstance      = m_hInstance;
        m_wc.hbrBackground  = GetSysColorBrush(COLOR_3DFACE);
        m_wc.lpszMenuName   = NULL;
        m_wc.lpfnWndProc    = &WndProc;
        m_wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        m_wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    }

    float       m_posX,
                m_posY,
                m_width,
                m_height;
    bool        m_parentWindows;
    int         m_nCmdShow;

    HWND        m_handle;
    HINSTANCE   m_hInstance;
    WNDCLASSW   m_wc;
    MSG         m_msg;
    LPCWSTR     m_title;
};
