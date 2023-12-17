#include "moveBtn.h"

bool moveBtn::init()
{
    if (!ui::Button::init()) {
        return false;
    }
    return true;
}

Action* moveBtn::addDirAndSpeed(Vec2 pos)
{
    MoveBy::create(2, pos);
    return nullptr;
}


void moveBtn::bindSceneAndSprite(Scene* scene, Sprite* sprite, Vec2 pos)
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(moveBtn::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(moveBtn::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(moveBtn::onTouchEnded, this);
}

bool moveBtn::onTouchBegan(Touch* touch, Event* event)
{
    return false;
}

void moveBtn::onTouchMoved(Touch* touch, Event* event)
{
}

void moveBtn::onTouchEnded(Touch* touch, Event* event)
{
}








