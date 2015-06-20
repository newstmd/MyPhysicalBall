//
//  ResultScene.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/21.
//
//

#ifndef __MyPhysicalBall__ResultScene__
#define __MyPhysicalBall__ResultScene__


#include "PlayScene.h"
#include "CCUMSocialSDK.h"
#include "NCSGameCenter.h"
#import <UIKit/UIKit.h>
#include "MainItem.h"
#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "MobClickCpp.h"
#include "ChanceAd.h"
#import "BaiduMobAdView.h"
#include "UMShareButton.h"
USING_NS_CC;
USING_NS_UM_SOCIAL;
class ResultScene :public cocos2d::Layer{
    
private:
    cocos2d::Size winSize;
    //void shareCallback(int platform, int stCode,const string& errorMsg);
public:
    umeng::social::UMShareButton *shareButton;
    //string imageName;
    
    static cocos2d::Scene* createScene();
    void afterCaptured(bool succeed, const std::string& outputFile);
    void captureIt();
    virtual bool init();
    //virtual void onEnter();
    CREATE_FUNC(ResultScene);
};


#endif /* defined(__MyPhysicalBall__ResultScene__) */
