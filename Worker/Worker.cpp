// Worker.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FuncCore.h"
#include <tchar.h>
#include <process.h>
long OldProc = 0;
HWND hGameWnd = NULL;
bool bWindowExist = false;
void DispatchCall(WPARAM wParam, LPARAM lParam)
{
	FuncCode fun = (FuncCode)wParam;
	int nRet = 0;
	__try
	{
		switch (fun)
		{
		case F_MOVE:
			CallMove(MoveInfo.x, MoveInfo.y);
			break;
		case F_GetPlayerPos:
			ReadPosition(&PlayerPos.x, &PlayerPos.y);
			break;
		case F_GetPlayerInfo:
		{
								void* p = ReadSelfInfo();
								memcpy(&_PlayerInfo, p, sizeof(RoundObjInfo));
		}
			break;
		case F_GetMonsterList:
			break;
		case F_CastUntargetSkill:
			CallUnTargetSkill(untargetSkill.x, untargetSkill.y, untargetSkill.num, untargetSkill.type);
			break;
		case F_CastTargetSkill:
			CallTargetSkill(SkillTargetObjPtr, SkillNum, SkillModel);
			break;
		case F_GetRoundList:
			pRoundList = (RoundObjInfo*)ReadRoundInfo();
			break;
		case F_StopMove:
			ReadPosition(&PlayerPos.x, &PlayerPos.y);
			MoveInfo.x = PlayerPos.x*0.092;
			MoveInfo.y = PlayerPos.y*0.092;
			CallMove(MoveInfo.x, MoveInfo.y);
			break;
		case F_ActiveTarget:
			CallActiveNPC(ActiveObjPtr, 8);
			break;
		case F_GetWaypointInfo:
			pWaypointList = ReadTransportList();
			break;
		case F_Transport:
			CallTransport(TransMapID, TransWaypointID, nDungeonModel);
			break;
		case F_CreateNewDungeon:
			nRet = CallTransportSelect(0xFF);
			break;
		case F_GetBagItemList:
			pBag = (ItemList*)ReadItemList(ContainerType, &dwBagItemCount);
			break;
		case F_GetMapID:
			nRet = ReadCurrentMapID(&CurMapInfo);
			break;
		case F_GetTrophyInfo:
			ReadWorldItemInfo(NolootTrophyObjPtr, &_TrophyInfo);
			break;
		case F_GetLoginStatus:
			nLoginStatus = ReadUIState();
			break;
		case F_UseItem:
			nRet = CallUseItem(UseItem_WinID, UseItem_ServiceID);
			break;
		case F_ClickNPCMenu:
			nRet = CallClickNPCMenu(lParam);
			break;
		case F_PutToSell:
			CallPutToSell(SellLeft, SellTop, SellServiceID, SellWinID);
			break;
		case F_ConfirmSell:
			nRet = CallConfirmSell();
			break;
		case F_Logout:
			nRet = CallReturnChoseRole();
			break;
		case F_Relive:
			nRet = CallRelive(lParam);
			break;
		case F_Pickup:
			nRet = CallItemTakeUP(PickBagPtr, PicupServiceID);
			break;
		case F_DropDown:
			nRet = CallItemTakeDown(nStoragePageObjPtr, StorageLeft, StorageTop);
			break;
		case F_DropDownStack:
			nRet = CallItemTakeDownStack(nStoragePageObjPtr, TargetStackServiceID);
			break;
		case F_ActiveStoragePage:
			nRet = GetStoragePageInfo(StoragePageNum);
			break;
		case F_ReadStorageUI:
			ReadPageUIRet = ReadStorageUIPTR(lParam);
			break;
		case F_ReadStoragePageNum:
			StoragePageCount = ReadStoragePageCount();
			break;
		case F_IdentityItem:
			CallIdentify(1, IdentityCurrencyServiceID, 1, IdentityItemServiceID);
			break;
		case F_UpSkill:
			AutoSkillUp();
			break;
		case F_ItemOnMouse:
			nItemOnMouse = IsItemOnMouse();
			break;
		case F_BuffExist:
			nBuffExist = IsBuffExists(lParam);
			break;
		case F_GetItemDescrib:
			nRet = GetDescription(lParam);
			break;
		}
	}
	__except (1)
	{
		TCHAR szErrorBuff[32] = { 0 };
		wsprintf(szErrorBuff, L"%d", fun);
		MessageBox(NULL,L"程式異常,請截圖聯繫管理員",szErrorBuff,MB_OK);
	}
	if (nRet)
		nCallRet = SUCCESS;
	else
		nCallRet = 1;
}
LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_LG_CALL)
	{
		//MessageBox(NULL, L"hook", L"ddd", MB_OK);
		//::OutputDebugString(L"hook api");
		DispatchCall(wParam, lParam);
		return 0;
	}
	return CallWindowProc((WNDPROC)OldProc, hwnd, uMsg, wParam, lParam);
}
#ifdef VM_PROTECT
#include "VMProtectSDK.h"
#pragma optimize( "g", off )
#endif
BOOL HookWindowsProc(HWND hwnd)
{
#ifdef VM_PROTECT
	VMProtectBegin("HookWindowsProc");
#endif
	OldProc = GetWindowLong(hwnd, GWL_WNDPROC);
	if (SetWindowLong(hwnd, GWL_WNDPROC, (long)MsgProc) == 0) //子类化
	{
	//	::MessageBoxA(0,"安装失败,请重启!","提示",0);
		return FALSE;
	}
	//LogA("***找到主窗口了");
#ifdef VM_PROTECT
	VMProtectEnd();
#endif
	return TRUE;
}
void TUpdate();

void InitCore()
{
#ifdef VM_PROTECT
	VMProtectBegin("InitCore");
#endif
	//::MessageBox(NULL, _T("aaa"), NULL, MB_OK);
	InitGobalData();
	hGameWnd = ::FindWindow(L"Direct3DWindowClass", NULL);
	//hGameWnd = ::FindWindow(L"classFoxitReader", NULL);
	if (hGameWnd)
	{
		HookWindowsProc(hGameWnd);
	}
	else
	{
		::MessageBox(NULL, _T("未找到窗口"), NULL, MB_OK);
	}

	//建立通信
	HANDLE hThread =(HANDLE) _beginthreadex(NULL,NULL,ServerThread,NULL,NULL,0);
	CloseHandle(hThread);
#ifdef VM_PROTECT
	VMProtectEnd();
#endif
}
#ifdef VM_PROTECT
#pragma optimize( "g", on )
#endif
//void TUpdate()
//{
//	//验证心跳
////	::MessageBox(NULL, _T("开始"), NULL, MB_OK);
////	::MessageBox(NULL, _T("结束"), NULL, MB_OK);
//	::SendMessage(hGameWnd, WM_LG_CALL, F_UPDATE, NULL);
//
//
////	::EnterCriticalSection(&cs_core);
//	//eFuncCode = F_UPDATE;
////	::SleepConditionVariableCS(&cv_core,&cs_core,1000*60);
////	::LeaveCriticalSection(&cs_core);
//	return;//返回读取到的数据
//}