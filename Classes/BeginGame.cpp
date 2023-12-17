#include "BeginGame.h"


bool BeginGame::init()
{
    if (!Scene::init()) {
        return false;
    }

    auto screenSize = Director::getInstance()->getVisibleSize();
    openingShowLayer* animate = openingShowLayer::create();
    this->addChild(animate);
    animate->removeAfterShow();
    //auto changeScene = Sequence::create(DelayTime::create(7),
    //    CallFunc::create([]() {
    //        Director::getInstance()->replaceScene(Interface::create());
    //        }),
    //    nullptr
    //);
    //this->runAction(changeScene);
    this->schedule([=](float dt) {
        Director::getInstance()->replaceScene(TransitionFade::create(1.5f, Interface::create(), Color3B::BLACK));
        }, 1, 0, 7, "replaceSceneKey");
    return true;
}


