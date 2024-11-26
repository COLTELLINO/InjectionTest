#include "pch.h"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "Malicious DLL Attached and Executed!!!!!!!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_PROCESS_DETACH:
        MessageBoxA(NULL, "Malicious DLL Detached!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_ATTACH:
        MessageBoxA(NULL, "Thread Created!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_DETACH:
        MessageBoxA(NULL, "Thread Terminated!", "WARNING", MB_ICONEXCLAMATION);
        break;
    }
    return TRUE;
}