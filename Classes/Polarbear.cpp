//
//  Polarbear.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 2. 3..
//
//

#include "Polarbear.h"

Polarbear::Polarbear()
{
    this->setContentSize(Size(43, 70));
    this->setAnchorPoint(Point(0.5f, 0));
    this->setIgnoreAnchorPointForPosition(false);
}

Polarbear::~Polarbear()
{
    _wait->release();
}

Polarbear* Polarbear::create(){
    Polarbear *ret = new Polarbear();
    if(ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Polarbear::init(){
    SpriteFrame *frame[6];
    
    frame[0] = SpriteFrame::create("w_bear01.png", Rect(0,0,43,70));
    frame[1] = SpriteFrame::create("w_bear02.png", Rect(0,0,43,70));
    frame[2] = SpriteFrame::create("w_bear03.png", Rect(0,0,43,70));
    frame[3] = SpriteFrame::create("w_bear04.png", Rect(0,0,43,70));
    frame[4] = SpriteFrame::create("w_bear02.png", Rect(0,0,43,70));
    frame[5] = SpriteFrame::create("w_bear01.png", Rect(0,0,43,70));
    
    _polarbear = Sprite::createWithSpriteFrame(frame[0]);
    _polarbear->setPosition(Point(this->getContentSize().width / 2, this->getContentSize().height / 2));
    this->addChild(_polarbear);
    
    Vector<SpriteFrame*> AniFrames;
    AniFrames.pushBack(frame[0]);
    AniFrames.pushBack(frame[1]);
    AniFrames.pushBack(frame[2]);
    AniFrames.pushBack(frame[3]);
    AniFrames.pushBack(frame[4]);
    AniFrames.pushBack(frame[5]);
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.3f);
    _wait = RepeatForever::create(Animate::create(animation));
    _wait->retain();
    
    _polarbear->runAction(_wait);
    return true;
}

void Polarbear::setAnimation(int type)
{
    
}
