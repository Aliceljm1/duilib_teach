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

//举例很多函数返回的指针确实可能为NULL
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
	demo->test();//错误写法

	// 正确写法，返回指针的函数代码永远要做非空判定，
	//if (demo)demo->test();

}


void ErrorDemo::errorPointer()
{
	InFo* pointer = NULL;
	{
		InFo test;
		pointer = &test;//超过作用域之后会自动执行析构函数，此时指针虽然有值，但是指向的对象已经被破坏了
	}
	int len = pointer->test();//应当掌握当前指针指向对象的生命周期，任何对象有生既有死。 在生命周期内安全是使用
}

//开启多线程操作UI元素，此时如果关闭窗口或者UI线程同步操作UI元素会导致崩溃发生
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
	//创建

}

void ErrorDemo::sehDemo()
{
	this->info.length();//没有经过构造函数一定会报错

	int a = 0, b = 0;
	__try {
		b = 5 / a;
	}

	__except (EXCEPTION_EXECUTE_HANDLER) {
		MessageBox(NULL, "exception", "exception", NULL);
	}
}
