//
//  GameRecords.h
//  xcm
//
//  Created by Yang on 15/8/28.
//
//

#ifndef __xcm__GameRecords__
#define __xcm__GameRecords__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"


USING_NS_CC;

const int MAXRECORDS = 12;

class GameRecords : public Layer
{
public:
    GameRecords();
    ~GameRecords();
    
    CREATE_FUNC(GameRecords);
    
    static GameRecords* getInstance();
    
    virtual bool init();
    
    virtual void update(float dt);
    
    void initrecords(bool e);       //参数e，判断是否为初始化
    
    void receiveEvent(EventCustom* event);
    void showrecords();
    
    void setvisiable(bool e);
    
private:
    
    HistoryInfo m_phistoryinfo;
    
};

#endif /* defined(__xcm__GameRecords__) */
