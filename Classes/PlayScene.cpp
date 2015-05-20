#include "PlayScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainItem.h"
#include "SimpleAudioEngine.h"


USING_NS_CC_MATH;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PlayScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-800));
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
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    
    
    initShuJu();
    addEdges();
    
    auto backGround1 = Sprite::create("BackGround2.jpg");
    backGround1->setAnchorPoint(Vec2(0.5,0.5));
    backGround1->setPosition(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height /2);
    addChild(backGround1, -1);
    
//    auto backGround = CSLoader::createNode("MainScene.csb");
//    addChild(backGround);
//    auto newGameButton = cocos2d::ui::Button::create("star.png");//backGround->getChildByName<cocos2d::ui::Button*>("Button_1");
//    newGameButton->setScale(0.3);
//    newGameButton->setPosition(Vec2(winSize.width - 100,winSize.height -100));
//    addChild(newGameButton);
//    newGameButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
//        if (type == ui::Widget::TouchEventType::ENDED) {
//            PlayScene::beginNewGame();
//        }
//    });
    //newGameButton->setZOrder(2);
    //临时返回的button
    auto backButton = cocos2d::ui::Button::create("pause.png");
    backButton->setAnchorPoint(Vec2(0.5,0.5));
    backButton->setPosition(Vec2(MiddleX - 230,1000));
    addChild(backButton);
    backButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->replaceScene(MainItemScene::createScene());
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
    messageLabel->setVisible(false);
    messageLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    messageLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    addChild(messageLabel,99);
    //messageLabel->autorelease();


    
    scoreLabel = Label::create();
        scoreLabel->setTextColor(Color4B::WHITE);
    scoreLabel->setSystemFontSize(40);
    scoreLabel->setSystemFontName("mnse.ttf");
    scoreLabel->setString("得分：0");
    scoreLabel->setPosition(winSize.width/2, 1000);
    addChild(scoreLabel,999);
    //scoreLabel->autorelease();

    mubiaoLabel = Label::create();
        mubiaoLabel->setTextColor(Color4B::WHITE);
    mubiaoLabel->setSystemFontSize(40);
    mubiaoLabel->setString("目标：");
    mubiaoLabel->setPosition(winSize.width/2 , 1100);
    addChild(mubiaoLabel,999);
    //mubiaoLabel->autorelease();

    rateLabel = Label::create();
        rateLabel->setTextColor(Color4B::WHITE);
    rateLabel->setSystemFontSize(40);
    rateLabel->setString("关卡数");
    rateLabel->setPosition(winSize.width/2 - 220, 1100);
    addChild(rateLabel,999);
    //rateLabel->autorelease();

    
    beginNewGame();
    
    return true;
}

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
    
    for (int i = 1; i<100; i++) {
        guanka[i] = guanka[i-1] + 1000 + 500*(i-1);
    }
    return;
}


void PlayScene::beginNewGame(){
    if (UserDefault::getInstance()->getIntegerForKey("TotalRate") == 0) {
        UserDefault::getInstance()->setIntegerForKey("TotalRate", 1);
    }
    defen = 0;
//    int guanka = UserDefault::getInstance()->getIntegerForKey("TotalRate");
//    UserDefault::getInstance()->setIntegerForKey("TotalRate", guanka+1);
//    UserDefault::getInstance()->flush();
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
    int tempguan = UserDefault::getInstance()->getIntegerForKey("TotalRate");
    sprintf(c_message, "第%d关\n目标：%d",tempguan,guanka[tempguan]);
    messageLabel->setString(c_message);
    auto jin = MoveTo::create(0.3, winSize/2);
    auto ting = DelayTime::create(1.5);
    auto chu = MoveTo::create(0.3, Vec2(-200,winSize.height/2));
    auto callFunc = CallFunc::create(CC_CALLBACK_0(PlayScene::AddBalls, this));
    auto hecheng =Sequence::create(jin,ting,chu,callFunc, NULL);
    messageLabel->setVisible(true);
    messageLabel->runAction(hecheng);
    
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

            for (int i = 0; i<selectedBalls.size(); i++)
            {
                //auto callfunc = CallFunc::create(CC_CALLBACK_1(PlayScene::deleteBall,this,selectedBalls.at(i)));
                deleteBall(selectedBalls.at(i));
               
            }
            if ((ballList.size()<1) ) {
                //log("结束游戏！");
                refreshRate();
                //        UserDefault
            }
            break;
            
        }
    }

    refreshScore();
    
    return false;
}

void PlayScene::refreshRate()
{
    int guankashu = UserDefault::getInstance()->getIntegerForKey("TotalRate");
    int zongfen =UserDefault::getInstance()->getIntegerForKey("TotalScore");
    
    if ((zongfen+ defen) < guanka[guankashu]) {
        //游戏失败，清零！
        UserDefault::getInstance()->setIntegerForKey("TotalRate", 0);
        
        UserDefault::getInstance()->setIntegerForKey("TotalScore", 0);
        UserDefault::getInstance()->flush();
        
        Director::getInstance()->replaceScene(MainItemScene::createScene());
    }else{
        //成功，进入下一关
        UserDefault::getInstance()->setIntegerForKey("TotalRate", guankashu +1);
        
        UserDefault::getInstance()->setIntegerForKey("TotalScore", zongfen + defen);
        UserDefault::getInstance()->flush();
        beginNewGame();
    }
    
    
}

void PlayScene::AddBalls(){
    int positionX = MiddleX -250;
    int positionY = winSize.height - 40;
    
    for (int y = 0; y<11; y++) {
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("mofa.wav");
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
    auto edges = PhysicsBody::createEdgeBox(winSize);
    auto node = Node::create();
    node->setPhysicsBody(edges);
    node->setPosition(winSize/2);
    
    auto edges2 = PhysicsBody::createEdgeSegment(Vec2(MiddleX, 100), Vec2(MiddleX-310, 410),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node2 = Node::create();
    node2->setPhysicsBody(edges2);
    
    auto edges3 = PhysicsBody::createEdgeSegment(Vec2(MiddleX, 100), Vec2(MiddleX+310, 410),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node3 = Node::create();
    node3->setPhysicsBody(edges3);
    
    auto edgeLeft  = PhysicsBody::createEdgeSegment(Vec2(MiddleX-310,0), Vec2(MiddleX-310,winSize.height),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node4 = Node::create();
    node4->setPhysicsBody(edgeLeft);
    
    auto edgeRight  = PhysicsBody::createEdgeSegment(Vec2(MiddleX+310,0), Vec2(MiddleX+310,winSize.height),PHYSICSBODY_MATERIAL_DEFAULT,1);
    auto node5 = Node::create();
    node5->setPhysicsBody(edgeRight);
    
    addChild(node);
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
    int guankashu = UserDefault::getInstance()->getIntegerForKey("TotalRate");
    char c_guanka[10];
    sprintf(c_guanka, "第%d关",guankashu);
    rateLabel->setString(c_guanka);
    
    char c_mubiao[10];
    sprintf(c_mubiao, "目标：%d",guanka[guankashu]);
    mubiaoLabel->setString(c_mubiao);
    
    int totaldefen = UserDefault::getInstance()->getIntegerForKey("TotalScore");
    char c_char[10];
    sprintf(c_char, "分数：%d",defen + totaldefen);
    scoreLabel->setString(c_char);
}













