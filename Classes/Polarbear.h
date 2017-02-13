//
//  Polarbear.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 2. 3..
//
//

#ifndef Polarbear_h
#define Polarbear_h

#include "cocos2d.h"

USING_NS_CC;

class Polarbear : public Layer
{
public:
    Polarbear();
    ~Polarbear();
    
    static Polarbear *create();
    
    bool init();
    
    Sprite *_polarbear;
    Action *_wait;
    Action *_jumpLeft;
    Action *_jumpTop;
    Action *_jumpBottom;
    
    void setAnimation(int type);
	bool setMoveTo(Point moveTo);

	void setWait();
	bool _isAnimation;
};


#endif /* Polarbear_h */
