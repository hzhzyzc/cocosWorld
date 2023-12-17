#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif


#include "mainScene.h"
#include"Gobang.h"


mainScene::mainScene() :
	isLeftButtonPressed(false),
	isRightButtonPressed(false),
	cocoPos(Vec2(120, -10)),
	_walkCoco(nullptr),
	_standCoco(nullptr),
	_paraNode(nullptr),
	_bg_music(0),
	running(false),
	stopGame(nullptr)
{
}

void mainScene::update(float dt)
{

	Vec2 cocoWorldPosition = _walkCoco->getParent()->convertToWorldSpace(_walkCoco->getPosition());
	if (isLeftButtonPressed) {
		_walkCoco->setScaleX(-0.2);
		_standCoco->setScaleX(-0.2);
		_walkCoco->setVisible(true);
		_standCoco->setVisible(false);
		if (cocoWorldPosition.x < 110) {
			if (_paraNode->getPosition().x > 0) {

			}
			else {
				_paraNode->runAction(MoveBy::create(1 / 60, Vec2(0.02, 0)));
			}
			
		}
		else {
			cocoPos -= Vec2(1.5, 0);
		}
	}
	else if (isRightButtonPressed) {
		_walkCoco->setScaleX(0.2);
		_standCoco->setScaleX(0.2);
		_walkCoco->setVisible(true);
		_standCoco->setVisible(false);
		if (cocoWorldPosition.x > Director::getInstance()->getVisibleSize().width - 110) {
			if (_paraNode->getPosition().x < -20.1) {

			}
			else {
				_paraNode->runAction(MoveBy::create(1 / 60, Vec2(-0.02, 0)));
			}
		}
		else {
			cocoPos += Vec2(1.5, 0);
		}
	}
	else {
		_walkCoco->setVisible(false);
		_standCoco->setVisible(true);
	}
	_walkCoco->setPosition(cocoPos);
	_standCoco->setPosition(cocoPos);
	
	//log("Vec2 coordinates: (%.2f, %.2f)", _paraNode->getPosition().x, _paraNode->getPosition().y);
	//log("%d",screenWidth);
	if (stopGame != nullptr) {
		if (stopGame->getStatus()) {
			AudioEngine::resumeAll();
		}
		else
		{
			AudioEngine::pauseAll();
		}
	}
	for (auto voiceNum:voice) {
		AudioEngine::setVolume(voiceNum,(double)voiceSlider->getPercent()/100);
	}
	
}



bool mainScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto screenSize = Director::getInstance()->getVisibleSize();
	_bg_music = AudioEngine::play2d("cocosWorld/audio/bg sound/bg_mainScene.mp3", true);
	if (_bg_music != AudioEngine::INVALID_AUDIO_ID) {
		voice.push_back(_bg_music);
	}
	
	//create backgroundlayer
	auto background = Layer::create();
	auto moom = Sprite::create("cocosWorld/img/bg/moom.png");
	moom->setScale(0.1f);
	auto moomSize = moom->getBoundingBox().size;
	moom->setPosition(Vec2(screenSize.width - moomSize.width * 1, screenSize.height - moomSize.height * 1));
	background->addChild(moom);
	//this->addChild(background, 1);

	//create citylayer
	auto cityLayer = Layer::create();
	auto city = Sprite::create("cocosWorld/img/bg/city.png");
	city->setScale(1.5f);
	auto citySize = city->getBoundingBox().size;
	city->setPosition(Vec2(citySize.width - screenSize.width, screenSize.height / 2));
	cityLayer->setContentSize(Size(citySize.width, screenSize.height));
	cityLayer->addChild(city);
	//this->addChild(cityLayer, 0);


	//create mainlayer
	auto mainLayer = Layer::create();
	auto road = LayerColor::create(Color4B::GRAY, citySize.width * 5, 58);
	road->setAnchorPoint(Vec2(1, 1));
	mainLayer->addChild(road, 1);
	mainLayer->setContentSize(Size(road->getContentSize().width, screenSize.height));

	//oldMan
	auto oldMan = ui::Button::create("cocosWorld/img/character/oldMan.png");
	oldMan->setScale(0.7f);
	oldMan->setPosition(Vec2(1600, oldMan->getBoundingBox().size.height / 2 - 20));
	oldMan->addClickEventListener([](Ref* sender) {
		Director::getInstance()->pushScene(TransitionFade::create(2.f, Gobang::create()));
		});
	mainLayer->addChild(oldMan, 3);
	auto textOldMan = textBox::create();
	textOldMan->setText("哟哟小伙子，来下一盘五子棋吧(本地双人对战)");
	mainLayer->addChild(textOldMan, 4);
	textOldMan->setScale(0.8);
	textOldMan->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	textOldMan->setPosition(Vec2(oldMan->getPosition().x + 20, oldMan->getBoundingBox().size.height + 20));
	auto changeColor = TintBy::create(1,-100,-100,-100);
	auto colorBack = changeColor->reverse();
	auto shader = Sequence::create(changeColor, colorBack,DelayTime::create(1), nullptr);
	oldMan->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.5), DelayTime::create(1.5f),FadeOut::create(1.5), nullptr)));
	

	//uncle
	auto uncle = Sprite::create("cocosWorld/img/character/uncle.png");
	uncle->setScale(0.3f);
	uncle->setPosition(Vec2(360, uncle->getBoundingBox().size.height / 2));
	mainLayer->addChild(uncle, 3);
	auto textUncle = textBox::create();
	textUncle->setText("是新来的吧，点击下面两侧按钮来控制人物行走，点击闪烁的事物来进行互动，去探索这个世界吧少年！");
	mainLayer->addChild(textUncle, 4);
	textUncle->setScale(0.8);
	textUncle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	textUncle->setPosition(Vec2(uncle->getPosition().x + 20, uncle->getBoundingBox().size.height + 70));

	//lady
	auto lady = Sprite::create("cocosWorld/img/character/lady.png");
	lady->setScale(0.5f);
	lady->setPosition(Vec2(1000, lady->getBoundingBox().size.height / 2 - 30));
	mainLayer->addChild(lady, 3);
	auto textLady = textBox::create();
	textLady->setText("左上角的按钮可以暂停游戏和控制音量哦，快去试试看吧！");
	mainLayer->addChild(textLady, 4);
	textLady->setScale(0.8);
	textLady->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	textLady->setPosition(Vec2(lady->getPosition().x + 20, lady->getBoundingBox().size.height + 40));

	//goodbye
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrame::create("cocosWorld/img/character/goodbye_01.png", Rect(0, 0, 326, 329)));
	frames.pushBack(SpriteFrame::create("cocosWorld/img/character/goodbye_02.png", Rect(0, 0, 326, 329)));
	frames.pushBack(SpriteFrame::create("cocosWorld/img/character/goodbye_03.png", Rect(0, 0, 326, 329)));
	frames.pushBack(SpriteFrame::create("cocosWorld/img/character/goodbye_02.png", Rect(0, 0, 326, 329)));
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);
	Animate* animate = Animate::create(animation);
	auto goodbyecoco = Sprite::create();
	goodbyecoco->initWithSpriteFrame(frames.front());
	goodbyecoco->runAction(RepeatForever::create(animate));
	goodbyecoco->setScale(0.5f);
	goodbyecoco->setPosition(Vec2(2200, goodbyecoco->getBoundingBox().size.height / 2 ));
	mainLayer->addChild(goodbyecoco, 3);
	auto textGoodbyecoco = textBox::create();
	textGoodbyecoco->setText("好朋友再见了，呜呜呜~~~");
	mainLayer->addChild(textGoodbyecoco, 4);
	textGoodbyecoco->setScale(0.8);
	textGoodbyecoco->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	textGoodbyecoco->setPosition(Vec2(goodbyecoco->getPosition().x + 20, goodbyecoco->getBoundingBox().size.height + 40));


	//button
	//leftButton
	auto leftButton = ui::Button::create("cocosWorld/img/icon/move_btn.png");
	auto node = Node::create();
	leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			isLeftButtonPressed = true;
			break;
		case ui::Widget::TouchEventType::ENDED:
			isLeftButtonPressed = false;
			break;
		default:
			break;
		}
		});
	leftButton->setPosition(Vec2(50, 50));
	leftButton->setScale(0.02f);
	leftButton->setOpacity(128);
	this->addChild(leftButton,4);

	//rightButton
	auto rightButton = leftButton->clone();
	rightButton->setRotation(180);
	rightButton->setScale(0.02f);
	rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			isRightButtonPressed = true;
			break;
		case ui::Widget::TouchEventType::ENDED:
			isRightButtonPressed = false;
			break;
		default:
			break;
		}
		});
	rightButton->setPosition(Vec2(screenSize.width - 50 , 50));
	rightButton->setOpacity(128);
	this->addChild(rightButton,4);

	//pauseButton
	auto pauseButton = ui::Button::create("cocosWorld/img/icon/pause.png");
	pauseButton->addClickEventListener([this](Ref* sender) {
		if (stopGame != nullptr) {
			stopGame->showLayer();
		}
		});
	this->addChild(pauseButton, 5);
	pauseButton->setScale(0.1f);
	pauseButton->setPosition(Vec2(pauseButton->getBoundingBox().size.width ,screenSize.height - pauseButton->getBoundingBox().size.height));

	//voiceSlider
	auto voiceButton = ui::Button::create("cocosWorld/img/icon/voice.png");
	voiceSlider = ui::Slider::create();
	voiceSlider->loadBarTexture("cocosWorld/img/icon/Slider_Back.png");
	voiceSlider->loadProgressBarTexture("cocosWorld/img/icon/Slider_PressBar.png");
	voiceSlider->loadSlidBallTextureNormal("cocosWorld/img/icon/Slider_Node.png");
	voiceSlider->setVisible(false);
	voiceSlider->setPercent(30);
	voiceSlider->setScale(0.5f);
	voiceSlider->setAnchorPoint(Vec2(0,0.5));
	voiceButton->setScale(0.12f);
	voiceButton->setPosition(Vec2(voiceButton->getBoundingBox().size.width, screenSize.height - pauseButton->getBoundingBox().size.height - voiceButton->getBoundingBox().size.height * 1.2));
	voiceButton->addClickEventListener([this](Ref* sender) {
		voiceSlider->setVisible(!voiceSlider->isVisible());
		});
	voiceSlider->setPosition(Vec2(voiceButton->getPosition().x + 20 , voiceButton->getPosition().y));
	this->addChild(voiceSlider,5);
	this->addChild(voiceButton, 5);
	

	//create coco
	_walkCoco = walkingCoco::create();
	_walkCoco->setScale(0.2f);
	_walkCoco->setAnchorPoint(Vec2(0.5, 0));
	_walkCoco->setPosition(cocoPos);
	_walkCoco->setVisible(false);
	this->addChild(_walkCoco, 3);

	_standCoco = Sprite::create("cocosWorld/img/character/walk_02.png");
	_standCoco->setScale(0.2f);
	_standCoco->setAnchorPoint(Vec2(0.5, 0));
	_standCoco->setPosition(cocoPos);
	this->addChild(_standCoco, 3);
	schedule([this](float dt) {
		this->update(dt);
		}, "update_key");


	// create paranode
	_paraNode = ParallaxNode::create();

	_paraNode->addChild(background, 1, Vec2(0, 0), Vec2::ZERO);

	_paraNode->addChild(cityLayer, 0, Vec2(20, 0), Vec2::ZERO);

	_paraNode->addChild(mainLayer, 2, Vec2(100, 0), Vec2::ZERO);

	this->addChild(_paraNode);

	
	stopGame = continueLayer::create();
	this->addChild(stopGame, 5);
	return true;
}
