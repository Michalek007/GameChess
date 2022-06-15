#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <map>
#include "ChessPieces.h"
#include "Position.h"
#include "Interface.h"

class Bot
{
public:
	static int powerNowB;
	static int powerAfterB;
	static int powerNowW;
	static int powerAfterW;
	static bool is_done;

	int powerB;
	int powerW;
	int deep;
	vector <ChessPieces> black;
	vector <ChessPieces> white;
	string move;

	Bot() {
		powerB = 0;
		powerW = 0;
		deep = 0;
	}

	void VectorOfPieces(vector<string>&);
	bool Is_legal(string&, char, char);
	vector<string> Legal_moves(string&, vector<string>&);

	string Move(vector<string>&, int, int);
	string Take(vector<string>&, int);

	int Power(vector<string>&, char);
	void Power(char, int&);

	void Take(vector<ChessPieces>&, vector<ChessPieces>&, int&, vector<string>&, vector<string>&);
	void TakeB(int&, int&, vector<ChessPieces>&, vector<ChessPieces>&,vector<string>&, int&, bool&);
	void TakeW(int&, int&, vector<ChessPieces>&, vector<ChessPieces>&,vector<string>&, int&, bool&);
	void _Move(int, int , vector<ChessPieces>& , vector<ChessPieces>& , int , string& , int& , vector<string>&);
	void Move(int&, int&, vector<ChessPieces>&, vector<ChessPieces>&, int&, vector<string>&, vector<string>&);
};