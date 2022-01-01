#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>
#include <thread>

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

bool freezefood, freezegold, freezestone, freezewood;
//Below are the functions that run on the thread that allow the program to keep a resource value constant.
void FreezeFoodResource(HANDLE handle, long address, float amount){
    do{
    WriteProcessMemory(handle, (LPVOID)address, &amount, sizeof(amount), 0);
    }while(freezefood == true);
}

void FreezeWoodResource(HANDLE handle, long address, float amount){
    do{
    WriteProcessMemory(handle, (LPVOID)address, &amount, sizeof(amount), 0);
    }while(freezewood == true);
}

void FreezeStoneResource(HANDLE handle, long address, float amount){
    do{
    WriteProcessMemory(handle, (LPVOID)address, &amount, sizeof(amount), 0);
    }while(freezestone == true);
}

void FreezeGoldResource(HANDLE handle, long address, float amount){
    do{
    WriteProcessMemory(handle, (LPVOID)address, &amount, sizeof(amount), 0);
    }while(freezegold == true);
}


int main()
{
    float food, wood, stone, gold;
    //The DWORD "Mem" variables are what store the memory addresses for each resource. Keep in mind that the variable are stored in the same array with in RAM.
    DWORD Mem = 0;
    DWORD StoneMem = 0;
    DWORD GoldMem = 0;
    DWORD WoodMem = 0;

    float readTest = 0;

    //Offset 1 is 0x0028E8F8;

    char moduleName[] = "age2_x1.exe";

    DWORD baseAddress;

    bool coderunning = true; //Keeps program looping.

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

        DWORD clientBase = dwGetModuleBaseAddress(_T(moduleName), procID); // Gets AOEII base address

        ReadProcessMemory(handle, (LPCVOID)(clientBase + 0x0028E8F8), &baseAddress, sizeof(baseAddress), NULL);
        cout << "Base Address is: " << hex << baseAddress << endl;
        //base address
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4c), &baseAddress, sizeof(baseAddress), NULL);
        cout << "1: " << hex << baseAddress << endl;
        //offset 1
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0x4), &baseAddress, sizeof(baseAddress), NULL);
        cout << "2: " << hex << baseAddress << endl;
        //offset 2
        ReadProcessMemory(handle, (LPCVOID)(baseAddress + 0xa8), &baseAddress, sizeof(baseAddress), NULL);
        cout << "3: " << hex << baseAddress << endl;
        //offset 3
        if (procID = NULL)
        {
            cout << "Could not obtain process." << endl;
            Sleep(3000);
            exit(-1);
        }


        else
        {
            do{
            system("title AOEII Hack v1.2");
            string option = "0";

            ReadProcessMemory(handle, (PBYTE*)baseAddress, &readTest, sizeof(float), 0);
            cout << "\nPlayer 1\n\n1:Food: ";
            cout << readTest;
            if (freezefood == true){
                        cout << " *Froze";
                    }
            cout << endl;
            food = readTest;

            WoodMem = baseAddress + 4;
            ReadProcessMemory(handle, (PBYTE*)WoodMem, &readTest, sizeof(float), 0);
            cout << "2:Wood: ";
            cout << readTest;
            if (freezewood == true){
                        cout << " *Froze";
                    }
            cout << endl;
            wood = readTest;

            StoneMem = baseAddress + 8;
            ReadProcessMemory(handle, (PBYTE*)StoneMem, &readTest, sizeof(float), 0);
            cout << "3:Stone: ";
            cout << readTest;
            if (freezestone == true){
                        cout << " *Froze";
                    }
            cout << endl;
            stone = readTest;

            GoldMem = baseAddress + 12;
            ReadProcessMemory(handle, (PBYTE*)GoldMem, &readTest, sizeof(float), 0);
            cout << "4:Gold: ";
            cout << readTest;
            if (freezegold == true){
                        cout << " *Froze";
                    }
            cout << endl;
            gold = readTest;

            cout << "5:Freeze or unfreeze" << endl;

            cout << "\nSelect Resource to change >";
            cin >> option;

            if (option == "1"){
                system("cls");
                cout << "Food is currently " << food;

                cout << "\n\nNew Value >";
                cin >> food;
                WriteProcessMemory(handle, (LPVOID)baseAddress, &food, sizeof(food), 0);
            }
            if (option == "2"){
                system("cls");

                cout << "Wood is currently " << wood << "\n\nNew Value >";
                cin >> wood;
                WriteProcessMemory(handle, (LPVOID)WoodMem, &wood, sizeof(wood), 0);
            }
            if (option == "3"){
                system("cls");

                cout << "Stone is currently " << stone << "\n\nNew Value >";
                cin >> stone;
                WriteProcessMemory(handle, (LPVOID)StoneMem, &stone, sizeof(StoneMem), 0);
            }
            if (option == "4"){
                system("cls");

                cout << "Gold is currently " << gold << "\n\n\nNew Value >";
                cin >> gold;
                WriteProcessMemory(handle, (LPVOID)GoldMem, &gold, sizeof(gold), 0);
            }
            //freeze menu below
            if (option == "5"){
                system("cls");
                cout << "--Freeze Mode--\n1:Food\n2:Wood\n3:Stone\n4:Gold\n5:Back to main menu\n\nSelect >";
                option = "0";
                cin >> option;
                    if (option == "1"){
                        if (!freezefood){
                            freezefood = true;
                        }
                        else {
                            freezefood = false;
                        }
                }
                if (option == "2"){
                        if (!freezewood){
                            freezewood = true;
                        }
                        else {
                            freezewood = false;
                        }
                }
                if (option == "3"){
                        if (!freezestone){
                            freezestone = true;
                        }
                        else {
                            freezestone = false;
                        }
                }if (option == "4"){
                        if (!freezegold){
                            freezegold = true;
                        }
                        else {
                            freezegold = false;
                        }
                }

            }

            else{
                cout << "Invalid" << endl; //Invalid Option
                option = "0";
            }

            //Below here is for the "Freeze" feature. It creates a thread for each resource constant resource count.

                thread FreezeFoodThread(FreezeFoodResource,handle,baseAddress,food);
                thread FreezeWoodThread(FreezeWoodResource,handle,WoodMem,wood);
                thread FreezeStoneThread(FreezeStoneResource,handle,StoneMem,stone);
                thread FreezeGoldThread(FreezeGoldResource,handle,GoldMem,gold);
                // Below detaches from main thread so you can go back to the main menu.
                FreezeFoodThread.detach();
                FreezeWoodThread.detach();
                FreezeStoneThread.detach();
                FreezeGoldThread.detach();



            system("cls");

            }while(coderunning == true);
        }
    }
}
