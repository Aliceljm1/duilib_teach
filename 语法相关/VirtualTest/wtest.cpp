/***
*wtest.cpp: 虚析构函数的作用，virtual关键字的使用
参考资料：
https://www.cnblogs.com/hushpa/p/5707475.html
https://www.cnblogs.com/lit10050528/p/3874703.html

@author bxd
*/ 

#include "stdafx.h"

class A1 {
public:
	A1(void)
	{	 
		printf_s("A1()\n");
	}
	virtual ~A1(void)
	{
		printf_s("~A1\n");
		PrintText();
	}

public:
	virtual void PrintText()
	{
		printf_s("A1 print!\n");
	}

	void TestPrint()
	{
		PrintText();
	}

	void TestFunc()
	{
		printf_s("A1 TestFunc\n");
	}

};

class B1 :public A1 {

public:
	B1(void)
	{
		printf_s("B1()\n");
	}
	~B1(void)
	{
		printf_s("~B1\n");
	}
public:
	//如果确定是重新基类函数，需要写override关键字明确标识
	virtual void PrintText() override
	{
		printf_s("B1! print\n");
	}

	void TestFunc()  
	{
		printf_s("B1 TestFunc\n");
	}

};

class A2 {
public:
	A2(void) {	 
		printf_s("A2\n");
	}
	virtual	~A2(void) //请删除virtual 关键字做测试
	{
		printf_s("~A2\n");
		PrintText();
	}

public:
	virtual void PrintText()
	{
		printf_s("A2 print!\n");
	}

	void TestPrint()
	{
		PrintText();
	}

};

class B2 :public A2 {

public:
	B2(void)
	{
		printf_s("B2()\n");
	}
	~B2(void)
	{
		printf_s("~B2\n");
	}
public:
	virtual void PrintText() override
	{
		printf_s("B2! print\n");
	}

};

int main()
{
	A1* b1 = new B1();		//打印A1() B1()
	b1->PrintText();		//打印 B1!Print
	b1->TestPrint();		//打印 B1!Print
	b1->TestFunc();		//打印A1 TestFunc
	static_cast< B1*>(b1)->TestFunc();//打印 B1 TestFunc

	delete b1;				//打印 ~B1 \n ~A1 \n A!Print
	//结论 1.虽然在A1类中调用PrintText可以调用B1类重写的PrintText方法,但是在A1类的析构函数中无法调用B1类的析构函数（原因如下）
	//        2.创建某类对象会依次先调用基类的构造函数，最后调用子类的构造函数，于此对称的，在delete对象的时候会先调用子类的析构函数，最后依次调用基类的析构函数，
	//			3.要实现多态需要依赖virtual关键字
	printf_s("----------------\n");
	A2* b2 = new B2();		//打印 B2() \n
	delete b2;				//打印 A2 print!
	//结论 如果A2的析构函数没有写virtual会导致删除指针时不调用 B2的析构函数 可能导致内存泄露

	//要求：所有类的析构函数都应该加上virtual，保证子类继承之后出现 基类的指针指向子类对象时候，调用delete可以分别执行子类和基类的析构函数
	//注意构造函数和析构函数的执行顺序是对称的，先创建的对象总是最后销毁

	getchar();
	return 0;
}

