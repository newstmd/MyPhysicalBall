//
//  ResultScene.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/21.
//
//

#include "ResultScene.h"


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
    backButton->setPosition(Vec2(winSize.width/2 - 110,100));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            
            Director::getInstance()->popToRootScene();
            
        }
        
    });
    
    
    auto scoreLabel = Label::create();
    scoreLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    scoreLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    scoreLabel->setTextColor(Color4B::WHITE);
    scoreLabel->setSystemFontSize(60);
    scoreLabel->setSystemFontName("mnse.ttf");
    scoreLabel->setString(StringUtils::format("通过%d关\n得分：%d",totalrate,totalscore));
    scoreLabel->setPosition(winSize/2);
    
    addChild(scoreLabel,999);
    
    
    
    //清除关卡数据
    UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
    UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, 0);
    UserDefault::getInstance()->flush();
    
    return true;
    
}

void ResultScene::onEnter(){
    Layer::onEnter();
    
    log("显示结果界面");
}