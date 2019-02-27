#include "StdAfx.h"
#include "ListMainForm.h"
#include "MenuWnd.h"


#include <objbase.h>   //思考此处为何把#include分段
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>


using namespace DuiLib;

#define TIMER_ID_TEST 100
#define TIMER_TIME_TEST 1000

/*
* 存放第二列数据
*/
std::vector<std::string> domain;

/*
* 存放第三列数据
*/
std::vector<std::string> desc;



/**
初始化UI控件
*/
void ListMainForm::Init()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	//static_cast 强制类型转换，_T 可以搜索文档16.2小节

	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pSearch = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_search")));
}

/**
*这是一个全局测试函数，不属于ListMainForm类。
*一个类里面的函数应该和类密切相关，不相干的函数需要抽出到其他类或者Utils中
*
*/
void TestMemoryFunc()
{
	int* array = new int[10]; //使用vs提供的内存查看工具可以得知 数组的内存是连续的，可以通过memset来统一初始化内存
	memset(array, 0x0F, sizeof(int) * 10);


	char chInput[512];
	sprintf(chInput, "int:%d\n", array[0]);//手动修改内存， 请将array中的第一个数字大小修改为15，
	DUITRACE(_T("array---[0]: %s"), chInput);//注意用此方法可以输出信息到vs的调试窗口中

	//OutputDebugString(chInput);

	//TestMem* m;
	//for (int i = 0; i < 190464; i++) {
	//	m =new  TestMem;
	//	m->count = 15;
	//}
}

DWORD WINAPI ListMainForm::Search(LPVOID lpParameter)
{
	TestMemoryFunc();

	try
	{
		struct Prama* prama = (struct Prama *)lpParameter;//指针类型转换，从void* 转换为目标指针类型
		CListUI* pList = prama->pList;
		CButtonUI* pSearch = prama->pSearch;
		CDuiString tDomain = prama->tDomain;
		//-------------------------------------
		/*
		* 添加数据循环
		*/
		for (int i = 0; i < 100; i++)
		{
			std::stringstream ss;//使用stringstream方便字符串拼接 
			ss << "www." << i << ".com";
			domain.push_back(ss.str());
			ss.clear();
			ss << "it's " << i;
			desc.push_back(ss.str());
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(i);
			if (pListElement != NULL)
			{
				::PostMessage(prama->hWnd, WM_ADDLISTITEM, 0L, (LPARAM)pListElement);
			}
			/*
			*	Sleep 为了展示添加的动态效果，故放慢了添加速度，同时可以看到添加过程中界面仍然可以响应
			*/
			::Sleep(100);
		}

		delete prama;//一定要删除这个变量，否则会造成内存泄漏，new Prama和delete要成对出现


		pSearch->SetEnabled(true);
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}

/***
*课程1 修改皮肤xml文件,对照“属性列表.xml”学习当前皮肤中使用了哪些属性和控件
自行修改属性，观察结果，查找并解答注释中的TODO和提问
*/


/***
*课程2 编写函数在点击search按钮之后当前窗口围绕左上角旋转，旋转半径为50，考虑多线程，定时器
*/


/**
* 课程3，学习布局，将《duilib入门和xml培训布局案例》文件夹中的布局文件全部拷贝到skin\\ListRes\\中，
然后修改 	CDuiString GetSkinFile() 的代码来切换布局文件，
要求自己编写要给复杂的包含垂直布局，水平布局组合的Ui文件，同时修改窗口圆角，等等熟悉，发挥自己的创作醒性
*/

/***
* 课程4 ,模拟qq，或者微信登陆窗口输入用户名密码，请求web接口，验证用户名密码，然后校验

自行安装node.js客户端，下载代码运行：
https://github.com/Aliceljm1/NodeDemo.git

自行搜索互联网资源查找libcurl的用发，发送HTTP请求
https://gitee.com/search?utf8=%E2%9C%93&q=libcurl++demo&type=


*/


/***
*课程5，改用http://localhost:8081/autologin接口登陆，解析出用户信息用CUserInfo模型装载，相关解析代码放到CUserControler中，然后创建新的窗口显示这些信息
其他字段自己完善，要求新的窗口需要继承WindowImplBase，而非CWindowWnd，仔细观察区别体会优点
CUserControler中的其他函数自己实现。仔细体会使用不同的类将各个抽象层次的逻辑代码拆分出来的好处。每一层只负责一个维度的逻辑，
每个层都很纯粹，可维护性，可复用性很强。

将之前的字符串操作方法，网络访问方法都重构到对应的utils类中，保持每个类的纯粹性
*/


/*****
*课程6练习抽出dll.lib库，分模块开发，将model和controler层分别拆分出lib，和dll调用。学会模块化开发
参考： vs关键配置相关信息.docx
*/


/*****
*课程7练习使用sqlite数据库，将登陆成功之后服务端返回的数据存储到数据库中使用（\3rd\sqlite\sqlite3.lib）
下次启动软件自动读取数据库中的登陆历史记录，供用户选择点击直接登陆。 
*/

/***
*课程8学习wtest项目中的语法知识
*/


void ListMainForm::OnSearch()
{

	struct Prama *prama = new Prama;

	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist"))); //提问： 此处可以如何优化？
	CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("input")));
	pEdit->SetEnabled(false);
	CDuiString input = pEdit->GetText();
	m_pSearch->SetEnabled(false);//提问：此处为何要SetEnabled(false);？
	pList->RemoveAll();
	domain.empty();
	domain.resize(0);
	desc.empty();
	desc.resize(0);
	DWORD dwThreadID = 0;
	pList->SetTextCallback(this);//[1]

	prama->hWnd = GetHWND();//给结构体赋值，用结构体传递参数的好处是：当要增加或者删除一个参数的时候可以直接修改结构体
	prama->pList = pList;
	prama->pSearch = m_pSearch;
	prama->tDomain = input;

	//开启线程进入线程执行函数，search,
	HANDLE hThread = CreateThread(NULL, 0, &ListMainForm::Search, (LPVOID)prama, 0, &dwThreadID);
}

/*
* 关键的回调函数，IListCallbackUI 中的一个虚函数，渲染时候会调用,在[1]中设置了回调对象
*/
LPCTSTR  ListMainForm::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	switch (iSubItem)
	{
	case 0:
		_stprintf(szBuf, _T("%d"), iIndex);
		break;
	case 1:
	{
#ifdef _UNICODE		
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, domain[iIndex].c_str());
#endif
	}
	break;
	case 2:
	{
#ifdef _UNICODE		
		int iLen = desc[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, desc[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, desc[iIndex].c_str());
#endif
}
	break;
	}
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}


/**
* DUI框架内部定义的消息回调函数，消息体TNotifyUI包括一个消息很自然的一些属性如消息的类型，
消息的发送者，消息发生的时间，消息发生时候鼠标的位置等等， 可以在此处打上断点，查看dui消息流转顺序
*/
void  ListMainForm::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
		OnPrepare(msg);
	else if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pCloseBtn)
		{
			PostQuitMessage(0);
			return;
		}
		else if (msg.pSender == m_pMinBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return;
		}
		else if (msg.pSender == m_pRestoreBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return;
		}
		else if (msg.pSender == m_pSearch)
		{
			OnSearch();
		}
	}
	else if (msg.sType == _T("setfocus"))
	{
	}
	else if (msg.sType == _T("itemclick"))
	{
	}
	else if (msg.sType == _T("itemactivate"))
	{
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
#ifdef _UNICODE		  //思考此处宏定义的目的是什么，
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		sMessage += lpText;
		delete[] lpText;
#else
		sMessage += domain[iIndex].c_str();//此处参详c++运算符重载，代码	CDuiString CDuiString::operator+(LPCTSTR lpStr) const

#endif
		::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);
	}
	else if (msg.sType == _T("menu"))
	{
		if (msg.pSender->GetName() != _T("domainlist")) return;
		CMenuWnd* pMenu = new CMenuWnd();
		if (pMenu == NULL) { return; }
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		::ClientToScreen(*this, &pt);//当前窗口坐标转换为系统坐标，相当于局部坐标系转换为绝对坐标系。
		pMenu->Init(msg.pSender, pt);
	}
	else if (msg.sType == _T("menu_Delete")) {
		CListUI* pList = static_cast<CListUI*>(msg.pSender);
		int nSel = pList->GetCurSel();//dui提供的快捷方法，
		if (nSel < 0) return;
		pList->RemoveAt(nSel);
		domain.erase(domain.begin() + nSel);//请思考此处为何要删除domain内数据
		desc.erase(desc.begin() + nSel);
	}
}

LRESULT  ListMainForm::OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist")));
	if (pList) pList->Add(pListElement);
	return 0;
}

/***
*以下部分代码来自WindowImplBase::OnCreate， 可以了解最原始的窗口建立过程
*/
LRESULT  ListMainForm::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	CDialogBuilder builder;
	CDuiString strResourcePath = m_pm.GetResourcePath();
	if (strResourcePath.IsEmpty())
	{
		strResourcePath = m_pm.GetInstancePath();
		strResourcePath += GetSkinFolder().GetData();
	}
	m_pm.SetResourcePath(strResourcePath.GetData());

	m_pm.Init(m_hWnd);
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();

	SetTimer(this->m_hWnd, TIMER_ID_TEST, TIMER_TIME_TEST, 0);

	return 0;
}



/***
可以使用内存诊断工具（调试，窗口，显示诊断工具）清晰的看到内存只增不减的情形
*/
void ListMainForm::onTimerTest()
{
	void * ptr = malloc(1024 * 1024);

	Sleep(10);//注释以下三句
	if (ptr)
		free(ptr);
}


void ListMainForm::OnTimer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case TIMER_ID_TEST:
	{
		onTimerTest();
		break;
	}
	default:
		break;
	}
}


LRESULT  ListMainForm::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

/**
*大小改变的回调函数，可以尝试注释，修改代码 看效果
*/
LRESULT  ListMainForm::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };
		HRGN hRgn1 = ::CreateRectRgnIndirect(&rc);
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);
		::CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);
		::SetWindowRgn(*this, hRgn1, TRUE);
		::DeleteObject(hRgn1);
		::DeleteObject(hRgn2);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT  ListMainForm::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT  ListMainForm::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(true);
		}
		else {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;
}

/***
* 处理来着windows系统的各种消息，WM= windows  message
*/
LRESULT  ListMainForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_ADDLISTITEM:   lRes = OnAddListItem(uMsg, wParam, lParam, bHandled); break;
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_TIMER:
	{
		OnTimer(wParam, lParam);
		break;
	}
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

/****
提问：
1.请统计下执行search前后listdemo.exe的内存增长情况（）28
2.请自己添加一个内存泄漏的代码，在执行serarch之后内存占用超过1M，


*/