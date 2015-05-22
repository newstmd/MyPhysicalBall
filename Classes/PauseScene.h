//
//  PauseScene.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/20.
//
//

#ifndef __MyPhysicalBall__PauseScene__
#define __MyPhysicalBall__PauseScene__

#define Key_TotalRate "TotalRate"
#define Key_TotalScore "TotalScore"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class PauseScene :public cocos2d::Layer{
    
private:
    cocos2d::ui::Button* effectButton;
    cocos2d::ui::Button* musicButton;
    cocos2d::Size winSize;
    void musciCallback(cocos2d::Ref* pSender,ui::TouchEventType type);
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PauseScene);
};


#endif /* defined(__MyPhysicalBall__PauseScene__) */
