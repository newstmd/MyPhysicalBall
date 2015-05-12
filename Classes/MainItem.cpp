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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    //auto button_1 = rootNode->getChildByName<ui::Button>("Button_1");
    //button_1.addTouchEventListener(cocos2d::ui::SEL_TouchEvent(newGameCallBack) );
    addChild(rootNode);
    
    return true;
}

void newGameCallBack(cocos2d::Ref* pSender)
{
    log("ok");
}