//
//  RoleLayer.h
//  xcm
//  角色层，灯位上的角色显示
//  Created by Yang on 15/8/20.
//
//

#ifndef __xcm__RoleLayer__
#define __xcm__RoleLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "GameInfo.h"

USING_NS_CC;

// Steve
    //人物
#define	RoleConfigmanm "manm"
#define	RoleConfigmanl "manl"
#define	RoleConfigmanr "manr"
#define	RoleConfigfox "fox"
#define	RoleConfigowl "owl"
#define	RoleConfigsquirrel "squirrel"
#define	RoleConfigmonkey "monkey"
#define	RoleConfigbigbear "bigbear"
    
#define	RoleConfigmantatol  38
#define	RoleConfigfoxtatol  22
#define	RoleConfigowltatol  29
#define	RoleConfigsquirreltatol  28
#define	RoleConfigmonkeytatol  33
#define	RoleConfigbigbeartatol  21
    
    //台子
#define	RoleConfigredtable  "redtable.png"
#define	RoleConfigbluetable  "bluetable.png"
#define	RoleConfigorgtable  "orgtable.png"
#define	RoleConfigcyantable  "cyantable.png"
#define	RoleConfiggreentable  "greentable.png"

class RoleLayer : public Layer
{
public:
    RoleLayer();
    ~RoleLayer();
    static RoleLayer* getInstance();
    
    
    virtual bool init();
    
    CREATE_FUNC(RoleLayer);
    
    void showAllRole();
    
    void pauseRole();
    void resumeRole(int roleid);
    
    virtual void update(float dt);
    
    void rescale(int roleid);
    
    void setCover(bool e);
    
private:

    Sprite* m_prole[MAXROLE];
    Sprite* m_ptable[MAXROLE];
    
    bool m_bSCaling[MAXROLE];
    
    CC_SYNTHESIZE(bool, isruning, Isruning);
    
    CC_SYNTHESIZE(int, m_prunroleID, runroleID);
    
    Sprite* m_pCover;
    
};


#endif /* defined(__xcm__RoleLayer__) */
