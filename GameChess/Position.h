#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "ChessPieces.h"

class Position
{
public:
    static void PiecePosition(int, int, ChessPieces&);
    static void SetAllPieces(vector<ChessPieces>&, vector<ChessPieces>&);
    static void Clear();
};