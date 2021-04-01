#include "isConnect.h"

typedef NTSTATUS(__stdcall* f_NtCreateThreadEx)(HANDLE* pHandle, ACCESS_MASK DesiredAccess, void* pAttr, HANDLE hProc, void* pFunc, void* pArg,
    ULONG Flags, SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaxStackSize, void* pAttrListOut);

HANDLE StartRoutine(HANDLE hTargetProc, void* pRoutine, void* pArg)
{
    auto _NtCTE = reinterpret_cast<f_NtCreateThreadEx>(GetProcAddress(GetModuleHandleA(dchar("ntdll.dll")), dchar("NtCreateThreadEx")));
    if (!_NtCTE)
        return CreateRemoteThreadEx(hTargetProc, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pRoutine), pArg, 0, nullptr, nullptr);

    HANDLE hRet = nullptr;
    _NtCTE(&hRet, THREAD_ALL_ACCESS, nullptr, hTargetProc, pRoutine, pArg, 0, 0, 0, 0, nullptr);
    return hRet;
}

int Inject(const char* szDllFile, HANDLE hProc)
{
    if (!hProc)
        return 1;

    ifstream dll(szDllFile);
    if (!dll.is_open())
        return 1;

    auto Len = lstrlenA(szDllFile);

    void* pArg = VirtualAllocEx(hProc, nullptr, Len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!pArg)
        return 1;

    if (!WriteProcessMemory(hProc, pArg, szDllFile, Len, nullptr))
    {
        VirtualFreeEx(hProc, pArg, 0, MEM_RELEASE);
        return 1;
    }

    DWORD dwExitCode = 0;
    HANDLE hThread = StartRoutine(hProc, LoadLibraryA, pArg);
    if (!hThread)
    {
        VirtualFreeEx(hProc, pArg, 0, MEM_RELEASE);
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);
    GetExitCodeThread(hThread, &dwExitCode);
    CloseHandle(hThread);

    VirtualFreeEx(hProc, pArg, 0, MEM_RELEASE);

    if (!dwExitCode)
        return 1;

    return 0;
}