#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include"walkingCoco.h"
#include"continueLayer.h"
#include"textBox.h"
#include"iostream"
#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H
USING_NS_CC;
class Gobang;
class mainScene : public Scene {
public:
	CREATE_FUNC(mainScene);

	virtual bool init() override;

	mainScene();
protected:
	void update(float dt) override;

private:
	bool isLeftButtonPressed;
	bool isRightButtonPressed;
	Vec2 cocoPos;
	Sprite* _walkCoco;
	Sprite* _standCoco;
	ParallaxNode* _paraNode;
	int _bg_music;
	bool running;
	continueLayer* stopGame;
	ui::Slider* voiceSlider;
	std::vector<int> voice;
};
#endif
