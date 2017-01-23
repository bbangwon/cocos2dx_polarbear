//
//  BackgroundLayer.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 23..
//
//

#include "BackgroundLayer.h"

BackgroundLayer* BackgroundLayer::create(){
    BackgroundLayer *pRet = new BackgroundLayer();
    if(pRet && pRet->init())
        pRet->autorelease();
    else
        CC_SAFE_DELETE(pRet);
    return pRet;
}

bool BackgroundLayer::init(){
    auto bg = Sprite::create("main_bg.png");
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg);
    return true;
}
