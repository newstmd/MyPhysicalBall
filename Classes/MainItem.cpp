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
    auto backGround = Sprite::create("BackGround.jpg");
    backGround->setAnchorPoint(Vec2(0.5,0.5));
    backGround->setPosition(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height /2);
    addChild(backGround, -1);
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
                log("这是新游戏");
            }else{
                log("第%d关！",guanka);
            }
            
            Director::getInstance()->replaceScene(PlayScene::createScene());
        }

    });
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("nekomimi.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("mofa.wav");
    //CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("nekomimi.mp3",true);
    
    
    
    return true;
}

void newGameCallBack(cocos2d::Ref* pSender)
{
    //log("ok");
}