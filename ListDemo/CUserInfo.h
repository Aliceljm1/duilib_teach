#pragma once
class CUserInfo
{


public:
	string getId();
	string getUserName();

	void setId(string id);
	void setUserName(string name);

private:
	string uid;
	string username;


public:
	CUserInfo();
	~CUserInfo();
};

