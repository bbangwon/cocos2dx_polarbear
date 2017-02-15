#include "ResultPopup.h"
#include "SimpleAudioEngine.h"

ResultPopup * ResultPopup::create(int score, int penguin)
{
	ResultPopup *ret = new ResultPopup();
	if (ret && ret->init(score, penguin))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool ResultPopup::init(int score, int penguin)
{
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
	this->addChild(fadeBack);
	fadeBack->runAction(FadeTo::create(0.5f, 200));

	auto back = Sprite::create("pop_up.png");
	back->setTag(1);
	back->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(back);

	auto pen1 = Sprite::create("score_penguin2.png");
	pen1->setTag(0);
	pen1->setPosition(Point(back->getContentSize().width / 2 - 50, 150));
	back->addChild(pen1);

	auto pen2 = Sprite::create("score_penguin2.png");
	pen2->setTag(1);
	pen2->setPosition(Point(back->getContentSize().width / 2, 160));
	back->addChild(pen2);

	auto pen3 = Sprite::create("score_penguin2.png");
	pen3->setTag(2);
	pen3->setPosition(Point(back->getContentSize().width / 2 + 50, 150));
	back->addChild(pen3);

	auto scoreBg = Sprite::create("box_score.png");
	scoreBg->setPosition(Point(back->getContentSize().width / 2, 90));
	back->addChild(scoreBg);

	auto okMenu = MenuItemImage::create("btn_ok.png", "btn_ok_on.png", CC_CALLBACK_1(ResultPopup::onClickOK, this));
	okMenu->setPosition(Point(back->getContentSize().width / 2, 33));

	auto menu = Menu::create(okMenu, nullptr);
	menu->setPosition(Point::ZERO);
	back->addChild(menu);

	_labelScore = Label::createWithSystemFont("0", "Arial", 40);
	_labelScore->setPosition(Point(scoreBg->getContentSize().width / 2, 25));
	_labelScore->setColor(Color3B(25, 163, 242));
	scoreBg->addChild(_labelScore);

	_totalScore = score;
	_tempScore = 0;
	_tickScore = score / 60;
	_updateCount = 0;
	_penguinCount = penguin;

	this->schedule(CC_SCHEDULE_SELECTOR(ResultPopup::updateScore), 3.0f / 60, 59, 0.05f);

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/score.wav");

	return true;
}

void ResultPopup::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ResultPopup::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool ResultPopup::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void ResultPopup::onClickOK(Ref * object)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->popScene();
}

void ResultPopup::updateScore(float time)
{
	_updateCount++;
	_tempScore = _tempScore + _tickScore;
	char scoreChar[50];

	if (_updateCount >= 60) {
		sprintf(scoreChar, "%d", _totalScore);
		unschedule(CC_SCHEDULE_SELECTOR(ResultPopup::updateScore));

		auto scaleTo = ScaleTo::create(0.1f, 1.2);
		_labelScore->runAction(scaleTo);
		setPenguinCount();
	}
	else
		sprintf(scoreChar, "%d", _tempScore);

	_labelScore->setString(scoreChar);
}

void ResultPopup::setPenguinCount()
{
	auto back = (Sprite*)this->getChildByTag(1);

	for (int i = 0; i < _penguinCount; i++)
	{
		auto penguin = (Sprite*)back->getChildByTag(i);
		auto getPenguin = Sprite::create("score_penguin1.png");
		getPenguin->setPosition(penguin->getPosition());
		back->addChild(getPenguin);

		getPenguin->setScale(0);
		auto delay = DelayTime::create(i * 0.5f);
		auto ScaleTo = ScaleTo::create(0.1f, 1);
		auto action = Sequence::create(delay, ScaleTo, CallFuncN::create(CC_CALLBACK_1(ResultPopup::setParticle, this)), nullptr);
		getPenguin->runAction(action);
		getPenguin->setTag(i);
	}
}

void ResultPopup::setParticle(Node * node)
{
	if (node->getTag() == 0)
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/firework1.mp3");
	else if (node->getTag() == 1)
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/firework2.mp3");
	else if (node->getTag() == 2)
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/firework3.mp3");


	auto particle = ParticleExplosion::createWithTotalParticles(30);
	particle->setPosition(Point(node->getContentSize().width / 2, node->getContentSize().height / 2));
	particle->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	particle->setSpeed(100);
	particle->setStartColor(Color4F(1, 1, 1, 0.80f));
	particle->setAutoRemoveOnFinish(true);
	node->addChild(particle);
}
