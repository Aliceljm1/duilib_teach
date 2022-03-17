/*
* 动态列表demo，
*/
#include "StdAfx.h"
#include "ErrorMainForm.h"
#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"
#include "StackWalker.h"

#include <imagehlp.h>
#include <stdlib.h>
#pragma comment(lib, "dbghelp.lib")


using namespace DuiLib;


class MyStackWalker : public StackWalker
{
public:
	MyStackWalker() : StackWalker()
	{
		m_info = "";
	}

	string m_info;

	virtual void OnOutput(LPCSTR szText) {
		printf(szText);
		m_info.append(szText);
		StackWalker::OnOutput(szText);
	}
};


string dumpname = "";
inline BOOL isDataSectionNeeded(const WCHAR* pModuleName)
{
	if (pModuleName == 0)
	{
		return FALSE;
	}

	WCHAR szFileName[_MAX_FNAME] = L"";
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);

	if (_wcsicmp(szFileName, L"ntdll") == 0)
		return TRUE;

	return FALSE;
}

inline BOOL CALLBACK miniDumpCallback(PVOID pParam,
	const PMINIDUMP_CALLBACK_INPUT   pInput,
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
	if (pInput == 0 || pOutput == 0)
		return FALSE;

	switch (pInput->CallbackType)
	{
	case ModuleCallback:
		if (pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
			if (!isDataSectionNeeded(pInput->Module.FullPath))
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);

	case IncludeModuleCallback:
	case IncludeThreadCallback:
	case ThreadCallback:
	case ThreadExCallback:
		return TRUE;

	default:;
	}

	return FALSE;
}

//创建Dump文件
inline void createMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName)
{
	HANDLE hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = pep;
		mdei.ClientPointers = FALSE;
		MINIDUMP_CALLBACK_INFORMATION mci;
		mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)miniDumpCallback;
		mci.CallbackParam = 0;
		MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)0x0000ffff;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &mdei, NULL, &mci);

		CloseHandle(hFile);
	}
}

void myPurecallHandler(void)
{
	{//方案一
		//MyStackWalker sw;
		//sw.ShowCallstack();
		//MessageBox(NULL, sw.m_info.c_str(), sw.m_info.c_str(), NULL);
		//exit(0);
	}
	
	{//方案二
		createMiniDump(NULL, "ErrorDemo.dmp");
		MessageBox(NULL, "抱歉软件出现了异常，请检查是否被弹窗拦截类软件拦截","出现异常", NULL);
		exit(0);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	_set_purecall_handler(myPurecallHandler);//增加纯虚函数捕获函数，使用stackwalker

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//加载资源包，可以解压之后查看里面的xml，png等等。

	ListMainForm* pFrame = new ListMainForm();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	//创建窗口，包括各种窗口属性，和扩展属性

	char* s = new char[5];
	strcpy(s, "abc00");

	pFrame->CenterWindow();//居中窗口位置

	::ShowWindow(*pFrame, SW_SHOW);//显示窗口

	CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

	return 0;
}
