//
//  PauseScene.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/20.
//
//

#include "PauseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PlayScene.h"
#include "MainItem.h"
USING_NS_CC_MATH;
USING_NS_CC;

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
    auto bg = Sprite::create("BackGround.jpg");
    bg->setAnchorPoint(Vec2(0.5,0.5));
    bg->setPosition(winSize/2);
    addChild(bg);
    
    
    auto pauseButton = cocos2d::ui::Button::create("play.png");
    pauseButton->setAnchorPoint(Vec2(0.5,0.5));
    pauseButton->setPosition(Vec2(winSize.width/2 - 200,100));
    addChild(pauseButton);
    pauseButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->popScene();
        }
        
    });
    
    auto backButton = cocos2d::ui::Button::create("backMain.png");
    backButton->setAnchorPoint(Vec2(0.5,0.5));
    backButton->setPosition(Vec2(winSize.width/2 - 110,100));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
            UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, 0);
            UserDefault::getInstance()->flush();
            Director::getInstance()->popToRootScene();
            //Director::getInstance()->replaceScene(MainItemScene::createScene());
        }
        
    });


    return true;
}