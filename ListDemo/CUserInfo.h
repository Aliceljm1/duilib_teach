#pragma once
/**
*�û�ģ�ͣ��ṩ�������ݣ����͹۴��ڵ�ʵ�����Ϊ���ģ������������̵Ļ���
�����ӵĹ��̳���Ϊ���������ӹ���֮��Ͼ��ǳ�����
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

