//
//  GameScene.h
//  xcm
//  游戏UI层，负责显示游戏界面
//  Created by Yang on 15/8/14.
//
//

#ifndef __xcm__GameScene__
#define __xcm__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "GameInfo.h"
#include "SystemHeader.h"
#include "MyUtility.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    GameScene();
    ~GameScene();
    
    static GameScene* getInstance();
    
    static Scene* createScene(void);
    
    CREATE_FUNC(GameScene);
    
    virtual bool init(void);
    
    virtual void update(float dt);
    
    //显示游戏背景
    void showGameBg(void);

    //倒计时事件
    void downTimeEvent(float dt);
    //初始化游戏事件监听
    void initlistenevent();
    
    void receiveRunEvent(EventCustom* event);
    
    //初始化
    void initGame();
    
    //灯柱发射
    void shotlight();
    void runlight();
    //开始跑测试
    void tablerun();
    //开始跑正式
    void runupdate(float dt);

	void dispatchRunRLEndCommandEvent(float dt);	// Steve 跑燈完畢後, 發佈紅黑跑燈完畢命令事件
    
    //测试结束
    void showbouns(float dt);
    void endgame(float dt);
    //重新开始
    void restartGame();
    
    Sprite* getShotlight(){return m_pshotlight;};
    
private:
    
    Sprite* m_pbottom;
    Sprite* m_pshoottable;          //炮台
    Sprite* m_pshotlight;           //炮台发射光柱
    //Sprite* m_prect;
    
    ActionInterval* m_pshotlightaction;     //光柱发射动画
    ActionInterval* m_prunlightaction;              //光柱循环动画
    
    RunDataInfo m_prundatainfo;
    ShoutDataInfo m_pshoutdatainfo;
    OddsInfo m_poddsinfo;
    
    float m_pangle;                 //炮台旋转角度
    float m_pangleSpeed;            //炮台旋转速度
    
    bool m_bRunFinish;
    
    int m_pruncount;                //炮台旋转圈数
    
    bool m_bshoutdata;
    
};


#endif /* defined(__xcm__GameScene__) */
