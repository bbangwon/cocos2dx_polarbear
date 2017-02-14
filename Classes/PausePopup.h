#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PausePopup: public Layer
{
public:
	static PausePopup* create();
	bool init();

	virtual void onEnter();
	bool onTouchBegan(Touch* touch, Event* event);

	void onClickBack(Ref* object);
	void onClickRestart(Ref* object);
	void onClickGoStage(Ref* object);

};

