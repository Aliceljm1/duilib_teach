/***
*wtest.cpp: 虚析构函数的作用，virtual关键字的使用
参考资料：
https://www.cnblogs.com/hushpa/p/5707475.html
https://www.cnblogs.com/lit10050528/p/3874703.html

@author bxd
*/ 

#include "stdafx.h"
#include <string>
using namespace std;

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

//尝试使用SSE优化base64编码
int base64Encode( char* Input,int Length, char* Output)
{
	int test_le = 0x01020304;
	int* tle = &test_le;//内存从低到高依次是 04 03 02 01，总结下内存中的16进制数字，如果解析为字符串，则符合直觉顺序，如果解析为数字，则需要倒序

	static const char* LookUpTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int CurrentIndex = 0, ValidLen = (Length / 3) * 3;
	for (int Y = 0; Y < ValidLen; Y += 3, CurrentIndex += 4)
	{
		int Temp = ((Input[Y]) << 24) + (Input[Y + 1] << 16) + (Input[Y + 2] << 8);    //    注意C++是Little-Endian布局的
		//按照算法第一步，每次将三个字节，扩充为四个字节，
		int Temp2 = _byteswap_ulong(*(int*)(Input + Y));
		int* t = &Temp;
		int* t2 = &Temp2;
		int V0 = (Temp >> 26) & 0x3f;//按照算法来，而不是内存排序来。
		int V1 = (Temp >> 20) & 0x3f;
		int V2 = (Temp >> 14) & 0x3f;
		int V3 = (Temp >> 8) & 0x3f;
		Output[CurrentIndex + 0] = LookUpTable[V0];
		Output[CurrentIndex + 1] = LookUpTable[V1];
		Output[CurrentIndex + 2] = LookUpTable[V2];
		Output[CurrentIndex + 3] = LookUpTable[V3];
	}
	//    如果字节数不足三
	int Remainder = Length - ValidLen;
	if (Remainder == 2)
	{
	}
	else if (Remainder == 1)
	{
	}
	return 1;
}


//参考文章：https://www.cnblogs.com/Imageshop/p/15218464.html
//可以使用SSE，
void testBase64()
{
	string input = "Maa";
	string out="";
	out.resize(input.length()*1.4);
	base64Encode(const_cast<char*>(input.c_str()),input.length(), const_cast<char*>(out.c_str()));

}


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

	testBase64();

	getchar();



	return 0;
}

