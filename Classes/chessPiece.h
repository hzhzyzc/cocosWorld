#pragma once
#include"cocos2d.h"
USING_NS_CC;

class chessPiece
{
public:
	chessPiece(int x,int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
private:
	int x;
	int y;
};
