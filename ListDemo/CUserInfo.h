#pragma once
/**
*用户模型，提供基础数据，将客观存在的实体抽象为类和模型是面向对象编程的基础
将复杂的过程抽象为单个存粹的子过程之组合就是抽象层次
*/
class CUserInfo
{
public:
	CUserInfo();
	~CUserInfo();

	string getId();
	string getUserName();

	void setId(string id);
	void setUserName(string name);

private:
	string m_uid;
	string m_username;



};

