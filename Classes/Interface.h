#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
#include"walkingCoco.h"
USING_NS_CC;
class mainScene;
class Interface : public Scene {
public:
	CREATE_FUNC(Interface);


	virtual bool init() override;

}; 
#endif
