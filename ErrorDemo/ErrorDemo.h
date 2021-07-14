#pragma once
class ErrorDemo
{


public:
	ErrorDemo();
	void nullPointer();
	void errorPointer();
	void notUIThreadError(void* uiWindow);
	void stackOverFlow();
	void notInit();
	void sehDemo();

private:
	string info;
};

