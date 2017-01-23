#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

typedef struct tagResource
{
    Size size;
    char directory[100];
}Resource;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static Resource smallResource = { Size(480, 320), "iphone"};
static Resource mediumResource = { Size(960, 640), "iphone_retina"};


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("polarbear", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));

        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    
    Size frameSize = glview->getFrameSize();
    std::vector<std::string> resDirOrders;
    if(frameSize.height <= smallResource.size.height){
        resDirOrders.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height / designResolutionSize.height);
    }
    else {
        resDirOrders.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height / designResolutionSize.height);
    }
    
    FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);

    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
