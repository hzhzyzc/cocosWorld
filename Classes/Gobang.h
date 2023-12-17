#pragma once
#ifndef GOBANG_H
#define GOBANG_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
#include"buttonWithText.h"
#include"GobangController.h"
USING_NS_CC;
class mainScene;
class Gobang : public Scene {
public:
	CREATE_FUNC(Gobang);

	virtual bool init() override;

protected:
	void exitGame(Ref* sender);

	void regretChess(Ref* sender);

	void reset(Ref* sender);

	virtual bool onTouchBegin(Touch* touch, Event* event);

	virtual void onTouchEnd(Touch* touch, Event* event);

	Node* createChessPiece(int type, int x, int y);

	void playSuccessAnimation(int type);
private:
	Rect boardSize;
	Sprite* chessMark;
	std::vector<Node*>* allChesses;
};
#endif
