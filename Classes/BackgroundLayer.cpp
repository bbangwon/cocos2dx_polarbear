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
    
    auto background1 = Sprite::create("bg_ice1.png");
    background1->setAnchorPoint(Point(0,0));
    
    auto background2 = Sprite::create("bg_ice2.png");
    background2->setAnchorPoint(Point(0,0));
    
    auto background3 = Sprite::create("cloud_bg.png");
    background3->setAnchorPoint(Point(0,0));
    
    auto parallaxNode = ParallaxNode::create();
    
    parallaxNode->addChild(background1, 1, Point(0.5f, 0.0f), Point(0, 225));
    parallaxNode->addChild(background2, 1, Point(0.75f, 0.0f), Point(0,218));
    parallaxNode->addChild(background3, 1, Point(1.0f, 0.0f), Point(0, 230));
    
    this->addChild(parallaxNode);
    
    auto go = MoveBy::create(60, Point(-1024 + 320, 0));
    auto go2 = MoveBy::create(60, Point(1024-320, 0));
    
    auto action1 = Sequence::create(go, go2, nullptr);
    auto action2 = RepeatForever::create(action1);
    
    parallaxNode->runAction(action2);
    
    callWhale();
    callWave();
    
    return true;
}

void BackgroundLayer::callWhale()
{
    auto texture = Director::getInstance()->getTextureCache()->addImage("whale.png");
    int frameCnt = 6;
    
    float textureWidth = texture->getContentSize().width / frameCnt;
    float textureHeight = texture->getContentSize().height;
    
    SpriteFrame *frame[6];
    
    frame[0] = SpriteFrame::createWithTexture(texture, Rect(0,0, textureWidth, textureHeight));
    frame[1] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 1, 0, textureWidth, textureHeight));
    frame[2] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 2, 0, textureWidth, textureHeight));
    frame[3] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 3, 0, textureWidth, textureHeight));
    frame[4] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 4, 0, textureWidth, textureHeight));
    frame[5] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 5, 0, textureWidth, textureHeight));
    
    Vector<SpriteFrame*> AniFrames;
    AniFrames.pushBack(frame[0]);
    AniFrames.pushBack(frame[1]);
    AniFrames.pushBack(frame[2]);
    AniFrames.pushBack(frame[3]);
    AniFrames.pushBack(frame[4]);
    AniFrames.pushBack(frame[5]);
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.4f);
    
    auto animate = Animate::create(animation);
    auto firstFrame = Sprite::createWithSpriteFrame(frame[0]);
    
    Point randPoint = Point(480 * CCRANDOM_0_1(), 200 * CCRANDOM_0_1());
    firstFrame->setPosition(randPoint);
    
    this->addChild(firstFrame);
    firstFrame->runAction(RepeatForever::create(Sequence::createWithTwoActions(animate, CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::removeMe, this)))));
    
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(5 * CCRANDOM_0_1()), CallFunc::create(CC_CALLBACK_0(BackgroundLayer::callWhale, this))));
}

void BackgroundLayer::callWave()
{
    auto texture = Director::getInstance()->getTextureCache()->addImage("wave.png");
    int frameCnt = 6;
    
    float textureWidth = texture->getContentSize().width / frameCnt;
    float textureHeight = texture->getContentSize().height;
    
    SpriteFrame *frame[6];
    Vector<SpriteFrame*> AniFrames;
    
    for(int i=0;i<frameCnt;i++){
        frame[i] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * i,0, textureWidth, textureHeight));
        AniFrames.pushBack(frame[i]);
    }
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.4f);
    
    auto animate = Animate::create(animation);
    auto firstFrame = Sprite::createWithSpriteFrame(frame[0]);
    
    Point randPoint = Point(480 * CCRANDOM_0_1(), 200 * CCRANDOM_0_1());
    firstFrame->setPosition(randPoint);
    
    this->addChild(firstFrame);
    
    firstFrame->runAction(RepeatForever::create(Sequence::createWithTwoActions(animate, CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::removeMe, this)))));
    
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(3 * CCRANDOM_0_1()), CallFunc::create(CC_CALLBACK_0(BackgroundLayer::callWave, this))));
}

void BackgroundLayer::removeMe(Node *node){
    node->removeFromParentAndCleanup(true);
}
