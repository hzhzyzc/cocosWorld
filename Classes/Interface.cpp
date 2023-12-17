#include "Interface.h"
#include"mainScene.h"
bool Interface::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto screenSize = Director::getInstance()->getVisibleSize();




	//background Layer
	auto bgLayer = Layer::create();
	auto bgpic = Sprite::create("cocosWorld/img/bg/beginGame.jpg");
	bgLayer->addChild(bgpic);
	int bg_music = AudioEngine::play2d("cocosWorld/audio/bg sound/bg_interface.mp3",true);
	this->addChild(bgLayer, 1);

	//cocoLayer
	auto cocoLayer = Layer::create();
	auto lw_coco = walkingCoco::create();
	auto rw_coco = walkingCoco::create();
	rw_coco->setFlippedX(true);
	lw_coco->setScale(0.1f);
	rw_coco->setScale(0.1f);
	auto cocoSize = lw_coco->getBoundingBox().size;
	lw_coco->setPosition(Vec2(cocoSize.width, screenSize.height - cocoSize.height));
	rw_coco->setPosition(Vec2(screenSize.width-cocoSize.width, screenSize.height - cocoSize.height));
	cocoLayer->addChild(lw_coco);
	cocoLayer->addChild(rw_coco);
	this->addChild(cocoLayer,3);

	//main Layer
	auto mainLayer = Layer::create();
	auto textSp = Sprite::create("cocosWorld/img/icon/title.png");
	textSp->setScale(0.3f);
	textSp->setPosition(Vec2(screenSize.width/2, screenSize.height-textSp->getBoundingBox().size.height/2));
	mainLayer->addChild(textSp);
	this->addChild(mainLayer, 2);
	auto startBtn = ui::Button::create("cocosWorld/img/icon/beginGame_normal.png", "cocosWorld/img/icon/beginGame_pressed.png", "cocosWorld/img/icon/beginGame_disabled.png");
	auto exitBtn = ui::Button::create("cocosWorld/img/icon/exit_normal.png", "cocosWorld/img/icon/exit_pressed.png", "cocosWorld/img/icon/exit_disabled.png");
	startBtn->setScale(0.1f);
	startBtn->setPosition(Vec2(screenSize.width / 2, startBtn->getBoundingBox().size.height * 2));
	exitBtn->setScale(0.1f);
	exitBtn->setPosition(Vec2(screenSize.width / 2, exitBtn->getBoundingBox().size.height ));
	AudioEngine::preload("cocosWorld/audio/Sound effects/btn_clicked.mp3");
	startBtn->addClickEventListener([bg_music](Ref* sender){
		int startBtn_event = AudioEngine::play2d("cocosWorld/audio/Sound effects/btn_clicked.mp3");
		AudioEngine::stop(bg_music);
		AudioEngine::setFinishCallback(startBtn_event, [=](int audioId, const std::string& filePath) {
			
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, mainScene::create()));
			});
		
		});
	exitBtn->addClickEventListener([](Ref* sender) {
		int exitBtn_event = AudioEngine::play2d("cocosWorld/audio/Sound effects/btn_clicked.mp3");

		AudioEngine::setFinishCallback(exitBtn_event, [=](int audioId, const std::string& filePath) {

			Director::getInstance()->end();
			});
		});
	mainLayer->addChild(startBtn);
	mainLayer->addChild(exitBtn);
	auto emitter = ParticleRain::create();
	mainLayer->addChild(emitter, 10);
	return true;
}
