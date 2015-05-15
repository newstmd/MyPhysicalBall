#include "PlayScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC_MATH;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-1000));
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
    imageNames.push_back("ball1.png");
    imageNames.push_back("ball2.png");
    imageNames.push_back("ball3.png");
    imageNames.push_back("ball4.png");
    imageNames.push_back("ball5.png");
    
    
    winSize = Director::getInstance()->getVisibleSize();
    
    auto backGround = CSLoader::createNode("MainScene.csb");
    addChild(backGround);
    auto newGameButton = backGround->getChildByName<cocos2d::ui::Button*>("Button_1");
    newGameButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            PlayScene::beginNewGame();
        }
    });
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(PlayScene::touchIt,this);
    listener1->onTouchMoved = [](Touch* touch, Event* event){};
    listener1->onTouchEnded = [=](Touch* touch, Event* event){};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    scoreLabel = Label::create();
    //scoreLabel->set
    scoreLabel->setTextColor(Color4B::RED);
    scoreLabel->setSystemFontSize(40);
    scoreLabel->setString("得分：0");
    scoreLabel->setPosition(winSize.width/2, 1100);
    addChild(scoreLabel,999);
//    scoreLabel->set
    
    PlayScene::beginNewGame();
    
    return true;
}



void PlayScene::beginNewGame(){
    
    defen = 0;
    
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
    addEdges();
    AddBalls();
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
                int ballTag = selectedBalls.at(i)->getTag();
                colorCount[ballTag]--;
                removeChild(selectedBalls.at(i));
                ballList.eraseObject(selectedBalls.at(i));
            }
            break;
            
        }
    }
    log("消除%zd个,还剩%zd个",selectedBalls.size(),ballList.size());
    log("总分%zd",defen);
    
    //scoreLabel->setString();
    if (ballList.size()<1) {
        log("结束游戏！");
    }
    
    return false;
}

void PlayScene::AddBalls(){
    int positionX = 80;
    int positionY = 1090;
    
    for (int y = 0; y<12; y++) {
        for (int x = 0; x<7; x++) {
            PlayScene::addBall(positionX+80*x, positionY-80*y);
        }
    }
    PlayScene::addBall(320, 130);
    PlayScene::addBall(240, 130);
    PlayScene::addBall(400, 130);
    PlayScene::addBall(320, 50);
}

void PlayScene::addBall(float positionX, float positionY){
    int rand = arc4random() % 5 ;
    std::string imageName = imageNames.at(rand);
    
    auto newBall = Sprite::create(imageName);
    newBall->setTag(rand);
    newBall->setPosition(positionX,positionY);
    
    auto ballBody = PhysicsBody::createCircle(newBall->getContentSize().width/2);
    //ballBody->setVelocity(Vec2(0.0f,-100.0f));
    ballBody->getFirstShape()->setDensity(8.0f);
    ballBody->getFirstShape()->setFriction(0.5f);
    ballBody->getFirstShape()->setRestitution(0.0f);
    
    newBall->setPhysicsBody(ballBody);
    ballList.pushBack(newBall);
    colorCount[rand]++;
    addChild(newBall);
        
}

void PlayScene::addEdges(){
    auto edges = PhysicsBody::createEdgeBox(winSize);
    auto node = Node::create();
    node->setPhysicsBody(edges);
    node->setPosition(winSize/2);
    
    auto edges2 = PhysicsBody::createEdgeSegment(Vec2(winSize.width/2, 0), Vec2(0, 220));
    auto node2 = Node::create();
    node2->setPhysicsBody(edges2);
    
    auto edges3 = PhysicsBody::createEdgeSegment(Vec2(winSize.width/2, 0), Vec2(winSize.width, 220));
    auto node3 = Node::create();
    node3->setPhysicsBody(edges3);
    
    auto edgeLeft  = PhysicsBody::createEdgeSegment(Vec2(20,0), Vec2(20,winSize.height));
    auto node4 = Node::create();
    node4->setPhysicsBody(edgeLeft);
    
    auto edgeRight  = PhysicsBody::createEdgeSegment(Vec2(winSize.width-20,0), Vec2(winSize.width-20,winSize.height));
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

void PlayScene::testIsNear(){
    auto s1 = ballList.at(0);
    auto s2 = ballList.at(2);
    isNear(s1, s2);
}

void PlayScene::chuliBall(cocos2d::Sprite *sp){
    for (int i = 0; i<ballList.size(); i++) {
        if (!selectedBalls.contains(ballList.at(i))) {//检查是否重复
            if (sp->getTag() == ballList.at(i)->getTag()) {//检查颜色是否一样
                if (isNear(sp, ballList.at(i))) {//检查是否触碰
                    selectedBalls.pushBack(ballList.at(i));
                    PlayScene::chuliBall(ballList.at(i));
                }
            }
        }
    }
}

void PlayScene::refreshScore()
{
    
}













