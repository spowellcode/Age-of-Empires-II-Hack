#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

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

int main()
{
    float food = 2040;
    DWORD Mem = 0;
    DWORD StoneMem = 0;
    DWORD GoldMem = 0;
    DWORD WoodMem = 0;
    float readTest = 0;
    DWORD off1 = 0x0028E8F8;
    DWORD off2 = 0;
    DWORD off3 = 0;
    char moduleName[] = "age2_x1.exe";
    DWORD baseAddress;


    HWND hwnd = FindWindowA(NULL, "Age of Empires II Expansion");
    if (hwnd == NULL)
    {
        cout << "Could not find window." << endl;
        Sleep(3000);
        exit(-1);
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

        DWORD clientBase = dwGetModuleBaseAddress(_T(moduleName), procID);
        ReadProcessMemory(handle, (LPCVOID)(clientBase + 0x0028E8F8), &baseAddress, sizeof(baseAddress), NULL);
        cout << "Base Addy is: " << std::hex << baseAddress << std::endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4c), &baseAddress, sizeof(baseAddress), NULL);
        cout << "1: " << std::hex << baseAddress << std::endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4), &baseAddress, sizeof(baseAddress), NULL);
        cout << "2: " << std::hex << baseAddress << std::endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0xa8), &baseAddress, sizeof(baseAddress), NULL);
        cout << "3: " << std::hex << baseAddress << std::endl;
        Mem = baseAddress;

        if (procID = NULL)
        {
            cout << "Could not obtain process." << endl;
            Sleep(3000);
            exit(-1);
        }

        else
        {
            ReadProcessMemory(handle, (PBYTE*)Mem, &readTest, sizeof(float), 0);
            cout << "\nPlayer 1\n\nFood: ";
            cout << readTest << endl;

            StoneMem = Mem + 4;
            ReadProcessMemory(handle, (PBYTE*)StoneMem, &readTest, sizeof(float), 0);
            cout << "Wood: ";
            cout << readTest << endl;

            WoodMem = Mem + 8;
            ReadProcessMemory(handle, (PBYTE*)WoodMem, &readTest, sizeof(float), 0);
            cout << "Stone: ";
            cout << readTest << endl;

            GoldMem = Mem + 12;
            ReadProcessMemory(handle, (PBYTE*)GoldMem, &readTest, sizeof(float), 0);
            cout << "Gold: ";
            cout << readTest << endl;
            Sleep(100000);

            WriteProcessMemory(handle, (LPVOID)Mem, &food, sizeof(food), 0);
        }
    }

}

