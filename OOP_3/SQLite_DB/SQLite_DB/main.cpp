#define _CRT_SECURE_NO_WARNINGS
#include "DataBase.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void create_all_tables(DataBase* db)
{
	char* sql = "CREATE TABLE tg_osu_id("  \
		"tg_id INT NOT NULL," \
		"osu_id INT NOT NULL," \
		"PRIMARY KEY(tg_id, osu_id));";
	db->exececute_sql(sql);

	sql = "CREATE TABLE osu_users("  \
		"osu_id INT PRIMARY KEY NOT NULL," \
		"username VARCHAR(255) NOT NULL," \
		"join_date DATETIME NOT NULL,"\
		"country VARCHAR(255) NOT NULL);";
	db->exececute_sql(sql);

	sql = "CREATE TABLE osu_stats("  \
		"osu_id INT NOT NULL," \
		"update_time DATETIME NOT NULL,"\
		"count300 VARCHAR(255) NOT NULL,"\
		"count100 VARCHAR(255) NOT NULL,"\
		"count50 VARCHAR(255) NOT NULL,"\
		"playcount VARCHAR(255) NOT NULL,"\
		"ranked_score VARCHAR(255) NOT NULL,"\
		"total_score VARCHAR(255) NOT NULL,"\
		"pp_rank VARCHAR(255) NOT NULL,"\
		"level VARCHAR(255) NOT NULL,"\
		"pp_raw VARCHAR(255) NOT NULL,"\
		"accuracy VARCHAR(255) NOT NULL,"\
		"count_rank_ss VARCHAR(255) NOT NULL,"\
		"count_rank_ssh VARCHAR(255) NOT NULL,"\
		"count_rank_s VARCHAR(255) NOT NULL,"\
		"count_rank_sh VARCHAR(255) NOT NULL,"\
		"count_rank_a VARCHAR(255) NOT NULL,"\
		"total_seconds_played VARCHAR(255) NOT NULL,"\
		"pp_country_rank VARCHAR(255) NOT NULL,"\
		"PRIMARY KEY(osu_id, update_time));";
	db->exececute_sql(sql);

	sql = "CREATE TABLE watchlist("  \
		"user_osu_id INT NOT NULL," \
		"watched_player_id INT NOT NULL,"\
		"PRIMARY KEY(user_osu_id, watched_player_id));";
	db->exececute_sql(sql);
}

void add_user(DataBase* db, char* tg_id, char* osu_id)
{
	char sql[255];
	sprintf(sql, "INSERT INTO tg_osu_id(tg_id, osu_id) VALUES(%s, %s);", tg_id, osu_id);
	db->exececute_sql(sql);

}

void add_user_info(DataBase* db, char* osu_id, char* username, char* join_date, char* country)
{
	char sql[255];
	sprintf(sql, "INSERT INTO osu_users(osu_id, username, join_date, country) VALUES(%s, %s, %s, %s);", osu_id, username, join_date, country);
	db->exececute_sql(sql);
}

void add_user_stats(
	DataBase* db,
	char* osu_id,
	char* update_time,
	char* count300,
	char* count100,
	char* count50,
	char* playcount,
	char* ranked_score,
	char* total_score,
	char* pp_rank,
	char* level,
	char* pp_raw,
	char* accuracy,
	char* count_rank_ss,
	char* count_rank_ssh,
	char* count_rank_s,
	char* count_rank_sh,
	char* count_rank_a,
	char* total_seconds_played,
	char* pp_country_rank)
{
	char sql[10000];
	sprintf(sql, "INSERT INTO osu_stats(osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank) " \
	"VALUES(%s, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",  osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank);
	printf(sql);
	db->exececute_sql(sql);
}


void select_all_users(DataBase* db)
{
	char* sql = "SELECT * FROM 'tg_osu_id';";
	db->exececute_sql(sql);
}

void select_all_info(DataBase* db)
{
	char* sql = "SELECT * FROM 'osu_users';";
	db->exececute_sql(sql);
}

void select_all_stats(DataBase* db)
{
	char* sql = "SELECT * FROM 'osu_stats';";
	db->exececute_sql(sql);
}

void get_user_info(DataBase* db, char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT osu_users.* FROM osu_users INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_users.osu_id AND tg_id = %s);", tg_id);
	db->exececute_sql(sql);
}


int main()
{
	DataBase* db = new DataBase("test.db", "callback.out");


	add_user(db, "12345", "54321");
	add_user_info(db, "54321", "'hjkj'", "'2015-07-29 19:05:11'", "'UA'");
	//add_user(db, "2334", "524321");
	//add_user(db, "12122345", "543241");
	//add_user(db, "123345", "545321");
	add_user_stats(db, "54321", "2015-07-29 19:05:11", "100", "100", "100", "100", "100", "100", "100", "100", "100", "100%", "100", "100", "100", "100", "100", "100", "100");
	select_all_users(db);
	select_all_info(db);
	get_user_info(db, "12345");
	get_user_info(db, "12355");
	select_all_stats(db);
	system("pause");
}