#ifndef __MyPhysicalBall_SCENE_H__
#define __MyPhysicalBall_SCENE_H__

#define Key_TotalRate "TotalRate"
#define Key_TotalScore "TotalScore"

#include "cocos2d.h"
//#include "ChanceAd.h"
//#include "MobClickCpp.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
private:
    int guanka[100];
    void initShuJu();
    int currentRate = 1;
    Label* messageLabel;
    Label* scoreLabel;
    Label* rateLabel;
    Label* mubiaoLabel;
    int defen;
    Vector<Sprite*> ballList;
    Vector<Sprite*> selectedBalls;
    int colorCount[5];
    std::vector<std::string> imageNames;
    cocos2d::Size winSize;
    float MiddleX,MiddleY;
    void beginNewGame();
    void addEdges();
    void addEdges2();
    void AddBalls();
    void deleteBall(Sprite* ball);
    void addBall(float positionX,float positionY);
    void chuliBall(Sprite* sp);
    void clickItEnd(Touch* touch,Event* event);
    bool isNear(Sprite* s1,Sprite* s2);
    float getjuli(Vec2 v1,Vec2 v2);
    void testIsNear();
    bool touchIt(Touch* touch,Event* event);
    void refreshScore();
    void refreshRate();
    void jiankongBall(float dt);
    //void touchNewGame(Ref* target,ui::Widget::TouchEventType type);
//    void dingshiqi(float dt);
//    void dingshiqi2(float dt);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float delta);
    //virtual void onEnter();
    CREATE_FUNC(PlayScene);
};

#endif // __MyPhysicalBall_SCENE_H__
