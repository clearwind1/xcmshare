//
//  GameEventConfig.h
//  TwinGame
//  游戏事件配置
//  Created by yang on 15/8/25.
//
//

#ifndef __testmm__GameEventConfig__
#define __testmm__GameEventConfig__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;


/**
 
 对事件发布简单配置
 EventConfig: 事件结构体，里面现在只有事件发布名称
 使用： EventCustom event(EventConfig.eventname);
 
 GameEventConfig: 事件数据类（现在主要是游戏数据）
 使用： 
 GameEventConfig* eventtest = new GameEventConfig();
 eventtest->setdownTime(30);
 
 EventCustom event(EventConfig.eventname);
 event.setUserData(eventtest);
 
 */


class GameEventConfig
{
public:
	GameEventConfig() {};
	~GameEventConfig() {};

	// 版本資訊, 包含版本號碼與機台號碼
	// 下位機開機時第一個發送的命令是版本資訊
	// 在遊戲場景收到版本號命令代表下位機以重開機, 要replaceScene()回資源加載畫面
	CC_SYNTHESIZE(VersionInfo, m_VersionInfo, VersionInfo);

	// 分機測試資訊, 包含分機的連線狀態
	// 在資源加載階段, 下位機發送完版本資訊後會發送各分機的連線狀態
	// lanID 分機ID
	// status 連線狀態 1 = 連線, 0 = 斷線
	CC_SYNTHESIZE(LanTestInfo, m_LanTestInfo, LanTestInfo);

	// 賠率資訊, 包含所有押位的賠率
	// 收到賠率資訊代表新的一局開使, 重新回到倒數階段
	CC_SYNTHESIZE(OddsInfo, m_OddsInfo, OddsInfo);

	// 歷史紀錄資訊, 包含過去幾局中獎的押位 (目前設定20局)
	// 收到新一局命令(賠率資訊)後不久下位機就會馬上送上歷史紀錄資訊
	CC_SYNTHESIZE(HistoryInfo, m_HistoryInfo, HistoryInfo);

	// 倒數秒數資訊
	CC_SYNTHESIZE(SecondInfo, m_SecondInfo, SecondInfo);

	// 分機ID重複錯誤, 如果有兩台分機的分機ID一樣, 下位機就會發這個錯誤
	// 裡面包含錯誤的分機ID, 需要把錯誤訊息顯示在螢幕上
	CC_SYNTHESIZE(LanConflictInfo, m_LanConflict, LanConflictInfo);

	// 分機下線資訊, 如果有分機沒連上線下位機就會發送這個訊息
	// 裡面的int lostID代表下線的分機ID
	// 可能同時會有好幾台分機下線, 所有下線的分機都需要顯示在螢幕上
	// 如果有N台分機下線, 每一局遊戲下位機都會發送N次這個訊息, 每個訊息裡的lostID都會不一樣
	CC_SYNTHESIZE(LanLostInfo, m_LanLostInfo, LanLostInfo);

	// 開跑命令, 收到此命令代表倒數結束, 開始跑燈
	// 裡面包含從哪個燈位開始跑(fromPosition), 跑到哪個燈位(toPosition)
	// 中哪個押位(winningItem) 紅色狐狸 綠色貓頭鷹等等的
	// 中的押位的賠率是多少(odds)
	// 中什麼顏色(rightOrLeft)
	// 送幾個燈(shouts) 幸運位(luckySeat)
	// 是否中彩金(isBonus) 是否中JP(isJP) 是否播放音樂(isMusic)
	// 彩金(bonus)
	CC_SYNTHESIZE(RunDataInfo, m_RunDataInfo, RunDataInfo);

	// 送燈資訊
	// 送哪個燈位(toPosition) 送哪個押位(winningItem) 賠率(odds)
	CC_SYNTHESIZE(ShoutDataInfo, m_ShoutDataInfo, ShoutDataInfo);

	// 彩金分配資訊
	// 裡面有一個float array, 代表每一台分機所分配到的彩金比率是多少
	// 你需要把這個比率 * 彩金(在開跑命令裡) 才會等於一台分機分配到多少彩金
	CC_SYNTHESIZE(BonusDistributionInfo, m_BonusDistributionInfo, BonusDistributionInfo);

	// 場景資訊, 代表要換場景
	// int scene;  0 = 遊戲場景, 1 = 設定機台ID場景, 2 = 設定場景, 3 = 歸零場景, 5 = 打碼場景, 6 = 查帳場景, 8 = 機台時間已過場景
	CC_SYNTHESIZE(SceneInfo, m_SceneInfo, SceneInfo);

	// 是否replaceScene()回資源加載場景
	// 在onEnter() 裡去判斷m_bIsResetSystem, 如果true就replaceScene()到資源加載場景
	CC_SYNTHESIZE(bool, m_bIsResetSystem, ResetSystem);
};

#endif /* defined(__testmm__GameEventConfig__) */
