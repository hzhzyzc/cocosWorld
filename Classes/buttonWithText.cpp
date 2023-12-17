#include "buttonWithText.h"

bool buttonWithText::init()
{
	if (!Node::init()) {
		return false;
	}
	return true;
}

void buttonWithText::setButton(const std::string& text, ui::Widget::ccWidgetClickCallback callback)
{
	auto buttonPic = ui::Button::create("cocosWorld/img/icon/button.png");
	buttonPic->addClickEventListener(callback);
	auto label = Label::createWithSystemFont(text, "¿¬Ìå", 40);
	label->setTextColor(Color4B::BLACK);
	this->addChild(buttonPic, -1);
	label->setContentSize(buttonPic->getContentSize());
	label->setPosition(buttonPic->getPosition());
	this->addChild(label, 1);
}

