//
//  BackgroundLayer.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 23..
//
//

#ifndef BackgroundLayer_h
#define BackgroundLayer_h

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
    static BackgroundLayer *create();
    bool init();
};

#endif /* BackgroundLayer_h */
