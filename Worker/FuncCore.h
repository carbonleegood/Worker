#pragma once
#include <tchar.h>
#include "GlobalData.h"
enum FuncCode
{
	F_NO_WORK = 1,
	F_UPDATE,
	F_GetPlayerPos,
	F_MOVE,
	F_GetPlayerInfo,
	F_GetMonsterList,
	F_CastUntargetSkill,
	F_CastTargetSkill,
	F_GetRoundList,
	F_StopMove,
	F_GetMapData,
	F_ActiveTarget,
	F_GetWaypointInfo,//��ȡ���͵���Ϣ
	F_Transport,//����
	F_CreateNewDungeon,//���ͽ��¸���
	F_GetBagItemList,//��ȡ�����б�
	F_GetMapID,//��ȡ��ͼID
	F_GetTrophyInfo,
	F_GetLoginStatus,//��ȡ����״̬
	F_UseItem,
	F_ClickNPCMenu,//���NPC�˵�
	F_PutToSell,//����Ʒ����������
	F_ConfirmSell,//ȷ������
	F_Logout,//С��
	F_Relive,//����
	F_Pickup,
	F_DropDown,
	F_DropDownStack,
	F_ActiveStoragePage,
	F_ReadStorageUI,
	F_ReadStoragePageNum,
	F_IdentityItem,//����װ��
	F_UpSkill,//��������ʯ
	F_ItemOnMouse,
	F_BuffExist,
	F_GetItemDescrib,
	F_GetNPCMenuInfo,
	F_TransHideHome,
	F_LeftClickItem,//��������ƷCALL
	F_SaveToStorage,//ֱ�Ӵ洢���ֿ�
};
//extern ::CRITICAL_SECTION cs_core;
//extern ::CONDITION_VARIABLE cv_core;
//extern FuncCode eFuncCode;

#define EVENT_STRING _T("lglglg")

//HOOK����
#define WM_LG_CALL WM_USER+5559
#define SUCCESS 0

extern HWND hGameWnd;
extern HANDLE hEvent;
//func core
extern bool InitGobalData();
extern void FUpdate();

extern unsigned int WINAPI ServerThread(LPVOID);

//С��CALL����
typedef int*(__stdcall*FP_GetCallAddr)(INT64);

//[1]function FZ_SetIsDLl(AIsDll: Boolean) : ULONG; stdcall;
typedef ULONG(__stdcall*FP_SetIsDLl)(BOOL);
extern FP_SetIsDLl SetIsDLl;

typedef unsigned char*(__stdcall*FP_ReadMapData)(DWORD*, DWORD*, DWORD*);
extern FP_ReadMapData ReadMapData;
//Funcs[3] : = @FZ_ReadPosition;  // ulong (*fp)(float OutX, float OutY);
typedef ULONG(__stdcall*FP_ReadPosition)(float* OutX, float* OutY);
extern FP_ReadPosition ReadPosition;

//h��ȡ��Χ�б�
//Funcs[4] : = @FZ_ReadRoundInfo; // void* (*fp)();
typedef void*(__stdcall*FP_ReadRoundInfo)();
extern FP_ReadRoundInfo ReadRoundInfo;

//Funcs[5] : = @FZ_ReadSelfInfo;  // void* (*fp)();
typedef void*(__stdcall*FP_ReadSelfInfo)();
extern FP_ReadSelfInfo ReadSelfInfo;

//�ƶ�CALL
//Funcs[201] : = @FZ_CallMove; // ulong (*fp)(ulong x, ulong y);
typedef ULONG(__stdcall*FP_CallMove)(ULONG x, ULONG y);
extern FP_CallMove CallMove;

//function FZ_CallUnTargetSkill(X, Y, �������, ��������: ULONG) : ULONG; stdcall;
typedef ULONG(__stdcall*FP_CallUnTargetSkill)(ULONG x, ULONG y,ULONG num,ULONG);
extern FP_CallUnTargetSkill CallUnTargetSkill;


typedef ULONG(__stdcall*FP_CallTargetSkill)(ULONG ObjPtr, ULONG num, ULONG);
extern FP_CallTargetSkill CallTargetSkill;


//FZ_CallActiveNPC
typedef ULONG(__stdcall*FP_CallActiveNPC)(ULONG x, ULONG y);
extern FP_CallActiveNPC CallActiveNPC;

// ����CALL�����뿿��������
//function FZ_CallTransport(��ͼID, ������ID: ULONG) : ULONG; stdcall;
typedef  ULONG(__stdcall*FP_CallTransport)(ULONG MapID, ULONG WaypointID, ULONG CTRL);
extern FP_CallTransport CallTransport;

//function FZ_CallTransportSelect(�˵����: ULONG) : ULONG;
// ���¸�����ʽ����
// ����1 ���0123 �¸����Ļ�ʼ�մ�FF 1�ֽ�
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallTransportSelect)(ULONG MenuID);
extern FP_CallTransportSelect CallTransportSelect;

// ��ȡ���͵���Ϣ
//function FZ_ReadTransportList : Pointer; stdcall;
typedef Waypoint*(__stdcall*FP_ReadTransportList)();
extern FP_ReadTransportList ReadTransportList;

//// �������̵� void* (*fp)(ulong ��ȡ����, ulong ����ֵ_��Ч��������);
//Funcs[7] : = @FZ_ReadItemList;
// ��ȡ����
//�Լ����� = 0;
//�̵��±ߵĴ��� = 1;
//�̵��ϱߵĴ��� = 2;
typedef  void*(__stdcall*FP_ReadItemList)(ULONG ItemType, ULONG* ItemCount);
extern FP_ReadItemList ReadItemList;

//function FZ_ReadCurrentMapID(var ����ֵ : TTransportInfo) : ULONG; stdcall;
// ��ȡ��ǰ��ͼID
// ����1 ��ŷ���ֵ ���غ�FZ_ReadTransportListһ���Ľṹ
// ����ֵ 1=�ɹ� 0=���������ȡʧ��
typedef  ULONG(__stdcall*FP_ReadCurrentMapID)(void* pMapInfo);
extern FP_ReadCurrentMapID ReadCurrentMapID;

//procedure FZ_ReadWorldItemInfo(PRound: ULONG; var ����ֵ : TItemInfo); stdcall;
// ��ȡ������Ʒ����ϸ��Ϣ
// ����1 ������Ʒ��Mem2
// ����2 ��ŷ���ֵ ���� TItemInfo �ṹָ��
// ����ֵ ��
typedef  void(__stdcall*FP_ReadWorldItemInfo)(ULONG ObjPtr,void* pItemInfo);
extern FP_ReadWorldItemInfo ReadWorldItemInfo;

//function FZ_ReadUIState : ULONG; stdcall;10
// �ж���Ϸ���ߡ���ͼ״̬
// 0 ����
// 1 ����ѡ��ɫ����
// 2 ������Ϸ��
// 3 ���ڶ�ͼ
typedef  ULONG(__stdcall*FP_ReadUIState)();
extern FP_ReadUIState ReadUIState;

//function FZ_CallUseItem(����ID, ��Ʒ����ID: ULONG) : ULONG; stdcall;205
// ����ID���� TItemList.ID
// ��Ʒ����ID���� TItemInfo.ServiceID
// ����ֵ0=��CALL���� 1=��CALL�ɹ�
// ʹ�ûسǾ������Χ�б���һ��Interfacename��Metadata/MiscellaneousObjects/PlayerPortal��
// ��ʰȡCALL������ܻسǣ��سǺ��кܶ�������һ���Ĵ����ţ�ȫ�С��������š�
// ��һ���б�����ֵģ����㷵��֮ǰ�ĵ�ͼ�����硰ĺ�⺣̲�������Ƿ��صĴ�����
typedef  ULONG(__stdcall*FP_CallUseItem)(ULONG WinID, ULONG ServiceID);
extern FP_CallUseItem CallUseItem;


//function FZ_CallClickNPCMenu(�˵�ID: ULONG) : ULONG; stdcall;206
// ���NPC�˵�CALL
// ���� �˵�ID Ŀǰ��֪14=���� 15=���ۣ�16���ƣ�
// ����ֵ0=��CALL���� 1=��CALL�ɹ�
typedef  ULONG(__stdcall*FP_CallClickNPCMenu)(ULONG MenuID);
extern FP_CallClickNPCMenu CallClickNPCMenu;

//function FZ_CallPutToSell(Left, Top, ServiceID, WinID: ULONG) : ULONG; stdcall;207
// ����Ʒ���뷷������
// ����1 ���뷷������ �� ����λ��
// ����2 ���뷷������ �� ����λ��
// ����3 ��Ʒ��ServiceID
// ����ֵ0=��CALL���� 1=��CALL�ɹ�
typedef  ULONG(__stdcall*FP_CallPutToSell)(ULONG LeftPos, ULONG TopPos, ULONG ServiceID, ULONG WinID);
extern FP_CallPutToSell CallPutToSell;

//function FZ_CallConfirmSell : ULONG; stdcall;208
// ȷ�ϳ���
// ���� ��
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallConfirmSell)();
extern FP_CallConfirmSell CallConfirmSell;




//function FZ_CallReturnChoseRole : ULONG; stdcall;209
// С��CALL
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallReturnChoseRole)();
extern FP_CallReturnChoseRole CallReturnChoseRole;


//function FZ_CallRelive(������ʽ: ULONG) : ULONG; stdcall;210
// ����CALL
// ����1 ������ʽ 0=��¼������ 1=��������
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallRelive)(ULONG ReliveType);
extern FP_CallRelive CallRelive;

//function FZ_CallItemTakeUP(�����ṹָ��, ��Ʒ����ID: ULONG) : ULONG; stdcall;
// ������ƷCALL
// ����1 TItemList.Mem
// ����2 ��Ʒ��ServiceID
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallItemTakeUP)(ULONG BagObjPtr,ULONG ServiceID);
extern FP_CallItemTakeUP CallItemTakeUP;


//function FZ_CallItemTakeDown(�����ṹָ��, Left, Top: ULONG) : ULONG; stdcall;
// ������ƷCALL
// ����1 TItemList.Mem
// ����2 λ��Left
// ����3 λ��Top
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_CallItemTakeDown)(ULONG StorageObjPtr, ULONG Left,ULONG Top);
extern FP_CallItemTakeDown CallItemTakeDown;


//function FZ_GetStoragePageInfo(Page: ULONG) : ULONG; stdcall;
// ��ȡ�ֿ����ݣ��㿪�ֿ�ֻ�ܻ�ȡ��һҳ����ߵ�Ҫ�ֶ���CALL��ȡ��Ȼû�����
// ����1 ҳ��  �±��0��
// ����ֵ 0=��callʱ��������1=�ɹ�
typedef  ULONG(__stdcall*FP_GetStoragePageInfo)(ULONG StoragePageNum);
extern FP_GetStoragePageInfo GetStoragePageInfo;


//FZ_ReadStorageUIPTR
typedef  ULONG(__stdcall*FP_ReadStorageUIPTR)(ULONG StoragePageNum,ULONG* pStoragePageNZNum);//��2�������ǻ�ȡ���ò�����
extern FP_ReadStorageUIPTR ReadStorageUIPTR;


typedef  ULONG(__stdcall*FP_ReadStoragePageCount)();
extern FP_ReadStoragePageCount ReadStoragePageCount;


typedef  ULONG(__stdcall*FP_CallItemTakeDownStack)(ULONG StorageObjPtr, ULONG TargetServiceID);
extern FP_CallItemTakeDownStack CallItemTakeDownStack;

//function FZ_CallIdentify(��������UIID, ����ServiceID, װ������UIID, װ��ServiceID: ULONG)
//: ULONG; stdcall;

typedef  ULONG(__stdcall*FP_CallIdentify)(ULONG CurrencyUIID, ULONG CurrencyServiceID, ULONG ItemUIID, ULONG ItemServiceID);
extern FP_CallIdentify CallIdentify;

typedef  ULONG(__stdcall*FP_AutoSkillUp)();
extern FP_AutoSkillUp AutoSkillUp;

typedef  ULONG(__stdcall*FP_IsBuffExists)(ULONG SkillID);
extern FP_IsBuffExists IsBuffExists;

typedef  ULONG(__stdcall*FP_IsItemOnMouse)();
extern FP_IsItemOnMouse IsItemOnMouse;

typedef  ULONG(__stdcall*FP_GetDescription)(ULONG ItemObjPtr);
extern FP_GetDescription GetDescription;

typedef  ULONG(__stdcall*FP_ReadNPCMenu)(NPCMenuItem* pNPCMenuList);
extern FP_ReadNPCMenu ReadNPCMenu;

typedef  ULONG(__stdcall*FP_ReadHideoutServiceID)();
extern FP_ReadHideoutServiceID ReadHideoutServiceID;

typedef  ULONG(__stdcall*FP_CallTransHidout)(ULONG ServiceID);
extern FP_CallTransHidout CallTransHidout;

typedef  ULONG(__stdcall*FP_CallClickItem)(ULONG BagObjPtr, ULONG ServiceID,ULONG ctrl);
extern FP_CallClickItem CallClickItem;

typedef  ULONG(__stdcall*FP_CallCtrlMoveItem)(ULONG StoragePageNum, ULONG ServiceID,ULONG MoveFlag);
extern FP_CallCtrlMoveItem CallCtrlMoveItem;