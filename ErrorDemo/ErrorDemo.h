#pragma once
class ErrorDemo
{


public:
	ErrorDemo();
	void nullPointer();
	void errorPointer();
	void notUIThreadError(void* uiWindow);
	void stackOverFlow();
	void windowsError(HDC hDC);
	void pureVirtualFuncError();
	void sehDemo();

private:
	string info;
};

