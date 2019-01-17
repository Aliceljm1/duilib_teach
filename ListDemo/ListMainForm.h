#pragma once

/*
* Code By Tojen (qq:342269237)
* 界面设计图片资源80%原创，布局完全原创,学习作品，不好请拍砖
*/
#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>

#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;


#define WM_ADDLISTITEM WM_USER + 50


/*
*  线程函数中传入的结构体变量，使用线程为了使界面线程立即返回，防止卡住，你们懂得。
*/
struct Prama
{
	HWND hWnd;
	CListUI* pList;
	CButtonUI* pSearch;
	CDuiString tDomain;
};

struct TestMem {
	int count;
};


class ListMainForm : public CWindowWnd, public INotifyUI, public IListCallbackUI
{
public:
    ListMainForm() {
    };

	CDuiString GetSkinFolder()
	{

		return _T("skin\\ListRes\\");
	}

	/**
	* 课程三，学习布局，将《duilib入门和xml培训布局案例》文件夹中的布局文件全部拷贝到skin\\ListRes\\中，
	然后修改此代码来切换布局文件，
	要求自己编写要给复杂的包含垂直布局，水平布局组合的Ui文件，同时修改窗口圆角，等等熟悉，发挥自己的创作醒性
	*/
	CDuiString GetSkinFile()
	{
		return _T("skin.xml");
		//return _T("1.xml");
	}

    LPCTSTR GetWindowClassName() const 
    { 
        return _T("ScanMainForm"); 
    };

    UINT GetClassStyle() const
    { 
        return CS_DBLCLKS; 
    };

    void OnFinalMessage(HWND /*hWnd*/) 
    { 
        delete this;
    };

	void Init();

    void OnPrepare(TNotifyUI& msg) 
    {

    }

	static DWORD WINAPI Search(LPVOID lpParameter);
	
	void OnSearch();
 
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);

	void Notify(TNotifyUI& msg);

	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }
	void					onTimerTest();
	void				  OnTimer(WPARAM wParam, LPARAM lParam); //定时器

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ::PostQuitMessage(0L);
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if( ::IsIconic(*this) ) bHandled = FALSE;
        return (wParam == 0) ? TRUE : FALSE;
    }

    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	*大小改变的回调函数，可以尝试注释，修改代码 看效果
	*/
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/***
	* 处理来着windows系统的各种消息，WM= windows  message
	*/
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pCloseBtn;  //此处成员变量用m_ 开头，请务必准守，不对外暴露的成员一律用private修饰
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    CButtonUI* m_pSearch;

};
