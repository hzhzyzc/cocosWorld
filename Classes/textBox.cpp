#include "textBox.h"

bool textBox::init()
{
    if (!Node::init()) {
        return false;
    }


    return true;
}

void textBox::setText(const std::string& text)
{

    label = Label::createWithSystemFont(text, "¿¬Ìå", 20);
    label->setTextColor(Color4B::BLACK);
    label->setWidth(149);
    label->setLineBreakWithoutSpace(true);
    this->addChild(label, 1);
    auto background = ui::Scale9Sprite::create("cocosWorld/img/icon/textBox.png");
    background->setCapInsets(Rect(33, 87, 149, 48));
    background->setContentSize(Size(label->getContentSize().width + 63, label->getContentSize().height + 164));
    background->setPosition(Vec2::ZERO);
    this->addChild(background, -1);
}




