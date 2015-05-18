#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include <Box2D/Box2D.h>
#include "ui/CocosGUI.h"

USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
private:
    Label* scoreLabel;
    int defen;
    Vector<Sprite*> ballList;
    Vector<Sprite*> selectedBalls;
    int colorCount[5];
    std::vector<std::string> imageNames;
    cocos2d::Size winSize;
    float MiddleX,MiddleY;
    void beginNewGame();
    void addEdges();
    void AddBalls();
    void addBall(float positionX,float positionY);
    void chuliBall(Sprite* sp);
    void clickItEnd(Touch* touch,Event* event);
    bool isNear(Sprite* s1,Sprite* s2);
    float getjuli(Vec2 v1,Vec2 v2);
    void testIsNear();
    bool touchIt(Touch* touch,Event* event);
    void refreshScore();
    //void touchNewGame(Ref* target,ui::Widget::TouchEventType type);
//    void dingshiqi(float dt);
//    void dingshiqi2(float dt);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayScene);
};

#endif // __HELLOWORLD_SCENE_H__
