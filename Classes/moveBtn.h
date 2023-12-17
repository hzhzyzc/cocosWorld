#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;
class moveBtn : public ui::Button {
public:
	CREATE_FUNC(moveBtn);

	virtual bool init() override;

	void bindSceneAndSprite(Scene* scene , Sprite* sprite, Vec2 pos);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	virtual void onTouchEnded(Touch* touch, Event* event);

	void update(float dt);


	Action* addDirAndSpeed(Vec2 pos);
};