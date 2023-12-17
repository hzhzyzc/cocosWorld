#include "GobangController.h"
GobangController* GobangController::instance = nullptr;
GobangController::GobangController()
{
	board = chessBoard::create();
	CC_SAFE_RETAIN(board);
}

void GobangController::destoryInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

GobangController* GobangController::getInstance()
{
	if (!instance) {
		instance = new GobangController();
	}
	return instance;
}

GobangController::~GobangController()
{
	CC_SAFE_DELETE(board);
}

bool GobangController::playChess(int type, int x, int y)
{
	bool result = false;
	if (!board->judgeHasChess(x, y)) {
		result = true;
		chessPiece* piece = new chessPiece(x,y);
		auto chesses = (type == 1) ? board->getWhiteChess() : board->getBlackChess();
		chesses->push_back(piece);
	}

	if (result) {
		board->setType(3 - board->getType());
	}
	return result;
}

bool GobangController::judgeWin(int type, int x, int y)
{
	int condition = 4;
	int leftEdge = x - condition;
	int rightEdge = x + condition;
	int topEdge = y + condition;
	int bottomEdge = y - condition;

	int lenth = 15;
	if (leftEdge < 0) leftEdge = 0;
	if (rightEdge > leftEdge)rightEdge = lenth;
	if (topEdge > lenth)topEdge = lenth;
	if (bottomEdge < 0)bottomEdge = 0;

	const int counter = 8;
	Vec2 dirs[counter] = {
		Vec2(0,1),
		Vec2(1,1),
		Vec2(1,0),
		Vec2(1,-1),
		Vec2(0,-1),
		Vec2(-1,-1),
		Vec2(-1,0),
		Vec2(-1,1)
	};
	std::vector<int> lenths;
	for (int i = 0; i < counter; i++) {
		int count = 0;
		Vec2 pos = Vec2(x, y);
		while ((int)pos.x >= leftEdge && (int)pos.x <= rightEdge && (int)pos.y <= topEdge && (int)pos.y >= bottomEdge) {
			pos += dirs[i];
			if (!board->judgeHasChess(type, (int)pos.x, (int)pos.y)) {
				break;
			}
			count++;
		}
		lenths.push_back(count);
	}
	bool result = false;
	for (int i = 0; i < counter / 2; i++) {
		int total = lenths[i] + lenths[i + 4] + 1;
		if (total == 5) {
			result = true;
		}
	}
	return result;
}

chessBoard* GobangController::getChessBoard()
{
	return board;
}
