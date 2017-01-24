//
//  GameScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"

static Node *_stageScene;
static int _stage;

Scene* GameScene::createScene(cocos2d::Node *stageScene, int stage)
{
    _stageScene = stageScene;
    _stage = stage;
    
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if(!Layer::init())
        return false;
    
    log("stageScene %d, Stage %d", _stageScene, _stage);
    this->addChild(BackgroundLayer::create());
    return true;
}
