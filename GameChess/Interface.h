#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "ChessPieces.h"
#include "Position.h"

class Interface
{
public:
    static bool show_legal_moves;
    static void Coord(int, int, int);
    static void CoordP(int, int);
    static void CoordMenu(int, int, int);
    static void Move(int, int, string&, vector <string>&, int, string&);
    static void Choice(int&, int&, vector <ChessPieces>&, vector <ChessPieces>&, string&, Matrix&, int&, vector <string>&, int&, bool&, vector<string>&);
    static void Return(vector <ChessPieces>&, vector <ChessPieces>&, int&, vector <string>&, int&);
    static void Promotion(ChessPieces&);
    //static void Menu(int&, int&, vector <ChessPieces>&, vector <ChessPieces>&, int&, vector <string>&, int&, bool&, vector<string>&);
};

