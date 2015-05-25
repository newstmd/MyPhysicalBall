//
//  MainItem.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/12.
//
//

#include "MainItem.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PlayScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//iOS代码
#define EffectReadyGo "readygo.wav"
#define EffectWao "wao.wav"
#define EffectMoFa "mofa.wav"
#define EffectZhuan "zhuan.wav"
#else
//Android代码
#define EffectReadyGo ""
#define EffectWao ""
#define EffectMoFa ""
#define EffectZhuan ""
#endif

//#include "PGStoreKitManager.h"
USING_NS_CC_MATH;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainItemScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainItemScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainItemScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //auto button_1 = rootNode->getChildByName<ui::Button>("Button_1");
    //button_1.addTouchEventListener(cocos2d::ui::SEL_TouchEvent(newGameCallBack) );
    //addChild(rootNode);
    //添加背景
    
    //id auth = PGStoreKitManager::getInstance();
    //    [auth authenticateLocalPlayer];
    
    
    auto backGround = Sprite::create("BackGround.jpg");
    backGround->setAnchorPoint(Vec2(0.5,0.5));
    backGround->setPosition(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height /2);
    addChild(backGround, -1);
    
    auto guanghuan  = Sprite::create("guanghuan.png");
    guanghuan->setAnchorPoint(Vec2(0.5,0.5));
    guanghuan->setPosition(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height * 0.66);
    addChild(guanghuan);
    
    auto xuanzhuanaction = RotateBy::create(3, 10);
    auto rep = RepeatForever::create(xuanzhuanaction);
    guanghuan->runAction(rep);
    
    
    auto logo  = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2(0.5,0.5));
    logo->setPosition(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height * 0.66);
    addChild(logo);
    
    //添加开始按钮
    auto beginButton = cocos2d::ui::Button::create("BeginGameButton.png");
    beginButton->setAnchorPoint(Vec2(0.5,0.5));
    beginButton->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height * 0.3));
    addChild(beginButton);
    beginButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            
            int guanka = UserDefault::getInstance()->getIntegerForKey("TotalGuanKa", 0);
            if (guanka == 0) {
                UserDefault::getInstance()->setIntegerForKey("Tatalscore", 0);
                UserDefault::getInstance()->flush();
                //log("这是新游戏");
            }else{
                //log("第%d关！",guanka);
            }
            auto fade = TransitionCrossFade::create(0.5, PlayScene::createScene());
            //auto scene = PlayScene::createScene();
            //auto fade = TransitionMoveInR::initWithDuration(0.2, scene);
            Director::getInstance()->pushScene(fade);
            //Director::getInstance()->pushScene(fade);
        }

    });
    auto fangda = ScaleTo::create(0.5, 1.2);
    auto suoxiao = ScaleTo::create(1,1.0);
    auto ac = Sequence::create(fangda,suoxiao,NULL);
    beginButton->runAction(RepeatForever::create(ac));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("nekomimi.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectMoFa);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectZhuan);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectReadyGo);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectWao);
    //CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("nekomimi.mp3",true);
    
    
    
    
    return true;
}

void newGameCallBack(cocos2d::Ref* pSender)
{
    //log("ok");
}