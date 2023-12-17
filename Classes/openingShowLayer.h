#pragma once
#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;
class openingShowLayer : public Layer {
public:
	CREATE_FUNC(openingShowLayer);

	virtual bool init() override;

	void setCircle(Sprite*& circle, Vec2 point, float scale, Sequence*& action, LayerColor*& layer);

	void removeAfterShow();

};
