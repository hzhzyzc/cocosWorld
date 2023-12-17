#include "openingShowLayer.h"

bool openingShowLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//set animationLayer
	auto animationLayer = LayerColor::create(Color4B::GRAY);
	this->addChild(animationLayer);
	auto screenSize = Director::getInstance()->getVisibleSize();
	animationLayer->setContentSize(screenSize);

	//create audio
	int clock_running = AudioEngine::play2d("cocosWorld/audio/Sound effects/clock_running.mp3", false, 1.0f);

	//create sprite
	auto circleTOP = Sprite::create("cocosWorld/img/icon/circle.png");
	auto circleLeft = Sprite::create("cocosWorld/img/icon/circle.png");
	auto circleRight = Sprite::create("cocosWorld/img/icon/circle.png");
	auto circleLowerLeft = Sprite::create("cocosWorld/img/icon/circle.png");
	auto circleLowerRight = Sprite::create("cocosWorld/img/icon/circle.png");
	auto coco = Sprite::create("cocosWorld/img/character/coco.png");
	animationLayer->addChild(coco);
	coco->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	coco->setScale(0.5f);
	coco->setVisible(false);

	//create action
	auto replaceSprite = CallFuncN::create([=](Node* node) {
		auto sp = dynamic_cast<Sprite*>(node);
		if (sp) {
			sp->setVisible(false);
		}
		coco->setVisible(true);
		AudioEngine::stop(clock_running);
		int clock_ding = AudioEngine::play2d("cocosWorld/audio/Sound effects/boom.mp3", false, 1.0f);
		});
	ActionInterval* moveToCenter = EaseSineIn::create(MoveTo::create(2, Vec2(screenSize.width / 2, screenSize.height / 2)));
	auto moveAndHide = Sequence::create(moveToCenter, Spawn::createWithTwoActions(TintTo::create(4, 223, 215, 80), Blink::create(3.f, 6)), replaceSprite, nullptr);


	setCircle(circleTOP, Vec2(screenSize.width / 2, screenSize.height - circleTOP->getContentSize().height / 4), 0.5f, moveAndHide, animationLayer);
	setCircle(circleLeft, Vec2(0 + circleLeft->getContentSize().width / 4, screenSize.height / 2), 0.5f, moveAndHide, animationLayer);
	setCircle(circleRight, Vec2(screenSize.width - circleRight->getContentSize().width / 4, screenSize.height / 2), 0.5f, moveAndHide, animationLayer);
	setCircle(circleLowerLeft, Vec2(screenSize.width / 3, 0 + circleLowerLeft->getContentSize().height / 4), 0.5f, moveAndHide, animationLayer);
	setCircle(circleLowerRight, Vec2(screenSize.width / 3 * 2, 0 + circleLowerLeft->getContentSize().height / 4), 0.5f, moveAndHide, animationLayer);


	return true;
}

void openingShowLayer::setCircle(Sprite*& circle, Vec2 point, float scale, Sequence*& action, LayerColor*& layer)
{
	circle->setPosition(point);
	circle->setScale(scale);
	layer->addChild(circle);
	circle->runAction(action->clone());
}

void openingShowLayer::removeAfterShow()
{
	this->schedule([=](float dt) {
		this->removeFromParent();
		}, 1.0f, 1, 7, "removeFromParent");
}
