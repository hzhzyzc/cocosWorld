#pragma once
#ifndef BEGIN_GAME_H
#define BEGIN_GAME_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
#include"openingShowLayer.h"
#include"Interface.h"
USING_NS_CC;
class BeginGame : public Scene {
public:
	CREATE_FUNC(BeginGame);
	

	virtual bool init() override;

};
#endif