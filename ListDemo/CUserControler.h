#pragma once
#include "CUserInfo.h"

/***
*��ģ�Ͷ�Ӧ�Ŀ������࣬�����˲���ģ�͵���ط��������л��ͷ����л�����
ģ���ṩ���������ݴ洢����������ת������ص����ݲ���Ӧ���ŵ�����������
�����������ṩ��UI����ģ�͵�������

add by ljm
*/
class CUserControler
{
public:
	CUserControler();

	void parseFromJson(const string& json,CUserInfo* info);
	void saveUserInfoToFile(CUserInfo* info,const string& filepath);
	void getUserInfoFromFile(CUserInfo* info, const string& filepath);


	virtual ~CUserControler();
};

