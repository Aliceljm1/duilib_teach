
/********************************************************************
filename: 	SQLite.cpp
created:	2012-11-05
author:		firehood

purpose:	SQLite���ݿ������
*********************************************************************/
#include "SQLite.h"
//#include "stdafx.h"
#include "log.h"
#include "string_utils.h"

const char* WcharToUtf8(const wchar_t *pwStr)
{
	if (pwStr == NULL)
	{
		return NULL;
	}

	int len = WideCharToMultiByte(CP_UTF8, 0, pwStr, -1, NULL, 0, NULL, NULL);
	if (len <= 0)
	{
		return NULL;
	}
	char *pStr = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, pwStr, -1, pStr, len, NULL, NULL);
	return pStr;
}

const wchar_t* Utf8ToWchar(const char *pStr)
{
	if (pStr == NULL)
	{
		return NULL;
	}

	int len = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0);
	if (len <= 0)
	{
		return NULL;
	}
	wchar_t *pwStr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, pStr, -1, pwStr, len);
	return pwStr;
}

SQLite::SQLite(void):
m_db(NULL)
{
}

SQLite::~SQLite(void)
{
	Close();
}

BOOL SQLite::Open(LPCTSTR lpDbFlie)
{
	if(lpDbFlie == NULL)
	{
		return FALSE;
	}
#ifdef  UNICODE 
	if(sqlite3_open16(lpDbFlie,&m_db) != SQLITE_OK)
#else
    if(sqlite3_open(lpDbFlie,&m_db) != SQLITE_OK)
#endif
	{
		return FALSE;
	}
	return TRUE;
}

void SQLite::Close()
{
	if(m_db)
	{
		sqlite3_close(m_db);
		m_db = NULL;
	}
}

BOOL SQLite::ExcuteNonQuery(LPCTSTR lpSql)
{
	if(lpSql == NULL)
	{
		return FALSE;
	}
    sqlite3_stmt* stmt;  
#ifdef  UNICODE 
	if(sqlite3_prepare16_v2(m_db, lpSql, -1, &stmt, NULL) != SQLITE_OK)
#else
    if(sqlite3_prepare_v2(m_db, lpSql, -1, &stmt, NULL) != SQLITE_OK)
#endif
	{ 
		return FALSE;  
	}  
	sqlite3_step(stmt);
	
	return (sqlite3_finalize(stmt) == SQLITE_OK) ? TRUE : FALSE ;
}

BOOL SQLite::ExcuteNonQuery(SQLiteCommand* pCmd)
{
	if(pCmd == NULL)
	{
		return FALSE;
	}
	return pCmd->Excute();
}

// ��ѯ(�ص���ʽ)
BOOL SQLite::ExcuteQuery(LPCTSTR lpSql,QueryCallback pCallBack)
{
	if(lpSql == NULL || pCallBack == NULL)
	{
		return FALSE;
	}
	char *errmsg = NULL;
#ifdef  UNICODE 
	const char *szSql = WcharToUtf8(lpSql);
	if(sqlite3_exec(m_db, szSql, pCallBack, NULL, &errmsg) != SQLITE_OK)
	{
		delete[] szSql;
		return FALSE;
	} 
    delete[] szSql;
#else
	if(sqlite3_exec(m_db, lpSql, pCallBack, NULL, &errmsg) != SQLITE_OK)
	{
		return FALSE;
	} 
#endif
	return TRUE;
}

// ��ѯ
SQLiteDataReader SQLite::ExcuteQuery(LPCTSTR lpSql)
{
	if(lpSql == NULL)
	{
		return FALSE;
	}
    sqlite3_stmt* stmt; 
#ifdef  UNICODE 
	if(sqlite3_prepare16_v2(m_db, lpSql, -1, &stmt, NULL) != SQLITE_OK)
#else
	if(sqlite3_prepare_v2(m_db, lpSql, -1, &stmt, NULL) != SQLITE_OK)
#endif
	{ 
		MessageBox(NULL,L"���ݿ��쳣���볢�����������ͻ��ˣ�",L"����",MB_OK);
		Logs::logError(CTextUtils::format("sqlite error:%d",GetLastError()));
		return FALSE;  
	}  
	return SQLiteDataReader(stmt);
}

// ��ʼ����
BOOL SQLite::BeginTransaction()
{
	char * errmsg = NULL;
    if(sqlite3_exec(m_db,"BEGIN TRANSACTION;",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		return FALSE;
	} 
	return TRUE;
}

// �ύ����
BOOL SQLite::CommitTransaction()
{
	char * errmsg = NULL;
	if(sqlite3_exec(m_db,"COMMIT TRANSACTION;;",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		return FALSE;
	} 
	return TRUE;
}

// �ع�����
BOOL SQLite::RollbackTransaction()
{
	char * errmsg = NULL;
	if(sqlite3_exec(m_db,"ROLLBACK  TRANSACTION;",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		return FALSE;
	} 
	return TRUE;
}

// ��ȡ��һ��������Ϣ
LPCTSTR SQLite::GetLastErrorMsg()
{
#ifdef UNICODE 
	return (LPCTSTR)sqlite3_errmsg16(m_db);
#else
    return sqlite3_errmsg(m_db);
#endif
}



SQLiteDataReader::SQLiteDataReader(sqlite3_stmt *pStmt):
m_pStmt(pStmt)
{

}

SQLiteDataReader::~SQLiteDataReader()
{
	Close();
}

// ��ȡһ������
BOOL SQLiteDataReader::Read()
{
	if(m_pStmt == NULL)
	{
		return FALSE;
	}
	if(sqlite3_step(m_pStmt) != SQLITE_ROW)
	{
		return FALSE;
	}
	return TRUE;
}

// �ر�Reader����ȡ���������
void SQLiteDataReader::Close()
{
	if(m_pStmt)
	{
		sqlite3_finalize(m_pStmt);
		m_pStmt = NULL;
	}
}

// �ܵ�����
int SQLiteDataReader::ColumnCount(void)
{
	return sqlite3_column_count(m_pStmt);
}

// ��ȡĳ�е����� 
LPCTSTR SQLiteDataReader::GetName(int nCol)
{
#ifdef  UNICODE 
	return (LPCTSTR)sqlite3_column_name16(m_pStmt, nCol);
#else
	return (LPCTSTR)sqlite3_column_name(m_pStmt, nCol);
#endif
}

// ��ȡĳ�е���������
SQLITE_DATATYPE SQLiteDataReader::GetDataType(int nCol)
{
	return (SQLITE_DATATYPE)sqlite3_column_type(m_pStmt, nCol);
}

// ��ȡĳ�е�ֵ(�ַ���)
LPCTSTR SQLiteDataReader::GetStringValue(int nCol)
{
#ifdef  UNICODE 
	return (LPCTSTR)sqlite3_column_text16(m_pStmt, nCol);
#else
    return (LPCTSTR)sqlite3_column_text(m_pStmt, nCol);
#endif
}

// ��ȡĳ�е�ֵ(����)
int SQLiteDataReader::GetIntValue(int nCol)
{
	return sqlite3_column_int(m_pStmt, nCol);
}

// ��ȡĳ�е�ֵ(������)
long SQLiteDataReader::GetInt64Value(int nCol)
{
	return (long)sqlite3_column_int64(m_pStmt, nCol);
}

// ��ȡĳ�е�ֵ(������)
double SQLiteDataReader::GetFloatValue(int nCol)
{
	return sqlite3_column_double(m_pStmt, nCol);
}

// ��ȡĳ�е�ֵ(����������)
const BYTE* SQLiteDataReader::GetBlobValue(int nCol, int &nLen)
{
	nLen = sqlite3_column_bytes(m_pStmt, nCol);
	return (const BYTE*)sqlite3_column_blob(m_pStmt, nCol);
}

SQLiteCommand::SQLiteCommand(SQLite* pSqlite):
m_pSqlite(pSqlite),
m_pStmt(NULL)
{
}

SQLiteCommand::SQLiteCommand(SQLite* pSqlite,LPCTSTR lpSql):
m_pSqlite(pSqlite),
m_pStmt(NULL)
{
	SetCommandText(lpSql);
}

SQLiteCommand::~SQLiteCommand()
{

}

BOOL SQLiteCommand::SetCommandText(LPCTSTR lpSql)
{
#ifdef  UNICODE 
	if(sqlite3_prepare16_v2(m_pSqlite->m_db, lpSql, -1, &m_pStmt, NULL) != SQLITE_OK)
#else
	if(sqlite3_prepare_v2(m_pSqlite->m_db, lpSql, -1, &m_pStmt, NULL) != SQLITE_OK)
#endif
	{ 
		return FALSE;  
	}  
	return TRUE;
}

BOOL SQLiteCommand::BindParam(int index, LPCTSTR szValue)
{
#ifdef  UNICODE 
	if(sqlite3_bind_text16(m_pStmt, index, szValue, -1, SQLITE_TRANSIENT) != SQLITE_OK)
#else
    if(sqlite3_bind_text(m_pStmt, index, szValue,-1, SQLITE_TRANSIENT) != SQLITE_OK)
#endif
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SQLiteCommand::BindParam(int index, const int nValue)
{
	if(sqlite3_bind_int(m_pStmt, index, nValue) != SQLITE_OK)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SQLiteCommand::BindParam(int index, const double dValue)
{
	if(sqlite3_bind_double(m_pStmt, index, dValue) != SQLITE_OK)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SQLiteCommand::BindParam(int index, const unsigned char* blobBuf, int nLen)
{
	if(sqlite3_bind_blob(m_pStmt, index, blobBuf,nLen,NULL) != SQLITE_OK)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SQLiteCommand::Excute()
{
	sqlite3_step(m_pStmt);

	return (sqlite3_reset(m_pStmt) == SQLITE_OK) ? TRUE : FALSE ;
}

void SQLiteCommand::Clear()
{
	if(m_pStmt)
	{
		sqlite3_finalize(m_pStmt);
	}
}

