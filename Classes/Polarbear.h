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

	static Polarbear *create(Node *listener, SEL_CallFunc selector);
	bool init(Node *listener, SEL_CallFunc selector);
    
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

	Node *_listener;
	SEL_CallFunc _selector;

	void callCallback();
	void fallSea(Node *listener, SEL_CallFunc selector);
	bool _isFall;

	Action *_penguinWait;
	Action *_penguinJumpLeft;
	Action *_penguinJumpTop;
	Action *_penguinJumpBottom;

	int _penguinCnt;
	void setPenguin();

	bool _isFlip;
	void setFlipNode(bool isFlip);
	void setPenguinAnimation(int type);
};


#endif /* Polarbear_h */
