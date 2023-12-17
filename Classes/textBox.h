#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;
class textBox : public Node {
public:
	CREATE_FUNC(textBox);

	virtual bool init() override;

	void setText(const std::string& text);

private:
	Label* label;
}; 
