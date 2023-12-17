#pragma once
#include"chessBoard.h"
class GobangController
{
public:
	static GobangController* getInstance();
	~GobangController();
	bool playChess(int type, int x, int y);
	bool judgeWin(int type, int x, int y);
	chessBoard* getChessBoard();
	static void destoryInstance();
private:
	GobangController();
	static GobangController* instance;
	chessBoard* board;
};
