#include "stdafx.h"
#include "FuncCore.h"
#include <fstream>
#include <iostream>
#include <atlstr.h>
using namespace std;
//CAll调用全局变量区
HANDLE hEvent = NULL;

FP_SetIsDLl SetIsDLl;
FP_ReadMapData ReadMapData;
FP_ReadPosition ReadPosition;
FP_ReadRoundInfo ReadRoundInfo;
FP_ReadSelfInfo ReadSelfInfo;
FP_CallMove CallMove;
FP_CallUnTargetSkill CallUnTargetSkill;
FP_CallTargetSkill CallTargetSkill;
FP_CallActiveNPC CallActiveNPC;
FP_CallTransport CallTransport;
FP_CallTransportSelect CallTransportSelect;
FP_ReadTransportList ReadTransportList;
FP_ReadItemList ReadItemList;
FP_ReadCurrentMapID ReadCurrentMapID;
FP_ReadWorldItemInfo ReadWorldItemInfo;
FP_ReadUIState ReadUIState;
FP_CallUseItem CallUseItem;
FP_CallClickNPCMenu CallClickNPCMenu;
FP_CallPutToSell CallPutToSell;
FP_CallConfirmSell CallConfirmSell;
FP_CallReturnChoseRole CallReturnChoseRole;
FP_CallRelive CallRelive;
FP_CallItemTakeUP CallItemTakeUP;
FP_CallItemTakeDown CallItemTakeDown;
FP_GetStoragePageInfo GetStoragePageInfo;
FP_ReadStorageUIPTR ReadStorageUIPTR;
FP_ReadStoragePageCount ReadStoragePageCount;
FP_CallItemTakeDownStack CallItemTakeDownStack;
FP_CallIdentify CallIdentify;
FP_AutoSkillUp AutoSkillUp;
FP_IsBuffExists IsBuffExists;
FP_IsItemOnMouse IsItemOnMouse;
FP_GetDescription GetDescription;
FP_ReadNPCMenu ReadNPCMenu;
FP_ReadHideoutServiceID ReadHideoutServiceID;
FP_CallTransHidout CallTransHidout;
FP_CallClickItem CallClickItem;
FP_CallCtrlMoveItem CallCtrlMoveItem;
FP_CallLButtonUP CallLButtonUP;
FP_CallYHOpen CallYHOpen;
int DrawMap(unsigned char* p, DWORD x, DWORD y);
extern TCHAR szModulePath[MAX_PATH];
#ifdef VM_PROTECT
#include "VMProtectSDK.h"
#pragma optimize( "g", off )
#endif
bool InitGobalData()
{
#ifdef VM_PROTECT
	VMProtectBegin("InitGobalData");
#endif
	FP_GetCallAddr GetCallAddr;
	//HMODULE hDll=::LoadLibrary(_T("E:\\流亡暗道\\Worker\\Debug\\mem.dll"));
	CString strDll = szModulePath;
	strDll += _T("\\mem.dll");
	HMODULE hDll = ::LoadLibrary(strDll.GetBuffer());
	if (!hDll)
		return false;
	GetCallAddr = (FP_GetCallAddr)GetProcAddress(hDll, "UnixTimeStamp");
//	CallTransport = (FP_CallTransport)GetProcAddress(hDll, "FZ_CallTransport");
	if (!GetCallAddr)
		return false;
	int* p = GetCallAddr(888);
	if (!p)
		return false;
	SetIsDLl = (FP_SetIsDLl)(*(p + 1));
	//p += 2;
	ReadMapData = (FP_ReadMapData)(*(p+2));

	ReadPosition = (FP_ReadPosition)(*(p + 3));

	ReadRoundInfo = (FP_ReadRoundInfo)(*(p + 4));

	ReadSelfInfo = (FP_ReadSelfInfo)(*(p + 5));

	ReadTransportList = (FP_ReadTransportList)(*(p + 6));

	ReadItemList = (FP_ReadItemList)(*(p + 7));

	ReadCurrentMapID = (FP_ReadCurrentMapID)(*(p + 8));

	ReadWorldItemInfo = (FP_ReadWorldItemInfo)(*(p + 9));

	ReadUIState = (FP_ReadUIState)(*(p + 10));

	ReadStorageUIPTR = (FP_ReadStorageUIPTR)(*(p + 13));

	ReadStoragePageCount = (FP_ReadStoragePageCount)(*(p + 14));

	AutoSkillUp = (FP_AutoSkillUp)(*(p + 16));

	IsBuffExists = (FP_IsBuffExists)(*(p + 17));

	IsItemOnMouse = (FP_IsItemOnMouse)(*(p + 18));

	ReadNPCMenu = (FP_ReadNPCMenu)(*(p + 19));

	ReadHideoutServiceID = (FP_ReadHideoutServiceID)(*(p + 20));
	

	CallMove = (FP_CallMove)(*(p + 66));

	CallUnTargetSkill = (FP_CallUnTargetSkill)(*(p + 102));

	CallActiveNPC = (FP_CallActiveNPC)(*(p + 203));

	CallTransport = (FP_CallTransport)(*(p + 204));
	
	CallUseItem = FP_CallUseItem(*(p + 205));

	CallClickNPCMenu = (FP_CallClickNPCMenu)(*(p + 206));

	CallPutToSell = (FP_CallPutToSell)(*(p + 207));

	CallConfirmSell = (FP_CallConfirmSell)(*(p + 208));

	CallReturnChoseRole = (FP_CallReturnChoseRole)(*(p + 209));

	CallRelive = (FP_CallRelive)(*(p + 210));

	CallItemTakeUP = (FP_CallItemTakeUP)(*(p + 211));

	CallItemTakeDown = (FP_CallItemTakeDown)(*(p + 212));

	GetStoragePageInfo = (FP_GetStoragePageInfo)(*(p + 213));

	CallTransportSelect = (FP_CallTransportSelect)(*(p + 214));

	CallTargetSkill = (FP_CallTargetSkill)(*(p + 215));

	CallItemTakeDownStack = (FP_CallItemTakeDownStack)(*(p + 216));

	CallIdentify = (FP_CallIdentify)(*(p + 218));

	GetDescription = (FP_GetDescription)(*(p + 219));

	CallTransHidout=(FP_CallTransHidout)(*(p+220));

	CallClickItem=(FP_CallClickItem)(*(p+221));

	CallCtrlMoveItem = (FP_CallCtrlMoveItem)(*(p + 222));
	
	CallLButtonUP = (FP_CallLButtonUP)(*(p + 223));

	CallYHOpen = (FP_CallYHOpen)(*(p + 224));

	SetIsDLl(TRUE);
#ifdef VM_PROTECT
	VMProtectEnd();
#endif
	return true;
}
#ifdef VM_PROTECT
#pragma optimize( "g", on )
#endif
//void MYTrancport(ULONG MapID, ULONG WaypointID)
//{
//	//_asm
//	//{
//	//	mov ecx, GAMEBASE
//	//	mov ecx, [ecx];
//	//	mov ebx, [ecx + ENTERGAME_CALLPARAM];
//	//	push RoleNum;
//	//	mov al, 0;//角色序号
//	//	//	mov BYTE PTR ds:[0x8e9612],0;
//	//	mov edi, CALLADDR_ENTERGAME;
//	//	call edi;
//	//}
//	CallTransport(0x235c, WaypointID);
//	__try
//	{
//		HANDLE hModule = ::GetModuleHandleA("PathOfExile.exe");
//		DWORD dwBaseAddr = (DWORD)hModule;
//
//		DWORD dwFunc = dwBaseAddr + 0x456770;
//		DWORD param = dwBaseAddr + 0x87A838;
//		DWORD ff = (DWORD)CallTransport;
//		__asm
//		{
//			mov ecx, param;
//			mov esi, [ecx];
//		//	mov esi, [param];
//			mov esi, [esi + 140];
//			mov ecx, WaypointID;//传送阵ID
//			push 0x235C;  //目标地图ID
//			mov edi, dwFunc;
//			call edi; //传送CALL地址
//		}
//	}
//	__except (1)
//	{
//	//	LogA("FClickUI Error");
//	}
//}
int DrawMap(unsigned char* p,DWORD x,DWORD y,DWORD halfX)
{
	fstream file;
	CString strPath = szModulePath;
	strPath += L"\\nnnn.bat";
//	file.open("d:\\map.txt", ios::out | ios::binary);
	file.open(strPath, ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "打开文件失败!" << endl;
		return 0;
	}
	short lineX = x;
	short rowY = y;


	file.write((char*)&lineX, sizeof(short));
	file.write((char*)&rowY, sizeof(short));
	char* buff = new char[lineX];
	for (int i = 0; i < rowY; ++i)
	{
		memset(buff, 0, lineX);
		for (int j = 0; j < lineX; ++j)
		{
			unsigned char* pBase = p + halfX*i + j / 2;
			if (j % 2)
			{
				buff[j] = (*pBase) & 0xE0;
				if (buff[j])
					buff[j] = 1;
			}
			else
			{
				buff[j] = (*pBase) & 0xE;
				if (buff[j])
					buff[j] = 1;
			}
		}
		file.write(buff, lineX);

	}
	file.flush();
	file.close();
	return 0;
}