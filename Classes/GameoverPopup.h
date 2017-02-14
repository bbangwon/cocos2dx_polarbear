#include "cocos2d.h"

USING_NS_CC;

class GameoverPopup : public Layer
{
public:
	static GameoverPopup *create();
	bool init();

	virtual void onEnter();
	bool onTouchBegan(Touch* touch, Event* event);
};