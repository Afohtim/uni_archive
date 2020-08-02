#include "DataBase.h"



DataBase::DataBase(char* db_file, char* file)
{
	int response = sqlite3_open("test.db", &db);
	if (response)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		fprintf(stderr, "db is opened\n", sqlite3_errmsg(db));
	}

	callback_file = file;
}


DataBase::~DataBase()
{
	sqlite3_close(db);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	FILE* out = fopen("callback.out", "w");
	fprintf(out, "{\n");
	for (int i = 0; i < argc; ++i)
	{
		fprintf(out, "'%s': '%s'%s\n", azColName[i], argv[i] ? argv[i] : "NULL", i != argc - 1 ? "," : "");
	}
	fprintf(out, "}\n");
	return 0;
}

void DataBase::check_request(char* request_type, int rc, char* zErrMsg)
{
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		printf("%s: OK\n", request_type);
	}
}

int exec_sql(sqlite3* db, char* sql_code, char* zErrMsg)
{
	sqlite3* db_1;
	sqlite3_open("test.db", &db_1);
	const char* data = "Callback function called";
	//printf(sql_code);
	int rc = sqlite3_exec(db_1, sql_code, callback, (void*)data, &zErrMsg);
	return rc;
	
}


void DataBase::exececute_sql(char * sql_code)
{
	char* zErrMsg = 0;
	int rc = exec_sql(this->db, sql_code, zErrMsg);
	check_request("request", rc, zErrMsg);
}

