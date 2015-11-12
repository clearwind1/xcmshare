//
//  GameTimeLayer.h
//  xcm
//
//  Created by Yang on 15/8/29.
//
//

#ifndef __xcm__GameTimeLayer__
#define __xcm__GameTimeLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"
#include "MyUtility.h"

USING_NS_CC;

class GameTimeLayer : public Layer
{
public:
    GameTimeLayer();
    ~GameTimeLayer();
    
    static GameTimeLayer* getInstance();
    
    CREATE_FUNC(GameTimeLayer);
    
    virtual bool init(void);
    
    virtual void update(float dt);
    
    //显示倒计时
    void showTime(int curtime);
    //设置时间可见性
    void setTimeVisble(bool bshow);
    
    void downTime(cocos2d::EventCustom *event);
    //初始化游戏事件监听
    void initlistenevent();
    
    void showDownTime();
    
    void resetTime();
    
private:
    
    Node* m_pNumNodeLeft;
    Node* m_pNumNodeRight;
    
    SecondInfo m_psecondinfo;
    
};

#endif /* defined(__xcm__GameTimeLayer__) */
