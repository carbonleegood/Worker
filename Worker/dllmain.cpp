// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <atlstr.h>
#ifdef VM_PROTECT
#include "VMProtectSDK.h"
#pragma optimize( "g", off )
#endif
bool bInit = false;
TCHAR szModulePath[MAX_PATH] = { 0 };
extern void InitCore();
LONG WINAPI TopLevelUnhandleExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
#ifdef VM_PROTECT
	VMProtectBegin("WorkerDllMain");
#endif
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!bInit)
		{
			GetModuleFileName(hModule, szModulePath, MAX_PATH);
			PathRemoveFileSpec(szModulePath);
		//	::MessageBoxA(0, "z注入", "提示", 0);
			bInit = true;
			InitCore();
			::SetUnhandledExceptionFilter(TopLevelUnhandleExceptionFilter);
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
#ifdef VM_PROTECT
	VMProtectEnd();
#endif
	return TRUE;
}

#ifdef VM_PROTECT
#pragma optimize( "g", on )
#endif