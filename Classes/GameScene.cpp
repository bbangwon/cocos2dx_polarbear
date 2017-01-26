//
//  GameScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"

static Node *_stageScene;
static int _stage;

int STAGE1[4][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
int STAGE2[4][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
int STAGE3[4][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};


Scene* GameScene::createScene(cocos2d::Node *stageScene, int stage)
{
    _stageScene = stageScene;
    _stage = stage;
    
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if(!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    this->addChild(BackgroundLayer::create(), 0);
    
    _mapLayer = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
    this->addChild(_mapLayer, 1);
    
    _menuLayer = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
    this->addChild(_menuLayer, 2);
    
    switch (_stage) {
        case 1:
            setMapLayer(STAGE1);
            break;
        case 2:
            setMapLayer(STAGE2);
            break;
        case 3:
            setMapLayer(STAGE3);
            break;
    }
    
    setMenuLayer();
    return true;
}

void GameScene::setMapLayer(int mapArr[4][5])
{
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            auto tile = getMaptile(i, j, mapArr[i][j]);
            _mapLayer->addChild(tile, 4-i);
        }
    }
}

LayerColor* GameScene::getMaptile(int row, int col, int type){
    auto tile = LayerColor::create(Color4B(255, 0, 0, 0), 96, 55);
    tile->setPosition(Point(col * tile->getContentSize().width, row * tile->getContentSize().height));
    
    if(type == 0){
        std::string iceImg;
        switch (row) {
            case 0:
                iceImg = "ice_1.png";
                break;
            case 1:
                iceImg = "ice_2.png";
                break;
            case 2:
                iceImg = "ice_3.png";
                break;
            case 3:
                iceImg = "ice_4.png";
                break;
        }
        auto ice = Sprite::create(iceImg.c_str());
        ice->setPosition(Point(tile->getContentSize().width / 2, tile->getContentSize().height / 2));
        tile->addChild(ice);
    }
    
    int tag = col + (5*row) + 1;
    log("mapArr[%d][%d], tag = %d", row, col, tag);
    tile->setTag(tag);
    return tile;
}

void GameScene::setMenuLayer(){
    
}
