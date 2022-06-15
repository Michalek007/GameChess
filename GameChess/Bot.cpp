#include "Bot.h"

using namespace std;
using Matrix = vector<vector<bool>>;
using Pieces = vector<ChessPieces>;

bool Bot::is_done = false;
int Bot::powerNowB = 0;
int Bot::powerAfterB = 0;
int Bot::powerNowW = 0;
int Bot::powerAfterW = 0;

void Bot::VectorOfPieces(vector<string>& pieces) {
	//white.clear();
	//black.clear();
	ChessPieces t;
	for (int i = 0; i < pieces.size(); i++) {
		t.X = pieces[i][1] - 96;
		t.Y = pieces[i][2] - 48;
		if (pieces[i][0] == 'q') {
			t.fType = t.queen;
		}
		if (pieces[i][0] == 'b') {
			t.fType = t.bishop;
		}
		if (pieces[i][0] == 'n') {
			t.fType = t.knight;
		}
		if (pieces[i][0] == 'r') {
			t.fType = t.rook;
		}
		if (pieces[i][0] == 'p') {
			t.fType = t.pone;
		}
		if (pieces[i][0] == 'k') {
			t.fType = t.king;
		}
		if (pieces[i][3] == 'w') {
			t.fColor = ChessPieces::white;
			t.Set_ID();
			t.Set_Symbols();
			white.push_back(t);
		}
		if (pieces[i][3] == 'b') {
			t.fColor = ChessPieces::black;
			t.Set_ID();
			t.Set_Symbols();
			black.push_back(t);
		}
	}
}
bool Bot::Is_legal(string& figure, char x, char y) {
	ChessPieces piece = black[1];
	if (figure[3] == 'w') {
		for (int i = 0; i < white.size(); i++) {
			if (white[i].X == figure[1]-96 && white[i].Y == figure[2] - 48) {
				piece = white[i];
			}
		}
	}
	if (figure[3] == 'b') {
		for (int i = 0; i < black.size(); i++) {
			if (black[i].X == figure[1] - 96 && black[i].Y == figure[2] - 48) {
				piece = black[i];
			}
		}
	}
	Matrix matrix = piece.AllowedMoves(white, black, piece.fColor, 0);
	piece.AllowedMoves(matrix, white, black);
	if (matrix[x - 1 - 96][y - 1 - 48] == true)
	{
		return true;
	}
	return false;
}
vector<string> Bot::Legal_moves(string& figure, vector<string>& pieces) {
	vector <ChessPieces> white;
	vector <ChessPieces> black;
	ChessPieces t;
	ChessPieces piece;
	for (int i = 0; i < pieces.size(); i++) {
		t.X = pieces[i][1] - 96;
		t.Y = pieces[i][2] - 48;
		if (pieces[i][0] == 'q') {
			t.fType = t.queen;
		}
		if (pieces[i][0] == 'b') {
			t.fType = t.bishop;
		}
		if (pieces[i][0] == 'n') {
			t.fType = t.knight;
		}
		if (pieces[i][0] == 'r') {
			t.fType = t.rook;
		}
		if (pieces[i][0] == 'p') {
			t.fType = t.pone;
		}
		if (pieces[i][0] == 'k') {
			t.fType = t.king;
		}
		if (pieces[i][3] == 'w') {
			t.fColor = ChessPieces::white;
			t.Set_ID();
			t.Set_Symbols();
			white.push_back(t);
		}
		if (pieces[i][3] == 'b') {
			t.fColor = ChessPieces::black;
			t.Set_ID();
			t.Set_Symbols();
			black.push_back(t);
		}
		if (figure == pieces[i]) {
			piece = t;
		}
	}
	Matrix matrix = piece.AllowedMoves(white, black, piece.fColor, 0);
	piece.AllowedMoves(matrix, white, black);
	return ChessPieces::AllowedMoves(matrix);
}

string Bot::Move(vector<string>& pieces, int count, int turn) {
	srand(time(NULL));
	string move;
	powerB = Power(pieces, 'b');
	powerW = Power(pieces, 'w');
	move = Bot::Take(pieces, turn);
	if (turn == 0 && move.empty()) {
		vector <string> whiteV;
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i][3] == 'w') {
				whiteV.push_back(pieces[i]);
			}
		}
		while (true) {
			int c = rand() % white.size();
			vector <string> legal_moves = Legal_moves(whiteV[c],pieces);
			if (legal_moves.empty() == true) {
				continue;
			}
			int d = rand() % legal_moves.size();
			return whiteV[c] + legal_moves[d];
		}
	}
	if (turn == 1 && move.empty()) {
		vector <string> blackV;
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i][3] == 'b') {
				blackV.push_back(pieces[i]);
			}
		}
		while (true) {
			int c = rand() % blackV.size();
			vector <string> legal_moves = Legal_moves(blackV[c], pieces);
			if (legal_moves.empty() == true) {
				continue;
			}
			int d = rand() % legal_moves.size();
			return blackV[c] + legal_moves[d];
		}
	}
	return move;
}
string Bot::Take(vector<string>& pieces, int turn) {
	map <int, string> moves;
	string s;
	string move;
	if (turn == 0 && deep != 3) {
		VectorOfPieces(pieces);
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i][3] == 'w') {
				for (int j = 0; j < pieces.size(); j++) {
					if (pieces[j][3] == 'b') {
						if (Is_legal(pieces[i], pieces[j][1], pieces[j][2])) {
							string s{ pieces[j] };
							pieces.erase(pieces.begin() + j);
							//deep++;
							//Take(pieces, 1);
							moves[Power(pieces, 'w') - Power(pieces, 'b')] = pieces[i];
							pieces.insert(pieces.begin() + j, s);
						}
					}
				}
			}
		}
		int diff = prev(moves.begin())->first;
		if (diff >= (powerW - powerB)) {
			move = moves[diff];
			move.pop_back();
			move.erase(move.begin());

		}
	}
	if (turn == 1 && deep != 3) {
		VectorOfPieces(pieces);
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i][3] == 'b') {
				for (int j = 0; j < pieces.size(); j++) {
					if (pieces[j][3] == 'w') {
						if (Is_legal(pieces[i], pieces[j][1], pieces[j][2])) {
							string s{ pieces[j] };
							string m{ pieces[i] };
							pieces.erase(pieces.begin() + j);
							//deep++;
							//Take(pieces, 0);
							moves[Power(pieces, 'w') - Power(pieces, 'b')] = m + s;
							pieces.insert(pieces.begin() + j, s);
						}
					}
				}
			}
		}
		if (moves.empty()) {
			return move;
		}
		int diff = moves.begin()->first;
		if (diff <= (powerW - powerB)) {
			move = moves[diff];
			move.pop_back();
			move.erase(move.begin() + 4);
			return move;
		}
	}
	return move;
}
int Bot::Power(vector<string>& pieces, char c) {
	int power = 0;
	int p;
	for (int i = 0; i < pieces.size(); i++) {
		if (pieces[i][3] == c) {
			Bot::Power(pieces[i][0], p);
			power += p;
		}
	}
	return power;
}
void Bot::Power(char c, int& power) {
	if (c == 'q') {
		power = 9;
	}
	if (c == 'b') {
		power = 3;
	}
	if (c == 'n') {
		power = 3;
	}
	if (c == 'r') {
		power = 5;
	}
	if (c == 'p') {
		power = 1;
	}
	if (c == 'k') {
		power = 0;
	}
}

void Bot::Take(Pieces& white, Pieces& black, int& count, vector<string>& moves, vector<string>& pieces) {
	int x;
	int y;
	string take;
	int i;
	bool move;
	TakeB(x, y, white, black, pieces, i, move);
	if (move == true) {
		_Move(x, y, white, black, i, take, count, moves);
		Bot::is_done = true;
		return;
	}
}
void Bot::TakeB(int& x, int& y, Pieces& white, Pieces& black, vector<string>& pieces,int& iterator, bool& move) {
	vector<string> pieces_f;
	Matrix m;
	for (int i = 0; i < black.size(); i++) {
		int powerW;
		int powerB;
		m = black[i].AllowedMoves(white, black, ChessPieces::black, 0);
		black[i].AllowedMoves(m, white, black);
		Bot::Power(black[i].ID[0],powerB);
		for (int l = 0; l < pieces.size(); l++) {
			if (pieces[l][3] == 'b') {
				continue;
			}
			x = pieces[l][1] - 96;
			y = pieces[l][2] - 48;
			Bot::Power(pieces[l][0], powerW);
			if (x - 1 < 0 || y - 1 < 0) {
				continue;
			}
			if (m[x - 1][y - 1] == true) {
				if (powerW >= powerB){
					move = true;
					iterator = i;
					return;
				}
			}
		}
	}
}
//void Bot::TakeB(int& x, int& y, Pieces& white, Pieces& black, vector<string>& pieces, int& iterator, bool& move) {
//	vector<string> pieces_f;
//	Matrix m;
//	for (int i = 0; i < black.size(); i++) {
//		int powerW;
//		int powerB;
//		m = black[i].AllowedMoves(white, black, ChessPieces::black, 0);
//		black[i].AllowedMoves(m, white, black);
//		Bot::Power(black[i].ID[0], powerB);
//		for (int l = 0; l < pieces.size(); l++) {
//			if (pieces[l][3] == 'b') {
//				continue;
//			}
//			x = pieces[l][1] - 96;
//			y = pieces[l][2] - 48;
//			Bot::Power(pieces[l][0], powerW);
//			if (x - 1 < 0 || y - 1 < 0) {
//				continue;
//			}
//			if (m[x - 1][y - 1] == true) {
//				if (powerW >= powerB) {
//					move = true;
//					iterator = i;
//					return;
//					/*pieces_f = pieces;
//					string str{ black[i].ID[0],pieces[l][1],pieces[l][2],'b' };
//					pieces_f.erase(pieces.begin() + l);
//					pieces_f.push_back(str);
//					Bot::deep += 1;
//					if (deep == 5) {
//						if ((Bot::powerNowB >= Bot::powerNowW && Bot::powerAfterB >= Bot::powerAfterW) || Bot::powerAfterB >= Bot::powerAfterW) {
//
//						}
//					}
//					TakeW(x, y, white, black, pieces_f, iterator, move);*/
//				}
//			}
//		}
//	}
//}
void Bot::TakeW(int& x, int& y, Pieces& white, Pieces& black,vector<string>& pieces, int& iterator, bool& move) {
	vector<string> pieces_f;
	string take;
	Matrix m;
	for (int i = 0; i < white.size(); i++) {
		int powerW;
		int powerB;
		m = white[i].AllowedMoves(white, black, ChessPieces::white, 0);
		white[i].AllowedMoves(m, white, black);
		Bot::Power(white[i].ID[0], powerW);
		for (int l = 0; l < pieces.size(); l++) {
			if (pieces[l][3] == 'w') {
				continue;
			}
			x = pieces[l][1] - 96;
			y = pieces[l][2] - 48;
			Bot::Power(pieces[l][0], powerB);
			if (x - 1 < 0 || y - 1 < 0) {
				continue;
			}
			if (m[x - 1][y - 1] == true) {
				if (powerB >= powerW) {
					pieces_f = pieces;
					string str{ black[i].ID[0],pieces[l][1],pieces[l][2],'b' };
					pieces_f.erase(pieces.begin() + l);
					pieces_f.push_back(str);
					Bot::deep += 1;
					return;
				}
			}
		}
	}
}
void Bot::_Move(int x, int y, Pieces& white, Pieces& black, int c, string& take, int& count, vector<string>& moves) {
	Position::PiecePosition(x, y, black[c]);
	black[c].X = x;
	black[c].Y = y;
	ChessPieces::Take(x, y, white, black, ChessPieces::black, take);
	Interface::Move(x, y, black[c].ID, moves, count, take);
	black[c].Set_ID();
	return;
}
void Bot::Move(int& x, int& y, Pieces& white, Pieces& black, int& count, vector<string>& moves, vector<string>& pieces) {
	srand(time(NULL));
	vector<string> vec;
	Matrix m;
	string take;
	Bot::is_done = false;
	Bot::Take(white, black, count, moves, pieces);
	if (count >= 0 && Bot::is_done == false) {
		while (true) {
			int c = rand() % black.size();
			m = black[c].AllowedMoves(white, black, ChessPieces::black, 0);
			black[c].AllowedMoves(m, white, black);
			vec = ChessPieces::AllowedMoves(m);
			if (vec.empty() == true) {
				continue;
			}	
			int move = rand() % vec.size();
			x = vec[move][0] - 96;
			y = vec[move][1] - 48;
			_Move(x, y, white, black, c, take, count, moves);
			return;
		}
	}
	/*	if (count < 3) {
			while (true) {
				int c = rand() % 8 + 8;
				m = black[c].AllowedMoves(white, black, f.black, 0);
				black[c].AllowedMoves(m, white, black);
				vec = f.AllowedMoves(m);
				if (vec.empty() == true) {
					continue;
				}
				int move = rand() % vec.size();
				x = vec[move][0] - 96;
				y = vec[move][1] - 48;
				_Move(x, y, white, black, c);
				return;
			}
		}*/
	
	/*if (count < 8) {
		for (int i = 0; i < black.size(); i++) {
			if (black[i].fType == f.bishop) {
				m = black[i].AllowedMoves(white, black, f.black, 0);
				black[i].AllowedMoves(m, white, black);
				vec = f.AllowedMoves(m);
				int move = rand() % vec.size();
				if (vec.empty() == true) {
					continue;
				}
				x = vec[move][0] - 96;
				y = vec[move][1] - 48;
				position.PiecePosition(x, y, black[i]);
				black[i].X = x;
				black[i].Y = y;
				f.Take(x, y, white, black, f.black);
				break;
			}
			if (black[i].fType == f.knight) {
				m = black[i].AllowedMoves(white, black, f.black, 0);
				black[i].AllowedMoves(m, white, black);
				vec = f.AllowedMoves(m);
				int move = rand() % vec.size();
				if (vec.empty() == true) {
					continue;;
				}
				x = vec[move][0] - 96;
				y = vec[move][1] - 48;
				position.PiecePosition(x, y, black[i]);
				black[i].X = x;
				black[i].Y = y;
				f.Take(x, y, white, black, f.black);
				break;
			}
		}
		for (int i = 0; i < black.size(); i++) {
			if (black[i].fType == f.knight) {
				m = black[i].AllowedMoves(white, black, f.black, 0);
				black[i].AllowedMoves(m, white, black);
				vec = f.AllowedMoves(m);
				int move = rand() % vec.size();
				if (vec.empty() == true) {
					continue;;
				}
				x = vec[move][0] - 96;
				y = vec[move][1] - 48;
				position.PiecePosition(x, y, black[i]);
				black[i].X = x;
				black[i].Y = y;
				f.Take(x, y, white, black, f.black);
				break;
			}
		}

	}*/
}
