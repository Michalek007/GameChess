#include "ChessPieces.h"
#include "Interface.h"

using namespace std;
using Matrix = vector<vector<bool>>;

void ChessPieces::Set_ID() {
    ID.erase();
    if (fType == king) {
        ID.push_back('k');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
    if (fType == queen) {
        ID.push_back('q');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
    if (fType == bishop) {

        ID.push_back('b');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
    if (fType == knight) {
        ID.push_back('n');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
    if (fType == rook) {
        ID.push_back('r');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
    if (fType == pone) {
        ID.push_back('p');
        ID.push_back(X + 96);
        ID.push_back(Y + 48);
    }
}

void ChessPieces::Set_Symbols(){
    if (fType == king) {
        if (fColor == white) {
            Symbol = u8"  \u2654  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265A  ";
        }
    }
    if (fType == queen) {
        if (fColor == white) {
            Symbol = u8"  \u2655  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265B  ";
        }
    }
    if (fType == bishop) {
        if (fColor == white) {
            Symbol = u8"  \u2657  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265D  ";
        }
    }
    if (fType == knight) {
        if (fColor == white) {
            Symbol = u8"  \u2658  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265E  ";
        }
    }
    if (fType == rook) {
        if (fColor == white) {
            Symbol = u8"  \u2656  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265C  ";
        }
    }
    if (fType == pone) {
        if (fColor == white) {
            Symbol = u8"  \u2659  ";
        }
        if (fColor == black) {
            Symbol = u8"  \u265F  ";
        }
    }
}


ChessPieces ChessPieces::TypeOfPieces(int x, int y, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color)
{
    if (color == black)
    {
        for (int i = 0; i < blackV.size(); i++)
        {
            if (blackV[i].AllowedMoves(x, y, whiteV, blackV, color, 0) == true)
            {
                return blackV[i];
            }
        }
    }
    if (color == white)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if (whiteV[i].AllowedMoves(x, y, whiteV, blackV, color, 0) == true)
            {
                return whiteV[i];
            }
        }
    }
    return blackV[0];
}

bool ChessPieces::Mate(vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color)
{
    Matrix mate_matrix;
    if (color == white) {
        for (int o = 0; o < blackV.size(); o++) {
            mate_matrix = blackV[o].AllowedMoves(whiteV, blackV, black, 0);
            blackV[o].AllowedMoves(mate_matrix, whiteV, blackV);
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (mate_matrix[i][j] == true) {
                        return false;
                    }
                }
            }
            mate_matrix.clear();
        }
    }
    if (color == black) {
        for (int o = 0; o < whiteV.size(); o++) {
            mate_matrix = whiteV[o].AllowedMoves(whiteV, blackV, black, 0);
            whiteV[o].AllowedMoves(mate_matrix, whiteV, blackV);
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (mate_matrix[i][j] == true) {
                        return false;
                    }
                }
            }
            mate_matrix.clear();
        }
    } 
    return true;
}

void ChessPieces::Take(int x, int y, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color, string& str) {
    if (color == white) {
        for (size_t i = 0; i < blackV.size(); i++) {
            if (blackV[i].X == x && blackV[i].Y == y) {
                str = blackV[i].ID;
                str.pop_back();
                str.pop_back();
                blackV.erase(blackV.begin() + i);
            }
        }
    }
    if (color == black) {
        for (size_t i = 0; i < whiteV.size(); i++) {
            if (whiteV[i].X == x && whiteV[i].Y == y) {
                str = whiteV[i].ID;
                str.pop_back();
                str.pop_back();
                whiteV.erase(whiteV.begin() + i);
            }
        }
    }
}

void ChessPieces::Promotion() {
    Interface::Promotion(*this);
};

void ChessPieces::QBR(int c, Matrix& matrix, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV) {
    vector< ChessPieces > all;
    for (int i = 0; i < whiteV.size(); i++) {
        if (X == whiteV[i].X && Y == whiteV[i].Y) {}
        else {
            all.push_back(whiteV[i]);
        }
    }
    for (int i = 0; i < blackV.size(); i++) {
        if (X == blackV[i].X && Y == blackV[i].Y) {}
        else {
            all.push_back(blackV[i]);
        }
    }
    if (c == 0) {
        for (int o = 1; o < 9 - X; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                matrix[X + o - 1][Y - 1] = true;
                if (all[a].X == X + o && all[a].Y == Y)
                {
                    //matrix[X + o][Y] = false;
                    return;
                }
            }
        }
    }
    if (c == 1) {
        for (int o = 1; o < X; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                matrix[X - o - 1][Y - 1] = true;
                if (all[a].X == X - o && all[a].Y == Y)
                {
                    //matrix[X - o][Y] = false;
                    return;
                }
            }
        }
    }
    if (c == 2) {
        for (int o = 1; o < 9 - Y; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                matrix[X - 1][Y + o - 1] = true;
                if (all[a].X == X && all[a].Y == Y + o)
                {
                    //matrix[X][Y + o] = false;
                    return;
                }
            }
        }
    }
    if (c == 3) {
        for (int o = 1; o < Y; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                matrix[X - 1][Y - o - 1] = true;
                if (all[a].X == X && all[a].Y == Y - o)
                {
                    //matrix[X][Y - o] = false;
                    return;
                }
            }
        }
    }
    if (c == 4) {
        for (int o = 1; o < 9; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                if (X + o > 8 || Y + o > 8) {
                    return;
                }
                matrix[X + o - 1][Y + o - 1] = true;
                if (all[a].X == X + o && all[a].Y == Y + o)
                {
                    //matrix[X + o][Y] = false;
                    return;
                }
            }
        }
    }
    if (c == 5) {
        for (int o = 1; o < 9; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                if (X - o < 1 || Y - o < 1) {
                    return;
                }
                matrix[X - o - 1][Y - o - 1] = true;
                if (all[a].X == X - o && all[a].Y == Y - o)
                {
                    //matrix[X + o][Y] = false;
                    return;
                }
            }
        }
    }
    if (c == 6) {
        for (int o = 1; o < 9; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                if (X + o > 8 || Y - o < 1) {
                    return;
                }
                matrix[X + o - 1][Y - o - 1] = true;
                if (all[a].X == X + o && all[a].Y == Y - o)
                {
                    //matrix[X + o][Y] = false;
                    return;
                }
            }
        }
    }
    if (c == 7) {
        for (int o = 1; o < 9; o++)
        {
            for (int a = 0; a < all.size(); a++)
            {
                if (X - o < 1 || Y + o > 8) {
                    return;
                }
                matrix[X - o - 1][Y + o - 1] = true;
                if (all[a].X == X - o && all[a].Y == Y + o)
                {
                    //matrix[X + o][Y] = false;
                    return;
                }
            }
        }
    }
}
Matrix ChessPieces::AllowedMoves(vector<ChessPieces>& white, vector<ChessPieces>& black, Color color, int use) {
    vector<bool> vec {false, false, false, false, false, false, false, false };
    Matrix moves {vec,vec,vec,vec,vec,vec,vec,vec };
    //vec.resize(8);
    //for (int i = 0; i < 8; i++) {
    //   vec.push_back(false);
    //}
    //for (int i = 0; i < 8; i++) {
    //    moves.push_back(vec);
    //}
    int x, y;
    x = X - 1;
    y = Y - 1;
    if (this->fType == queen || this->fType == rook)
    {
        this->QBR(0, moves, white, black);
        this->QBR(1, moves, white, black);
        this->QBR(2, moves, white, black);
        this->QBR(3, moves, white, black);

        if (this->fType == rook) {
            return moves;
        }
    }
    if (this->fType == queen || this->fType == bishop)
    {
        this->QBR(4, moves, white, black);
        this->QBR(5, moves, white, black);
        this->QBR(6, moves, white, black);
        this->QBR(7, moves, white, black);
        return moves;
    }
    if (this->fType == king)
    {
        if (y + 1 < 8) {
            moves[x][y + 1] = true;
        }
        if (y - 1 > -1) {
            moves[x][y - 1] = true;
        }
        if (x + 1 < 8) {
            moves[x + 1][y] = true;
        }
        if (x - 1 > -1) {
            moves[x - 1][y] = true;
        }
        if ((x + 1 < 8) && (y + 1 < 8)) {
            moves[x + 1][y + 1] = true;
        }
        if ((x - 1 > -1) && (y - 1 > -1)) {
            moves[x - 1][y - 1] = true;
        }
        if ((x + 1 < 8) && (y - 1 > -1)) {
            moves[x + 1][y - 1] = true;
        }
        if ((x - 1 > -1) && (y + 1 < 8)) {
            moves[x - 1][y + 1] = true;
        }
        return moves;
    }
    if (fType == knight)
    {
        if ((x + 2 < 8) && (y + 1 < 8)) {
            moves[x + 2][y + 1] = true;
        }
        if ((x - 2 > -1) && (y - 1 > -1)) {
            moves[x - 2][y - 1] = true;
        }
        if ((x + 2 < 8) && (y - 1 > -1)) {
            moves[x + 2][y - 1] = true;
        }
        if ((x - 2 > -1) && (y + 1 < 8)) {
            moves[x - 2][y + 1] = true;
        }
        if ((x + 1 < 8) && (y + 2 < 8)) {
            moves[x + 1][y + 2] = true;
        }
        if ((x - 1 > -1) && (y - 2 > -1)) {
            moves[x - 1][y - 2] = true;
        }
        if ((x + 1 < 8) && (y - 2 > -1)) {
            moves[x + 1][y - 2] = true;
        }
        if ((x - 1 > -1) && (y + 2 < 8)) {
            moves[x - 1][y + 2] = true;
        }
        return moves;


    }
    if (fType == pone)
    {
        if (use == 0)
        {
            if (color == 0)
            {
                if (!enPassant.empty()) {
                    int ep = enPassant[1] - 96;
                    if (X + 1 == ep || X - 1 == ep) {
                        if (Y == 5) {
                            moves[ep - 1][5] = true;
                        }
                    }
                }
                moves[x][y + 1] = true;
                for (int i = 0; i < black.size(); i++)
                {
                    if (black[i].X == x + 1 && black[i].Y == y + 1 + 1)
                    {
                        moves[x][y + 1] = false;
                    }
                }
                for (int i = 0; i < white.size(); i++)
                {
                    if (white[i].X == x + 1 && white[i].Y == y + 1 + 1)
                    {
                        moves[x][y + 1] = false;
                    }
                }
                for (int i = 0; i < black.size(); i++)
                {
                    if (black[i].X == x - 1 + 1 && black[i].Y == y + 1 + 1)
                    {
                        moves[x - 1][y + 1] = true;
                    }
                    if (black[i].X == x + 1 + 1 && black[i].Y == y + 1 + 1)
                    {
                        moves[x + 1][y + 1] = true;
                    }
                }
                if (y == 1)
                {
                    moves[x][y + 2] = true;
                    for (int i = 0; i < black.size(); i++)
                    {
                        if (black[i].X == x + 1 && black[i].Y == y + 2 + 1)
                        {
                            moves[x][y + 2] = false;
                        }
                        if (black[i].X == x + 1 && black[i].Y == y + 1 + 1)
                        {
                            moves[x][y + 2] = false;
                        }

                    }
                    for (int i = 0; i < white.size(); i++)
                    {
                        if (white[i].X == x + 1 && white[i].Y == y + 2 + 1)
                        {
                            moves[x][y + 2] = false;
                        }
                        if (white[i].X == x + 1 && white[i].Y == y + 1 + 1)
                        {
                            moves[x][y + 2] = false;
                        }
                    }
                }
            }
            if (color == 1)
            {
                if (!enPassant.empty()) {
                    int ep = enPassant[1] - 96;
                    if (X + 1 == ep || X - 1 == ep) {
                        if (Y == 4) {
                            moves[ep - 1][3] = true;
                        }
                    }
                }
                moves[x][y - 1] = true;
                for (int i = 0; i < white.size(); i++)
                {
                    if (white[i].X == x + 1 && white[i].Y == y - 1 + 1)
                    {
                        moves[x][y - 1] = false;
                    }
                }
                for (int i = 0; i < black.size(); i++)
                {
                    if (black[i].X == x + 1 && black[i].Y == y - 1 + 1)
                    {
                        moves[x][y - 1] = false;
                    }
                }
                for (int i = 0; i < white.size(); i++)
                {
                    if (white[i].X == x - 1 + 1 && white[i].Y == y - 1 + 1)
                    {
                        moves[x - 1][y - 1] = true;
                    }
                    if (white[i].X == x + 1 + 1 && white[i].Y == y - 1 + 1)
                    {
                        moves[x + 1][y - 1] = true;
                    }
                }
                if (y == 6)
                {
                    moves[x][y - 2] = true;
                    for (int i = 0; i < white.size(); i++)
                    {
                        if (white[i].X == x + 1 && white[i].Y == y - 2 + 2)
                        {
                            moves[x][y - 2] = false;
                        }
                        if (white[i].X == x + 1 && white[i].Y == y - 2 + 1)
                        {
                            moves[x][y - 2] = false;
                        }
                    }
                    for (int i = 0; i < black.size(); i++)
                    {
                        if (black[i].X == x + 1 && black[i].Y == y - 2 + 2)
                        {
                            moves[x][y - 2] = false;
                        }
                        if (black[i].X == x + 1 && black[i].Y == y - 2 + 1)
                        {
                            moves[x][y - 2] = false;
                        }
                    }
                }
            }
            return moves;
        }
        else
        {
            if (color == 0)
            {
                if (x + 1 < 8) {
                    moves[x + 1][y + 1] = true;
                }
                if (x - 1 > -1) {
                    moves[x - 1][y + 1] = true;
                }
            }
            if (color == 1)
            {
                if (x + 1 < 8) {
                    moves[x + 1][y - 1] = true;
                }
                if (x - 1 > -1) {
                    moves[x - 1][y - 1] = true;
                }
            }
        }
        return moves;
    }
    return moves;
}
void ChessPieces::AllowedMoves(Matrix& matrix, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV) {
    for (int i = 0; i < 8; i++) {
        for (int o = 0; o < 8; o++) {
            if (fColor == white && !AllowedMovesKing(whiteV[0].X, whiteV[0].Y, whiteV, blackV, black)) {
                ChessPieces check = TypeOfPieces(whiteV[0].X, whiteV[0].Y, whiteV, blackV, black);
                int a{}, b{};
                a = check.X;
                b = check.Y;
                if (fType == king) {
                    if (matrix[i][o] == true) {
                        if (AllowedMovesKing(i + 1, o + 1, whiteV, blackV, black) == false) {
                            matrix[i][o] = false;
                        }
                    }
                }
                if (fType != king && this->Block(i + 1, o + 1, whiteV, blackV, fColor, 1) == false) {
                    matrix[i][o] = false;
                }
                if (fColor == white && AllowedMoves(i + 1, o + 1, whiteV) == false) {
                    matrix[i][o] = false;
                }
                if (fType != king) {
                    if (this->Cover(i + 1, o + 1, check, whiteV[0], whiteV, blackV) == true || (i + 1 == a && o + 1 == b)) {

                    }
                    else {
                        matrix[i][o] = false;
                    }
                }
            }
            if (fColor == black && !AllowedMovesKing(blackV[0].X, blackV[0].Y, whiteV, blackV, white)) {
                ChessPieces check = TypeOfPieces(blackV[0].X, blackV[0].Y, whiteV, blackV, white);
                int a{}, b{};
                a = check.X;
                b = check.Y;
                if (fType == king) {
                    if (matrix[i][o] == true) {
                        if (AllowedMovesKing(i + 1, o + 1, whiteV, blackV, white) == false) {
                            matrix[i][o] = false;
                        }
                    }
                }
                if (fType != king && this->Block(i + 1, o + 1, whiteV, blackV, fColor, 1) == false) {
                    matrix[i][o] = false;
                }
                if (fColor == black && AllowedMoves(i + 1, o + 1, blackV) == false) {
                    matrix[i][o] = false;
                }
                if (fType != king) {
                    if (this->Cover(i + 1, o + 1, check, blackV[0], whiteV, blackV) == true || (i + 1 == a && o + 1 == b)) {

                    }
                    else {
                        matrix[i][o] = false;
                    }
                }
            }
            if (fType == king) {
                if (matrix[i][o] == true) {
                    Color ffColor {white};
                    if (fColor == white) {
                        if (castleLW == true && CastleL(3, 1, whiteV, blackV, fColor) == true) {
                            if (matrix[2][0] == false) {
                                matrix[2][0] = true;
                            }
                        }
                        if (castleRW == true && Castle(7, 1, whiteV, blackV, fColor) == true) {
                            if (matrix[6][0] == false) {
                                matrix[6][0] = true;
                            }
                        }
                        ffColor = black;
                    }
                    if (fColor == black) {
                        if (castleLB == true && CastleL(3, 8, whiteV, blackV, fColor) == true) {
                            if (matrix[2][7] == false) {
                                matrix[2][7] = true;
                            }
                        }
                        if (castleRB == true && Castle(7, 8, whiteV, blackV, fColor) == true) {
                            if (matrix[6][7] == false) {
                                matrix[6][7] = true;
                            }
                        }
                        ffColor = white;
                    }
                    if (AllowedMovesKing(i + 1, o + 1, whiteV, blackV, ffColor) == false) {
                        matrix[i][o] = false;
                    }
                }
            }
            if (fType != king && this->Block(i + 1, o + 1, whiteV, blackV, fColor, 0) == false) {
                matrix[i][o] = false;
            }
            if (fColor == white && AllowedMoves(i + 1, o + 1, whiteV) == false) {
                matrix[i][o] = false;
            }
            if (fColor == black && AllowedMoves(i + 1, o + 1, blackV) == false) {
                matrix[i][o] = false;
            }
        }
    }
}

vector<string> ChessPieces::AllowedMoves(Matrix& matrix) {
    vector<string> vec;
    for (int i = 0; i < 8; i++) {
        for (int o = 0; o < 8; o++) {
            if (matrix[i][o] == true) {
                char c1 = i + 1 + 96;
                char c2 = o + 1 + 48;
                string str;
                str.push_back(c1);
                str.push_back(c2);
                vec.push_back(str);
            }
        }
    }
    return vec;
}

//jesli sprawdzamy dla figury koloru bia³ego to wstwiamy wektor bia³ych figur(analogicznie dla czarnych)
bool ChessPieces::AllowedMoves(int x, int y, vector<ChessPieces>& pieces)
{
    for (int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i].X == x && pieces[i].Y == y)
        {
            return false;
        }
    }
    return true;
}

bool ChessPieces::AllowedMovesKing(int x, int y, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color)
{
    if (color == black) {
        for (int i = 0; i < blackV.size(); i++)
        {
            if (blackV[i].AllowedMoves(x, y, whiteV, blackV, color, 1) == true)
            {
                return false;
            }
        }
    }
    if (color == white) {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if (whiteV[i].AllowedMoves(x, y, whiteV, blackV, color, 1) == true)
            {
                return false;
            }
        }
    }

    return true;
}

//parametr 'int use' ma byæ równy jeden dla kóla, 0 dla ka¿dej innej figury
bool ChessPieces::AllowedMoves(int x, int y, vector<ChessPieces>& white, vector<ChessPieces>& black, Color color, int use) {
    if (x > 8)
    {
        return false;
    }
    if (y > 8)
    {
        return false;
    }
    if (x < 1)
    {
        return false;
    }
    if (y < 1)
    {
        return false;
    }
    if (this->fType == queen || this->fType == rook)
    {
        for (int i = 1; i < 9 - X; i++)
        {
            if (x == X + i && y == Y)
            {
                for (int o = 1; o < x - X; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X + o && white[a].Y == Y)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X + o && white[a].Y == Y)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X + o && black[b].Y == Y)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X + o && black[b].Y == Y)
                            {
                                return false;
                            }
                        }

                    }
                }
                return true;
            }
        }
        for (int i = 1; i < 9 - Y; i++)
        {
            if (x == X && y == Y + i)
            {
                for (int o = 1; o < y - Y; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        for (int i = 1; i < X; i++)
        {
            if (x == X - i && y == Y)
            {
                for (int o = 1; o < X - x; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X - o && white[a].Y == Y)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X - o && white[a].Y == Y)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X - o && black[b].Y == Y)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X - o && black[b].Y == Y)
                            {
                                return false;
                            }
                        }

                    }
                }
                return true;
            }
        }
        for (int i = 1; i < Y; i++)
        {
            if (x == X && y == Y - i)
            {
                for (int o = 1; o < Y - y; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        if (this->fType == rook) {
            return false;
        }
    }
    if (this->fType == queen || this->fType == bishop)
    {
        for (int i = 1; i < 9; i++)
        {
            if (x == X + i && y == Y + i)
            {
                for (int o = 1; o < x - X; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X + o && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X + o && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X + o && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X + o && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        for (int i = 1; i < 9; i++)
        {
            if (x == X - i && y == Y - i)
            {
                for (int o = 1; o < X - x; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X - o && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X - o && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X - o && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X - o && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        for (int i = 1; i < 9; i++)
        {
            if (x == X + i && y == Y - i)
            {
                for (int o = 1; o < x - X; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 0)
                        {
                            if (white[a].X == X + o && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X + o && white[a].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X + o && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X + o && black[b].Y == Y - o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        for (int i = 1; i < 9; i++)
        {
            if (x == X - i && y == Y + i)
            {
                for (int o = 1; o < X - x; o++)
                {
                    for (int a = 0; a < white.size(); a++)
                    {
                        if (color == 1)
                        {
                            if (white[a].X == X - o && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (white[a].fType == king)
                            {

                            }
                            else if (white[a].X == X - o && white[a].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                    for (int b = 0; b < black.size(); b++)
                    {
                        if (color == 1)
                        {
                            if (black[b].X == X - o && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            if (black[b].fType == king)
                            {

                            }
                            else if (black[b].X == X - o && black[b].Y == Y + o)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }
    else if (this->fType == king)
    {
        if ((x == X || x == X + 1 || x == X - 1) && (y == Y || y == Y + 1 || y == Y - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (this->fType == knight)
    {
        if (x == X + 2 && y == Y + 1)
        {
            return true;
        }
        if (x == X + 2 && y == Y - 1)
        {
            return true;
        }
        if (x == X - 2 && y == Y + 1)
        {
            return true;
        }
        if (x == X - 2 && y == Y - 1)
        {
            return true;
        }
        if (x == X + 1 && y == Y + 2)
        {
            return true;
        }
        if (x == X - 1 && y == Y + 2)
        {
            return true;
        }
        if (x == X + 1 && y == Y - 2)
        {
            return true;
        }
        if (x == X - 1 && y == Y - 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (this->fType == pone)
    {
        if (use == 0)
        {
            if (color == 0)
            {
                if (x == X && y == Y + 1)
                {
                    for (int i = 0; i < black.size(); i++)
                    {
                        if (black[i].X == x && black[i].Y == y)
                        {
                            return false;
                        }
                    }
                    for (int i = 0; i < white.size(); i++)
                    {
                        if (white[i].X == x && white[i].Y == y)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                for (int i = 0; i < black.size(); i++)
                {
                    if (black[i].X == X - 1 && black[i].Y == Y + 1)
                    {
                        if (x == X - 1 && y == Y + 1)
                        {
                            return true;
                        }
                    }
                    if (black[i].X == X + 1 && black[i].Y == Y + 1)
                    {
                        if (x == X + 1 && y == Y + 1)
                        {
                            return true;
                        }
                    }
                }
                if (Y == 2)
                {
                    if (X == x && y == Y + 2)
                    {
                        for (int i = 0; i < black.size(); i++)
                        {
                            if (black[i].X == x && black[i].Y == y)
                            {
                                return false;
                            }
                        }
                        for (int i = 0; i < white.size(); i++)
                        {
                            if (white[i].X == x && white[i].Y == y)
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
            if (color == 1)
            {
                if (x == X && y == Y - 1)
                {
                    for (int i = 0; i < white.size(); i++)
                    {
                        if (white[i].X == x && white[i].Y == y)
                        {
                            return false;
                        }
                    }
                    for (int i = 0; i < black.size(); i++)
                    {
                        if (black[i].X == x && black[i].Y == y)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                for (int i = 0; i < white.size(); i++)
                {
                    if (white[i].X == X - 1 && white[i].Y == Y - 1)
                    {
                        if (x == X - 1 && y == Y - 1)
                        {
                            return true;
                        }
                    }
                    if (white[i].X == X + 1 && white[i].Y == Y - 1)
                    {
                        if (x == X + 1 && y == Y - 1)
                        {
                            return true;
                        }
                    }
                }
                if (Y == 7)
                {
                    for (int i = 0; i < white.size(); i++)
                    {
                        if (white[i].X == x && white[i].Y == y)
                        {
                            return false;
                        }
                    }
                    for (int i = 0; i < black.size(); i++)
                    {
                        if (black[i].X == x && black[i].Y == y)
                        {
                            return false;
                        }
                    }
                    if (X == x && y == Y - 2)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            if (color == 0)
            {
                if ((x == X + 1 || x == X - 1) && y == Y + 1)
                {
                    return true;
                }
            }
            if (color == 1)
            {
                if ((x == X + 1 || x == X - 1) && y == Y - 1)
                {
                    return true;
                }
            }

        }
        return false;
    }
    else
    {
        return false;
    }
}

bool ChessPieces::Castle(int x, int y, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color)
{
    if ((x != 7 && y != 1) || (x != 7 && y != 8))
    {
        return false;
    }
    if (x == X + 2 && y == Y)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if ((whiteV[i].X == X + 1 || whiteV[i].X == X + 2) && whiteV[i].Y == Y)
            {
                return false;
            }
        }
        for (int i = 0; i < blackV.size(); i++)
        {
            if ((blackV[i].X == X + 1 || blackV[i].X == X + 2) && blackV[i].Y == Y)
            {
                return false;
            }
        }
        if (color == 0)
        {
            if (AllowedMovesKing(x, y, whiteV, blackV, black) == false)
            {
                return false;
            }
            if (AllowedMovesKing(x - 1, y, whiteV, blackV, black) == false)
            {
                return false;
            }
            //for (int i = 0; i < blackV.size(); i++)
            //{
            //    if ((blackV[i].AllowedMoves(6,1,whiteV,blackV,1,0) == true || blackV[i].AllowedMoves(7, 1, whiteV, blackV, 1,0) == true) && blackV[i].Y == Y)
            //    {
            //        return false;
            //    }

            //}
        }
        if (color == 1)
        {
            if (AllowedMovesKing(x, y, whiteV, blackV, white) == false)
            {
                return false;
            }
            if (AllowedMovesKing(x - 1, y, whiteV, blackV, white) == false)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool ChessPieces::CastleL(int x, int y, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV, Color color)
{
    if ((x != 3 && y != 1) || (x != 3 && y != 8))
    {
        return false;
    }
    if (x == X - 2 && y == Y)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if ((whiteV[i].X == X - 1 || whiteV[i].X == X - 2) && whiteV[i].Y == Y)
            {
                return false;
            }
        }
        for (int i = 0; i < blackV.size(); i++)
        {
            if ((blackV[i].X == X - 1 || blackV[i].X == X - 2) && blackV[i].Y == Y)
            {
                return false;
            }

        }
        if (color == 0)
        {
            if (AllowedMovesKing(x, y, whiteV, blackV, black) == false)
            {
                return false;
            }
            if (AllowedMovesKing(x + 1, y, whiteV, blackV, black) == false)
            {
                return false;
            }
            //for (int i = 0; i < blackV.size(); i++)
            //{
            //    if ((blackV[i].AllowedMoves(6,1,whiteV,blackV,1,0) == true || blackV[i].AllowedMoves(7, 1, whiteV, blackV, 1,0) == true) && blackV[i].Y == Y)
            //    {
            //        return false;
            //    }

            //}

        }
        if (color == 1)
        {
            if (AllowedMovesKing(x, y, whiteV, blackV, white) == false)
            {
                return false;
            }
            if (AllowedMovesKing(x + 1, y, whiteV, blackV, white) == false)
            {
                return false;
            }

        }
        return true;


    }
    return false;
}

//parametr 'int use' ma byæ równy jeden gdy król jest szachowany
bool ChessPieces::Block(int x, int y, vector<ChessPieces> whiteV, vector<ChessPieces> blackV, Color color, int use)
{
    if (color == 0 && use != 1)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if (X == whiteV[i].X && Y == whiteV[i].Y)
            {
                ChessPieces p = whiteV[i];
                whiteV.erase(whiteV.begin() + i);
                ChessPieces check = TypeOfPieces(whiteV[0].X, whiteV[0].Y, whiteV, blackV, black);
                int a = check.X;
                int b = check.Y;
                if (this->Cover(x, y, check, whiteV[0], whiteV, blackV) == true || (x == a && y == b))
                {
                    whiteV.insert(whiteV.begin() + i, p);
                    return true;
                }
                if (AllowedMovesKing(whiteV[0].X, whiteV[0].Y, whiteV, blackV, black) == false)
                {
                    whiteV.insert(whiteV.begin() + i, p);
                    return false;
                }
                whiteV.insert(whiteV.begin() + i, p);
            }
        }
    }
    if (color == 1 && use != 1)
    {
        for (int i = 0; i < blackV.size(); i++)
        {
            if (X == blackV[i].X && Y == blackV[i].Y)
            {
                ChessPieces p = blackV[i];
                blackV.erase(blackV.begin() + i);
                ChessPieces check = TypeOfPieces(blackV[0].X, blackV[0].Y, whiteV, blackV, white);
                int a = check.X;
                int b = check.Y;
                if (this->Cover(x, y, check, blackV[0], whiteV, blackV) == true || (x == a && y == b))
                {
                    blackV.insert(blackV.begin() + i, p);
                    return true;
                }
                if (AllowedMovesKing(blackV[0].X, blackV[0].Y, whiteV, blackV, white) == false)
                {
                    blackV.insert(blackV.begin() + i, p);
                    return false;
                }
                blackV.insert(blackV.begin() + i, p);
            }
        }
    }
    if (color == 0 && use == 1)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if (X == whiteV[i].X && Y == whiteV[i].Y)
            {
                ChessPieces p;
                int k = whiteV[i].X;
                int l = whiteV[i].Y;
                whiteV[i].X = x;
                whiteV[i].Y = y;
                for (int o = 0; o < blackV.size(); o++)
                {
                    if (x == blackV[o].X && y == blackV[o].Y)
                    {
                        p = blackV[o];
                        blackV.erase(blackV.begin() + o);
                        if (AllowedMovesKing(whiteV[0].X, whiteV[0].Y, whiteV, blackV, black) == false)
                        {
                            whiteV[i].X = k;
                            whiteV[i].Y = l;
                            blackV.insert((blackV.begin() + o), p);
                            return false;
                        }
                        whiteV[i].X = k;
                        whiteV[i].Y = l;
                        blackV.insert((blackV.begin() + o), p);
                        return true;

                    }

                }

            }

        }
    }
    if (color == 1 && use == 1)
    {
        for (int i = 0; i < blackV.size(); i++)
        {
            if (X == blackV[i].X && Y == blackV[i].Y)
            {
                ChessPieces p;
                int k = blackV[i].X;
                int l = blackV[i].Y;
                blackV[i].X = x;
                blackV[i].Y = y;
                for (int o = 0; o < whiteV.size(); o++)
                {
                    if (x == whiteV[o].X && y == whiteV[o].Y)
                    {
                        p = whiteV[o];
                        whiteV.erase(whiteV.begin() + o);
                        if (AllowedMovesKing(blackV[0].X, blackV[0].Y, whiteV, blackV, white) == false)
                        {
                            blackV[i].X = k;
                            blackV[i].Y = l;
                            whiteV.insert((whiteV.begin() + o), p);
                            return false;
                        }
                        blackV[i].X = k;
                        blackV[i].Y = l;
                        whiteV.insert((whiteV.begin() + o), p);
                        return true;
                    }
                }
            }
        }
    }
    return true;
}

bool ChessPieces::Cover(int x, int y, ChessPieces& piece, ChessPieces& king, vector<ChessPieces>& whiteV, vector<ChessPieces>& blackV)
{
    if (piece.fColor == 1)
    {
        for (int i = 0; i < blackV.size(); i++)
        {
            if (blackV[i].AllowedMoves(x, y, whiteV, blackV, piece.fColor, 0) == true)
            {
                int z = 0;
                z++;
                if (z == 2)
                {
                    return false;
                }
            }
        }
    }
    if (piece.fColor == 0)
    {
        for (int i = 0; i < whiteV.size(); i++)
        {
            if (whiteV[i].AllowedMoves(x, y, whiteV, blackV, piece.fColor, 0) == true)
            {
                int z = 0;
                z++;
                if (z == 2)
                {
                    return false;
                }
            }
        }
    }
    if (piece.Y == king.Y && piece.X < king.X)
    {
        for (int i = 1; i < king.X - piece.X; i++)
        {
            if (x == piece.X + i && y == piece.Y)
            {
                return true;
            }
        }
    }
    else if (piece.Y == king.Y && piece.X > king.X)
    {
        for (int i = 1; i < piece.X - king.X; i++)
        {
            if (x == piece.X - i && y == piece.Y)
            {
                return true;
            }
        }
    }
    else if (piece.Y < king.Y && piece.X == king.X)
    {
        for (int i = 1; i < king.Y - piece.Y; i++)
        {
            if (x == piece.X && y == piece.Y + i)
            {
                return true;
            }
        }
    }
    else if (piece.Y > king.Y && piece.X == king.X)
    {
        for (int i = 1; i < piece.Y - king.Y; i++)
        {
            if (x == piece.X && y == piece.Y - i)
            {
                return true;
            }
        }
    }
    else if (piece.Y > king.Y && piece.X > king.X)
    {
        for (int i = 1; i < piece.X - king.X; i++)
        {
            if (x == piece.X - i && y == piece.Y - i)
            {
                return true;
            }
        }
    }
    else if (piece.Y < king.Y && piece.X < king.X)
    {
        for (int i = 1; i < king.X - piece.X; i++)
        {
            if (x == piece.X + i && y == piece.Y + i)
            {
                return true;
            }
        }
    }
    else if (piece.Y > king.Y && piece.X < king.X)
    {
        for (int i = 1; i < king.X - piece.X; i++)
        {
            if (x == piece.X + i && y == piece.Y - i)
            {
                return true;
            }
        }

    }
    else if (piece.Y < king.Y && piece.X > king.X)
    {
        for (int i = 1; i < piece.X - king.X; i++)
        {
            if (x == piece.X - i && y == piece.Y + i)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}
