//
//  ResultScene.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/21.
//
//

#ifndef __MyPhysicalBall__ResultScene__
#define __MyPhysicalBall__ResultScene__

#define Key_TotalRate "TotalRate"
#define Key_TotalScore "TotalScore"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
//#include "MobClickCpp.h"
//#include "ChanceAd.h"
USING_NS_CC;
class ResultScene :public cocos2d::Layer{
    
private:
    cocos2d::Size winSize;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    //virtual void onEnter();
    CREATE_FUNC(ResultScene);
};


#endif /* defined(__MyPhysicalBall__ResultScene__) */
