// This file is a part of tiger engine.

#include <Windows.h>
#include <iostream>
#include <algorithm>

#if TIGER_INONE
#include "tiger.h"
#else

extern "C"
{
    __declspec(dllimport) void run_game(int argc, char **argv);
}

#endif

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
        // Do nothing, to avoid onexit assert.
    case CTRL_CLOSE_EVENT:
        return TRUE;
        // Pass through, let the system to handle the event.
    default:
        return FALSE;
    }
}

void setup_console()
{
    ::AllocConsole();
    {
        COORD  coord = { 124, 8000 };
        HANDLE ho    = ::GetStdHandle(STD_OUTPUT_HANDLE);
        ::SetConsoleScreenBufferSize(ho, coord);

        _CONSOLE_SCREEN_BUFFER_INFO info;
        ::GetConsoleScreenBufferInfo(ho, &info);
        SMALL_RECT windowMaxSize = {
            (SHORT)0, (SHORT)0, (SHORT)(info.dwMaximumWindowSize.X - 1), (SHORT)(info.dwMaximumWindowSize.Y - 1)
        };
        SMALL_RECT rect = { (SHORT)0,
                            (SHORT)0,
                            (SHORT)windowMaxSize.Right,
                            std::min<SHORT>((SHORT)(windowMaxSize.Bottom / 2), (SHORT)45) };
        ::SetConsoleWindowInfo(ho, TRUE, &rect);
        ::SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);

        // enable virtual terminal sequences (@ref
        // https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences) for colorful output
        DWORD dwOriginalOutMode = 0;
        ::GetConsoleMode(ho, &dwOriginalOutMode);
        ::SetConsoleMode(ho, dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        ::SetConsoleTitle(L"Tigerkin Console");
    }

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

// WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
#if !_FINAL
    bool wait_debugger = false;
    bool console = true;
    // waiting for debugger attched...
    if (wait_debugger)
    {
        do
        {
            if (::MessageBoxW(nullptr, L"Waiting for debugger attached...", L"Tiger Engine", MB_OKCANCEL) == IDOK)
            {
                break;
            };
        } while (!::IsDebuggerPresent());
    }
    // setup console
    if (console)
    {
        setup_console();
    }
#endif

    int argc = 0;
    char **argv = nullptr;

    std::cout << "Hello Tiger!" << std::endl;
    run_game(argc, argv);

    while(true)
    {
        Sleep(1);
    }
    return 0;
}