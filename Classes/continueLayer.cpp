#include "continueLayer.h"

bool continueLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    AudioEngine::pauseAll();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(continueLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto bgcolor = LayerColor::create(Color4B::BLACK);
    bgcolor->setOpacity(128);
    this->addChild(bgcolor);
    auto continueLabel = Label::createWithSystemFont("点击屏幕任意处继续游戏", "楷体", 24);
    continueLabel->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 50));
    this->addChild(continueLabel);
    status = true;
    this->setVisible(false);
    return true;
}



bool continueLayer::onTouchBegan(Touch* touch, Event* event)
{
    this->setVisible(false);
    status = true;
	return true;
}

void continueLayer::showLayer()
{
    this->setVisible(true);
    status = false;
}

bool continueLayer::getStatus()
{
    return status;
}
