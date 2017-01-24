//
//  StageScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "StageScene.h"
#include "BackgroundLayer.h"
#include "GameScene.h"

USING_NS_CC;

Scene* StageScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StageScene::create();
    scene->addChild(layer);
    return scene;
}

bool StageScene::init()
{
    if(!Layer::init())
        return false;
    
    this->addChild(BackgroundLayer::create());
    
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    auto deco = Sprite::create("stage_bear.png");
    deco->setAnchorPoint(Point(1,0));
    deco->setPosition(Point(winSize.width + deco->getContentSize().width, - deco->getContentSize().height));
    this->addChild(deco);
    
    auto easeAction = EaseInOut::create(MoveBy::create(0.5f, Point(-deco->getContentSize().width, deco->getContentSize().height)), 1);
    deco->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), easeAction));
    
    auto back = MenuItemImage::create("btn_back.png", "btn_back_on.png", CC_CALLBACK_1(StageScene::onClickBack, this));
    back->setPosition(Point(30, winSize.height - 20));
    
    auto menu = Menu::create(back, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    _stageLayer = nullptr;
    setStage();
    
    return true;
}

void StageScene::onClickBack(cocos2d::Ref *object)
{
    Director::getInstance()->popScene();
}

void StageScene::setStage()
{
    if(_stageLayer){
        _stageLayer->removeAllChildrenWithCleanup(true);
        _stageLayer = nullptr;
    }
    
    _stageLayer = LayerColor::create(Color4B(0,0,0,0), 480, 150);
    _stageLayer->setPosition(Point(0, 100));
    this->addChild(_stageLayer);
    
    auto stage1Text = Sprite::create("text_stage1.png");
    stage1Text->setPosition(Point(100, 130));
    _stageLayer->addChild(stage1Text);
    
    auto stage2Text = Sprite::create("text_stage2.png");
    stage2Text->setPosition(Point(240, 130));
    _stageLayer->addChild(stage2Text);
    
    auto stage3Text = Sprite::create("text_stage3.png");
    stage3Text->setPosition(Point(380, 130));
    _stageLayer->addChild(stage3Text);
    
    auto item1 = MenuItemImage::create("box_stage.png", "box_stage_on.png", "box_stage_lock.png", CC_CALLBACK_1(StageScene::onClickStage, this));
    item1->setPosition(Point(100, 55));
    item1->setTag(1);
    
    auto item2 = MenuItemImage::create("box_stage.png", "box_stage_on.png", "box_stage_lock.png", CC_CALLBACK_1(StageScene::onClickStage, this));
    item2->setPosition(Point(240, 55));
    item2->setTag(2);
    
    auto item3 = MenuItemImage::create("box_stage.png", "box_stage_on.png", "box_stage_lock.png", CC_CALLBACK_1(StageScene::onClickStage, this));
    item3->setPosition(Point(380, 55));
    item3->setTag(3);
    
    auto menu = Menu::create(item1, item2, item3, nullptr);
    menu->setPosition(Point::ZERO);
    _stageLayer->addChild(menu);
    
    UserDefault *UserDefault = UserDefault::getInstance();
    bool lock2 = UserDefault->getBoolForKey("lock2", true);
    bool lock3 = UserDefault->getBoolForKey("lock3", true);
    
    if(lock2)
        item2->setEnabled(false);
    
    if(lock3)
        item3->setEnabled(false);
    
}

void StageScene::onClickStage(cocos2d::Ref *object)
{
    auto clickItem = (MenuItemImage *)object;
    log("Click Tag = %d", clickItem->getTag());
    
    auto scene = TransitionCrossFade::create(0.5f, GameScene::createScene(this, clickItem->getTag()));
    Director::getInstance()->pushScene(scene);
    
}
