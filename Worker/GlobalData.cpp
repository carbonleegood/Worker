#include "stdafx.h"
#include "GlobalData.h"
GPlayerPos PlayerPos;
GMoveInfo MoveInfo;
RoundObjInfo _PlayerInfo;
UntargetSkill untargetSkill;
int SkillTargetObjPtr;
int SkillNum;
int SkillModel;
RoundObjInfo* pRoundList;

int ActiveObjPtr;
int MapHalfX;
int MapX;
int MapY;
char* pMapData;

int TransMapID;
int TransWaypointID;
int nDungeonModel;
Waypoint* pWaypointList;


ItemList* pBag;
ULONG dwBagItemCount;

Waypoint CurMapInfo;
int nLoginStatus;
int nCallRet;

int UseItem_WinID;
int UseItem_ServiceID;

int ContainerType;

 int SellLeft;
 int SellTop;
 int SellServiceID;
 int SellWinID;
 int StoragePageNum;
 int StroagePageNZNum;//≤÷ø‚“≥ƒ⁄÷√ID
 int nStoragePageObjPtr;
 int TargetStackServiceID;
 int StorageLeft;
 int StorageTop;
 int PickBagPtr;
 int PicupServiceID;

 int NolootTrophyObjPtr;
 SItemInfo _TrophyInfo;

 int ReadPageUIRet;
 int StoragePageCount;

 int IdentityCurrencyServiceID;
 int IdentityItemServiceID;

 int nItemOnMouse;
 int nBuffExist;

 int DescribItemObjPtr;

 NPCMenuItem NPCMenuList[20];