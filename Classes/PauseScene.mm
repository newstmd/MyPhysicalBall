//
//  PauseScene.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/20.
//
//

#include "PauseScene.h"

using namespace cocostudio::timeline;

Scene* PauseScene::createScene()
{
    
    auto scene = Scene::create();
    auto layer = PauseScene::create();
    scene->addChild(layer);
    return scene;
}

bool PauseScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("pausebackground.png");
    bg->setAnchorPoint(Vec2(0.5,0.5));
    bg->setPosition(winSize/2);
    addChild(bg);
    
    
    auto playButton = cocos2d::ui::Button::create("play.png");
    playButton->setAnchorPoint(Vec2(0.5,0.5));
    playButton->setPosition(Vec2(winSize.width/2 - 225,200));
    addChild(playButton);
    playButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->popScene();
        }
        
    });
    auto fangda = ScaleTo::create(0.5, 1.2);
    auto suoxiao = ScaleTo::create(1,1.0);
    auto ac = Sequence::create(fangda,suoxiao,NULL);
    playButton->runAction(RepeatForever::create(ac));
    
    auto backButton = cocos2d::ui::Button::create("backMain.png");
    backButton->setAnchorPoint(Vec2(0.5,0.5));
    backButton->setPosition(Vec2(winSize.width/2 - 75,200));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            UserDefault::getInstance()->setBoolForKey("isWillContinue", false);
            UserDefault::getInstance()->flush();
            UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
            UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, 0);
            UserDefault::getInstance()->flush();
            Director::getInstance()->popToRootScene();
            //Director::getInstance()->replaceScene(MainItemScene::createScene());
        }
        
    });
    auto effectFile = "effectOpen.png";
    if (CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume() == 0.0f) {
        effectFile = "effectClose.png";
    }
    
    effectButton = cocos2d::ui::Button::create(effectFile);
    effectButton->setAnchorPoint(Vec2(0.5,0.5));
    effectButton->setPosition(Vec2(winSize.width/2 + 75,200));
    addChild(effectButton);
    effectButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
                 //CocosDenshion::SimpleAudioEngine::getInstance()->
            if (CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume() == 1.0f) {
                CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
                effectButton->loadTextures("effectClose.png", "effectClose.png");
            }else{
                CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
                effectButton->loadTextures("effectOpen.png", "effectOpen.png");
            }
            
        }
        
    });
    auto musicFile = "musicOpen.png";
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        musicFile = "musicClose.png";
    }

    musicButton = cocos2d::ui::Button::create(musicFile);
    musicButton->setAnchorPoint(Vec2(0.5,0.5));
    musicButton->setPosition(Vec2(winSize.width/2 + 225,200));
    addChild(musicButton);
    //musicButton->loadTextures("musicClose.png", "musicClose.png");
    musicButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
                //auto temp = CocosDenshion::SimpleAudioEngine::getInstance();
                //log("%f",temp->getEffectsVolume());
                CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
                //musicButton->loadTextureNormal("musicClose.png");
                musicButton->loadTextures("musicClose.png", "musicClose.png");
            }
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
                musicButton->loadTextures("musicOpen.png", "musicOpen.png");
            }

            
        }
    });
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    [[CSInterstitial sharedInterstitial] loadInterstitial];
    [[CSInterstitial sharedInterstitial] showInterstitialWithScale:0.9f];

#else
    //Android代码
#endif

    return true;
}

