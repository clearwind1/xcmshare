//
//  BonusLayer.h
//  xcm
//  奖励层，显示中奖画面
//  Created by Yang on 15/8/20.
//
//

#ifndef __xcm__BonusLayer__
#define __xcm__BonusLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"
#include "MyUtility.h"

USING_NS_CC;

#define	PrizeConfigman "prizeman"
#define	PrizeConfigfox "prizefox"
#define	PrizeConfigowl "prizeowl"
#define	PrizeConfigsquirrel "prizesquirrel"
#define	PrizeConfigmonkey "prizemonkey"
#define	PrizeConfigbigbear "prizesbear"

#define	PrizeConfigmantatol  38
#define	PrizeConfigfoxtatol  35
#define	PrizeConfigowltatol  40
#define	PrizeConfigsquirreltatol  38
#define	PrizeConfigmonkeytatol  51
#define	PrizeConfigbigbeartatol  38

class BonusLayer : public Layer
{
public:
    BonusLayer();
    ~BonusLayer();
    
    CREATE_FUNC(BonusLayer);
    
    //virtual bool init();
    
    static BonusLayer* getInstance();
    
    void showBonus(int type);
    
    void removeBonus();
    
    virtual void update(float dt);
    
private:
    BonusDistributionInfo m_pbonusinfo;
    
};


#endif /* defined(__xcm__BonusLayer__) */
