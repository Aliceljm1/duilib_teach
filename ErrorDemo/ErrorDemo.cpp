#include "stdafx.h"
#include "ErrorDemo.h"
#include "ErrorMainForm.h"
#include <thread>


class InFo {
public:
	string* m_p_data;
	string  m_data;

	InFo()
	{
		m_data = "data";
		m_p_data = &m_data;
	}

	~InFo()
	{
		m_p_data = NULL;
	}

	int test()
	{
		return m_p_data->length();
	}

};

class Task
{
public:
	void operator()(void * uiWindow)
	{
		for (int i = 0; i < 1000; i++) {
			ListMainForm* info = (ListMainForm*)uiWindow;
			info->ChangeButtonName();
		}
	}
};

//�����ܶຯ�����ص�ָ��ȷʵ����ΪNULL
static int g_createCount = 1;
InFo* CreateDemo()
{
	if (g_createCount++ % 2 == 0)
		return NULL;
	return new InFo();
}

InFo* CreateDemoWithObj()
{
	InFo f;
	return &f;//�и��ʵĻ���ֿ�ָ�����Ұָ�룬��Ϊf�����ڱ���������֮��ᱻ���٣������ڴ治һ����ʱ����
}


ErrorDemo::ErrorDemo() :
	info("abc")
{
}

void ErrorDemo::nullPointer()
{
	InFo* demo = CreateDemo();
	demo->test();//����д��

	// ��ȷд��������ָ��ĺ���������ԶҪ���ǿ��ж���
	//if (demo)demo->test();

	InFo* demo2 = CreateDemoWithObj();
	demo2->test();
}


void ErrorDemo::errorPointer()
{
	InFo* pointer = NULL;
	{
		InFo test;
		pointer = &test;//����������֮����Զ�ִ��������������ʱָ����Ȼ��ֵ������ָ��Ķ����Ѿ����ƻ���
	}
	int len = pointer->test();//Ӧ�����յ�ǰָ��ָ�������������ڣ��κζ��������������� �����������ڰ�ȫ��ʹ��
}

//�������̲߳���UIԪ�أ���ʱ����رմ��ڻ���UI�߳�ͬ������UIԪ�ػᵼ�±�������
void ErrorDemo::notUIThreadError(void* uiWindow)
{
	Task task;
	std::thread t(task, uiWindow);
	t.detach();
}

int foo()
{
	return foo();
}

void ErrorDemo::stackOverFlow()
{
	int array[1000000];//ֱ�����볬���ڴ���ջ�ڴ棬�����ڴ治�㣬
	// ȫ�ֱ�����new�����Ķ���malloc�洢�ڶ��ڴ棬������һ������¶��Ǵ洢��ջ�ڴ�

	int* p = (int*)malloc(1000000 * sizeof(int));//ע����һ�У�������ִ�����

	foo();//ѭ�����ú���������ջ�ڴ治�㣬���ú�����ִ��ѹջ��ջ��������ջ�ڴ�

}


void ErrorDemo::windowsError(HDC hDC)
{
	for (int i = 0; i < 10000; i++) {
		HDC hCloneDC = ::CreateCompatibleDC(hDC);
	}
	MessageBox(NULL,"��������޷�����","��������޷�����",NULL);
	//gdi����ռ�ó���ϵͳ���Ƶ�1�����ֱ�ӵ���UI�쳣������ͨ������������鿴ÿ�����̵�gdi�������
}

void ErrorDemo::sehDemo()
{
	this->info.length();//û�о������캯��һ���ᱨ��

	int a = 0, b = 0;
	__try {
		b = 5 / a;
	}

	__except (EXCEPTION_EXECUTE_HANDLER) {
		MessageBox(NULL, "exception", "exception", NULL);
	}
}
