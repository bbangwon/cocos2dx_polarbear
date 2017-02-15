#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ResultPopup :public Layer
{
public:
	static ResultPopup* create(int score, int penguin);
	bool init(int score, int penguin);

	virtual void onEnter();
	bool onTouchBegan(Touch* touch, Event *event);
	void onClickOK(Ref* object);

	int _totalScore;
	int _tempScore;
	int _tickScore;
	int _updateCount;

	Label *_labelScore;
	void updateScore(float time);

	int _penguinCount;
	void setPenguinCount();

	void setParticle(Node *node);
};

