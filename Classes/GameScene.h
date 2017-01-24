//
//  GameScene.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(Node *stageScene, int stage);
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_h */
