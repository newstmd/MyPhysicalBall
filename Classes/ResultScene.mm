//
//  ResultScene.cpp
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/5/21.
//
//

#include "ResultScene.h"
#include "PlayScene.h"
//#include "CCUMSocialSDK.h"
//#include "UMShareButton.h"
//#include "ChanceAd.h"
#define font_type "YuppySC-Regular"

//USING_NS_UM_SOCIAL;
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
    backButton->setPosition(Vec2(winSize.width/2 - 200,300));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            
            Director::getInstance()->popToRootScene();
            
        }
        
    });
    
    auto newGameButton = cocos2d::ui::Button::create("newGame.png");
    newGameButton->setAnchorPoint(Vec2(0.5,0.5));
    newGameButton->setPosition(Vec2(winSize.width/2,300));
    addChild(newGameButton);
    newGameButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->replaceScene(PlayScene::createScene());
            //Director::getInstance()->popToRootScene();
            
        }
        
    });
    
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
    
//    umeng::MobClickCpp::failLevel(StringUtils::format("游戏结束在第%d关，%d分！",totalrate,totalscore).c_str());
    //清除关卡数据
    UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
    UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, 0);
    UserDefault::getInstance()->flush();
    
    //分享按钮代码
    // 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
    
    //UMShareButton *shareButton = UMShareButton::create("shareNormal.png","shareSelected.png", "你的友盟appkey", share_selector(shareCallback)) ;
    
//    UMShareButton *shareButton = UMShareButton::create("share.png","share.png", "556279e967e58ebe7e004aee", NULL) ;
    
//    CCUMSocialSDK *sdk = shareButton->getSocialSDK();
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
//    sdk->setTargetUrl("http://moodle.bashu.com.cn:12121/savestars.html");
//    sdk->setWeiXinAppInfo("wx79ed32927e487511","706a20ae37a78ec5f604f8ab3656146c");
//    sdk->setQQAppIdAndAppKey("1104667164", "ZK9OLfLqaGPsrRW9");
//    
//    sdk->setLogEnable(false);
    // 显示在友盟分享面板上的平台
//    vector<int>* platforms = new vector<int>();
//    platforms->push_back(WEIXIN);
//    platforms->push_back(WEIXIN_CIRCLE);
//    platforms->push_back(QQ) ;
//    platforms->push_back(QZONE) ;
//    
//    platforms->push_back(SINA);
//    platforms->push_back(TENCENT_WEIBO) ;
//    platforms->push_back(RENREN) ;
//    platforms->push_back(DOUBAN) ;
//
//    platforms->push_back(SMS) ;
//    platforms->push_back(EMAIL) ;
    // 设置友盟分享面板上显示的平台
//    sdk->setPlatforms(platforms);
//    shareButton->setPlatforms(platforms);
    //屏幕截图
    //std::string imageFilePath = "shareImage.jpg";
//    shareButton->setShareImage("shareImage.jpg") ;
    
    // 设置文本分享内容
//    shareButton->setShareContent(StringUtils::format("根本停不下来！我正在玩‘拯救星星’！成功攻克%d关，总分%d。求超越。。。求挑战。。。",totalrate,totalscore).c_str()) ;
    // 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
    //shareButton->setShareImage(imageFilePath.c_str()) ;
    // 设置按钮的位置
//    shareButton->setPosition(Vec2(winSize.width/2 + 200,300));
    //shareButton->setPosition(ccp(winSize.width/2 + 200,300));
    // 然后开发者需要将该按钮添加到游戏场景中
    
//    Menu* pMenu = Menu::create(shareButton, NULL);
//    pMenu->setPosition(Vec2::ZERO);
//    this->addChild(pMenu, 1);
    

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
//    [[CSInterstitial sharedInterstitial] loadInterstitial];
//    [[CSInterstitial sharedInterstitial] showInterstitialWithScale:0.9f];
#else
    //Android代码
#endif

    
    return true;
    
}

//void shareCallback(int platform, int stCode,string& errorMsg)
//{
//    if ( stCode == 100 )
//    {
//        CCLog("#### HelloWorld 开始分享");
//    }
//    else if ( stCode == 200 )
//    {
//        CCLog("#### HelloWorld 分享成功");
//    }
//    else
//    {
//        CCLog("#### HelloWorld 分享出错");
//    }
//    
//    CCLog("platform num is : %d.", platform);
//}
