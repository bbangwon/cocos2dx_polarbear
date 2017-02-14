#include "GameoverPopup.h"

GameoverPopup * GameoverPopup::create()
{
	GameoverPopup *ret = new GameoverPopup();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameoverPopup::init()
{
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
	this->addChild(fadeBack);
	fadeBack->runAction(FadeTo::create(0.5f, 200));

	auto gameover = Sprite::create("gameover.png");
	gameover->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(gameover);
	return true;
}

void GameoverPopup::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameoverPopup::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameoverPopup::onTouchBegan(Touch * touch, Event * event)
{
	Director::getInstance()->popScene();
	return true;
}
