#include "chessBoard.h"

bool chessBoard::init()
{
	ptr_type = 2;
	return true;
}

bool chessBoard::judgeHasChess(int x, int y)
{
	bool result = false;
	result = judgeHasChess(1, x, y);
	if (!result) {
		result = judgeHasChess(2, x, y);
	}
	return result;
}

bool chessBoard::judgeHasChess(int type, int x, int y)
{
	bool result = false;
	if (type == 1) {
		for (auto chess : whiteChesses) {
			if (chess->getX() == x && chess->getY() == y) {
				result = true;
				break;
			}
		}
	}
	else
	{
		for (auto chess : blackChesses) {
			if (chess->getX() == x && chess->getY() == y) {
				result = true;
				break;
			}
		}
	}
	return result;
}

std::vector<chessPiece*>* chessBoard::getWhiteChess()
{
	return &whiteChesses;
}

std::vector<chessPiece*>* chessBoard::getBlackChess()
{
	return &blackChesses;
}

int chessBoard::getType()
{
	return ptr_type;
}

void chessBoard::setType(int type)
{
	ptr_type = type;
}
