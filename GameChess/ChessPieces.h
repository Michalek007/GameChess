#pragma once

#include <vector>
#include <string>

using namespace std;
using Matrix = vector<vector<bool>>;

class ChessPieces {
public:
    int X;
    int Y;
    string Symbol;
    string ID;
    enum Color
    {
        white,
        black
    };
    enum Type{
        king,
        queen,
        bishop,
        knight,
        rook,
        pone
    };
    static bool castleLW;
    static bool castleRW;
    static bool castleLB;
    static bool castleRB;
    static string enPassant;
    Color fColor;
    Type fType;

    ChessPieces(int x = 0, int y = 0, Type type = queen, Color color = white) :X{ x }, Y{ y }, fType{ type }, fColor{ color }
    {
        this->Set_ID();
        this->Set_Symbols();       
    }
    void Set_Symbols();
    void Set_ID();

    //jesli sprawdzamy dla figury koloru bia³ego to wstwiamy wektor bia³ych figur(analogicznie dla czarnych)
    static bool AllowedMoves(int, int, vector<ChessPieces>&);

    static bool AllowedMovesKing(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color);

    //parametr 'int use' ma byæ równy jeden dla kóla, 0 dla ka¿dej innej figury
    bool AllowedMoves(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color, int);

    bool Castle(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color);

    bool CastleL(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color);

    //parametr 'int use' ma byæ równy jeden gdy król jest szachowany
    bool Block(int, int, vector<ChessPieces>, vector<ChessPieces>, Color, int);

    bool Cover(int, int, ChessPieces&, ChessPieces&, vector<ChessPieces>&, vector<ChessPieces>&);

    static ChessPieces TypeOfPieces(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color);

    static bool Mate(vector<ChessPieces>&, vector<ChessPieces>&, Color);

    static void Take(int, int, vector<ChessPieces>&, vector<ChessPieces>&, Color, string&);

    void Promotion();

    void QBR(int, Matrix&, vector<ChessPieces>&, vector<ChessPieces>&);
    Matrix AllowedMoves(vector<ChessPieces>&, vector<ChessPieces>&, Color, int);
    void AllowedMoves(Matrix&, vector<ChessPieces>&, vector<ChessPieces>&);
    static vector<string> AllowedMoves(Matrix&);
};