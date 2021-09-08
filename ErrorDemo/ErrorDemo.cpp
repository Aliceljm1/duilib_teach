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

void ErrorDemo::stackOverFlow()
{

}

void ErrorDemo::notInit()
{
	//����

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
