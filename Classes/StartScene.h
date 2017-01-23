//
//  StartScene.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 23..
//
//

#ifndef StartScene_h
#define StartScene_h

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
    
    void onClickGame(Ref *object);
    void onClickRank(Ref *object);
};


#endif /* StartScene_h */
