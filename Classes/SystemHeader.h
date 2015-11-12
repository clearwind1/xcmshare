#ifndef _SYSTEM_HEADER_H__
#define _SYSTEM_HEADER_H__

//#define BOOMBALL
#define BOONIEBEARS

#define USE_EVENT_LISTENER	0	// �Ƿ�ʹ�ñO �C��

// define ��ӆ�¼����Q
#define VERSION_INFO_EVENT				"version_info_event"			// �汾̖�¼�
#define MACHINE_ID_INFO_EVENT			"machine_id_info_event"			// �C̨̖�¼�
#define LAN_TEST_INFO_EVENT				"lan_test_info_event"			// �֙C�yԇ�¼�
#define ODDS_INFO_EVENT					"odds_info_event"				// �r���¼�
#define HISTORY_INFO_EVENT				"history_info_event"			// �vʷ�o������¼�
#define MACHINE_ERROR_INFO_EVENT		"machine_error_info_event"		// �֙C�e�`�����¼�
#define SECOND_INFO_EVENT				"second_info_event"				// �딵�����¼�
#define LAN_CONFLICT_INFO_EVENT			"lan_conflict_info_event"		// �֙CID���}�����¼�
#define LAN_LOST_INFO_EVENT				"lan_lost_info_event"			// �֙C�ྀ�����¼�
#define RUN_DATA_INFO_EVENT				"run_data_info_event"			// �ܟ������¼�
#define RUN_END_INFO_EVENT				"run_end_info_event"			// �ܟ��ꮅ�����¼�
#define RUN_RL_END_INFO_EVENT			"run_rl_end_info_event"			// �t���ܟ��ꮅ�����¼�
#define SHOUT_DATA_INFO_EVENT			"shout_data_info_event"			// �͟������¼�
#define SHOUT_END_INFO_EVENT			"shout_end_info_event"			// �͟��Y�������¼�
#define BONUS_DISTRIBUTION_INFO_EVENT	"bonus_distribution_info_event"	// �ʽ���������¼�
#define SCENE_INFO_EVENT				"scene_info_event"				// �Q���������¼�
#define SETTING_INFO_EVENT				"setting_info_event"			// �O�������¼�
#define CODE_INFO_EVENT					"code_info_event"				// ݔ��a�¼�
#define ACCOUNT_INFO_EVENT				"account_info_event"			// �鎤�����¼�
#define LOADING_COMPLETE_INFO_EVENT		"loading_complete_info_event"	// �YԴ���d�ꮅ�����¼�
#define ACTIVATION_CODE_INFO_EVENT		"activation_code_info_event"	// ��a�����¼�
#define OPERATE_TIME_INFO_EVENT			"operate_time_info_event"		// �\�Еr�g�����¼�
#define MACHINE_STATUS_INFO_EVENT		"machine_status_info_event"		// �C̨��B�¼�
#define PLAYER_TABLES_INFO_EVENT		"player_tables_info_event"		// ������������¼�
#define CREDIT_AND_WIN_INFO_EVENT		"credit_and_win_info_event"		// credit�cwin�¼�
#define BONUS_INFO_EVENT				"bonus_info_event"				// �ʽ��¼�
#define DRAW_LOTTERY_INFO_EVENT			"draw_lottery_info_event"		// �_���c�ʽ�����¼�

#define REPLACE_WITH_LOADING_SCENE		"replace_with_loading_scene"	// ֪ͨ�[�����replaceScene��LoadingScene

// �[���O��
#ifdef BOONIEBEARS
#define NUMBER_OF_ODDS				12		// 12���r��
#define NUMBER_OF_HISTORIES			14		// 14�֚vʷ�o�
#define NUMBER_OF_LANS				8		// ��ϵ�y���֙C��
#define NUMBER_OF_LAMPS				28		// �ׂ���λ
#define PASSWORD_LENGTH				8		// �ܴa�L��
#define NUMBER_OF_SETTINGS			20		// �ׂ��O���
//#define SIZE_OF_PLAYER_TABLE_INFO	2		// PlayerTableInfo һ���̓ɂ��֙C���YӍ
#define TO_SLAVE					0x91
#define TO_MASTER					0x90
#endif

#ifdef BOOMBALL
#define NUMBER_OF_ODDS				5		// 4�T
#define NUMBER_OF_HISTORIES			20		// 20�֚vʷ�o�
#define NUMBER_OF_LANS				8		// ��ϵ�y���֙C��
#define PASSWORD_LENGTH				8		// �ܴa�L��
#define NUMBER_OF_SETTINGS			20		// �ׂ��O���
#define SIZE_OF_PLAYER_TABLE_INFO	2		// PlayerTableInfo һ���̓ɂ��֙C���YӍ
#define START_LAN_ID				1		// ��ϵ�y��ʼ�֙CID
#define END_LAN_ID					4		// ��ϵ�y����֙CID
#define TO_SLAVE					0x99
#define TO_MASTERS					0x90
#define TO_MASTER_1					0x91
#define TO_MASTER_2					0x92
#endif

// UserDefault keys
#define VERSION_NUMBER_KEY		"version_number_key"
#define MACHINE_ID_KEY			"machine_id_key"

// �汾�YӍ
struct VersionInfo
{
	bool isNew;
	int versionNumber;
};

// �C̨ID�YӍ
struct MachineIDInfo
{
	bool isNew;
	int machineID;
};

// �֙C�yԇ�YӍ
struct LanTestInfo
{
	bool isNew;
	int lanID;		// �֙C̖�a
	int status;		// �B����B
};

// �r���YӍ
struct OddsInfo
{
	bool isNew;
	int odds[NUMBER_OF_ODDS];	// �r��
};

// �vʷ�o��YӍ
struct HistoryInfo
{
	bool isNew;
	int histories[NUMBER_OF_HISTORIES];		// �vʷ�o�
};

// �֙C�e�`�a�YӍ
struct MachineErrorInfo
{
	bool isNew;
	int machineID;
	int errorCode;
};

// �딵�YӍ
struct SecondInfo
{
	bool isNew;
	int second;
};

// �֙CID���}�YӍ
struct LanConflictInfo
{
	bool isNew;
	int conflictID;
};

// �֙C�ྀ�YӍ
struct LanLostInfo
{
	bool isNew;
	int lostNumber;		// �ڎ�̨�ྀ
	int lostID;			// �ྀ�ķ֙CID;
};

// �ܟ��YӍ
struct RunDataInfo
{
	bool isNew;
	int fromPosition;	// ���Ă���λ�_ʼ��
	int toPosition;		// ͣ���Ă���λ
	int winningItem;	// ���Ă�Ѻλ eg. �tɫ���� �Gɫ؈�^��
	int odds;			// �r��
	int rightOrLeft;	// ����/�t��
	int shouts;			// �ׂ͎���
	int luckySeat;		// ���\λ
	bool isBonus;		// �Ƿ��вʽ�
	bool isJP;			// �Ƿ���JP
	bool isMusic;		// �Ƿ񲥷�����
	int bonus;			// �ʽ�
};

// �͟��YӍ
struct ShoutDataInfo
{
	bool isNew;
	int toPosition;		// �ܵ��Ă���λ
	int winningItem;	// ���Ă�Ѻλ
	int odds;			// �r��
};

// �ʽ�����YӍ
struct BonusDistributionInfo
{
	bool isNew;
	float bonusDistributionRatio[NUMBER_OF_LANS];	// ���֙C�ʽ�������
};

// ����ID
enum SceneID 
{
	Game_Scene,				// �[����� 
	MachineID_Scene,		// ���O�C̨ID����
	Setting_Scene,			// �O������
	ResetAccount_Scene,		// �w�����
	ActivationCode_Scene,	// ��a����
	Account_Scene,			// �鎤����
	Deactivated_Scene		// �\�Еr�g���^����
};

// �����YӍ
// �Q����
struct SceneInfo
{
	bool isNew;
	SceneID sceneID;	// ����ID
};

// �O�������YӍ
struct SettingSceneInfo
{
	bool isNew;
	int number;		// �{�ڎ��				0 indexed
	int item;		// �{ʲ�N				0 indexed
	int color;		// ��item헵��ɫ
	int value;		// ��item헵�ֵ
};

enum CodeType { GameSettingPassword = 10, SetNewPassword, MachineIDPassword = 20, MachineID, ActivationCode = 30 };
enum CodeStatus { Invalid = 20, Valid };

// �ܴa�YӍ
struct CodeInfo
{
	bool isNew;
	CodeType codeType;			// ����ݔ�����N�N�a
	CodeStatus codeStatus;		// 20 �e�`, 21 ���_
	int cursorPosition;			// �Θ�λ�� 0 indexed
	int code[PASSWORD_LENGTH];	// ֵ
};

enum AccountType {
	BasicTransaction = 1,	// �_Ͷϴ��
	BetAndPay				// Ѻ��
};

// �鎤�YӍ
struct AccountInfo
{
	bool isNew;
	int lanID;					// ��һ̨�֙C�Ď�
	AccountType accountType;	// 1: �_Ͷϴ�ˎ�		2: Ѻ�Î�
	int note;					// �_��
	int coin;					// Ͷ
	int clear;					// ϴ��
	int pay;					// ��
	int passIn;					// Ѻ��
	int passOut;				// �÷�
	int passIn_RL;				// �ɫѺ��
	int passOut_RL;				// �ɫ�÷�
};

// ��a�YӍ
struct ActivationCodeInfo
{
	bool isNew;
	int machineID;		// �C̨ID
	int reportTimes;	// ��a�Δ�
	int totalIn;		// ����
	int totalOut;		// ����
};

// �\�Еr�g�YӍ
struct OperateTimeInfo
{
	bool isNew;
	int seconds;
	int minutes;
	int hours;
	int days;
};

// �C̨��B
struct MachineStatusInfo
{
	bool isNew;
	int machineStatus;		// ÿ���[���machineStatus������ͬ�����x
};

#ifdef BOOMBALL
// ��������YӍ
struct PlayerTableInfo
{
	bool isNew;
	int lanID;													// �֙CID ��1�_ʼ��
	int credit[SIZE_OF_PLAYER_TABLE_INFO];
	int win[SIZE_OF_PLAYER_TABLE_INFO];
	int creditPerBet[SIZE_OF_PLAYER_TABLE_INFO];				// һѺ�׷�
	int selectedBetItem[SIZE_OF_PLAYER_TABLE_INFO];				// �x���Ѻλ
	int betItemBets[SIZE_OF_PLAYER_TABLE_INFO][NUMBER_OF_ODDS];	// ��Ѻλ��Ѻ��
	int lanStatus[SIZE_OF_PLAYER_TABLE_INFO];					// �֙C1 �e�`��B	���� = 0;
};
#endif

// �ʽ��YӍ
struct BonusInfo
{
	bool isNew;
	bool isBonus;
	int bonus;
};

// Credit�cWin�YӍ
struct CreditAndWinInfo
{
	bool isNew;
	int credit[NUMBER_OF_LANS];
	int win[NUMBER_OF_LANS];
};

// �_���YӍ ���Ă�Ѻλ, �ʽ����
struct DrawLotteryInfo
{
	bool isNew;
	int betItem;							// ���Ă�Ѻλ	0 indexed
	int bonusMode;							// 0 �]�ʽ�, 1 �вʽ� ��һ����, 2 �Ͳʽ�
	int bonus;								// �ʽ�
	int bonusBetItemBet[NUMBER_OF_LANS];	// �ʽ�ѺλѺ��
	int minBonusBetItemBetToGetBonus;		// �ʽ�Ѻλ���Ѻ��
	int totalBonusBetItemBet;				// �ʽ�Ѻλ��Ѻ��
	int lanBonus[NUMBER_OF_LANS];			// ���֙C��òʽ�
};

#endif