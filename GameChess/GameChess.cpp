#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <map>
#include "GUI.h"
#include "ChessPieces.h"
#include "Position.h"  
#include "Bot.h"
#include "Interface.h"

#pragma execution_character_set( "utf-8" )

using namespace std;
using Matrix = vector<vector<bool>>;
bool ChessPieces::castleLW = true;
bool ChessPieces::castleRW = true;
bool ChessPieces::castleLB = true;
bool ChessPieces::castleRB = true;
string ChessPieces::enPassant{};

int main()
{
    SetConsoleOutputCP(65001);
    Bot bot;
    ChessPieces p;
    GUI::CreateBoard();
    GUI::CreateMenu();
    vector<ChessPieces> black {};
    vector<ChessPieces> white {};
    Position::Clear();
    Position::SetAllPieces(white, black);
    vector<string> moves;
    Matrix m;
    Matrix matrix;
    vector<string> pieces;
    for (int i = 0; i < white.size(); i++) {
        string s = white[i].ID;
        s.push_back('w');
        pieces.push_back(s);
    }
    for (int i = 0; i < black.size(); i++) {
        string s = black[i].ID;
        s.push_back('b');
        pieces.push_back(s);
    }
    for (int i = 0; i < white.size(); i++)
    {
        Position::PiecePosition(white[i].X, white[i].Y, white[i]);
    }
    for (int i = 0; i < black.size(); i++)
    {
        Position::PiecePosition(black[i].X, black[i].Y, black[i]);
    }
    bool bot_gamemode {false};
    bool mate = false;
    int turn = 0;
    int x{}, y{}, count{1};
    string id;
    string move;
    string take;
    COORD c;
    vector<string> vec;
    while (true) {
        mate = false;
        c.X = 55;
        c.Y = 3;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        if (turn == 0) {
            cout << "White move  " << endl;
        }
        if (turn == 1) {
            cout << "Black move  " << endl;
        }
        Interface::Choice(x, y, white, black, id, m, turn, moves, count, bot_gamemode,pieces);
        if (turn == 0) {
            for (int i = 0; i < white.size(); i++) {
                if (white[i].ID == id) {
                    matrix = white[i].AllowedMoves(white, black, p.white, 0);
                    white[i].AllowedMoves(matrix, white, black);
                    if (m[x - 1][y - 1] == true) {
                        if (id == "ke1") {
                            if (white[i].X == x - 2) {
                                for (int o = 0; o < white.size(); o++) {
                                    if (white[o].ID == "rh1") {
                                        Position::PiecePosition(x - 1, y, white[o]);
                                        white[o].X = x - 1;
                                        white[o].Y = y;
                                        white[o].Set_ID();
                                        take = "O-O";
                                        id.erase();
                                    }
                                }
                            }
                            if (white[i].X == x + 2) {
                                for (int o = 0; o < white.size(); o++) {
                                    if (white[o].ID == "ra1") {
                                        Position::PiecePosition(x + 1, y, white[o]);
                                        white[o].X = x + 1;
                                        white[o].Y = y;
                                        white[o].Set_ID();
                                        take = "O-O-O";
                                        id.erase();
                                    }
                                }
                            }
                            ChessPieces::castleLW = false;
                            ChessPieces::castleRW = false;
                        }
                        if (white[i].fType == ChessPieces::pone && white[i].Y + 2 == y) {
                            ChessPieces::enPassant = white[i].ID;
                            ChessPieces::enPassant.push_back('w');
                        }
                        Position::PiecePosition(x, y, white[i]);
                        white[i].X = x;
                        white[i].Y = y;
                        ChessPieces::Take(x, y, white, black, p.white, take);
                        Interface::Move(x, y, white[i].ID, moves, count , take);
                        white[i].Set_ID();
                        turn = 1;
                        count += 1;
                        id.erase();
                        if (white[i].fType == ChessPieces::pone && white[i].Y == 8) {
                            white[i].Promotion();
                        }
                        if (id == "ra1") {
                            ChessPieces::castleLW = false;
                        }
                        if (id == "rh1") {
                            ChessPieces::castleRW = false;
                        }
                    }
                }
            }
            id.erase();   
        }
        if (!ChessPieces::enPassant.empty()) {
            if (ChessPieces::enPassant[3] == 'b') {
                ChessPieces::enPassant.clear();
            }
        }
        c.X = 55;
        c.Y = 3;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        if (turn == 0) {
            cout << "White move  " << endl;
        }
        if (turn == 1) {
            cout << "Black move  " << endl;
        }
        pieces.clear();
        for (int i = 0; i < white.size(); i++) {
            string s = white[i].ID;
            s.push_back('w');
            pieces.push_back(s);
        }
        for (int i = 0; i < black.size(); i++) {
            string s = black[i].ID;
            s.push_back('b');
            pieces.push_back(s);
        }
        if (turn == 1 && black[0].AllowedMovesKing(black[0].X, black[0].Y, white, black, p.white) == false) {
            Matrix mate_matrix = black[0].AllowedMoves(white, black, p.black, 0);
            black[0].AllowedMoves(mate_matrix, white, black);
            if (ChessPieces::Mate(white, black, ChessPieces::white) == true) {
                c.X = 7;
                c.Y = 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                cout << "Mate. White won!" << endl;
                mate = true;
            }
        }
        if (turn == 1 && bot_gamemode == true && !mate) {
            bot.Move(x, y, white, black, count, moves, pieces);
            /*string bot_move = bot.Move(pieces, count, turn);
            if (bot_move[3] == 'w') {
                for (int i = 0; i < white.size(); i++) {
                    if (white[i].X == bot_move[1] - 96 && white[i].Y == bot_move[2] - 48) {
                        x = bot_move[4] - 96;
                        y = bot_move[5] - 48;
                        if (white[i].fType == ChessPieces::pone && white[i].Y + 2 == y) {
                            ChessPieces::enPassant = white[i].ID;
                            ChessPieces::enPassant.push_back('w');
                        }
                        Position::PiecePosition(x, y, white[i]);
                        white[i].X = x;
                        white[i].Y = y;
                        ChessPieces::Take(x, y, white, black, p.white, take);
                        Interface::Move(x, y, white[i].ID, moves, count, take);
                        white[i].Set_ID();
                        turn = 1;
                        bot_move.pop_back();
                        bot_move.pop_back();
                        if (white[i].fType == ChessPieces::pone && white[i].Y == 8) {
                        }
                        if (bot_move == "ke4") {
                            ChessPieces::castleLW = false;
                            ChessPieces::castleRW = false;
                        }
                        if (id == "ra1") {
                            ChessPieces::castleLW = false;
                        }
                        if (id == "rh1") {
                            ChessPieces::castleRW = false;
                        }
                    }
                }
            }
            if (bot_move[3] == 'b') {
                for (int i = 0; i < black.size(); i++) {
                    if (black[i].X == bot_move[1] - 96 && black[i].Y == bot_move[2] - 48) {
                        x = bot_move[4] - 96;
                        y = bot_move[5] - 48;
                        if (black[i].fType == ChessPieces::pone && black[i].Y - 2 == y) {
                            ChessPieces::enPassant = black[i].ID;
                            ChessPieces::enPassant.push_back('b');
                        }
                        Position::PiecePosition(x, y, black[i]);
                        black[i].X = x;
                        black[i].Y = y;
                        ChessPieces::Take(x, y, white, black, p.black, take);
                        Interface::Move(x, y, black[i].ID, moves, count, take);
                        black[i].Set_ID();
                        turn = 0;
                        bot_move.pop_back();
                        bot_move.pop_back();
                        if (black[i].fType == ChessPieces::pone && black[i].Y == 1) {
                            black[i].Promotion();
                        }
                        if (bot_move == "ke8") {
                            ChessPieces::castleLB = false;
                            ChessPieces::castleRB = false;
                        }
                        if (bot_move == "ra8") {
                            ChessPieces::castleLB = false;
                        }
                        if (bot_move == "rh8") {
                            ChessPieces::castleRB = false;
                        }
                    }
                }
            }*/
            turn = 0;
            count++;
            
        }
        if (turn == 1 && bot_gamemode == false) {
            for (int i = 0; i < black.size(); i++) {
                if (black[i].ID == id) {
                    matrix = black[i].AllowedMoves(white, black, p.black, 0);
                    black[i].AllowedMoves(matrix, white, black);
                    if (matrix[x - 1][y - 1] == true) {
                        if (id == "ke8") {
                            if (black[i].X == x - 2) {
                                for (int o = 0; o < black.size(); o++) {
                                    if (black[o].ID == "rh8") {
                                        Position::PiecePosition(x-1, y, black[o]);
                                        black[o].X = x-1;
                                        black[o].Y = y;
                                        take = "O-O";
                                        id.erase();
                                    }
                                }
                            }
                            if (black[i].X == x + 2) {
                                for (int o = 0; o < black.size(); o++) {
                                    if (black[o].ID == "ra8") {
                                        Position::PiecePosition(x+1, y, black[o]);
                                        black[o].X = x+1;
                                        black[o].Y = y;
                                        take = "O-O-O";
                                        id.erase();
                                    }
                                }
                            }
                            ChessPieces::castleLB = false;
                            ChessPieces::castleRB = false;
                        }
                        if (black[i].fType == ChessPieces::pone && black[i].Y - 2 == y) {
                            ChessPieces::enPassant = black[i].ID;
                            ChessPieces::enPassant.push_back('b');
                        }
                        Position::PiecePosition(x, y, black[i]);
                        black[i].X = x;
                        black[i].Y = y;
                        ChessPieces::Take(x, y, white, black, p.black, take);
                        Interface::Move(x, y, black[i].ID, moves, count, take);
                        black[i].Set_ID();
                        turn = 0;
                        count += 1;
                        id.erase();
                        if (black[i].fType == ChessPieces::pone && black[i].Y == 1) {
                            black[i].Promotion();
                        }
                        if (id == "ra8") {
                            ChessPieces::castleLB = false;
                        }
                        if (id == "rh8") {
                            ChessPieces::castleRB= false;
                        }                       
                    }
                }
            }
            id.erase();
        }
        if (!ChessPieces::enPassant.empty() && turn == 0) {
            if (ChessPieces::enPassant[3] == 'w') {
                ChessPieces::enPassant.clear();
            }
        }
        if (white[0].AllowedMovesKing(white[0].X, white[0].Y, white, black, ChessPieces::black) == false) {
            Matrix mate_matrix = white[0].AllowedMoves(white, black, p.white, 0);
            white[0].AllowedMoves(mate_matrix, white, black);
            if (ChessPieces::Mate(white, black, ChessPieces::black) == true) {
                c.X = 7;
                c.Y = 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                cout << "Mate. Black won!" << endl;
                mate = true;
            }
        }
        /*c.X = 70;
        int i = 0;
        for (auto elements : moves) {
            if (moves.size() > 15) {
                if (i <= 20) {
                    c.Y = 5 + i;
                    c.X = 70;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                    cout << elements.first << " -> ";
                    cout << elements.second << endl;
                    i++;
                }
                if (i < 40 && i > 20) {
                    c.Y = 5 + i - 21;
                    c.X = 90;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                    cout << elements.first << " -> ";
                    cout << elements.second << endl;
                    i++;
                }
            }
            else {
                c.Y = 5 + i;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                cout << elements.first << " -> ";
                cout << elements.second << endl;
                i++;
            }
        }*/
    }
}
