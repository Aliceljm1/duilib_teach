/*
* 动态列表demo，
*/
#include "ListMainForm.h"
#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//加载资源包，可以解压之后查看里面的xml，png等等。

	ListMainForm* pFrame = new ListMainForm();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	//创建窗口，包括各种窗口属性，和扩展属性



	pFrame->CenterWindow();//居中窗口位置

	::ShowWindow(*pFrame, SW_SHOW);//显示窗口

	CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

	return 0;
}
