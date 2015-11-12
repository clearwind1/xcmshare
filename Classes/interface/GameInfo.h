//
//  GameInfo.h
//  xcm
//  游戏信息，配置。
//  Created by Yang on 15/8/5.
//
//

#ifndef __xcm__GameInfo__
#define __xcm__GameInfo__

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

#define cache SpriteFrameCache::getInstance()

//游戏debug模式，0为关，1为开
#define GAMEDEBUG           1
//游戏是否为接收事件模式，0为否，1为是
#define GAMEEventMODE       1

const int STARTDOWNTIME = 5;
const int MAXROLE       = 28;

class GameInfo : public Layer
{
public:
    GameInfo();
    ~GameInfo();
    
    static GameInfo* getInstance();
    
    //CREATE_FUNC(GameInfo);
    
    //游戏设计尺寸
    CC_SYNTHESIZE(Size, m_GameDesignSize, GameDesignSize);
    
    //创建一个帧动画
    Action* createAnitmation(const char* pathname/*路径名*/,int total/*图片总数*/,int loopcount/*动作循环次数(-1永久循环)*/,float delay/*播放速度*/,bool reverse=false);
    
    //对一个节点对象设置坐标
    void spriteSetPosition(Node* node,Node* sprite,float x,float y);
    
    //创建图片数字
    void createSpriteNum(Node* node,const char* numName,int num);
    
    Sprite* createRect(Rect rect,float x,float y);
    
    //判断点在直线上
    bool isPointInLine(Point soildP,float linelen,float angle,Point judeP,float deta = 0.25);
    
    //播放中奖音效
    void playEffect(int prizeID);
    
    
private:
    
    
    
};


#endif /* defined(__xcm__GameInfo__) */
