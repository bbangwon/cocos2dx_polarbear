//
//  StageScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "StageScene.h"
#include "BackgroundLayer.h"

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
    return true;
}
