#include "walkingCoco.h"



bool walkingCoco::init()
{
    if (!Sprite::init()) {
        return false;
    }

    Vector<SpriteFrame*> frames;
    frames.pushBack(SpriteFrame::create("cocosWorld/img/character/walk_01.png", Rect(0, 0, 500, 629)));
    frames.pushBack(SpriteFrame::create("cocosWorld/img/character/walk_02.png", Rect(0, 0, 500, 629)));
    frames.pushBack(SpriteFrame::create("cocosWorld/img/character/walk_03.png", Rect(0, 0, 500, 629)));
    frames.pushBack(SpriteFrame::create("cocosWorld/img/character/walk_02.png", Rect(0, 0, 500, 629)));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);
    Animate* animate = Animate::create(animation);    
    this->initWithSpriteFrame(frames.front());
    this->runAction(RepeatForever::create(animate));
    return true;
}
