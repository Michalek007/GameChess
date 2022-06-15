#include "Interface.h"

using namespace std;
using Matrix = vector<vector<bool>>;
bool Interface::show_legal_moves = true;
void Interface::Coord(int x, int y, int z) {
    COORD c;
    // (1,1) -> (7,24)
    int a = 6 * x + 1;
    int b = 27 - 3 * y;
    c.X = a -2;
    c.Y = b -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    if (z == 1) {
        if ((x % 2 != 0 && y % 2 != 0) || (x % 2 == 0 && y % 2 == 0)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 130);
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
        }
        cout << u8"\u250C";
        cout << u8"\u2500";
        cout << u8"\u2500";
        cout << u8"\u2500";
        cout << u8"\u2510";
        c.Y = b;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << u8"\u2502";
        c.X = a + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << u8"\u2502";
        c.X = a - 2;
        c.Y = b+1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << u8"\u2514";
        cout << u8"\u2500";
        cout << u8"\u2500";
        cout << u8"\u2500";
        cout << u8"\u2518";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    if (z == 0) {
        if ((x % 2 != 0 && y % 2 != 0) || (x % 2 == 0 && y % 2 == 0)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 130);
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
        }
        c.Y = b - 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << "      ";
        c.Y = b;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << " ";
        c.X = a + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << " ";
        c.X = a - 2;
        c.Y = b+1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << "      ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}
void Interface::CoordP(int x, int y) {
    COORD c;
    int a = 55 * x;
    int b = 3 + 2 * y;
    c.X = a;
    c.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Interface::CoordMenu(int x, int y, int z) {
    COORD c;
    int a = 73 * x;
    int b = 10 + 2 * y;
    c.X = a;
    c.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    cout << ">";
    if (z == 0) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << " ";
    }
}
void Interface::Move(int x, int y, string& ID, vector <string>& moves, int count, string& take) {
    string move;
    string id = ID;
    move.push_back(x + 96);
    move.push_back(y + 48);   
    if (take.empty() == false) {
        move.insert(move.size(), take);
    }
    if (id[0] == 'p' && (y == 8 || y == 1)) {
        move.insert(move.size(), "promotion");
    }
    moves.push_back(id + move);
    take.erase();
    /*string move;
    string id = to_string(count);
    id.push_back('.');
    id.push_back(ID[0]);
    id.push_back(ID[1]);
    id.push_back(ID[2]);
    move.push_back(x + 96);
    move.push_back(y + 48);
    
    take.erase();
    m[id] = move;*/
}
void Interface::Choice(int& a, int& b, vector <ChessPieces>& white, vector <ChessPieces>& black, string& id, Matrix& m, int& turn, vector <string>& moves, int& count, bool& bot_gamemode, vector<string>& pieces){
    int x = 1;
    int y = 1;
    ChessPieces p;
    while (true) {
        Coord(x, y, 1);
        //cout << _getch() << endl;
        char c = _getch();
        Coord(x, y, 0);
        if (c == 72) {
            if (y + 1 < 9) {
                y += 1;
            }
        }
        if (c == 80) {
            if (y - 1 > 0) {
                y -= 1;
            }
        }
        if (c == 75) {
            if (x - 1 > 0) {
                x -= 1;
            }
        }
        if (c == 77) {
            if (x + 1 < 9) {
                x += 1;
            }
            else {
                x = 1;
                y = 1;
                while (true) {
                    CoordMenu(x, y, 1);
                    char c = _getch();
                    CoordMenu(x, y, 0);
                    if (c == 80) {
                        if (y + 1 < 6) {
                            y += 1;
                        }
                    }
                    if (c == 72) {
                        if (y - 1 > 0) {
                            y -= 1;
                        }
                    }
                    if (c == 75) {
                        x = 1;
                        y = 1;
                        break;
                    }
                    if (c == 13) {
                        if (y == 1) {
                            COORD m{ 7,1 };
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
                            cout << "                  " << endl;
                            Position::SetAllPieces(white, black);
                            count = 1;
                            turn = 0;
                            moves.clear();
                            a = 1;
                            b = 1;
                            ChessPieces::castleLW = true;
                            ChessPieces::castleRW = true;
                            ChessPieces::castleLB = true;
                            ChessPieces::castleRB = true;
                            bot_gamemode = false;
                        }
                        if (y == 2) {
                            ofstream save{ "partia.txt" };
                            fstream file("partia.txt");
                            if (file.is_open()) {
                                file << turn;
                                for (int i = 0; i < pieces.size(); i++) {
                                    file << pieces[i];
                                }
                                file.close();
                            }
                        }
                        if (y == 3) {
                            COORD m{ 7,1 };
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
                            cout << "                  " << endl;
                            vector<string> save;
                            string line;
                            string str;
                            fstream file("partia.txt");
                            if (file.is_open()) {
                                getline(file, line);
                                file.close();
                            }
                            for (int i = 0; i < line.size()/4; i++) {
                                for (int j = 1; j < 5; j++) {
                                    int index = 4 * i + j;
                                    str.push_back(line[index]);
                                }
                                save.push_back(str);
                                str.clear();
                            }
                            black.clear();
                            white.clear();
                            moves.clear();
                            a = 1;
                            b = 1;
                            count = 1;
                            ChessPieces t;
                            for (int i = 0; i < save.size(); i++) {
                                t.X = save[i][1] - 96;
                                t.Y = save[i][2] - 48;
                                if (save[i][0] == 'q') {
                                    t.fType = t.queen;
                                }
                                if (save[i][0] == 'b') {
                                    t.fType = t.bishop;
                                }
                                if (save[i][0] == 'n') {
                                    t.fType = t.knight;
                                }
                                if (save[i][0] == 'r') {
                                    t.fType = t.rook;
                                }
                                if (save[i][0] == 'p') {
                                    t.fType = t.pone;
                                }
                                if (save[i][0] == 'k') {
                                    t.fType = t.king;
                                }
                                if (save[i][3] == 'w') {
                                    t.fColor = ChessPieces::white;
                                    t.Set_ID();
                                    t.Set_Symbols();
                                    white.push_back(t);
                                }
                                if (save[i][3] == 'b') {
                                    t.fColor = ChessPieces::black;
                                    t.Set_ID();
                                    t.Set_Symbols();
                                    black.push_back(t);
                                }
                            }
                            Position::Clear();
                            for (int i = 0; i < white.size(); i++)
                            {
                                Position::PiecePosition(white[i].X, white[i].Y, white[i]);
                            }
                            for (int i = 0; i < black.size(); i++)
                            {
                                Position::PiecePosition(black[i].X, black[i].Y, black[i]);
                            }
                            turn = line[0] - 48;
                        }
                        if (y == 4) {
                            ofstream record{ "zapis_partii.txt" };
                            if (record.is_open()) {
                                for (int i = 0; i < moves.size(); i++) {
                                    record << moves[i] << endl;
                                }
                            }
                        }
                        if (y == 5) {
                            COORD e{ 0,30 };
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), e);
                            exit(0);
                        }
                        return;
                    }
                }
            }
        }
        if (c == 98) {
            bot_gamemode = !bot_gamemode;
        }
        if (c == 116) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for (int i = 0; i < 8; i++) {
                for (int o = 0; o < 8; o++) {
                    COORD c;
                    c.X = 6 * i + 6;
                    c.Y = 24 - 3 * o;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                    if ((o % 2 != 0 && i % 2 != 0) || (o % 2 == 0 && i % 2 == 0)) {
                        SetConsoleTextAttribute(hConsole, 130);
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 114);
                    }
                    cout << " " << endl;
                }
            }
            SetConsoleTextAttribute(hConsole, 7);
            show_legal_moves = !show_legal_moves;
        }
        if (c == 114 && moves.empty() == false) {
            COORD m{ 7,1 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
            cout << "                  " << endl;
            Interface::Return(white, black, turn, moves, count);
                }
        if (c == 13) {
            for (size_t i = 0; i < white.size(); i++) {
                if (white[i].X == x && white[i].Y == y) {
                    id = white[i].ID;
                }
            }
            for (size_t i = 0; i < black.size(); i++) {
                if (black[i].X == x && black[i].Y == y) {
                    id = black[i].ID;
                }
            }
            if (id.empty()) {
                return;
            }
            if (id.empty() == false) {
                if (turn == 0) {
                    for (int i = 0; i < white.size(); i++) {
                        if (white[i].ID == id) {
                            m = white[i].AllowedMoves(white, black, p.white, 0);
                            white[i].AllowedMoves(m, white, black);
                        }
                    }
                }
                if (turn == 1) {
                    for (int i = 0; i < black.size(); i++) {
                        if (black[i].ID == id) {
                            m = black[i].AllowedMoves(white, black, p.black, 0);
                            black[i].AllowedMoves(m, white, black);
                        }
                    }
                }
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                for (int i = 0; i < 8; i++) {
                    for (int o = 0; o < 8; o++) {
                        COORD c;
                        c.X = 6 * i + 6;
                        c.Y = 24 - 3 * o;
                        //c.X = 9 + 9 * i;
                        //c.Y = 41 - 5 * o;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                        /* cout << i+1 << o+1;*/
                        //cout << m[i][o] << endl;
                        if (m.empty() == true) {
                            return;
                        }
                        if (Interface::show_legal_moves) {
                            if (m[i][o] == true) {
                                if ((o % 2 != 0 && i % 2 != 0) || (o % 2 == 0 && i % 2 == 0)) {
                                    SetConsoleTextAttribute(hConsole, 130);
                                }
                                else {
                                    SetConsoleTextAttribute(hConsole, 114);
                                }
                                cout << "+" << endl;
                            }
                            else {
                                if ((o % 2 != 0 && i % 2 != 0) || (o % 2 == 0 && i % 2 == 0)) {
                                    SetConsoleTextAttribute(hConsole, 132);
                                }
                                else {
                                    SetConsoleTextAttribute(hConsole, 116);
                                }
                                cout << "-" << endl;
                            }
                        }
                    }
                }
                SetConsoleTextAttribute(hConsole, 7);

                while (true) {
                    Coord(x, y, 1);
                    c = _getch();
                    Coord(x, y, 0);
                    if (c == 72) {
                        if (y + 1 < 9) {
                            y += 1;
                        }
                    }
                    if (c == 80) {
                        if (y - 1 > 0) {
                            y -= 1;
                        }
                    }
                    if (c == 75) {
                        if (x - 1 > 0) {
                            x -= 1;
                        }
                    }
                    if (c == 77) {
                        if (x + 1 < 9) {
                            x += 1;
                        }
                    }
                    if (c == 13) {
                        a = x;
                        b = y;
                        return;
                    }
                }
                return;
            }
        }
    }
}
void Interface::Return(vector <ChessPieces>& white, vector <ChessPieces>& black, int& turn, vector <string>& moves, int& count) {
    ChessPieces c;
    //string s;
    //for (auto elements : moves) {
    //    s.push_back(elements.first[0] - 48);
    //    s.push_back(elements.first[1] - 48);
    //}
    /*string first = prev(moves.end())->first;
    string second = moves[first];*/
    /* string ab;
     for (int i = 0; i < first.size()-1; i++) {
         int crop{0};
         if (crop == 1) {
             ab.push_back(first[i + 1]);
         }s
         if (first[i] == '.') {
             crop = 1;
         }
     }*/
    string last = moves[moves.size() - 1];
    int a = last[1] - 96;
    int b = last[2] - 48;
    if (turn == 0) {
        for (int i = 0; i < black.size(); i++) {
            if (black[i].X == last[3] - 96 && black[i].Y == last[4] - 48) {
                if (last.size() > 10) {
                    black[i].fType = ChessPieces::pone;
                }
                black[i].Set_Symbols();
                c = black[i];
                black[i].X = a;
                black[i].Y = b;
                black[i].Set_ID();
            }
        }
    }
    if (turn == 1) {
        for (int i = 0; i < white.size(); i++) {
            if (white[i].X == last[3] - 96 && white[i].Y == last[4] - 48) {
                if (last.size() > 10) {
                    white[i].fType = ChessPieces::pone;
                }
                white[i].Set_Symbols();
                c = white[i];
                white[i].X = a;
                white[i].Y = b;
                white[i].Set_ID();
            }
        }
    }
    Position::PiecePosition(a, b, c);
    count -= 1;
    if (last.size() == 8) {
        if (turn == 0) {
            for (int i = 0; i < black.size(); i++) {
                if (black[i].ID == "rf8") {
                    Position::PiecePosition(8, 8, black[i]);
                    black[i].X = 8;
                    black[i].Y = 8;
                    black[i].Set_ID();
                    ChessPieces::castleRB = true;
                    ChessPieces::castleLB = true;
                }
            }
        }
        else {
            for (int i = 0; i < white.size(); i++) {
                if (white[i].ID == "rf1") {
                    Position::PiecePosition(8, 1, white[i]);
                    white[i].X = 8;
                    white[i].Y = 1;
                    white[i].Set_ID();
                    ChessPieces::castleRW = true;
                    ChessPieces::castleLW = true;
                }
            }
        }
    }
    if (last.size() == 10) {
        if (turn == 0) {
            for (int i = 0; i < black.size(); i++) {
                if (black[i].ID == "rd8") {
                    Position::PiecePosition(1, 8, black[i]);
                    black[i].X = 1;
                    black[i].Y = 8;
                    black[i].Set_ID();
                    ChessPieces::castleLB = true;
                    ChessPieces::castleRB = true;
                }
            }
        }
        else {
            for (int i = 0; i < white.size(); i++) {
                if (white[i].ID == "rd1") {
                    Position::PiecePosition(1, 1, white[i]);
                    white[i].X = 1;
                    white[i].Y = 1;
                    white[i].Set_ID();
                    ChessPieces::castleLW = true;
                    ChessPieces::castleRW = true;
                }
            }
        }
    }
    if (last.size() == 6 || last.size() == 15) {
        ChessPieces t;
        t.X = last[3] - 96;
        t.Y = last[4] - 48;
        if (last[5] == 'q') {
            t.fType = t.queen;
        }
        if (last[5] == 'b') {
            t.fType = t.bishop;
        }
        if (last[5] == 'n') {
            t.fType = t.knight;
        }
        if (last[5] == 'r') {
            t.fType = t.rook;
        }
        if (last[5] == 'p') {
            t.fType = t.pone;
        }
        if (turn == 1) {
            ChessPieces taken{ t.X,t.Y,t.fType,t.black };
            black.push_back(taken);
            Position::PiecePosition(taken.X, taken.Y, taken);
        }
        if (turn == 0) {
            ChessPieces taken{ t.X,t.Y,t.fType,t.white };
            white.push_back(taken);
            Position::PiecePosition(taken.X, taken.Y, taken);
        }
    }
    if (c.fColor == c.white) {
        turn = 0;
    }
    if (c.fColor == c.black) {
        turn = 1;
    }
    moves.pop_back();
    //COORD z;
    //z.X = 70;
    //int o = moves.size() - 1;
    //z.Y = 5 + o;
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), z);
    //cout << "                          " << endl;
    //moves.erase(prev(moves.end()));
}
void Interface::Promotion(ChessPieces& piece) {
    const int x = 1;
    int y = 1;
    CoordP(x, 1);
    cout << "queen" << endl;
    CoordP(x, 2);
    cout << "rook" << endl;
    CoordP(x, 3);
    cout << "bishop" << endl;
    CoordP(x, 4);
    cout << "knight" << endl;
    while (true) {
        CoordP(x, y);
        //cout << _getch() << endl;
        char c = _getch();
        //int x = c;
        //cout << x;
        CoordP(x, y);
        if (c == 80) {
            if (y + 1 < 5) {
                y += 1;
            }
        }
        if (c == 72) {
            if (y - 1 > 0) {
                y -= 1;
            }
        }
        if (c == 13) {
            if (y == 1) {
                piece.fType = ChessPieces::queen;
            }
            if (y == 2) {
                piece.fType = ChessPieces::rook;
            }
            if (y == 3) {
                piece.fType = ChessPieces::bishop;
            }
            if (y == 4) {
                piece.fType = ChessPieces::knight;
            }
            piece.Set_Symbols();
            piece.Set_ID();
            Position::PiecePosition(piece.X, piece.Y, piece);
            for (int i = 1; i < 5; i++) {
                CoordP(x, i);
                cout << "      " << endl;
            }
            return;
        }
    }
}
//void Interface::Menu(int& a, int& b, vector <ChessPieces>& white, vector <ChessPieces>& black, int& turn, vector <string>& moves, int& count, bool& bot_gamemode, vector<string>& pieces) {
//    int x = 1;
//    int y = 1;
//    while (true) {
//        CoordMenu(x, y, 1);
//        char c = _getch();
//        CoordMenu(x, y, 0);
//        if (c == 80) {
//            if (y + 1 < 7) {
//                y += 1;
//            }
//        }
//        if (c == 72) {
//            if (y - 1 > 0) {
//                y -= 1;
//            }
//        }
//        if (c == 75) {
//            x = 1;
//            y = 1;
//            break;
//        }
//        if (c == 13) {
//            if (y == 1) {
//                COORD m{ 7,1 };
//                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
//                cout << "                  " << endl;
//                Position::SetAllPieces(white, black);
//                count = 1;
//                turn = 0;
//                moves.clear();
//                a = 1;
//                b = 1;
//                ChessPieces::castleLW = true;
//                ChessPieces::castleRW = true;
//                ChessPieces::castleLB = true;
//                ChessPieces::castleRB = true;
//                bot_gamemode = false;
//            }
//            if (y == 2) {
//                COORD m{ 7,1 };
//                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
//                cout << "                  " << endl;
//                Position::SetAllPieces(white, black);
//                count = 1;
//                turn = 0;
//                moves.clear();
//                a = 1;
//                b = 1;
//                ChessPieces::castleLW = true;
//                ChessPieces::castleRW = true;
//                ChessPieces::castleLB = true;
//                ChessPieces::castleRB = true;
//                bot_gamemode = true;
//            }
//            if (y == 3) {
//                ofstream save{ "partia.txt" };
//                fstream file("partia.txt");
//                if (file.is_open()) {
//                    file << turn;
//                    for (int i = 0; i < pieces.size(); i++) {
//                        file << pieces[i];
//                    }
//                    file.close();
//                }
//            }
//            if (y == 4) {
//                COORD m{ 7,1 };
//                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
//                cout << "                  " << endl;
//                vector<string> save;
//                string line;
//                string str;
//                fstream file("partia.txt");
//                if (file.is_open()) {
//                    getline(file, line);
//                    file.close();
//                }
//                for (int i = 0; i < line.size() / 4; i++) {
//                    for (int j = 1; j < 5; j++) {
//                        str.push_back(line[4 * i + j]);
//                    }
//                    save.push_back(str);
//                    str.clear();
//                }
//                //cout << line;
//                //for (int i = 0; i < save.size(); i++) {
//                //    cout << save[i] << endl;
//                //}
//                black.clear();
//                white.clear();
//                moves.clear();
//                a = 1;
//                b = 1;
//                count = 1;
//                ChessPieces t;
//                for (int i = 0; i < save.size(); i++) {
//                    t.X = save[i][1] - 96;
//                    t.Y = save[i][2] - 48;
//                    if (save[i][0] == 'q') {
//                        t.fType = t.queen;
//                    }
//                    if (save[i][0] == 'b') {
//                        t.fType = t.bishop;
//                    }
//                    if (save[i][0] == 'n') {
//                        t.fType = t.knight;
//                    }
//                    if (save[i][0] == 'r') {
//                        t.fType = t.rook;
//                    }
//                    if (save[i][0] == 'p') {
//                        t.fType = t.pone;
//                    }
//                    if (save[i][0] == 'k') {
//                        t.fType = t.king;
//                    }
//                    if (save[i][3] == 'w') {
//                        t.fColor = ChessPieces::white;
//                        t.Set_ID();
//                        t.Set_Symbols();
//                        white.push_back(t);
//                    }
//                    if (save[i][3] == 'b') {
//                        t.fColor = ChessPieces::black;
//                        t.Set_ID();
//                        t.Set_Symbols();
//                        black.push_back(t);
//                    }
//                }
//                Position::Clear();
//                for (int i = 0; i < white.size(); i++)
//                {
//                    Position::PiecePosition(white[i].X, white[i].Y, white[i]);
//                }
//                for (int i = 0; i < black.size(); i++)
//                {
//                    Position::PiecePosition(black[i].X, black[i].Y, black[i]);
//                }
//                turn = line[0] - 48;
//            }
//            if (y == 5) {
//                ofstream record{ "zapis_partii.txt" };
//                if (record.is_open()) {
//                    for (int i = 0; i < moves.size(); i++) {
//                        record << moves[i] << endl;
//                    }
//                }
//            }
//            if (y == 6) {
//                ofstream save{ "partia.txt" };
//                fstream file("partia.txt");
//                if (file.is_open()) {
//                    file << turn;
//                    for (int i = 0; i < pieces.size(); i++) {
//                        file << pieces[i];
//                    }
//                    file.close();
//                }
//                COORD e{ 0,30 };
//                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), e);
//                exit(0);
//            }
//            return;
//        }    
//    }
//}
