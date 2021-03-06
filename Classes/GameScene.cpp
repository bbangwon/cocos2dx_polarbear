//
//  GameScene.cpp
//  polarbear
//
//  Created by YOUNG IL CHUNG on 2017. 1. 24..
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameoverPopup.h"
#include "PausePopup.h"
#include "ResultPopup.h"
#include "SimpleAudioEngine.h"

#define RESCUE 5000
#define TILE 1000
#define TIME 30.00f
#define GOAL_BONUS 10000


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

Menu* GameScene::getMaptile(int row, int col, int type){
    auto tile = LayerColor::create(Color4B(255, 0, 0, 0), 96, 55);
	tile->setTag(1);

	auto tileMenu = MenuItemSprite::create(tile, nullptr, CC_CALLBACK_1(GameScene::onClickTile, this));
	tileMenu->setPosition(Point(col * tile->getContentSize().width, row * tile->getContentSize().height));
	tileMenu->setAnchorPoint(Point(0, 0));

	tileMenu->setTag(1);

	auto menu = Menu::create(tileMenu, nullptr);
	menu->setPosition(Point::ZERO);    
    
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
		ice->setTag(1);
        tile->addChild(ice);
        
        if(type == 1){
            _polarbear = Polarbear::create(this, CC_CALLFUNC_SELECTOR(GameScene::polarbearAnimationFinish));
            _polarbear->setAnchorPoint(Point(0.5f, 0));
            _polarbear->setPosition(Point(tileMenu->getPositionX() + tileMenu->getContentSize().width / 2, tileMenu->getPositionY() + tileMenu->getContentSize().height / 2));
            _mapLayer->addChild(_polarbear, 5);

			_beforeIceTile = ice;
			_beforeIceTile->setTag(1);
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
		ice->setTag(1);
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
		breakIce->setTag(1);
        tile->addChild(breakIce);
    }
    
    int tag = col + (5*row) + 1;
    log("mapArr[%d][%d], tag = %d", row, col, tag);
    menu->setTag(tag);

	if (type == 1)
		_polarbearCurrentTag = tag;

    return menu;
}

void GameScene::setMenuLayer(){
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto pause = MenuItemImage::create("btn_pause.png", "btn_pause_on.png", CC_CALLBACK_1(GameScene::onClickPause, this));
	pause->setPosition(Point(winSize.width - 20, winSize.height - 20));

	auto menu = Menu::create(pause, nullptr);
	menu->setPosition(Point::ZERO);
	_menuLayer->addChild(menu);

	_score = 0;
	_rescueCount = 0;

	auto _scoreIcon = Sprite::create("score.png");
	_scoreIcon->setPosition(Point(30, winSize.height - 20));
	_menuLayer->addChild(_scoreIcon);

	_labelScore = Label::createWithSystemFont("0", "Arial", 20);
	_labelScore->setAnchorPoint(Point(0, 0.5f));
	_labelScore->setPosition(Point(60, winSize.height - 20));
	_menuLayer->addChild(_labelScore);

	auto penguinIcon = Sprite::create("icon_penguin.png");
	penguinIcon->setPosition(Point(140, winSize.height - 20));
	_menuLayer->addChild(penguinIcon);

	_labelPenguin = Label::createWithSystemFont("0", "Arial", 20);
	_labelPenguin->setPosition(Point(160, winSize.height - 20));
	_labelPenguin->setColor(Color3B(247, 136, 211));
	_menuLayer->addChild(_labelPenguin);

	auto timerBack = Sprite::create("time_bar.png");
	timerBack->setPosition(Point(80, winSize.height - 40));
	_menuLayer->addChild(timerBack);

	auto progressSprite = Sprite::create("time_gage.png");
	_progressBar = ProgressTimer::create(progressSprite);
	_progressBar->setPosition(Point(timerBack->getContentSize().width / 2 + 8, timerBack->getContentSize().height / 2));
	_progressBar->setType(ProgressTimer::Type::BAR);
	_progressBar->setBarChangeRate(Point(1, 0));
	_progressBar->setMidpoint(Point(0, 0.5f));
	_progressBar->setPercentage(100);
	timerBack->addChild(_progressBar);

	_labelCountdown = Label::createWithSystemFont("30.00", "Arial Bold", 10);
	_labelCountdown->setColor(Color3B::BLACK);
	_labelCountdown->setAnchorPoint(Point(0.5f, 0.5f));
	_labelCountdown->setPosition(Point(timerBack->getContentSize().width / 2 + 8, timerBack->getContentSize().height / 2 - 1));
	timerBack->addChild(_labelCountdown);

	setTimer();
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
	penguin->setTag(1);
    
    Vector<SpriteFrame*> AniFrames;
    AniFrames.pushBack(frame[0]);
    AniFrames.pushBack(frame[1]);
    AniFrames.pushBack(frame[2]);
    
    auto animation = Animation::createWithSpriteFrames(AniFrames);
    animation->setDelayPerUnit(0.3f);
    auto animate = Animate::create(animation);
    
    penguin->runAction(RepeatForever::create(animate));
    
    auto cage = Sprite::create("cage.png");
	cage->setTag(1);
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

void GameScene::onClickTile(Ref * object)
{
	auto tile = (MenuItem *)object;
	log("tag = %d", tile->getParent()->getTag());	
	
	bool isMove = checkTileMove(tile->getParent()->getTag(), _polarbearCurrentTag);
	if (isMove == false || tile->getParent()->getTag() < 0)
		return;

	bool result = _polarbear->setMoveTo(Point(tile->getPositionX() + tile->getContentSize().width / 2, tile->getPositionY() + tile->getContentSize().height / 2));
	if (result) {
		_beforeIceTile->runAction(FadeOut::create(1));
		_beforeIceTile->getParent()->getParent()->getParent()->setTag(-1);
		_beforeIceTile = (Sprite*)tile->getChildByTag(1)->getChildByTag(1);

		_polarbearCurrentTag = tile->getParent()->getTag();
	}
}

bool GameScene::checkTileMove(int tileTag, int bearTag)
{
	log("tag = %d", tileTag);

	int col = (tileTag - 1) % 5;
	int row = (tileTag - 1 - col) / 5;

	log("col = %d, row = %d", col, row);

	log("polarbear_current_tag = %d", bearTag);

	int bearCol = (bearTag - 1) % 5;
	int bearRow = (bearTag - 1 - bearCol) / 5;

	log("bearCol = %d, bearRow = %d", bearCol, bearRow);
	if (tileTag == bearTag)
	{
		log("move false");
		return false;
	}
	else if ((col <= bearCol + 1 && col >= bearCol - 1) && (row <= bearRow + 1 && row >= bearRow - 1)) {
		if (!(col == bearCol - 1 && row == bearRow + 1) && !(col == bearCol - 1 && row == bearRow - 1) &&
			!(col == bearCol + 1 && row == bearRow - 1) && !(col == bearCol + 1 && row == bearRow + 1)) {
			log("move true");
			return true;
		}
		else
		{
			log("move false");
			return false;
		}
	}
	else {
		log("move false");
		return false;
	}
}

void GameScene::polarbearAnimationFinish()
{
	log("polarbearAnimationFinish");

	int col = (_polarbearCurrentTag - 1) % 5;
	int row = (_polarbearCurrentTag - 1 - col) / 5;

	log("col = %d, row = %d", col, row);

	int type = getTileType(col, row);
	log("type = %d", type);

	switch (type)
	{
	case 0:
		_score = _score + TILE;
		break;
	case 2:
		_score = _score + TILE;
		stopTimer();
		_score = _score + ((_countdownTimer / TIME) * GOAL_BONUS);
		{
			auto UserDefault = UserDefault::getInstance();
			if (_stage == 1)
				UserDefault->setBoolForKey("lock2", false);
			else if (_stage == 2)
				UserDefault->setBoolForKey("lock3", false);

			UserDefault->flush();
		}
		this->addChild(ResultPopup::create(_score, _rescueCount), 99);
		break;
	case 3:
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cage.wav");
		_score = _score + RESCUE;
		_rescueCount = _rescueCount + 1;

		auto ice = (Sprite*)_mapLayer->getChildByTag(_polarbearCurrentTag)->getChildByTag(1)->getChildByTag(1)->getChildByTag(1);
		auto penguin = (Sprite *)ice->getChildByTag(1);
		auto cage = (Sprite *)penguin->getChildByTag(1);

		int multiplication = 1;
		float random = CCRANDOM_MINUS1_1();
		if (random < 0)
			multiplication = -1;

		auto move = MoveBy::create(0.5f, Point(200 * multiplication, 100));
		auto scale = ScaleTo::create(0.5f, 5);
		auto rotate = RotateBy::create(0.5f, 360);
		auto fade = FadeOut::create(0.5f);

		auto action = Spawn::create(move, scale, rotate, fade, nullptr);
		cage->runAction(Sequence::createWithTwoActions(action, CallFuncN::create(CC_CALLBACK_1(GameScene::removeMe, this))));		
		penguin->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), CallFuncN::create(CC_CALLBACK_1(GameScene::removeMe, this))));

		_polarbear->setPenguin();
	}
		break;
	case 4:
		stopTimer();
		runIceBreakAnimation((Sprite *)_mapLayer->getChildByTag(_polarbearCurrentTag)->getChildByTag(1)->getChildByTag(1)->getChildByTag(1));
		_polarbear->fallSea(this, CC_CALLFUNC_SELECTOR(GameScene::fallSeaCallBack));
		break;
	}

	char c_score[50];
	sprintf(c_score, "%d", _score);
	_labelScore->setString(c_score);

	char c_rescue[20];
	sprintf(c_rescue, "%d", _rescueCount);
	_labelPenguin->setString(c_rescue);

}

int GameScene::getTileType(int col, int row)
{
	int type;

	switch (_stage)
	{
	case 1:
		type = STAGE1[row][col];
		break;
	case 2:
		type = STAGE2[row][col];
		break;
	case 3:
		type = STAGE3[row][col];
		break;
	}
	return type;
}

void GameScene::runIceBreakAnimation(Sprite * ice)
{
	std::string iceImg;

	int row = (ice->getParent()->getParent()->getParent()->getTag() - 1) / 5;
	switch (row)
	{
	case 0:
		iceImg = "break1.png";
		break;
	case 1:
		iceImg = "break2.png";
		break;
	case 2:
		iceImg = "break3.png";
		break;
	case 3:
		iceImg = "break4.png";
		break;
	}

	auto texture = Director::getInstance()->getTextureCache()->addImage(iceImg.c_str());
	float textureWidth = texture->getContentSize().width / 5;
	float textureHeight = texture->getContentSize().height;

	SpriteFrame *frame[5];
	frame[0] = SpriteFrame::createWithTexture(texture, Rect(0, 0, textureWidth, textureHeight));
	frame[1] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 1, 0, textureWidth, textureHeight));
	frame[2] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 2, 0, textureWidth, textureHeight));
	frame[3] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 3, 0, textureWidth, textureHeight));
	frame[4] = SpriteFrame::createWithTexture(texture, Rect(textureWidth * 4, 0, textureWidth, textureHeight));

	Vector<SpriteFrame*> AniFrames;
	AniFrames.pushBack(frame[0]);
	AniFrames.pushBack(frame[1]);
	AniFrames.pushBack(frame[2]);
	AniFrames.pushBack(frame[3]);
	AniFrames.pushBack(frame[4]);

	auto animation = Animation::createWithSpriteFrames(AniFrames);
	animation->setDelayPerUnit(0.1f);
	auto animate = Animate::create(animation);

	ice->runAction(animate);

}

void GameScene::fallSeaCallBack()
{
	log("fallSeaCallBack");
	this->addChild(GameoverPopup::create(), 99);
}

void GameScene::onClickPause(Ref * object)
{
	log("onClickPause");
	pauseTimer();
	this->addChild(PausePopup::create(), 99);
}

void GameScene::restartGame()
{
	log("restartGame");
	resumeTimer();

	_mapLayer->removeAllChildrenWithCleanup(true);
	_menuLayer->removeAllChildrenWithCleanup(true);

	switch (_stage)
	{
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
}

void GameScene::removeMe(Node * node)
{
	node->removeFromParentAndCleanup(true);
}

void GameScene::setTimer()
{
	_progressBar->runAction(ProgressFromTo::create(TIME, 100, 0));
	_countdownTimer = TIME;
	schedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
}

void GameScene::updateTimer(float time)
{
	_countdownTimer -= time;
	if (_countdownTimer < 0) {
		_countdownTimer = 0;
		unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
		_labelCountdown->setString("0.0");

		this->addChild(GameoverPopup::create(), 99);
	}

	log("_countDownTimer : %f", _countdownTimer);
	char str[10] = { 0 };
	sprintf(str, "%2.2f", _countdownTimer);
	_labelCountdown->setString(str);
}

void GameScene::stopTimer()
{
	unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
	_progressBar->stopAllActions();
}

void GameScene::resumeTimer()
{
	this->resume();
	_progressBar->resume();
}

void GameScene::pauseTimer()
{
	this->pause();
	_progressBar->pause();
}

