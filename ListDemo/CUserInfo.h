#pragma once
class CUserInfo
{


public:
	string getId();
	string getUserName();

	void setId(string id);
	void setUserName(string name);

private:
	string m_uid;
	string m_username;


public:
	CUserInfo();
	~CUserInfo();
};

