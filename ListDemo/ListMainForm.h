#pragma once

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

	CDuiString GetSkinFolder();
	CDuiString GetSkinFile();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;

	static DWORD WINAPI Search(LPVOID lpParameter);
	void OnSearch();
	void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND /*hWnd*/);
	void Init();

	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void					OnPrepare(TNotifyUI& msg);
	void					OnTimerTest();
	void				   OnTimer(WPARAM wParam, LPARAM lParam); //定时器
public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pCloseBtn;  //此处成员变量用m_ 开头，请务必准守，不对外暴露的成员一律用private修饰
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    CButtonUI* m_pSearch;

};
