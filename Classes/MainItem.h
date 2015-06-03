//
//  MainItem.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/12.
//
//

#ifndef __MyPhysicalBall__MainItem__
#define __MyPhysicalBall__MainItem__


#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class MainItemScene :public cocos2d::Layer
{
private:
    //void newGameCallBack(cocos2d::Ref* pSender);
    
public:
    bool backGroundMusicIsOpen = true;
    bool effectIsOpen = true;
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainItemScene);
};

#endif /* defined(__MyPhysicalBall__MainItem__) */
