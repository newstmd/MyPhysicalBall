#include "PlayScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainItem.h"
#include "SimpleAudioEngine.h"
#include "PauseScene.h"
#include "ResultScene.h"


#define font_type "-"
//#define font_type "YuppySC-Regular"
#define EffectReadyGo "readygo.wav"
#define EffectWao "wao.wav"
#define EffectMoFa "mofa.wav"
#define EffectZhuan "zhuan.wav"

USING_NS_CC_MATH;
USING_NS_CC;

using namespace cocostudio::timeline;


Scene* PlayScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-1000));
    scene->getPhysicsWorld()->setAutoStep(false);
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    initShuJu();
    
    auto backGround1 = Sprite::create("PlayGround.jpg");
    backGround1->setAnchorPoint(Vec2(0.5,0.5));
    backGround1->setPosition(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height /2);
    addChild(backGround1, -1);
    

    //暂停的button
    auto pauseButton = cocos2d::ui::Button::create("pause.png");
    //pauseButton->setScale(0.8);
    pauseButton->setAnchorPoint(Vec2(0.5,0.5));
    pauseButton->setPosition(Vec2(MiddleX + 230,1080));
    addChild(pauseButton);
    pauseButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto fade = TransitionMoveInT::create(0.5, PauseScene::createScene());
            Director::getInstance()->pushScene(fade);
        }
        
    });

    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(PlayScene::touchIt,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    messageLabel = Label::create();
    //messageLabel = Label::createWithTTF("", const std::string &fontFilePath, float fontSize)
    messageLabel->setTextColor(Color4B::WHITE);
    messageLabel->setSystemFontSize(60);
    messageLabel->setString("浮动信息");
    messageLabel->setSystemFontName(font_type);
    messageLabel->setVisible(false);
    messageLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    messageLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    addChild(messageLabel,99);
    //messageLabel->autorelease();


    
    scoreLabel = Label::create();
    //scoreLabel = Label::createWithTTF("", "STHeitiSC-Light", 40);
    scoreLabel->setTextColor(Color4B::WHITE);
    scoreLabel->setSystemFontSize(40);
    //log("%s",scoreLabel->getSystemFontName().c_str());
    //scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setSystemFontName(font_type);
    
    scoreLabel->setString("得分：0");
    scoreLabel->setPosition(winSize.width/2, 1020);
    addChild(scoreLabel,999);
    //scoreLabel->autorelease();

    mubiaoLabel = Label::create();
        mubiaoLabel->setTextColor(Color4B::WHITE);
    mubiaoLabel->setSystemFontSize(40);
    mubiaoLabel->setString("目标：");
    mubiaoLabel->setSystemFontName(font_type);
    mubiaoLabel->setPosition(winSize.width/2 , 1080);
    addChild(mubiaoLabel,999);
    //mubiaoLabel->autorelease();

    rateLabel = Label::create();
    
    //log("%s",rateLabel->getFontName().c_str());
    //rateLabel->setFontName(;)
    rateLabel->setTextColor(Color4B::WHITE);
    rateLabel->setSystemFontSize(40);
    rateLabel->setString("关卡数");
    rateLabel->setSystemFontName(font_type);
    rateLabel->setPosition(winSize.width/2 - 220, 1080);
    addChild(rateLabel,999);
    //rateLabel->autorelease();
    
    countLabel = Label::create();
    countLabel->setTextColor(Color4B::WHITE);
    countLabel->setSystemFontSize(30);
    countLabel->setSystemFontName(font_type);
    countLabel->setString("");
    countLabel->setPosition(winSize.width/2, 960);
    addChild(countLabel,999);

    //schedule(schedule_selector(PlayScene::jiankongBall), 1.0f/10, kRepeatForever, 0);
    addEdges();

    scheduleUpdate();
    
    beginNewGame();

    
    return true;
}

void PlayScene::update(float delta)
{
    for (int i = 0; i < 3; ++i)
        
    {
        
        //Director::getInstance()->getRunningScene()->getPhysicsWorld()->step(1/180.0f);
        //log("ok");
        getScene()->getPhysicsWorld()->step(1/180.0f);
        
    }
}

void PlayScene::jiankongBall(float dt)
{
    auto fanwei =cocos2d::Rect(MiddleX-310, 100, 620, 1036);
    for (int i = 0; i<ballList.size(); i++) {
        if (!fanwei.containsPoint(ballList.at(i)->getPosition())) {
//            removeChild(ballList.at(i));
//            ballList.erase(i);
            //auto shape = ballList.at(i)->getPhysicsBody()->getFirstShape()->set
            deleteBall(ballList.at(i));
            addBall(MiddleX, 1000);
            //log("修复！");
        }
    }
}

//void PlayScene::onEnter(){
//    Layer::onEnter();
//    
//
//}

void PlayScene::initShuJu()
{
    imageNames.push_back("ball1.png");
    imageNames.push_back("ball2.png");
    imageNames.push_back("ball3.png");
    imageNames.push_back("ball4.png");
    imageNames.push_back("ball5.png");
    
    
    winSize = Director::getInstance()->getVisibleSize();
    MiddleX = winSize.width / 2;
    MiddleY = winSize.height / 2;
    guanka[1] = 1000;
    guanka[2] = 2500;
    guanka[3] = 4500;
    for (int i = 4; i<200; i++) {
        guanka[i] = guanka[i-1] + 2000 + 50*(i-3);
    }
    return;
}


void PlayScene::beginNewGame(){
    countLabel->setString("");
    if (UserDefault::getInstance()->getIntegerForKey(Key_TotalRate) == 0) {
        UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 1);
    }
    defen = 0;
    scoreLabel->setTextColor(Color4B::WHITE);

    refreshScore();
    if (ballList.size()>0) {
        for (int i = 0; i<ballList.size(); i++) {
            removeChild(ballList.at(i));
        }
    }
    
    ballList.clear();
    selectedBalls.clear();
    for (int i = 0; i<5; i++) {
        colorCount[i] = 0;
    }
    
    messageLabel->setPosition(Vec2(winSize.width+100,winSize.height/2));
    char c_message[50];
    int tempguan = UserDefault::getInstance()->getIntegerForKey(Key_TotalRate);
    sprintf(c_message, "第%d关\n目标：%d",tempguan,guanka[tempguan]);
    
    messageLabel->setPosition(winSize.width+200, MiddleY);
    messageLabel->setString(c_message);
    auto jin = MoveTo::create(0.3, winSize/2);
    auto ting = DelayTime::create(1);
    auto chu = MoveTo::create(0.3, Vec2(-200,winSize.height/2));
    auto callFunc = CallFunc::create(CC_CALLBACK_0(PlayScene::AddBalls, this));
    auto hecheng =Sequence::create(jin,ting,chu,callFunc, NULL);
    messageLabel->setVisible(true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectReadyGo);
    messageLabel->runAction(hecheng);
    
    umeng::MobClickCpp::startLevel(StringUtils::format("第%d关",tempguan).c_str());
    
    //AddBalls();
    }


bool PlayScene::touchIt(Touch* touch,Event* event){
    selectedBalls.clear();
    auto clickLocation = touch->getLocation();
    
    for (int i = 0; i<ballList.size(); i++)
    {
        auto tar = ballList.at(i);
        if (PlayScene::getjuli(clickLocation, tar->getPosition()) < tar->getContentSize().width/2)
        {
            chuliBall(tar);
            defen += selectedBalls.size() * selectedBalls.size() * 5;
            countLabel->setString(StringUtils::format("%zd个星星：%ld",selectedBalls.size(),selectedBalls.size() * selectedBalls.size() * 5));
            for (int i = 0; i<selectedBalls.size(); i++)
            {
                //auto callfunc = CallFunc::create(CC_CALLBACK_1(PlayScene::deleteBall,this,selectedBalls.at(i)));
                deleteBall(selectedBalls.at(i));
               
            }
            refreshScore();
            //清理单球
            bool isWillEnd = true;
            for (int i = 0; i<5; i++) {
                if (colorCount[i] > 1) {
                    isWillEnd = false;
                }
            }
            if (isWillEnd) {
                selectedBalls.clear();
                for (int i = 0; i<ballList.size(); i++) {
                    selectedBalls.pushBack(ballList.at(i));
                }
                //动态消除剩余球球
                for (int i = 0; i<selectedBalls.size(); i++) {
                    //deleteBall(ballList);
                    deleteBall(selectedBalls.at(i));
                    defen = defen +5;
                    refreshScore();
                }
                
                refreshRate();
                break;
            }
            
            
            if ((ballList.size()<1) ) {
                //log("结束游戏！");
                refreshRate();
                //return false;
                //        UserDefault
            }
            break;
            
        }
    }

    
    
    return false;
}

void PlayScene::refreshRate()
{
    int guankashu = UserDefault::getInstance()->getIntegerForKey(Key_TotalRate);
    int zongfen =UserDefault::getInstance()->getIntegerForKey(Key_TotalScore);
    
    if ((zongfen+ defen) < guanka[guankashu]) {
        //游戏失败，清零！
        //UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, 0);
        
        UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, zongfen+defen);
        UserDefault::getInstance()->flush();
        auto huadong = TransitionMoveInR::create(0.5, ResultScene::createScene());
        Director::getInstance()->pushScene(huadong);
    }else{
        //成功，进入下一关
        UserDefault::getInstance()->setIntegerForKey(Key_TotalRate, guankashu +1);
        
        UserDefault::getInstance()->setIntegerForKey(Key_TotalScore, zongfen + defen);
        UserDefault::getInstance()->flush();
        messageLabel->setPosition(winSize.width+200, MiddleY);
        
        messageLabel->setString(StringUtils::format("过关\n%d",UserDefault::getInstance()->getIntegerForKey(Key_TotalScore)));
        auto jin = MoveTo::create(0.3, winSize/2);
        auto ting = DelayTime::create(1.5);
        auto chu = MoveTo::create(0.3, Vec2(-200,winSize.height/2));
        auto callFunc = CallFunc::create(CC_CALLBACK_0(PlayScene::beginNewGame, this));
        auto hecheng =Sequence::create(jin,ting,chu,callFunc, NULL);
        messageLabel->setVisible(true);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectZhuan);
        messageLabel->runAction(hecheng);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //iOS代码
        if (guankashu % 3 == 0) {
            [[CSInterstitial sharedInterstitial] loadInterstitial];
            [[CSInterstitial sharedInterstitial] showInterstitialWithScale:0.9f];
        }

#else
        //Android代码
#endif

        //beginNewGame();
    }
    
    
}

void PlayScene::AddBalls(){
    int positionX = MiddleX -250;
    int positionY = winSize.height - 40;
    
    for (int y = 0; y<10; y++) {
        for (int x = 0; x<8; x++) {
            PlayScene::addBall(positionX+70*x, positionY-70*y);
        }
    }
}

void PlayScene::addBall(float positionX, float positionY){
    int rand = arc4random() % 5 ;
    std::string imageName = imageNames.at(rand);
    
    auto newBall = Sprite::create(imageName);
    newBall->setTag(rand);
    newBall->setPosition(positionX,positionY);
    
    auto ballBody = PhysicsBody::createCircle(newBall->getContentSize().width/2 );
    ballBody->setVelocity(Vec2(0.0f,-100.0f));
    ballBody->getFirstShape()->setDensity(8.0f);
    ballBody->getFirstShape()->setFriction(0.1f);
    ballBody->getFirstShape()->setRestitution(0.0f);
    
    newBall->setPhysicsBody(ballBody);
    ballList.pushBack(newBall);
    colorCount[rand]++;
    addChild(newBall);
        
}

void PlayScene::deleteBall(cocos2d::Sprite *ball){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectMoFa);
    auto fire = ParticleSystemQuad::create("lizi.plist");
    switch (ball->getTag()) {
        case 0:
            fire->setTexture(Director::getInstance()->getTextureCache()->addImage("lizihuang.png"));
            break;
        case 1:
            fire->setTexture(Director::getInstance()->getTextureCache()->addImage("lizilan.png"));
            break;
        case 2:
            fire->setTexture(Director::getInstance()->getTextureCache()->addImage("lizizi.png"));
            break;
        case 3:
            fire->setTexture(Director::getInstance()->getTextureCache()->addImage("lizihong.png"));
            break;
        case 4:
            fire->setTexture(Director::getInstance()->getTextureCache()->addImage("lizilv.png"));
            break;
        default:
            break;
    }
    fire->setPosition(ball->getPosition());
    fire->setAutoRemoveOnFinish(true);
    addChild(fire,99);
    
    int ballTag = ball->getTag();
    colorCount[ballTag]--;
    removeChild(ball);
    ballList.eraseObject(ball);
}
void PlayScene::addEdges(){

    auto edges2 = PhysicsBody::createEdgeSegment(Vec2(MiddleX, 100), Vec2(MiddleX-310, 420),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node2 = Node::create();
    node2->setPhysicsBody(edges2);
    //node2->setPosition(winSize/2);
    
    auto edges3 = PhysicsBody::createEdgeSegment(Vec2(MiddleX, 100), Vec2(MiddleX+310, 416),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node3 = Node::create();
    node3->setPhysicsBody(edges3);
    
    auto edgeLeft  = PhysicsBody::createEdgeSegment(Vec2(MiddleX-299,0), Vec2(MiddleX-299,winSize.height),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node4 = Node::create();
    node4->setPhysicsBody(edgeLeft);
    
    auto edgeRight  = PhysicsBody::createEdgeSegment(Vec2(MiddleX+302,0), Vec2(MiddleX+302,winSize.height),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node5 = Node::create();
    node5->setPhysicsBody(edgeRight);
    

    addChild(node2);
    addChild(node3);
    addChild(node4);
    addChild(node5);
    
}

bool PlayScene::isNear(cocos2d::Sprite *s1, cocos2d::Sprite *s2){
    float x1 = s1->getPosition().x;
    float x2 = s2->getPosition().x;
    float y1 = s1->getPosition().y;
    float y2 = s2->getPosition().y;
    float juli = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    if (juli > (s1->getContentSize().width+2)) {
        return false;
    }
    return true;
}
float PlayScene::getjuli(Vec2 v1,Vec2 v2){
    float x1 = v1.x;
    float x2 = v2.x;
    float y1 = v1.y;
    float y2 = v2.y;
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


void PlayScene::chuliBall(cocos2d::Sprite *sp)
{
    for (int i = 0; i<ballList.size(); i++)
    {
        if (!selectedBalls.contains(ballList.at(i)))
        {//检查是否重复
            if (sp->getTag() == ballList.at(i)->getTag())
            {//检查颜色是否一样
                if (isNear(sp, ballList.at(i)))
                {//检查是否触碰
                    selectedBalls.pushBack(ballList.at(i));
                    PlayScene::chuliBall(ballList.at(i));
                }
            }
        }
    }
}

void PlayScene::refreshScore()
{
    int guankashu = UserDefault::getInstance()->getIntegerForKey(Key_TotalRate);
    
    rateLabel->setString(StringUtils::format("第%d关",guankashu));
    
    mubiaoLabel->setString(StringUtils::format("目标：%d",guanka[guankashu]));
    
    int totaldefen = UserDefault::getInstance()->getIntegerForKey(Key_TotalScore);
    int currentScore = totaldefen + defen;
    
    scoreLabel->setString(StringUtils::format("分数：%d",currentScore));
    //scoreLabel->setSystemFontName("SiCChaoCuHei-M10S");
    if (scoreLabel->getTextColor() == Color4B::WHITE) {
        if (currentScore >= guanka[guankashu]) {
            scoreLabel->setTextColor(Color4B::GREEN);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectWao);
            auto fangda = ScaleTo::create(0.3, 1.2);
            auto huanyuan =ScaleTo::create(0.3, 1.0);
            auto duilie = Sequence::create(fangda,huanyuan,fangda,huanyuan,fangda,huanyuan, NULL);
            
            scoreLabel->runAction(duilie);
        }
    }
    
}







