#include "PausePopup.h"
#include "GameScene.h"

PausePopup * PausePopup::create()
{
	PausePopup *ret = new PausePopup();
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

bool PausePopup::init()
{
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
	this->addChild(fadeBack);
	fadeBack->runAction(FadeTo::create(0.5f, 200));

	auto pauseBg = Sprite::create("pop_up.png");
	pauseBg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(pauseBg);

	auto backMenu = MenuItemImage::create("btn_back2.png", "btn_back2_on.png", CC_CALLBACK_1(PausePopup::onClickBack, this));
	backMenu->setPosition(Point(pauseBg->getContentSize().width / 2, pauseBg->getContentSize().height / 2 + 50));
	auto restartMenu = MenuItemImage::create("btn_restart.png", "btn_restart_on.png", CC_CALLBACK_1(PausePopup::onClickRestart, this));
	restartMenu->setPosition(Point(pauseBg->getContentSize().width / 2, pauseBg->getContentSize().height / 2));
	auto goStageMenu = MenuItemImage::create("btn_stage.png", "btn_stage_on.png", CC_CALLBACK_1(PausePopup::onClickGoStage, this));
	goStageMenu->setPosition(Point(pauseBg->getContentSize().width / 2, pauseBg->getContentSize().height / 2 - 50));

	auto menu = Menu::create(backMenu, restartMenu, goStageMenu, nullptr);
	menu->setPosition(Point::ZERO);
	pauseBg->addChild(menu);

	return true;
}

void PausePopup::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PausePopup::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PausePopup::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void PausePopup::onClickBack(Ref * object)
{
	log("onClickBack");

	GameScene *gameScene = (GameScene*)this->getParent();
	gameScene->resumeTimer();

	this->removeFromParentAndCleanup(true);
}

void PausePopup::onClickRestart(Ref * object)
{
	log("onClickRestart");
	((GameScene *)this->getParent())->restartGame();
	onClickBack(nullptr);
}

void PausePopup::onClickGoStage(Ref * object)
{
	log("onClickGoStage");

	Director::getInstance()->popScene();
}
