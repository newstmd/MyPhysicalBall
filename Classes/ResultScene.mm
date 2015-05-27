//
//  ResultScene.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/21.
//
//

#include "ResultScene.h"
#include "PlayScene.h"
#define font_type "YuppySC-Regular"

Scene* ResultScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool ResultScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    int totalscore = UserDefault::getInstance()->getIntegerForKey(Key_TotalScore);
    int totalrate = UserDefault::getInstance()->getIntegerForKey(Key_TotalRate);
    winSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("BackGround.jpg");
    bg->setAnchorPoint(Vec2(0.5,0.5));
    bg->setPosition(winSize/2);
    addChild(bg);
    
    auto backButton = cocos2d::ui::Button::create("backMain.png");
    backButton->setAnchorPoint(Vec2(0.5,0.5));
    backButton->setPosition(Vec2(winSize.width/2 - 150,300));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            
            Director::getInstance()->popToRootScene();
            
        }
        
    });
    
    auto newGameButton = cocos2d::ui::Button::create("newGame.png");
    newGameButton->setAnchorPoint(Vec2(0.5,0.5));
    newGameButton->setPosition(Vec2(winSize.width/2 +150,300));
    addChild(newGameButton);
    newGameButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->replaceScene(PlayScene::createScene());
            //Director::getInstance()->popToRootScene();
            
        }
        
    });
    
//    auto shareButton = cocos2d::ui::Button::create("share.png");
//    shareButton->setAnchorPoint(Vec2(0.5,0.5));
//    shareButton->setPosition(Vec2(winSize.width/2 + 75,300));
//    addChild(shareButton);
//    shareButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
//        if (type == ui::Widget::TouchEventType::ENDED) {
//            
//            //Director::getInstance()->popToRootScene();
//            
//        }
//        
//    });
    
//    auto gameCenterButton = cocos2d::ui::Button::create("gameCenter.png");
//    gameCenterButton->setAnchorPoint(Vec2(0.5,0.5));
//    gameCenterButton->setPosition(Vec2(winSize.width/2 + 225,300));
//    addChild(gameCenterButton);
//    gameCenterButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
//        if (type == ui::Widget::TouchEventType::ENDED) {
//            
//            //Director::getInstance()->popToRootScene();
//            
//        }
//        
//    });
    
    auto guanghuan  = Sprite::create("guanghuan.png");
    guanghuan->setAnchorPoint(Vec2(0.5,0.5));
    guanghuan->setPosition(winSize/2);
    addChild(guanghuan);
    auto xuanzhuanaction = RotateBy::create(3, 10);
    auto rep = RepeatForever::create(xuanzhuanaction);
    guanghuan->runAction(rep);
    
    auto logo  = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2(0.5,0.5));
    logo->setScale(0.7);
    logo->setPosition(winSize.width /2 - 80,900);
    addChild(logo);

    auto scoreLabel = Label::create();
    scoreLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    scoreLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    scoreLabel->setTextColor(Color4B::WHITE);
    scoreLabel->setSystemFontSize(100);
    scoreLabel->setString(StringUtils::format("%d",totalscore));
    scoreLabel->setSystemFontName(font_type);
    scoreLabel->setPosition(winSize/2);
    addChild(scoreLabel,999);
    
    auto rateLabel = Label::create();
    rateLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    rateLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    rateLabel->setTextColor(Color4B::WHITE);
    rateLabel->setSystemFontSize(40);
    rateLabel->setString(StringUtils::format("游戏结束 - 第%d关",totalrate));
    rateLabel->setSystemFontName(font_type);
    rateLabel->setPosition(winSize.width /2 -80,700);
    addChild(rateLabel,999);
    
    umeng::MobClickCpp::failLevel(StringUtils::format("游戏结束在第%d关，%d分！",totalrate,totalscore).c_str());
    //清除关卡数据
    UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
    UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, 0);
    UserDefault::getInstance()->flush();
    

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    [[CSInterstitial sharedInterstitial] loadInterstitial];
    [[CSInterstitial sharedInterstitial] showInterstitialWithScale:0.9f];
#else
    //Android代码
#endif

    
    return true;
    
}

