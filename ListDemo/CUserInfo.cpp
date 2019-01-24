#include "stdafx.h"
#include "CUserInfo.h"


CUserInfo::CUserInfo()
{
}

string CUserInfo::getId() { return uid; };
string CUserInfo::getUserName() { return username; };


void CUserInfo::setId(string id)
{
	uid = id;
};

void CUserInfo::setUserName(string name)
{
	username = name;
};


CUserInfo::~CUserInfo()
{
}
