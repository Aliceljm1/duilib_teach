/*
* ��̬�б�demo��
*/
#include "StdAfx.h"
#include "ErrorMainForm.h"
#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"
#include "StackWalker.h"

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

void myPurecallHandler(void)
{
	MyStackWalker sw;
	sw.ShowCallstack();
	MessageBox(NULL, sw.m_info.c_str(), sw.m_info.c_str(), NULL);
	exit(0);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	_set_purecall_handler(myPurecallHandler);//���Ӵ��麯����������

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//������Դ�������Խ�ѹ֮��鿴�����xml��png�ȵȡ�

	ListMainForm* pFrame = new ListMainForm();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	//�������ڣ��������ִ������ԣ�����չ����

	char* s = new char[5];
	strcpy(s, "abc00");

	pFrame->CenterWindow();//���д���λ��

	::ShowWindow(*pFrame, SW_SHOW);//��ʾ����

	CPaintManagerUI::MessageLoop();//����duilib����Ϣѭ����ͨ��������Windows�ǻ�����Ϣ���ƵĲ���ϵͳ

	return 0;
}
