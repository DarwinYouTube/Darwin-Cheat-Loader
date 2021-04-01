typedef NTSTATUS(__stdcall* f_NtCreateThreadEx)(HANDLE* pHandle, ACCESS_MASK DesiredAccess, void* pAttr, HANDLE hProc, void* pFunc, void* pArg,
    ULONG Flags, SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaxStackSize, void* pAttrListOut);

HANDLE StartRoutine(HANDLE hTargetProc, void* pRoutine, void* pArg);

int Inject(const char* szDllFile, HANDLE hProc);