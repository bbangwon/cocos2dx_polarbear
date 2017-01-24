//
//  RankingPopup.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#ifndef RankingPopup_h
#define RankingPopup_h

#include "cocos2d.h"

USING_NS_CC;

class RankingPopup : public Layer
{
public:
    static RankingPopup* create();
    bool init();
    virtual void onEnter();
    bool onTouchBegan(Touch* touch, Event* event);
    
    void onClickOk(Ref *object);
};;


#endif /* RankingPopup_h */
