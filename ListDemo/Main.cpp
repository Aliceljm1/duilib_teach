/*
* ��̬�б�demo��
*/
#include "ListMainForm.h"
#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//������Դ�������Խ�ѹ֮��鿴�����xml��png�ȵȡ�

	ListMainForm* pFrame = new ListMainForm();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	//�������ڣ��������ִ������ԣ�����չ����



	pFrame->CenterWindow();//���д���λ��

	::ShowWindow(*pFrame, SW_SHOW);//��ʾ����

	CPaintManagerUI::MessageLoop();//����duilib����Ϣѭ����ͨ��������Windows�ǻ�����Ϣ���ƵĲ���ϵͳ

	return 0;
}
