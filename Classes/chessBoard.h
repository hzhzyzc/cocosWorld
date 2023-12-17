#pragma once
#include"cocos2d.h"
#include"chessPiece.h"
USING_NS_CC;

class chessBoard : public Ref
{
public:
	CREATE_FUNC(chessBoard);
	virtual bool init();
	bool judgeHasChess(int x, int y);
	bool judgeHasChess(int type,int x, int y);
	std::vector<chessPiece*>* getWhiteChess();
	std::vector<chessPiece*>* getBlackChess();
	int getType();
	void setType(int type);
private:

	std::vector<chessPiece*> whiteChesses;

	std::vector<chessPiece*> blackChesses;

	//��¼��ǰ�ǰ��廹�Ǻ��壬����Ϊ1������Ϊ2
	int ptr_type;
};
