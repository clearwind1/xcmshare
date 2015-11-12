#ifndef _SYSTEM_HEADER_H__
#define _SYSTEM_HEADER_H__

//#define BOOMBALL
#define BOONIEBEARS

#define USE_EVENT_LISTENER	0	// 是否使用監聽機制

// define 自訂事件名稱
#define VERSION_INFO_EVENT				"version_info_event"			// 版本號事件
#define MACHINE_ID_INFO_EVENT			"machine_id_info_event"			// 機台號事件
#define LAN_TEST_INFO_EVENT				"lan_test_info_event"			// 分機測試事件
#define ODDS_INFO_EVENT					"odds_info_event"				// 賠率事件
#define HISTORY_INFO_EVENT				"history_info_event"			// 歷史紀錄命令事件
#define MACHINE_ERROR_INFO_EVENT		"machine_error_info_event"		// 分機錯誤命令事件
#define SECOND_INFO_EVENT				"second_info_event"				// 秒數命令事件
#define LAN_CONFLICT_INFO_EVENT			"lan_conflict_info_event"		// 分機ID重複命令事件
#define LAN_LOST_INFO_EVENT				"lan_lost_info_event"			// 分機斷線命令事件
#define RUN_DATA_INFO_EVENT				"run_data_info_event"			// 跑燈命令事件
#define RUN_END_INFO_EVENT				"run_end_info_event"			// 跑燈完畢命令事件
#define RUN_RL_END_INFO_EVENT			"run_rl_end_info_event"			// 紅黑跑燈完畢命令事件
#define SHOUT_DATA_INFO_EVENT			"shout_data_info_event"			// 送燈命令事件
#define SHOUT_END_INFO_EVENT			"shout_end_info_event"			// 送燈結束命令事件
#define BONUS_DISTRIBUTION_INFO_EVENT	"bonus_distribution_info_event"	// 彩金分配命令事件
#define SCENE_INFO_EVENT				"scene_info_event"				// 換場景命令事件
#define SETTING_INFO_EVENT				"setting_info_event"			// 設定命令事件
#define CODE_INFO_EVENT					"code_info_event"				// 輸入碼事件
#define ACCOUNT_INFO_EVENT				"account_info_event"			// 查帳命令事件
#define LOADING_COMPLETE_INFO_EVENT		"loading_complete_info_event"	// 資源加載完畢命令事件
#define ACTIVATION_CODE_INFO_EVENT		"activation_code_info_event"	// 打碼命令事件
#define OPERATE_TIME_INFO_EVENT			"operate_time_info_event"		// 運行時間命令事件
#define MACHINE_STATUS_INFO_EVENT		"machine_status_info_event"		// 機台狀態事件
#define PLAYER_TABLES_INFO_EVENT		"player_tables_info_event"		// 玩家桌面命令事件
#define CREDIT_AND_WIN_INFO_EVENT		"credit_and_win_info_event"		// credit與win事件
#define BONUS_INFO_EVENT				"bonus_info_event"				// 彩金事件
#define DRAW_LOTTERY_INFO_EVENT			"draw_lottery_info_event"		// 開獎與彩金分配事件

#define REPLACE_WITH_LOADING_SCENE		"replace_with_loading_scene"	// 通知遊戲場景replaceScene到LoadingScene

// 遊戲設置
#ifdef BOONIEBEARS
#define NUMBER_OF_ODDS				12		// 12個賠率
#define NUMBER_OF_HISTORIES			14		// 14局歷史紀錄
#define NUMBER_OF_LANS				8		// 總系統最大分機數
#define NUMBER_OF_LAMPS				28		// 幾個燈位
#define PASSWORD_LENGTH				8		// 密碼長度
#define NUMBER_OF_SETTINGS			20		// 幾個設定項
//#define SIZE_OF_PLAYER_TABLE_INFO	2		// PlayerTableInfo 一次送兩個分機的資訊
#define TO_SLAVE					0x91
#define TO_MASTER					0x90
#endif

#ifdef BOOMBALL
#define NUMBER_OF_ODDS				5		// 4門
#define NUMBER_OF_HISTORIES			20		// 20局歷史紀錄
#define NUMBER_OF_LANS				8		// 總系統最大分機數
#define PASSWORD_LENGTH				8		// 密碼長度
#define NUMBER_OF_SETTINGS			20		// 幾個設定項
#define SIZE_OF_PLAYER_TABLE_INFO	2		// PlayerTableInfo 一次送兩個分機的資訊
#define START_LAN_ID				1		// 子系統起始分機ID
#define END_LAN_ID					4		// 子系統最後分機ID
#define TO_SLAVE					0x99
#define TO_MASTERS					0x90
#define TO_MASTER_1					0x91
#define TO_MASTER_2					0x92
#endif

// UserDefault keys
#define VERSION_NUMBER_KEY		"version_number_key"
#define MACHINE_ID_KEY			"machine_id_key"

// 版本資訊
struct VersionInfo
{
	bool isNew;
	int versionNumber;
};

// 機台ID資訊
struct MachineIDInfo
{
	bool isNew;
	int machineID;
};

// 分機測試資訊
struct LanTestInfo
{
	bool isNew;
	int lanID;		// 分機號碼
	int status;		// 連線狀態
};

// 賠率資訊
struct OddsInfo
{
	bool isNew;
	int odds[NUMBER_OF_ODDS];	// 賠率
};

// 歷史紀錄資訊
struct HistoryInfo
{
	bool isNew;
	int histories[NUMBER_OF_HISTORIES];		// 歷史紀錄
};

// 分機錯誤碼資訊
struct MachineErrorInfo
{
	bool isNew;
	int machineID;
	int errorCode;
};

// 秒數資訊
struct SecondInfo
{
	bool isNew;
	int second;
};

// 分機ID重複資訊
struct LanConflictInfo
{
	bool isNew;
	int conflictID;
};

// 分機斷線資訊
struct LanLostInfo
{
	bool isNew;
	int lostNumber;		// 第幾台斷線
	int lostID;			// 斷線的分機ID;
};

// 跑燈資訊
struct RunDataInfo
{
	bool isNew;
	int fromPosition;	// 從哪個燈位開始跑
	int toPosition;		// 停在哪個燈位
	int winningItem;	// 中哪個押位 eg. 紅色狐狸 綠色貓頭鷹
	int odds;			// 賠率
	int rightOrLeft;	// 右左/紅黑
	int shouts;			// 送幾個燈
	int luckySeat;		// 幸運位
	bool isBonus;		// 是否中彩金
	bool isJP;			// 是否中JP
	bool isMusic;		// 是否播放音樂
	int bonus;			// 彩金
};

// 送燈資訊
struct ShoutDataInfo
{
	bool isNew;
	int toPosition;		// 跑到哪個燈位
	int winningItem;	// 中哪個押位
	int odds;			// 賠率
};

// 彩金分配資訊
struct BonusDistributionInfo
{
	bool isNew;
	float bonusDistributionRatio[NUMBER_OF_LANS];	// 各分機彩金分配比例
};

// 場景ID
enum SceneID 
{
	Game_Scene,				// 遊戲場景 
	MachineID_Scene,		// 重設機台ID場景
	Setting_Scene,			// 設定場景
	ResetAccount_Scene,		// 歸零場景
	ActivationCode_Scene,	// 打碼場景
	Account_Scene,			// 查帳場景
	Deactivated_Scene		// 運行時間已過場景
};

// 場景資訊
// 換場景
struct SceneInfo
{
	bool isNew;
	SceneID sceneID;	// 場景ID
};

// 設定場景資訊
struct SettingSceneInfo
{
	bool isNew;
	int number;		// 調第幾項				0 indexed
	int item;		// 調什麼				0 indexed
	int color;		// 第item項的顏色
	int value;		// 第item項的值
};

enum CodeType { GameSettingPassword = 10, SetNewPassword, MachineIDPassword = 20, MachineID, ActivationCode = 30 };
enum CodeStatus { Invalid = 20, Valid };

// 密碼資訊
struct CodeInfo
{
	bool isNew;
	CodeType codeType;			// 正在輸入甚麼種碼
	CodeStatus codeStatus;		// 20 錯誤, 21 正確
	int cursorPosition;			// 游標位置 0 indexed
	int code[PASSWORD_LENGTH];	// 值
};

enum AccountType {
	BasicTransaction = 1,	// 開投洗退
	BetAndPay				// 押得
};

// 查帳資訊
struct AccountInfo
{
	bool isNew;
	int lanID;					// 哪一台分機的帳
	AccountType accountType;	// 1: 開投洗退帳		2: 押得帳
	int note;					// 開分
	int coin;					// 投
	int clear;					// 洗分
	int pay;					// 退
	int passIn;					// 押分
	int passOut;				// 得分
	int passIn_RL;				// 顏色押分
	int passOut_RL;				// 顏色得分
};

// 打碼資訊
struct ActivationCodeInfo
{
	bool isNew;
	int machineID;		// 機台ID
	int reportTimes;	// 打碼次數
	int totalIn;		// 總入
	int totalOut;		// 總出
};

// 運行時間資訊
struct OperateTimeInfo
{
	bool isNew;
	int seconds;
	int minutes;
	int hours;
	int days;
};

// 機台狀態
struct MachineStatusInfo
{
	bool isNew;
	int machineStatus;		// 每款遊戲的machineStatus各代表不同的意義
};

#ifdef BOOMBALL
// 玩家桌面資訊
struct PlayerTableInfo
{
	bool isNew;
	int lanID;													// 分機ID 從1開始算
	int credit[SIZE_OF_PLAYER_TABLE_INFO];
	int win[SIZE_OF_PLAYER_TABLE_INFO];
	int creditPerBet[SIZE_OF_PLAYER_TABLE_INFO];				// 一押幾分
	int selectedBetItem[SIZE_OF_PLAYER_TABLE_INFO];				// 選擇的押位
	int betItemBets[SIZE_OF_PLAYER_TABLE_INFO][NUMBER_OF_ODDS];	// 各押位的押分
	int lanStatus[SIZE_OF_PLAYER_TABLE_INFO];					// 分機1 錯誤狀態	正常 = 0;
};
#endif

// 彩金資訊
struct BonusInfo
{
	bool isNew;
	bool isBonus;
	int bonus;
};

// Credit與Win資訊
struct CreditAndWinInfo
{
	bool isNew;
	int credit[NUMBER_OF_LANS];
	int win[NUMBER_OF_LANS];
};

// 開獎資訊 中哪個押位, 彩金分配
struct DrawLotteryInfo
{
	bool isNew;
	int betItem;							// 中哪個押位	0 indexed
	int bonusMode;							// 0 沒彩金, 1 有彩金 不一定送, 2 送彩金
	int bonus;								// 彩金數
	int bonusBetItemBet[NUMBER_OF_LANS];	// 彩金押位押分
	int minBonusBetItemBetToGetBonus;		// 彩金押位最低押分
	int totalBonusBetItemBet;				// 彩金押位總押分
	int lanBonus[NUMBER_OF_LANS];			// 個分機配得彩金
};

#endif