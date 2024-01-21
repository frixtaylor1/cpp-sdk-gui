#include <windows.h>

#include "./GUI/Window/Windows/Window.hpp"

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WindowWindows window(
        L"Hello, World!",
        200, 200,
        1024, 768,
        nCmdShow,
        hInstance
    );

    window.render();
    window.run();

    double x = GetSystemMetrics(SM_CXSCREEN);
    double y = GetSystemMetrics(SM_CYSCREEN);

    printf("The screen size is: %dx%d\n", static_cast<int>(x), static_cast<int>(y));

    return 0;
}
