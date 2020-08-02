#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "sqlite3.h"
#include <stdio.h>

class DataBase
{
	//friend int callback(void *NotUsed, int argc, char **argv, char **azColName);
private:
	sqlite3* db;
	char* callback_file;
	void check_request(char* request_type, int rc, char* zErrMsg);
public:
	void exececute_sql(char* sql_code);
	DataBase(char* db_file, char* file);
	~DataBase();
};

