#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

DWORD dwGetModuleBaseAddress
(TCHAR *lpszModuleName, DWORD pID) {
    DWORD dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32))
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
            {
                dwModuleBaseAddress = (DWORDLONG)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32));


    }
    CloseHandle(hSnapshot);
    return dwModuleBaseAddress;
}

int main()
{
    float food, wood, stone, gold;
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
    bool coderunning = true;


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
        cout << "Base Addy is: " << hex << baseAddress << endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4c), &baseAddress, sizeof(baseAddress), NULL);
        cout << "1: " << hex << baseAddress << endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4), &baseAddress, sizeof(baseAddress), NULL);
        cout << "2: " << hex << baseAddress << endl;
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0xa8), &baseAddress, sizeof(baseAddress), NULL);
        cout << "3: " << hex << baseAddress << endl;
        Mem = baseAddress;

        if (procID = NULL)
        {
            cout << "Could not obtain process." << endl;
            Sleep(3000);
            exit(-1);
        }

        else
        {
            do{
            system("title AOEII Food Hack");
            int option = 0;

            ReadProcessMemory(handle, (PBYTE*)Mem, &readTest, sizeof(float), 0);
            cout << "\nPlayer 1\n\n1:Food: ";
            cout << readTest << endl;
            food = readTest;

            WoodMem = Mem + 4;
            ReadProcessMemory(handle, (PBYTE*)WoodMem, &readTest, sizeof(float), 0);
            cout << "2:Wood: ";
            cout << readTest << endl;
            wood = readTest;

            StoneMem = Mem + 8;
            ReadProcessMemory(handle, (PBYTE*)StoneMem, &readTest, sizeof(float), 0);
            cout << "3:Stone: ";
            cout << readTest << endl;
            stone = readTest;

            GoldMem = Mem + 12;
            ReadProcessMemory(handle, (PBYTE*)GoldMem, &readTest, sizeof(float), 0);
            cout << "4:Gold: ";
            cout << readTest << endl;
            gold = readTest;

            cout << "\nSelect Resource to change >";
            cin >> option;

            if (option == 1){
                system("cls");

                cout << "Food is currently " << food << "\n\nNew Value >";
                cin >> food;
                WriteProcessMemory(handle, (LPVOID)Mem, &food, sizeof(food), 0);
            }
            if (option == 2){
                system("cls");

                cout << "Wood is currently " << wood << "\n\nNew Value >";
                cin >> wood;
                WriteProcessMemory(handle, (LPVOID)WoodMem, &wood, sizeof(wood), 0);
            }
            if (option == 3){
                system("cls");

                cout << "Stone is currently " << stone << "\n\nNew Value >";
                cin >> stone;
                WriteProcessMemory(handle, (LPVOID)StoneMem, &stone, sizeof(StoneMem), 0);
            }
            if (option == 4){
                system("cls");

                cout << "Gold is currently " << gold << "\n\nNew Value >";
                cin >> gold;
                WriteProcessMemory(handle, (LPVOID)GoldMem, &gold, sizeof(gold), 0);
            }


            system("cls");

            }while(coderunning == true);
        }
    }

}

