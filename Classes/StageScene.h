//
//  StageScene.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#ifndef StageScene_h
#define StageScene_h

#include "cocos2d.h"

class StageScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(StageScene);
};


#endif /* StageScene_h */
