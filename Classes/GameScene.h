//
//  GameScene.h
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "Polarbear.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(Node *stageScene, int stage);
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    LayerColor *_mapLayer;
    LayerColor *_menuLayer;
    
    void setMapLayer(int mapArr[4][5]);
    Menu* getMaptile(int row, int col, int type);
    void setMenuLayer();
    
    Sprite *getPenguinSprite();
    Sprite *getGoalFlagSprite();
    
    Polarbear *_polarbear;

	void onClickTile(Ref *object);

	int _polarbearCurrentTag;
	bool checkTileMove(int tileTag, int bearTag);

	Sprite *_beforeIceTile;

	void polarbearAnimationFinish();
	int getTileType(int col, int row);
	void runIceBreakAnimation(Sprite *ice);
	void fallSeaCallBack();
	void onClickPause(Ref *object);
	void restartGame();
};

#endif /* GameScene_h */
