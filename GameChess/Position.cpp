#include "Position.h"

void Position::PiecePosition(int x, int y, ChessPieces & piece)
{
    COORD c;
    int a = 6 * x + 1;
    int b = 27 - 3 * y;
    int s = 6 * piece.X + 1;
    int t = 27 - 3 * piece.Y;
    c.X = s;
    c.Y = t;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    if ((piece.Y % 2 != 0 && piece.X % 2 != 0) || (piece.Y % 2 == 0 && piece.X % 2 == 0)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    }
    printf("   ");
    c.X = a - 2;
    c.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    if ((y%2 != 0 && x%2 != 0) || (y % 2 == 0 && x % 2 == 0)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    }
    cout << piece.Symbol;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    c.X = 0;
    c.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Position::SetAllPieces(vector<ChessPieces>& white, vector<ChessPieces>& black) {
    ChessPieces p;
    white.clear();
    black.clear();

    ChessPieces kW(5, 1, p.king, p.white);
    ChessPieces qW(4, 1, p.queen, p.white);
    ChessPieces b1W(3, 1, p.bishop, p.white);
    ChessPieces b2W(6, 1, p.bishop, p.white);
    ChessPieces n1W(2, 1, p.knight, p.white);
    ChessPieces n2W(7, 1, p.knight, p.white);
    ChessPieces r1W(1, 1, p.rook, p.white);
    ChessPieces r2W(8, 1, p.rook, p.white);
    ChessPieces p1W(1, 2, p.pone, p.white);
    ChessPieces p2W(2, 2, p.pone, p.white);
    ChessPieces p3W(3, 2, p.pone, p.white);
    ChessPieces p4W(4, 2, p.pone, p.white);
    ChessPieces p5W(5, 2, p.pone, p.white);
    ChessPieces p6W(6, 2, p.pone, p.white);
    ChessPieces p7W(7, 2, p.pone, p.white);
    ChessPieces p8W(8, 2, p.pone, p.white);

    ChessPieces kB(5, 8, p.king, p.black);
    ChessPieces qB(4, 8, p.queen, p.black);
    ChessPieces b1B(3, 8, p.bishop, p.black);
    ChessPieces b2B(6, 8, p.bishop, p.black);
    ChessPieces n1B(2, 8, p.knight, p.black);
    ChessPieces n2B(7, 8, p.knight, p.black);
    ChessPieces r1B(1, 8, p.rook, p.black);
    ChessPieces r2B(8, 8, p.rook, p.black);
    ChessPieces p1B(1, 7, p.pone, p.black);
    ChessPieces p2B(2, 7, p.pone, p.black);
    ChessPieces p3B(3, 7, p.pone, p.black);
    ChessPieces p4B(4, 7, p.pone, p.black);
    ChessPieces p5B(5, 7, p.pone, p.black);
    ChessPieces p6B(6, 7, p.pone, p.black);
    ChessPieces p7B(7, 7, p.pone, p.black);
    ChessPieces p8B(8, 7, p.pone, p.black);
    black = { kB,qB,b1B,b2B,n1B,n2B,r1B,r2B,p1B,p2B,p3B,p4B,p5B,p6B,p7B,p8B };
    white = { kW,qW,b1W,b2W,n1W,n2W,r1W,r2W,p1W,p2W,p3W,p4W,p5W,p6W,p7W,p8W };

    Position::Clear();
    for (int i = 0; i < white.size(); i++)
    {
        Position::PiecePosition(white[i].X, white[i].Y, white[i]);
    }
    for (int i = 0; i < black.size(); i++)
    {
        Position::PiecePosition(black[i].X, black[i].Y, black[i]);
    }

};
void Position::Clear() {
    COORD c;
    int i, j;
    for (int x = 1; x < 9; x++) {
        for (int y = 1; y < 9; y++) {
            i = 6 * x + 1;
            j = 27 - 3 * y;
            c.X = i;
            c.Y = j;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
            if ((y % 2 != 0 && x % 2 != 0) || (y % 2 == 0 && x % 2 == 0)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
            }
            printf("   ");

        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
};
