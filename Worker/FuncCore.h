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
	F_GetWaypointInfo,//获取传送点信息
	F_Transport,//传送
	F_CreateNewDungeon,//传送进新副本
	F_GetBagItemList,//获取背包列表
	F_GetMapID,//获取地图ID
	F_GetTrophyInfo,
	F_GetLoginStatus,//获取连接状态
	F_UseItem,
	F_ClickNPCMenu,//点击NPC菜单
	F_PutToSell,//放物品到售卖窗口
	F_ConfirmSell,//确认售卖
	F_Logout,//小退
	F_Relive,//复活
	F_Pickup,
	F_DropDown,
	F_DropDownStack,
	F_ActiveStoragePage,
	F_ReadStorageUI,
	F_ReadStoragePageNum,
	F_IdentityItem,//鉴定装备
	F_UpSkill,//升级技能石
	F_ItemOnMouse,
	F_BuffExist,
	F_GetItemDescrib,
	F_GetNPCMenuInfo,
	F_TransHideHome,
	F_LeftClickItem,//左键点击物品CALL
	F_SaveToStorage,//直接存储到仓库
};
//extern ::CRITICAL_SECTION cs_core;
//extern ::CONDITION_VARIABLE cv_core;
//extern FuncCode eFuncCode;

#define EVENT_STRING _T("lglglg")

//HOOK窗口
#define WM_LG_CALL WM_USER+5559
#define SUCCESS 0

extern HWND hGameWnd;
extern HANDLE hEvent;
//func core
extern bool InitGobalData();
extern void FUpdate();

extern unsigned int WINAPI ServerThread(LPVOID);

//小宋CALL声明
typedef int*(__stdcall*FP_GetCallAddr)(INT64);

//[1]function FZ_SetIsDLl(AIsDll: Boolean) : ULONG; stdcall;
typedef ULONG(__stdcall*FP_SetIsDLl)(BOOL);
extern FP_SetIsDLl SetIsDLl;

typedef unsigned char*(__stdcall*FP_ReadMapData)(DWORD*, DWORD*, DWORD*);
extern FP_ReadMapData ReadMapData;
//Funcs[3] : = @FZ_ReadPosition;  // ulong (*fp)(float OutX, float OutY);
typedef ULONG(__stdcall*FP_ReadPosition)(float* OutX, float* OutY);
extern FP_ReadPosition ReadPosition;

//h获取周围列表
//Funcs[4] : = @FZ_ReadRoundInfo; // void* (*fp)();
typedef void*(__stdcall*FP_ReadRoundInfo)();
extern FP_ReadRoundInfo ReadRoundInfo;

//Funcs[5] : = @FZ_ReadSelfInfo;  // void* (*fp)();
typedef void*(__stdcall*FP_ReadSelfInfo)();
extern FP_ReadSelfInfo ReadSelfInfo;

//移动CALL
//Funcs[201] : = @FZ_CallMove; // ulong (*fp)(ulong x, ulong y);
typedef ULONG(__stdcall*FP_CallMove)(ULONG x, ULONG y);
extern FP_CallMove CallMove;

//function FZ_CallUnTargetSkill(X, Y, 技能序号, 操作类型: ULONG) : ULONG; stdcall;
typedef ULONG(__stdcall*FP_CallUnTargetSkill)(ULONG x, ULONG y,ULONG num,ULONG);
extern FP_CallUnTargetSkill CallUnTargetSkill;


typedef ULONG(__stdcall*FP_CallTargetSkill)(ULONG ObjPtr, ULONG num, ULONG);
extern FP_CallTargetSkill CallTargetSkill;


//FZ_CallActiveNPC
typedef ULONG(__stdcall*FP_CallActiveNPC)(ULONG x, ULONG y);
extern FP_CallActiveNPC CallActiveNPC;

// 传送CALL，必须靠近传送阵
//function FZ_CallTransport(地图ID, 传送阵ID: ULONG) : ULONG; stdcall;
typedef  ULONG(__stdcall*FP_CallTransport)(ULONG MapID, ULONG WaypointID, ULONG CTRL);
extern FP_CallTransport CallTransport;

//function FZ_CallTransportSelect(菜单序号: ULONG) : ULONG;
// 以新副本方式传送
// 参数1 序号0123 新副本的话始终传FF 1字节
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallTransportSelect)(ULONG MenuID);
extern FP_CallTransportSelect CallTransportSelect;

// 获取传送点信息
//function FZ_ReadTransportList : Pointer; stdcall;
typedef Waypoint*(__stdcall*FP_ReadTransportList)();
extern FP_ReadTransportList ReadTransportList;

//// 读背包商店 void* (*fp)(ulong 读取类型, ulong 返回值_有效数据数量);
//Funcs[7] : = @FZ_ReadItemList;
// 读取类型
//自己背包 = 0;
//商店下边的窗口 = 1;
//商店上边的窗口 = 2;
typedef  void*(__stdcall*FP_ReadItemList)(ULONG ItemType, ULONG* ItemCount);
extern FP_ReadItemList ReadItemList;

//function FZ_ReadCurrentMapID(var 返回值 : TTransportInfo) : ULONG; stdcall;
// 读取当前地图ID
// 参数1 存放返回值 返回和FZ_ReadTransportList一样的结构
// 返回值 1=成功 0=遇到错误读取失败
typedef  ULONG(__stdcall*FP_ReadCurrentMapID)(void* pMapInfo);
extern FP_ReadCurrentMapID ReadCurrentMapID;

//procedure FZ_ReadWorldItemInfo(PRound: ULONG; var 返回值 : TItemInfo); stdcall;
// 读取地面物品的详细信息
// 参数1 地面物品的Mem2
// 参数2 存放返回值 返回 TItemInfo 结构指针
// 返回值 无
typedef  void(__stdcall*FP_ReadWorldItemInfo)(ULONG ObjPtr,void* pItemInfo);
extern FP_ReadWorldItemInfo ReadWorldItemInfo;

//function FZ_ReadUIState : ULONG; stdcall;10
// 判断游戏掉线、读图状态
// 0 出错
// 1 还在选角色界面
// 2 正常游戏中
// 3 正在读图
typedef  ULONG(__stdcall*FP_ReadUIState)();
extern FP_ReadUIState ReadUIState;

//function FZ_CallUseItem(窗口ID, 物品服务ID: ULONG) : ULONG; stdcall;205
// 窗口ID就是 TItemList.ID
// 物品服务ID就是 TItemInfo.ServiceID
// 返回值0=调CALL出错 1=调CALL成功
// 使用回城卷轴后，周围列表会多一个Interfacename叫Metadata/MiscellaneousObjects/PlayerPortal的
// 用拾取CALL点击就能回城，回城后有很多类型名一样的传送门，全叫“城镇传送门”
// 有一个叫别的名字的，是你返回之前的地图，比如“暮光海滩”，就是返回的传送门
typedef  ULONG(__stdcall*FP_CallUseItem)(ULONG WinID, ULONG ServiceID);
extern FP_CallUseItem CallUseItem;


//function FZ_CallClickNPCMenu(菜单ID: ULONG) : ULONG; stdcall;206
// 点击NPC菜单CALL
// 参数 菜单ID 目前已知14=购买 15=出售（16进制）
// 返回值0=调CALL出错 1=调CALL成功
typedef  ULONG(__stdcall*FP_CallClickNPCMenu)(ULONG MenuID);
extern FP_CallClickNPCMenu CallClickNPCMenu;

//function FZ_CallPutToSell(Left, Top, ServiceID, WinID: ULONG) : ULONG; stdcall;207
// 把物品放入贩卖窗口
// 参数1 放入贩卖窗口 横 格子位置
// 参数2 放入贩卖窗口 竖 格子位置
// 参数3 物品的ServiceID
// 返回值0=调CALL出错 1=调CALL成功
typedef  ULONG(__stdcall*FP_CallPutToSell)(ULONG LeftPos, ULONG TopPos, ULONG ServiceID, ULONG WinID);
extern FP_CallPutToSell CallPutToSell;

//function FZ_CallConfirmSell : ULONG; stdcall;208
// 确认出售
// 参数 无
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallConfirmSell)();
extern FP_CallConfirmSell CallConfirmSell;




//function FZ_CallReturnChoseRole : ULONG; stdcall;209
// 小退CALL
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallReturnChoseRole)();
extern FP_CallReturnChoseRole CallReturnChoseRole;


//function FZ_CallRelive(重生方式: ULONG) : ULONG; stdcall;210
// 重生CALL
// 参数1 重生方式 0=记录点重生 1=城镇重生
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallRelive)(ULONG ReliveType);
extern FP_CallRelive CallRelive;

//function FZ_CallItemTakeUP(容器结构指针, 物品服务ID: ULONG) : ULONG; stdcall;
// 拿起物品CALL
// 参数1 TItemList.Mem
// 参数2 物品的ServiceID
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallItemTakeUP)(ULONG BagObjPtr,ULONG ServiceID);
extern FP_CallItemTakeUP CallItemTakeUP;


//function FZ_CallItemTakeDown(容器结构指针, Left, Top: ULONG) : ULONG; stdcall;
// 拿起物品CALL
// 参数1 TItemList.Mem
// 参数2 位置Left
// 参数3 位置Top
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_CallItemTakeDown)(ULONG StorageObjPtr, ULONG Left,ULONG Top);
extern FP_CallItemTakeDown CallItemTakeDown;


//function FZ_GetStoragePageInfo(Page: ULONG) : ULONG; stdcall;
// 获取仓库数据，点开仓库只能获取第一页，后边的要手动调CALL获取不然没法存放
// 参数1 页码  下标从0起
// 返回值 0=调call时遇到错误，1=成功
typedef  ULONG(__stdcall*FP_GetStoragePageInfo)(ULONG StoragePageNum);
extern FP_GetStoragePageInfo GetStoragePageInfo;


//FZ_ReadStorageUIPTR
typedef  ULONG(__stdcall*FP_ReadStorageUIPTR)(ULONG StoragePageNum,ULONG* pStoragePageNZNum);//第2个参数是获取内置参数的
extern FP_ReadStorageUIPTR ReadStorageUIPTR;


typedef  ULONG(__stdcall*FP_ReadStoragePageCount)();
extern FP_ReadStoragePageCount ReadStoragePageCount;


typedef  ULONG(__stdcall*FP_CallItemTakeDownStack)(ULONG StorageObjPtr, ULONG TargetServiceID);
extern FP_CallItemTakeDownStack CallItemTakeDownStack;

//function FZ_CallIdentify(卷轴所在UIID, 卷轴ServiceID, 装备所在UIID, 装备ServiceID: ULONG)
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