#include "chessPiece.h"

chessPiece::chessPiece(int x, int y):
	x(x),
	y(y)
{
}

int chessPiece::getX()
{
	return x;
}

int chessPiece::getY()
{
	return y;
}

void chessPiece::setX(int x)
{
	this->x = x;
}

void chessPiece::setY(int y)
{
	this->y = y;
}
