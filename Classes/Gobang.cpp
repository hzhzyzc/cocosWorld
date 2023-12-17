#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif

#include "Gobang.h"
#include"mainScene.h"
bool Gobang::init()
{
	if (!Scene::init()) {
		return false;
	}
	allChesses = new std::vector<Node*>;
	AudioEngine::preload("cocosWorld/audio/Sound effects/play_chess.mp3");
	//create listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Gobang::onTouchBegin,this);
	listener->onTouchEnded = CC_CALLBACK_2(Gobang::onTouchEnd, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//create chessBoard
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto backgroundColor = LayerColor::create(Color4B::WHITE);
	backgroundColor->setPosition(origin);
	backgroundColor->setContentSize(visibleSize);
	this->addChild(backgroundColor, 1);
	auto chessBoard = Sprite::create("cocosWorld/img/chess/chessboard.png");
	chessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2));
	this->addChild(chessBoard, 2);

	//create button
	auto btnExit = buttonWithText::create();
	btnExit->setButton("退出游戏", CC_CALLBACK_1(Gobang::exitGame,this));
	btnExit->setScale(0.5f);
	btnExit->setPosition(Vec2(80,80));
	this->addChild(btnExit, 3);
	auto btnRegret = buttonWithText::create();
	btnRegret->setButton("悔棋", CC_CALLBACK_1(Gobang::regretChess, this));
	btnRegret->setScale(0.5f);
	btnRegret->setPosition(Vec2(80, 160));
	//this->addChild(btnRegret, 3);
	auto btnLoss = buttonWithText::create();
	btnLoss->setButton("重新开始", CC_CALLBACK_1(Gobang::reset, this));
	btnLoss->setScale(0.5f);
	btnLoss->setPosition(Vec2(80, 240));
	this->addChild(btnLoss, 3);
	int pieceCount = 15;
	Size pieceSize = Size(20, 20);
	Vec2 boardOriginPos = Vec2((float)origin.x + visibleSize.width / 2 + 80 - pieceCount * pieceSize.width / 2, (float)origin.y + visibleSize.height / 2 - pieceCount * pieceSize.height / 2);
	boardSize = Rect(boardOriginPos.x, boardOriginPos.y, pieceCount * pieceSize.width, pieceCount * pieceSize.height);
	chessMark = Sprite::create("cocosWorld/img/chess/mark.png");
	chessMark->setVisible(false);
	chessMark->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(chessMark, 8);
	return true;
}

void Gobang::exitGame(Ref* sender)
{
	reset(sender);
	Director::getInstance()->popScene();
}

void Gobang::regretChess(Ref* sender)
{

}

void Gobang::reset(Ref* sender)
{	
	GobangController::destoryInstance();
	for (auto chess : *allChesses) {
		if (chess!=nullptr) {
			chess->setVisible(false);
		}
	}
	chessMark->setVisible(false);
	GobangController::getInstance();
}

bool Gobang::onTouchBegin(Touch* touch, Event* event)
{
	Vec2 pos = touch->getLocation();
	if (boardSize.containsPoint(pos)) {
		Vec2 relative = pos - boardSize.origin;
		float val = relative.x / 20;
		int row = int(val);
		if (val > row) {
			row++;
		}
		val = relative.y / 20;
		int cols = int(val);
		if (val > cols) {
			cols++;
		}
		int type = GobangController::getInstance()->getChessBoard()->getType();
		bool result = GobangController::getInstance()->playChess(type, row, cols);
		if (result) {
			createChessPiece(type, row, cols);
			if (GobangController::getInstance()->judgeWin(type, row, cols)) {
				playSuccessAnimation(type);
				reset(nullptr);
			}
		}
	}
	return true;
}

void Gobang::onTouchEnd(Touch* touch, Event* event)
{
}

Node* Gobang::createChessPiece(int type, int x, int y)
{
	int bg_music = AudioEngine::play2d("cocosWorld/audio/Sound effects/play_chess.mp3",false);
	x--;
	y--;
	auto chessNode = Sprite::create(StringUtils::format("cocosWorld/img/chess/%d.png", type));
	chessNode->setPosition(boardSize.origin + Vec2(20 * (x + 0.5), 20 * (y + 0.5)));
	this->addChild(chessNode, 4);
	allChesses->push_back(chessNode);
	if (!chessMark->isVisible()) {
		chessMark->setVisible(true);
	}
	chessMark->setPosition(chessNode->getPosition());
	chessMark->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5), FadeOut::create(0.5), nullptr)));
	return nullptr;
}

void Gobang::playSuccessAnimation(int type)
{
	std::string text = (type == 1) ? std::string("白棋获胜！") : std::string("黑棋获胜！");
	Label* label = Label::createWithSystemFont(text, "楷体", 50);
	label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 80, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(label, 10);
	label->setScale(0.1f);
	label->setColor(Color3B::RED);
	auto beBig = ScaleTo::create(0.2f, 1.2f);
	auto beSmall = ScaleTo::create(0.2f, 1.f);
	auto fadeout = FadeOut::create(0.5f);
	label->runAction(Sequence::create(beBig, DelayTime::create(0.1f), beSmall, DelayTime::create(1.f),fadeout, nullptr));

}
