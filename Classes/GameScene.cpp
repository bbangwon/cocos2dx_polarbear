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

int STAGE1[4][5] = {{0,0,0,3,1}, {0,3,0,0,4}, {4,0,0,0,0}, {2,0,3,0,4}};
int STAGE2[4][5] = {{0,3,0,0,1}, {3,0,4,0,0}, {0,0,0,4,0}, {2,0,0,0,3}};
int STAGE3[4][5] = {{0,0,4,0,1}, {4,3,0,3,4}, {0,0,0,0,0}, {2,0,3,0,0}};


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
    
    if(type == 0 || type == 1 || type == 3){
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
        
        if(type == 1){
            
        }
        else if(type == 3){
            auto penguin = getPenguinSprite();
            penguin->setAnchorPoint(Point(0.5f, 0));
            penguin->setPosition(Point(ice->getContentSize().width / 2, 25));
            ice->addChild(penguin);
        }
    }
    else if(type == 2)
    {
        auto ice = Sprite::create("goal.png");
        ice->setPosition(Point(tile->getContentSize().width / 2, tile->getContentSize().height / 2));
        tile->addChild(ice);
        
        auto flag = getGoalFlagSprite();
        flag->setAnchorPoint(Point(0.5f, 0));
        flag->setPosition(Point(50, 35));
        ice->addChild(flag);
    }
    else if(type == 4)
    {
        std::string iceImg;
        
        switch (row) {
            case 0:
                iceImg = "break1_default.png";
                break;
            case 1:
                iceImg = "break2_default.png";
                break;
            case 2:
                iceImg = "break3_default.png";
                break;
            case 3:
                iceImg = "break4_default.png";
                break;
        }
        
        auto breakIce = Sprite::create(iceImg.c_str());
        breakIce->setPosition(Point(tile->getContentSize().width / 2, tile->getContentSize().height / 2));
        tile->addChild(breakIce);
    }
    
    int tag = col + (5*row) + 1;
    log("mapArr[%d][%d], tag = %d", row, col, tag);
    tile->setTag(tag);
    return tile;
}

void GameScene::setMenuLayer(){
    
}

Sprite* GameScene::getPenguinSprite(){
    auto texture = Director::getInstance()->getTextureCache()->addImage("penguin.png");
    float textureWidth = texture->getContentSize().width / 3;
    float textureHeight = texture->getContentSize().height;
    
    SpriteFrame *frame[3];
    
    frame[0] = SpriteFrame::createWithTexture(texture, Rect(0,0,textureWidth, textureHeight));
    frame[1] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 1,0, textureWidth, textureHeight));
    frame[2] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 2,0, textureWidth, textureHeight));
    
    auto penguin = Sprite::createWithSpriteFrame(frame[0]);
    
    Vector<SpriteFrame*> AniFrames;
    AniFrames.pushBack(frame[0]);
    AniFrames.pushBack(frame[1]);
    AniFrames.pushBack(frame[2]);
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.3f);
    auto animate = Animate::create(animation);
    
    penguin->runAction(RepeatForever::create(animate));
    
    auto cage = Sprite::create("cage.png");
    cage->setPosition(Point(penguin->getContentSize().width / 2, 20));
    penguin->addChild(cage);
    
    auto help = Sprite::create("help.png");
    help->setAnchorPoint(Point(0.5f, 0));
    help->setPosition(Point(17, 40));
    penguin->addChild(help);
    
    auto action1 = Spawn::createWithTwoActions(ScaleTo::create(0, 0.5f), FadeTo::create(0, 0));
    auto action2 = Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1), FadeTo::create(0.4f, 100));
    auto action = Sequence::createWithTwoActions(action1, action2);
    help->runAction(RepeatForever::create(action));
    
    return penguin;
}

Sprite* GameScene::getGoalFlagSprite()
{
    SpriteFrame *frame[3];
    
    frame[0] = SpriteFrame::create("flag_1.png", Rect(0,0,39,53));
    frame[1] = SpriteFrame::create("flag_2.png", Rect(0,0,39,53));
    frame[2] = SpriteFrame::create("flag_3.png", Rect(0,0,39,53));
    
    auto flag = Sprite::createWithSpriteFrame(frame[0]);
    
    Vector<SpriteFrame*> AniFrames;
    AniFrames.pushBack(frame[0]);
    AniFrames.pushBack(frame[1]);
    AniFrames.pushBack(frame[2]);
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.1f);
    auto animate = Animate::create(animation);
    
    flag->runAction(RepeatForever::create(animate));
    
    return flag;
}
