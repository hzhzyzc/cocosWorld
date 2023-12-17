#include "startLayer.h"

bool startLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto screenSize = Director::getInstance()->getVisibleSize();
    walkingCoco* coco = walkingCoco::create();
    //coco->setPosition
    this->addChild(coco);
    return true;
}
