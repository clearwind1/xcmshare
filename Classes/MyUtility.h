#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;

#define SERIAL_PORT_READ_LENGTH		128	

//#define	VER_COM				1	// VER_CODE(4), Machine_in(4),sale_type(1), id_max(1), DIP_SW(4) 
//#define	LAN_TEST_COM		2	// id(1), test_status(1)
//#define	START_COM			3	// odds(2)x12 
//#define	HISTORY_COM			4	// pass(1)x20
//#define	MACHINE_ERROR_COM	5	// machine_error_id(1), error_code(1)
//#define	SEC_COM				6	// sec(1)
//#define	LAN_CONFLICT_COM	7	// conflict_id(1)
//#define	LAN_LOST_COM		8	// lost_counter(1), lost_id(1) 
//#define	RUN_DATA_COM		9	// run_led(1) 從哪個燈位開始跑	
//									// pass1_stop(1), 停在哪個燈位
//									// get_word(1) 中什麼item
//									// I_get_odds(2); 中的賠率
//									// RL_word(1); 紅黑/右左
//									// lucky_table(1); 幸運座位
//									// bonus_f(1); 是否中彩金
//									// jp_f(1); 有沒有JP (multiply the amount won by n)
//									// sound_f(1); 是否播放音樂
//									// V_L_bonus_1_buf(3);
//#define	RUN_END_COM			10
//#define	RUN_RL_END_COM		11
//#define	SHOUT_DATA_COM		12	// pass1_stop(1), get_word(1), I_get_odds(2)
//#define	SHOUT_END_COM		13
//#define	GET_WIN_COM			14	// L_bet_sum_total(3);
//									// L_over_get_bonus_min_bet_sum_buf(3);
//									// V_I_get_bonus_bet_min(2);
//									// I_slave_bet_buf[0][get_word](2);
//									// I_slave_bet_buf[1][get_word](2);
//									// I_slave_bet_buf[2][get_word](2);
//									// I_slave_bet_buf[3][get_word](2);
//									// I_slave_bet_buf[4][get_word](2);
//									// I_slave_bet_buf[5][get_word](2);
//									// I_slave_bet_buf[6][get_word](2);
//									// I_slave_bet_buf[7][get_word](2);
//#define	GET_RL_WIN_COM		15	
//#define	CLEAR_SCREEN_COM	16	// 0	just black screen
////1111 	set machine code
////2222  set setting
////3333  reset recoder
////5555  test SEG and KEY
//
//#define	SETTING_COM			17	// item(1), color(1), value(4)
//#define	PASSWORD_COM		18	// item(1);		01 entry    setting password,
////				02 entry    new setting password
////				03 entry    machine id password
////				04 setting  machine id
////				05 entry    code
//
//// status(1);	00     normal
//// 				01--10 cursor  
//// 				20     mistake
//// 				21     right
//// value(4);
//#define	LIST_COM	19	// item(1);		11 id=1	coin			note				pay				clear
//							//				12 id=8	coin			note				pay				clear
//							//				81 id=1	pass1_in		pass1_out			RL_in			RL_out
//							//				82 id=8	pass1_in		pass1_out			RL_in			RL_out 
//							//				91 		Total_coin,		total_note,			total_pay,		total_clear
//							//				92 		total_pass1_in,	total_pass1_out,	total_RL_in,	total_RL_out
//							// value_1(4);
//							// value_2(4);
//							// value_3(4);
//							// value_4(4);
//#define	ACC_CODE_COM		20	// V_L_machine_id(4), V_I_report_times(2), total_in(4), total_out(4)
//#define	PRINT_COM			21	// data pass to PRINTER PORT
//// bytes(1), data(1)x40
//#define	TEST_POINT_COM		22	// value(4)x10


// define 命令
#define VERSION_COMMAND				1	// 版本號
#define LOADING_COMPLETE_COMMAND	2	// 資源加載完畢命令
#define LAN_TEST_COMMAND			3	// 分機測試
#define START_COMMAND				4	// 開始一局 資料包含賠率
#define HISTORY_COMMAND				5	// 歷史紀錄命令
#define MACHINE_ERROR_COMMAND		6	// 分機錯誤命令
#define SECOND_COMMAND				7	// 秒數命令
#define LAN_CONFLICT_COMMAND		8	// 分機ID重複命令
#define LAN_LOST_COMMAND			9	// 分機斷線命令
#define RUN_DATA_COMMAND			10	// 跑燈命令
#define RUN_END_COMMAND				11	// 跑燈完畢命令
#define RUN_RL_END_COMMAND			12	// 紅黑跑燈完畢命令
#define SHOUT_DATA_COMMAND			13	// 送燈命令
#define SHOUT_END_COMMAND			14	// 送燈完畢命令
#define GET_WIN_COMMAND				15	// 彩金分配命令
#define GET_RL_WIN_COMMAND			16
#define CHANGE_SCENE_COMMAND		17	// 換場景命令
#define SETTING_COMMAND				18	// 設定命令
#define PASSWORD_COMMAND			19	// 密碼命令
#define LIST_COMMAND				20	// 查帳命令
#define ACTIVATION_CODE_COMMAND		21	// 打碼訊息命令
#define OPERATE_TIME_COMMAND		24	// 運行時間命令
#define PLAYER_TABLES_COMMAND		50	// 玩家桌面命令 各個玩家的credit, win, 一押幾分, 押位 highlight, 各押位押分   頂球機用

#define ID_BYTE			3
#define COMMAND_BYTE	4
#define DATA0_BYTE		5

class semaphore {
public:
	semaphore(int value);

	void wait();
	void signal();

private:
	int count;
	std::mutex mutex;
	std::condition_variable condition;
};

class ThreadPool
{
private:
	int m_iMaxThreadNumber;
	int m_MaxQueueSize;
	std::queue<unsigned char*> m_WorkItemQueue;
	std::mutex m_WorkItemQueueMutex;
	semaphore* m_pAvailableQueueSlots;	// 标识任务队列是否已满，如果已满，用户线程如果调用AddWorkItem(workItem)，向队列提交任务，将处于阻塞状态，直到线程池中的线程提取了任务队列中的任务，才会唤醒AddWorkItem(workItem)继续执行
	semaphore* m_pAvailableWorkItems;		// 如果任务队列中没有任务，线程池中的等待线程将会因为sem_wait(availableWorkItem)而进入休眠等待状态，直到用户向任务队列提交任务，信号量availableWorkItems将会唤醒ThreadPool中相应个数的等待线程来执行相应的workItem(任务)
	semaphore* m_pTerminatedThreads;

public:
	ThreadPool();
	~ThreadPool();
	void Open(int iMaxThreadNumber, int iMaxQueueSize);		// 线程池打开函数
	void Close();											// 线程池关闭函数
	void AddWorkItem(unsigned char* pucReadBuffer);			// 用户提交任务函数
	void GetWorkItem(unsigned char** pucReadBuffer);			// 线程获取任务函数
	void WorkerLoop();										// 线程主函数
};

/**
 * 下位機類別
 * 單例 (Singleton) 設計模式
 * 負責串口讀寫
 * 分析下位機傳來的命令, 分析後傳給畫面層
 */
class SlaveMachine : public Node
{
private:
	static SlaveMachine* instance;

	bool m_bIsSerialPortThreadRunning;	// 串口線程是否已running, 如果已經running就禁止再開第二個串口讀寫線程

	bool init();

	int getIntFromByteArray(int startIndex, int length, unsigned char* pucReadBuffer);

	void SerialPortReadThread();			// 串口讀線程

	// 事件發布函式
	void dispatchCommandEvent(const std::string &eventName, void* data);	// 發布事件
	void dispatchVersionCommandEvent(unsigned char* pucReadBuffer);			// 發布版本命令事件
	void dispatchLanTestCommandEvent(unsigned char* pucReadBuffer);			// 發布分機測試命令事件
	void dispatchStartCommandEvent(unsigned char* pucReadBuffer);			// 發佈開始一局命令事件
	void dispatchHistoryCommandEvent(unsigned char* pucReadBuffer);			// 發佈歷史紀錄命令事件
	void dispatchMachineErrorCommandEvent(unsigned char* pucReadBuffer);	// 發佈分機錯誤命令事件
	void dispatchSecondCommandEvent(unsigned char* pucReadBuffer);			// 發佈秒數命令事件
	void dispatchLanConflictCommandEvent(unsigned char* pucReadBuffer);		// 發佈分機ID重複命令事件
	void dispatchLanLostCommandEvent(unsigned char* pucReadBuffer);			// 發佈分機斷線命令事件
	void dispatchRunDataCommandEvent(unsigned char* pucReadBuffer);			// 發佈跑燈命令事件
	void dispatchShoutDataCommandEvent(unsigned char* pucReadBuffer);		// 發佈送燈命令事件
	void dispatchGetWinCommandEvent(unsigned char* pucReadBuffer);			// 發佈彩金分配命令事件
	void dispatchChangeSceneCommandEvent(unsigned char* pucReadBuffer);		// 發佈進入後台命令事件
	void dispatchSettingCommandEvent(unsigned char* pucReadBuffer);			// 發佈設定命令事件
	void dispatchPasswordCommandEvent(unsigned char* pucReadBuffer);		// 發佈密碼命令事件
	void dispatchListCommandEvent(unsigned char* pucReadBuffer);			// 發佈查帳命令事件
	void dispatchActivationCodeCommandEvent(unsigned char* pucReadBuffer);	// 發佈打碼命令事件
	void dispatchOperateTimeCommandEvent(unsigned char* pucReadBuffer);		// 發佈運行時間命令事件
	void dispatchPlayerTablesCommandEvent(unsigned char* pucReadBuffer);	// 發佈玩家桌面命令事件

	void onRunEndCommandEventCallback(EventCustom* event);					// 跑燈完畢命令事件回呼
	void onRunRLEndCommandEventCallback(EventCustom* event);				// 紅黑跑燈完畢命令事件回呼
	void onShoutEndCommandEventCallback(EventCustom* event);				// 送燈完畢命令事件回呼
	void onLoadingCompleteCommandEventCallback(EventCustom* event);			// 資源加載完畢命令事件回呼
	
public:
    static SlaveMachine* getInstance();
	~SlaveMachine();

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

	// "設定"場景資訊
	// 正在調第幾項, 文字顏色, 設定值
	CC_SYNTHESIZE(SettingSceneInfo, m_SettingSceneInfo, SettingSceneInfo);

	// 密碼資訊
	//CC_SYNTHESIZE(PasswordInfo, m_PasswordInfo, PasswordInfo);

	// 查帳資訊
	CC_SYNTHESIZE(AccountInfo, m_AccountInfo, AccountInfo);

	// 打碼資訊
	// 機台ID, 打碼次數, 總入, 總出
	//CC_SYNTHESIZE(ActivationCodeInfo, m_ActivationCodeInfo, ActivationCodeInfo);

	// 運行時間資訊
	//CC_SYNTHESIZE(OperateTimeInfo, m_OperateTimeInfo, OperateTimeInfo);

	// 玩家檯面資訊
	//CC_SYNTHESIZE(PlayerTableInfo, m_PlayerTableInfo, PlayerTableInfo);

	bool startSerialPortCommunication();					// 開啟串口並開始通信線程
	void analyzeReadBuffer(unsigned char* pucReadBuffer);
};

#endif