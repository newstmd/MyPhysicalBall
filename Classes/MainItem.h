//
//  MainItem.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/12.
//
//

#ifndef __MyPhysicalBall__MainItem__
#define __MyPhysicalBall__MainItem__

#define Key_TotalRate "TotalRate"
#define Key_TotalScore "TotalScore"
#define Key_isWillContinue "isWillContinue"
#define font_type "-"

#define EffectReadyGo "readygo.wav"
#define EffectWao "wao.wav"
#define EffectMoFa "mofa.wav"
#define EffectZhuan "zhuan.wav"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "PlayScene.h"
#include "ChanceAd.h"
#include "NCSGameCenter.h"

USING_NS_CC_MATH;
USING_NS_CC;


class MainItemScene :public cocos2d::Layer
{
private:
    //void newGameCallBack(cocos2d::Ref* pSender);
    cocos2d::Size  winSize;
    
public:
    //bool backGroundMusicIsOpen = true;
    //bool effectIsOpen = true;
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainItemScene);
};

#endif /* defined(__MyPhysicalBall__MainItem__) */
