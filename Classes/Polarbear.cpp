//
//  Polarbear.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 2. 3..
//
//

#include "Polarbear.h"

Polarbear::Polarbear()
{
    this->setContentSize(Size(43, 70));
    this->setAnchorPoint(Point(0.5f, 0));
    this->setIgnoreAnchorPointForPosition(false);

	_isAnimation = false;
	_isFall = false;
}

Polarbear::~Polarbear()
{
    _wait->release();
	_jumpLeft->release();
	_jumpTop->release();
	_jumpBottom->release();
}

Polarbear * Polarbear::create(Node * listener, SEL_CallFunc selector)
{
	Polarbear *ret = new Polarbear();
	if (ret && ret->init(listener, selector))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Polarbear::init(Node * listener, SEL_CallFunc selector)
{
	_listener = listener;
	_selector = selector;
	return init();
}

Polarbear* Polarbear::create(){
    Polarbear *ret = new Polarbear();
    if(ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Polarbear::init(){
	{
		SpriteFrame *frame[6];

		frame[0] = SpriteFrame::create("w_bear01.png", Rect(0, 0, 43, 70));
		frame[1] = SpriteFrame::create("w_bear02.png", Rect(0, 0, 43, 70));
		frame[2] = SpriteFrame::create("w_bear03.png", Rect(0, 0, 43, 70));
		frame[3] = SpriteFrame::create("w_bear04.png", Rect(0, 0, 43, 70));
		frame[4] = SpriteFrame::create("w_bear02.png", Rect(0, 0, 43, 70));
		frame[5] = SpriteFrame::create("w_bear01.png", Rect(0, 0, 43, 70));

		_polarbear = Sprite::createWithSpriteFrame(frame[0]);
		_polarbear->setPosition(Point(this->getContentSize().width / 2, this->getContentSize().height / 2));
		this->addChild(_polarbear);

		Vector<SpriteFrame*> AniFrames;
		AniFrames.pushBack(frame[0]);
		AniFrames.pushBack(frame[1]);
		AniFrames.pushBack(frame[2]);
		AniFrames.pushBack(frame[3]);
		AniFrames.pushBack(frame[4]);
		AniFrames.pushBack(frame[5]);

		auto animation = Animation::createWithSpriteFrames(AniFrames);
		animation->setDelayPerUnit(0.3f);
		_wait = RepeatForever::create(Animate::create(animation));
		_wait->retain();

		_polarbear->runAction(_wait);
	}
	{
		SpriteFrame *frame[5];

		frame[0] = SpriteFrame::create("w_bear02.png", Rect(0, 0, 43, 70));
		frame[1] = SpriteFrame::create("w_bear05.png", Rect(0, 0, 43, 70));
		frame[2] = SpriteFrame::create("w_bear06.png", Rect(0, 0, 43, 70));
		frame[3] = SpriteFrame::create("w_bear07.png", Rect(0, 0, 43, 70));
		frame[4] = SpriteFrame::create("w_bear05.png", Rect(0, 0, 43, 70));

		Vector<SpriteFrame*> AniFrames;
		AniFrames.pushBack(frame[0]);
		AniFrames.pushBack(frame[1]);
		AniFrames.pushBack(frame[2]);
		AniFrames.pushBack(frame[3]);
		AniFrames.pushBack(frame[4]);

		auto animation = Animation::createWithSpriteFrames(AniFrames);
		animation->setDelayPerUnit(0.2f);
		_jumpLeft = Animate::create(animation);
		_jumpLeft->retain();
	}
	{
		SpriteFrame *frame[3];
		frame[0] = SpriteFrame::create("w_bear11.png", Rect(0, 0, 43, 70));
		frame[1] = SpriteFrame::create("w_bear12.png", Rect(0, 0, 43, 70));
		frame[2] = SpriteFrame::create("w_bear13.png", Rect(0, 0, 43, 70));

		Vector<SpriteFrame*> AniFrames;
		AniFrames.pushBack(frame[0]);
		AniFrames.pushBack(frame[1]);
		AniFrames.pushBack(frame[2]);

		auto animation = Animation::createWithSpriteFrames(AniFrames);
		animation->setDelayPerUnit(0.33f);
		_jumpTop = Animate::create(animation);
		_jumpTop->retain();
	}
	{
		SpriteFrame *frame[3];
		frame[0] = SpriteFrame::create("w_bear08.png", Rect(0, 0, 43, 70));
		frame[1] = SpriteFrame::create("w_bear09.png", Rect(0, 0, 43, 70));
		frame[2] = SpriteFrame::create("w_bear10.png", Rect(0, 0, 43, 70));

		Vector<SpriteFrame*> AniFrames;
		AniFrames.pushBack(frame[0]);
		AniFrames.pushBack(frame[1]);
		AniFrames.pushBack(frame[2]);

		auto animation = Animation::createWithSpriteFrames(AniFrames);
		animation->setDelayPerUnit(0.33f);
		_jumpBottom = Animate::create(animation);
		_jumpBottom->retain();
	}
    return true;
}

void Polarbear::setAnimation(int type)
{
	_polarbear->stopAllActions();

	switch (type)
	{
	case 0:
		_polarbear->runAction(_wait);
		_isAnimation = false;
		break;
	case 1:
		_polarbear->setFlipX(false);
		_polarbear->runAction(Sequence::createWithTwoActions((ActionInterval*)_jumpLeft, CallFunc::create(CC_CALLBACK_0(Polarbear::setWait, this))));
		break;
	case 2:
		_polarbear->setFlipX(true);
		_polarbear->runAction(Sequence::createWithTwoActions((ActionInterval*)_jumpLeft, CallFunc::create(CC_CALLBACK_0(Polarbear::setWait, this))));
		break;
	case 3:
		_polarbear->runAction(Sequence::createWithTwoActions((ActionInterval*)_jumpTop, CallFunc::create(CC_CALLBACK_0(Polarbear::setWait, this))));
		break;
	case 4:
		_polarbear->runAction(Sequence::createWithTwoActions((ActionInterval*)_jumpBottom, CallFunc::create(CC_CALLBACK_0(Polarbear::setWait, this))));
		break;
	}
}

bool Polarbear::setMoveTo(Point moveTo)
{
	if (_isAnimation || _isFall)
		return false;

	_isAnimation = true;

	auto action = JumpTo::create(1, moveTo, 20, 1);
	this->runAction(action);

	Point beforePoint = this->getPosition();

	if (beforePoint.x > moveTo.x)
		setAnimation(1);
	else if (beforePoint.x < moveTo.x)
		setAnimation(2);
	else if (beforePoint.y < moveTo.y)
		setAnimation(3);
	else if (beforePoint.y > moveTo.y)
		setAnimation(4);
	return true;
}

void Polarbear::setWait()
{
	setAnimation(0);

	callCallback();
}

void Polarbear::callCallback()
{
	if (_listener && _selector)
		(_listener->*_selector)();
}

void Polarbear::fallSea(Node * listener, SEL_CallFunc selector)
{
	_isFall = true;
	_listener = listener;
	_selector = selector;

	auto moveBy = MoveBy::create(0.5f, Point(0, -50));
	auto easeMove = EaseSineIn::create(moveBy);

	auto fadeout = FadeOut::create(0.5f);

	auto action = Spawn::createWithTwoActions(easeMove, fadeout);
	auto action2 = Sequence::createWithTwoActions(action, CallFunc::create(CC_CALLBACK_0(Polarbear::callCallback, this)));

	_polarbear->runAction(action2);
}
