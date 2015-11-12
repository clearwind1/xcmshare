//
//  GameData.h
//  xcm
//  游戏数据，存储数据用
//  Created by Yang on 15/8/20.
//
//

#ifndef __xcm__GameData__
#define __xcm__GameData__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;

class GameData
{
public:
    GameData();
    ~GameData();
    
    static GameData* getInstance();
    
    //倒计时
    CC_SYNTHESIZE(int, g_curdowntime, curdowntime);
    //中奖ID
    CC_SYNTHESIZE(int, g_prizeid, prizeid);
    //机台号
    CC_SYNTHESIZE(int, g_machineID, machineID);
    //彩金分配
    CC_SYNTHESIZE(BonusDistributionInfo, g_bonusinfo, bonusinfo);
};

#endif /* defined(__xcm__GameData__) */
