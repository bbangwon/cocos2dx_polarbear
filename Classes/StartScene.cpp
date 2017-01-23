//
//  StartScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 23..
//
//

#include "StartScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init()
{
    if(!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    this->addChild(BackgroundLayer::create());
    
    auto title = Sprite::create("title_1.png");
    title->setPosition(Point(winSize.width / 2, 230));
    this->addChild(title);
    
    auto action1 = Sequence::createWithTwoActions(RotateTo::create(0.05f, -1), RotateTo::create(0.05f, 1));
    title->runAction(RepeatForever::create(action1));
    
    auto deco = Sprite::create("intro_bear1.png");
    deco->setAnchorPoint(Point(0,1));
    deco->setPosition(Point(winSize.width, 0));
    this->addChild(deco);
    
    auto easeAction = EaseInOut::create(MoveBy::create(0.5f, Point(-deco->getContentSize().width, deco->getContentSize().height)), 1);
    
    deco->runAction(easeAction);
    
    auto gameMenu = MenuItemImage::create("btn_play.png", "btn_play_on.png", CC_CALLBACK_1(StartScene::onClickGame, this));
    gameMenu->setPosition(Point(winSize.width / 2, 130));
    auto rankMenu = MenuItemImage::create("btn_ranking.png", "btn_ranking_on.png", CC_CALLBACK_1(StartScene::onClickRank, this));
    rankMenu->setPosition(Point(winSize.width / 2, 70));
    
    auto menu = Menu::create(gameMenu, rankMenu, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void StartScene::onClickGame(cocos2d::Ref *object)
{
    log("onClickGame");
}

void StartScene::onClickRank(cocos2d::Ref *object)
{
    log("onClickRank");
}
