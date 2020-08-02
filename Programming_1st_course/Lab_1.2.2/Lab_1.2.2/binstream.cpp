#include "binstream.h"

Binstream::Binstream(char file_name[])
{
	way = file_name;
	streamer = fopen(file_name, "r+b");
}

Binstream::~Binstream()
{
	fclose(streamer);
}

void Binstream::close()
{
	fclose(streamer);
}

unsigned char Binstream::read_byte()
{
	unsigned char res;
	fread(&res, sizeof(unsigned char), 1, streamer);
	return res;
}

void Binstream::goto_start()
{
	fseek(streamer, 0, SEEK_SET);
}

void Binstream::goto_end()
{
	fseek(streamer, 0, SEEK_END);
}

void Binstream::goto_pos(unsigned offset)
{
	fseek(streamer, offset, SEEK_SET);
}


unsigned Binstream::size()
{
	fseek(streamer, 0, SEEK_END);
	unsigned ans =  ftell(streamer);
	return ans;
}

void Binstream::clear()
{
	fclose(streamer);
	streamer = fopen(way, "w");
	fclose(streamer);
	streamer = fopen(way, "r+b");
}
