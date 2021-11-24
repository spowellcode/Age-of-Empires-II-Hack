#ifndef BASEFUNCTION_H_INCLUDED
#define BASEFUNCTION_H_INCLUDED



#endif // BASEFUNCTION_H_INCLUDED

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

   int findbase(){
    DWORD dwGetModuleBaseAddress(TCHAR *lpszModuleName, DWORD pID) {
    DWORD dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32))
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
            {
                dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32));


    }
    CloseHandle(hSnapshot);
    return dwModuleBaseAddress;
}

    DWORD pID;
    DWORD baseAddress;
    char moduleName[] = "age2_x1.exe"
    HWND hGameWindow;
    HANDLE pHandle;

    //Get Handles
    hGameWindow = FindWindow(NULL, "Age of Empires II Expansion");
    GetWindowThreadProcessId(hGameWindow, &pID);
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

    //Get Client Base Addy
    DWORD clientBase = dwGetModuleBaseAddress(_T(moduleName), pID);
    ReadProcessMemory(pHandle, (LPCVOID)(clientBase + 0x04EDCF74), &baseAddress, sizeof(baseAddress), NULL);
    cout << "Base Addy is: " << std::hex << baseAddress << std::endl;
}

