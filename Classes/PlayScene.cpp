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
    scene->getPhysicsWorld()->setGravity(Vec2(0,-300));
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
    
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(PlayScene::touchIt,this);
    listener1->onTouchMoved = [](Touch* touch, Event* event){};
    listener1->onTouchEnded = [=](Touch* touch, Event* event){};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    PlayScene::beginNewGame();
    
    return true;
}

void PlayScene::beginNewGame(){
    ballList.clear();
    selectedBalls.clear();
    for (int i = 0; i<5; i++) {
        colorCount[i] = 0;
    }
    addEdges();
    AddBalls();
    this->schedule(schedule_selector(PlayScene::dingshiqi), 2);
}
//定时器,判断结束游戏的条件
void  PlayScene::dingshiqi(float dt){
    
    for (int i = 0; i< ballList.size(); i++) {
        if (ballList.at(i)->getPhysicsBody()->isResting()) {
            return;
        }
    }
    
    bool lost = false;
//    for (int i = 0; i<5; i++) {
//        if (colorCount[i] > 1) {
//            lost = true;
//        }
//    }
    
    for (int i = 0; i < ballList.size() - 1; i++)
    {
        for (int j = i+1; j<ballList.size(); j++)
        {
            if (lost) {
                break;
            }
            if ((isNear(ballList.at(i), ballList.at(j)))) {
                if (ballList.at(i)->getTag() == ballList.at(j)->getTag()) {
                    lost = true;
                    break;
                }
                
                //break;
            }
        }
    }

    if (!lost) {
        log("结束");
        this->unschedule(schedule_selector(PlayScene::dingshiqi));
    }
    log("0:[%d],1:[%d],2:[%d],3:[%d],4:[%d]",colorCount[0],colorCount[1],colorCount[2],colorCount[3],colorCount[4]);
}

bool PlayScene::touchIt(Touch* touch,Event* event){
    //Director::getInstance()->stopAnimation();
    selectedBalls.clear();
    auto clickLocation = touch->getLocation();
    
    for (int i = 0; i<ballList.size(); i++)
    {
        auto tar = ballList.at(i);
        if (PlayScene::getjuli(clickLocation, tar->getPosition()) < tar->getContentSize().width/2)
        {
            chuliBall(tar);
            if (selectedBalls.size()>1)
            {
                for (int i = 0; i<selectedBalls.size(); i++)
                {
                    int ballTag = selectedBalls.at(i)->getTag();
                    colorCount[ballTag]--;
                    removeChild(selectedBalls.at(i));
                    ballList.eraseObject(selectedBalls.at(i));
                }
                
            }
            break;
            
        }
    }
    //Director::getInstance()->startAnimation();
    log("消除%zd个",selectedBalls.size());
    log("还剩%zd个球球",ballList.size());
    return true;
}

void PlayScene::AddBalls(){
    int positionX = 80;
    int positionY = 930;
    
    for (int y = 0; y<11; y++) {
        for (int x = 0; x<9; x++) {
            PlayScene::addBall(positionX+60*x, positionY-60*y);
        }
    }
}

void PlayScene::addBall(float positionX, float positionY){
    int rand = arc4random() % 5 ;
    std::string imageName = imageNames.at(rand);
    
    auto newBall = Sprite::create(imageName);
    newBall->setTag(rand);
    newBall->setPosition(positionX,positionY);
    
    auto ballBody = PhysicsBody::createCircle(newBall->getContentSize().width/2);
    //ballBody->isResting()
    ballBody->setVelocity(Vec2(0.0f,-100.0f));
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
    
    auto edges2 = PhysicsBody::createEdgeSegment(Vec2(winSize.width/2, 50), Vec2(0, 350));
    auto node2 = Node::create();
    node2->setPhysicsBody(edges2);
    
    auto edges3 = PhysicsBody::createEdgeSegment(Vec2(winSize.width/2, 50), Vec2(winSize.width, 350));
    auto node3 = Node::create();
    node3->setPhysicsBody(edges3);
    
    auto edgeLeft  = PhysicsBody::createEdgeSegment(Vec2(50,0), Vec2(50,winSize.height));
    auto node4 = Node::create();
    node4->setPhysicsBody(edgeLeft);
    
    auto edgeRight  = PhysicsBody::createEdgeSegment(Vec2(winSize.width-50,0), Vec2(winSize.width-50,winSize.height));
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
    if (juli > (s1->getContentSize().width+1)) {
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















