#include "AppDelegate.h"
#include "MainItem.h"
#include "ResultScene.h"
//#include "NCSGameCenter.h"
//#include "UMSocial.h"
//#include "ChanceAd.h"
//#include ""
//#include "ChanceAd.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    
    
    //MOBCLICKCPP_START_WITH_APPKEY("556279e967e58ebe7e004aee");
    //NCSGameCenter *sGameCenter = [NCSGameCenter sharedGameCenter];
    
    
    //MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("556279e967e58ebe7e004aee", "asdfadfa");
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
                glview = GLViewImpl::createWithRect("MyPhysicalBall",cocos2d::Rect(0, 0, 640, 1136));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(640, 1136, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 120);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene =MainItemScene::createScene();

    // run
    director->runWithScene(scene);
//    CGRect frameBanner = CGRectMake(0.0f, 0.0f, 320.0f, 50.0f);
//    CSBannerView *bannerView = [[CSBannerView alloc] initWithFrame:frameBanner];
//    [bannerView loadRequest:[CSADRequest request]];
//    scene->addChild(bannerView);
    //glview->get

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    //umeng::MobClickCpp::applicationDidEnterBackground();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    //umeng::MobClickCpp::applicationWillEnterForeground();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

