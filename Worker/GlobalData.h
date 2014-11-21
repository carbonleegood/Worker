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
//Mem: ULONG;  // ��ͼ�������ָ��
	ULONG MEm;
//Mem2: ULONG; // obj�ṹָ��
	ULONG mem2;
//OriginIndex: ULONG;
	ULONG OriginIndex;
	// ԭʼ�� y*x���ֵ+x �����ʽ�����
	// ����Ҫ�ж�ĳ��������û�й��ﵲ· ��y*x���ֵ+x��ѯ�Ϳ�����
	// ��Ϸ�Լ����жϵ�[x-5, y-5]��[x+5, y+5]����������η�Χ����û�й���
//ID: ULONG;
	ULONG ID;

//EnemyID: ULONG;
	ULONG EnemyID;

//Kind: ULONG;
	ULONG ActorCode;//����?
//InterfaceName: array[0 .. 191] of Byte; // ��������
	BYTE InterfaceName[192];
//Name: array[0 .. 63] of Byte;           // ��Byte����ת��Unicode��������
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
	ULONG Color;//���ӡ��������ɫ�ȼ�0=�� 1=�� 2=�� 3=����
//	BYTE HashNames[200][32];
//	BYTE HashIndexs[200];
//HashNames: array[0 .. 199] of array[0 .. 31] of Byte;
	// ��ά���� ����200*32��Byteռ�ӾͿ�����
//HashIndexs: array[0 .. 199] of Byte;
	// 200��Byte ��Щ���Ƿ�����ԵĹ۲���Ϣ ��Ȼռ�ռ䵫��û�취 ��Ȼ���Ժ��鷳
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
	ULONG ServiceID;                  // ����ID CALL���õ�
	ULONG Count;					  // ����
	ULONG MaxCount;                   //�������
	BYTE InterfaceName[192];		  // ������
	BYTE Special[8];				  // ǰ׺����  "xx��"��һ�� "xx֮"��һ��
	BYTE Name[64];					  // ��Ʒ��
	ULONG Color;					  // ��ɫ
	ULONG Width;					  // ռ�ñ������
	ULONG Height;					  // ռ�ñ����߶�
	ULONG Left;						  // �ڱ�����Xλ��
	ULONG Top;						  // �ڱ�����Yλ��
	ULONG Sockets[6];
	BYTE  SocketsContact[6];          //��������Ϣ
	BYTE IsEquipment; // �Ƿ���װ�� 0=��  1=��
	BYTE IsIdentity; // �Ƿ�δ���� 0=δ���� 1=�Ѽ���
	ULONG Quality; // Ʒ��
	ULONG Stats[20];
	// �������꾭����Ʒ���Ѿ�ˢ�µ������ı�����Ҫ��������Ҫ��CALL
	BYTE StatDescriptions[14][32];  //14x32�ֽڵĽṹ
};
#pragma pack (pop)

struct  ItemList
{
	ULONG Mem;
	ULONG WinID;                         // ����ID CALL����õ�
	SItemInfo Items[200]; // ��Ʒ����
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