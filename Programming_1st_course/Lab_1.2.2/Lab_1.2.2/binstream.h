#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BYTE_SIZE 8


class Binstream
{
	FILE* streamer = NULL;
	char* way;
public:
	Binstream(char file_name[]);
	~Binstream();

	void close();
	unsigned char read_byte();
	void goto_start();
	void goto_end();
	void goto_pos(unsigned offset);
	unsigned size();
	template<typename T> T read();
	template<typename T> void write(T data);
	void clear();
	

};

template<typename T>
T Binstream::read()
{
	int size = sizeof(T);
	T res = 0;
	for (int i = 0; i < size; ++i)
	{
		res |= read_byte() << (i * BYTE_SIZE);
	}
	return res;
}

template<typename T>
inline void Binstream::write(T data)
{
	fwrite(&data, sizeof(T), 1, streamer);
}
