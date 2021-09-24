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

InFo* CreateDemoWithObj()
{
	InFo f;
	return &f;//有概率的会出现空指针或者野指针，因为f对象在本函数结束之后会被销毁，但是内存不一定及时回收
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

	InFo* demo2 = CreateDemoWithObj();
	demo2->test();
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

int foo()
{
	return foo();
}

void ErrorDemo::stackOverFlow()
{
	int array[1000000];//直接申请超大内存在栈内存，导致内存不足，
	// 全局变量、new出来的对象、malloc存储在堆内存，其他的一般情况下都是存储到栈内存

	int* p = (int*)malloc(1000000 * sizeof(int));//注释上一行，看本行执行情况

	foo();//循环调用函数，导致栈内存不足，调用函数会执行压栈出栈，会消耗栈内存

}


void ErrorDemo::windowsError(HDC hDC)
{
	for (int i = 0; i < 10000; i++) {
		HDC hCloneDC = ::CreateCompatibleDC(hDC);
	}
	MessageBox(NULL,"这个弹窗无法弹出","这个弹窗无法弹出",NULL);
	//gdi对象占用超过系统限制的1万个，直接导致UI异常，可以通过任务管理器查看每个进程的gdi对象个数
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
