#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;
class buttonWithText : public Node {
public:
	CREATE_FUNC(buttonWithText);

	virtual bool init() override;

	void setButton(const std::string& text,ui::Widget::ccWidgetClickCallback callback);

private:
	Label* label;
};

