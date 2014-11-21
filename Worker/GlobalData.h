#pragma once
struct GPlayerPos
{
	float x;
	float y;
};
extern GPlayerPos PlayerPos;
struct GMoveInfo
{
	ULONG x;
	ULONG y;
};
extern GMoveInfo MoveInfo;

struct RoundObjInfo
{
//Mem: ULONG;  // 地图块归属的指针
	ULONG MEm;
//Mem2: ULONG; // obj结构指针
	ULONG mem2;
//OriginIndex: ULONG;
	ULONG OriginIndex;
	// 原始的 y*x最大值+x 这个格式的序号
	// 比如要判断某个坐标有没有怪物挡路 就y*x最大值+x查询就可以了
	// 游戏自己是判断的[x-5, y-5]、[x+5, y+5]……这个矩形范围内有没有怪物
//ID: ULONG;
	ULONG ID;

//EnemyID: ULONG;
	ULONG EnemyID;

//Kind: ULONG;
	ULONG ActorCode;//类型?
//InterfaceName: array[0 .. 191] of Byte; // 类型名字
	BYTE InterfaceName[192];
//Name: array[0 .. 63] of Byte;           // 把Byte数组转成Unicode就是名字
	BYTE Name[64]; 
//HP: ULONG;
	ULONG HP;
//HPMax: ULONG;
	ULONG MaxHP;
//MP: ULONG;
	ULONG MP;
//MPMax: ULONG;
	ULONG MaxMP;
//Shield: ULONG;
	ULONG Shield;
//ShieldMax: ULONG;
	ULONG MaxShield;
//Level: ULONG;
	ULONG Level;
//X: Single; // float
//Y: Single;
//Z: Single;
	//X2: ULONG; // X2=X*0.092
	//Y2: ULONG; // Y2=Y*0.092
	//X3: ULONG; // X3=X2/0x17
	//Y3: ULONG; // Y3=Y2/0x17
	float X;
	float Y;
	float Z;
	ULONG X2;
	ULONG Y2;
	ULONG X3;
	ULONG Y3;
	BYTE TargetAble;
	BYTE Unknow;
	BYTE IsNPC;
	BYTE IsNPCAttackAble;
	ULONG Color;//箱子、怪物的颜色等级0=白 1=蓝 2=金 3=暗金
//	BYTE HashNames[200][32];
//	BYTE HashIndexs[200];
//HashNames: array[0 .. 199] of array[0 .. 31] of Byte;
	// 二维数组 就是200*32个Byte占坑就可以了
//HashIndexs: array[0 .. 199] of Byte;
	// 200个Byte 这些都是方便调试的观察信息 虽然占空间但是没办法 不然调试很麻烦
};
extern RoundObjInfo _PlayerInfo;
extern RoundObjInfo* pRoundList;

struct UntargetSkill
{
	ULONG x;
	ULONG y;
	ULONG num;
	ULONG type;
};
extern UntargetSkill untargetSkill;
extern int SkillTargetObjPtr;
extern int SkillNum;
extern int SkillModel;
struct Waypoint
{
	ULONG Mem;
	BYTE ActName[32];
	BYTE Name[32];
	ULONG ID;
};
extern Waypoint* pWaypointList;

extern int ActiveObjPtr;
extern int MapHalfX;
extern int MapX;
extern int MapY;
extern char* pMapData;
extern int TransMapID;
extern int TransWaypointID;
extern int nDungeonModel;

#pragma pack(push,1)
struct SItemInfo
{
	ULONG Mem1;
	ULONG ObjPtr;
	ULONG ID;
	ULONG ServiceID;                  // 服务ID CALL会用到
	ULONG Count;					  // 数量
	ULONG MaxCount;                   //最大数量
	BYTE InterfaceName[192];		  // 类型名
	BYTE Special[8];				  // 前缀数量  "xx的"算一个 "xx之"算一个
	BYTE Name[64];					  // 物品名
	ULONG Color;					  // 颜色
	ULONG Width;					  // 占用背包宽度
	ULONG Height;					  // 占用背包高度
	ULONG Left;						  // 在背包的X位置
	ULONG Top;						  // 在背包的Y位置
	ULONG Sockets[6];
	BYTE  SocketsContact[6];          //孔连接信息
	BYTE IsEquipment; // 是否是装备 0=否  1=是
	BYTE IsIdentity; // 是否未鉴定 0=未鉴定 1=已鉴定
	ULONG Quality; // 品质
	ULONG Stats[20];
	// 这个是鼠标经过物品后已经刷新的描述文本，若要读这里需要调CALL
	BYTE StatDescriptions[14][32];  //14x32字节的结构
};
#pragma pack (pop)

struct  ItemList
{
	ULONG Mem;
	ULONG WinID;                         // 窗口ID CALL里会用到
	SItemInfo Items[200]; // 物品数组
};
extern ItemList* pBag;
extern ULONG dwBagItemCount;

extern Waypoint CurMapInfo;
extern int nLoginStatus;
extern int nCallRet;

extern int UseItem_WinID;
extern int UseItem_ServiceID;

extern int ContainerType;
extern int SellLeft;
extern int SellTop;
extern int SellServiceID;
extern int SellWinID;

extern int StoragePageNum;
extern int nStoragePageObjPtr;
extern  int TargetStackServiceID;
extern int StorageLeft;
extern int StorageTop;
extern int PickBagPtr;
extern int PicupServiceID;

extern int NolootTrophyObjPtr;
extern SItemInfo _TrophyInfo;

extern int ReadPageUIRet;
extern int StoragePageCount;

extern int IdentityCurrencyServiceID;
extern int IdentityItemServiceID;

extern int nItemOnMouse;
extern int nBuffExist;

extern  int DescribItemObjPtr;

struct Point
{
	int x;
	int y;
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	};
	Point()
	{
		x = 0;
		y = 0;
	};
	bool operator ==(Point p)
	{
		if (this->x == p.x&&this->y == p.y)
		{
			return true;
		}
		return false;
	}
	bool operator !=(Point p)
	{
		if (this->x == p.x&&this->y == p.y)
		{
			return false;
		}
		return true;
	}
	bool operator <(Point p) const
	{
		if (this->x == p.x)
		{
			return this->y<p.y;
		}
		else
			return this->x<p.x;
	};
	Point& operator =(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
};