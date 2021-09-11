#include "stdafx.h"
#include "CUserInfo.h"


CUserInfo::CUserInfo()
{
}

string CUserInfo::getId()
{
	return m_uid;
};

string CUserInfo::getUserName() 
{ 
	return m_username; 
};


void CUserInfo::setId(string id)
{
	m_uid = id;
};

void CUserInfo::setUserName(string name)
{
	m_username = name;
};


CUserInfo::~CUserInfo()
{
}
