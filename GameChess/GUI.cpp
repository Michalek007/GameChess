#include "GUI.h"

using namespace std;

void GUI::CreateBoard()
{
    COORD v;
    v.X = 200;
    v.Y = 35;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), v);
   
    COORD d;
    for (int i = 8; i > 0; i--) {
        d.X = 3;
        d.Y = 27 - i * 3;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
        cout << i << endl;
    }
    for (int i = 1; i < 9; i++) {
        d.Y = 27;
        d.X = i * 6 + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
        char z = i + 64;
        cout << z;
    }
    d.X = 5;
    bool k = false;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 24; i++) {
        d.Y = i+2;
        SetConsoleCursorPosition(hConsole, d);
        if (i % 3 == 0) {
            k = !k;
        }
        for (int o = 0; o < 4; o++) {
            if (k == true) {
                SetConsoleTextAttribute(hConsole, 112);
                cout << "      " ;
                SetConsoleTextAttribute(hConsole, 128);
                cout <<  "      ";
            }
            else {
                SetConsoleTextAttribute(hConsole, 128);
                cout << "      ";
                SetConsoleTextAttribute(hConsole, 112);
                cout <<  "      ";
            }
        }
    }
}
void GUI::CreateMenu() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    COORD d{ 0,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << u8"\u250C";
    for (int i = 0; i < 129; i++) {
        cout << u8"\u2500";
    }
    cout << u8"\u2510";
    d.Y = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    for (int i = 0; i < 28; i++) {
        cout << u8"\u2502" << endl;
    }
    cout << u8"\u2514";
    for (int i = 0; i < 129; i++) {
        cout << u8"\u2500";
    }
    cout << u8"\u2518";
    d.X = 130;
    for (int i = 0; i < 28; i++) {
        d.Y = 1 + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
        cout << u8"\u2502";
    }

    d.X = 75;
    d.Y = 12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "New game";
    d.Y = 14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "Save position";
    d.Y = 16;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "Load position";
    d.Y = 18;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "Save game record";
    d.Y = 20;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "Quit";

    d.X = 75;
    d.Y = 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << " a88888b. dP     dP   88888888b .d88888b  .d88888b ";
    d.Y = 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "d8'   `88 88     88   88        88.    \"' 88.    \"' ";
    d.Y = 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "88        88aaaaa88a a88aaaa    `Y88888b. `Y88888b. ";
    d.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "88        88     88   88              `8b       `8b ";
    d.Y = 6;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "Y8.   .88 88     88   88        d8'   .8P d8'   .8P ";
    d.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << " Y88888P' dP     dP   88888888P  Y88888P   Y88888P  ";

    d.X = 100;
    d.Y = 12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "[R] - return last move ";
    d.Y = 14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "[T] - turn on/off vis.";
    d.Y = 16;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "[W,A,S,D] - navigate in menu";
    d.Y = 18;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "[Enter] - choose option";
    d.Y = 20;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
    cout << "[B] - change gamemode";

    COORD c{ 0,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}