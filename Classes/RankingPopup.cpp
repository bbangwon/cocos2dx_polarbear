//
//  RankingPopup.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "RankingPopup.h"

RankingPopup * RankingPopup::create()
{
    RankingPopup *ret = new RankingPopup();
    if(ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    
    return ret;
}

bool RankingPopup::init()
{
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    auto fadeBack = LayerColor::create(Color4B(0,0,0,0), winSize.width, winSize.height);
    this->addChild(fadeBack);
    fadeBack->runAction(FadeTo::create(0.5f, 200));
    
    auto back = Sprite::create("pop_rank.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    auto okMenu = MenuItemImage::create("btn_ok.png", "btn_ok_on.png", CC_CALLBACK_1(RankingPopup::onClickOk, this));
    okMenu->setPosition(Point(back->getContentSize().width / 2, 10));
    
    auto menu = Menu::create(okMenu, nullptr);
    menu->setPosition(Point::ZERO);
    back->addChild(menu);
    
    return true;
}

void RankingPopup::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(RankingPopup::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool RankingPopup::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void RankingPopup::onClickOk(cocos2d::Ref *object)
{
    this->removeFromParentAndCleanup(true);
}
