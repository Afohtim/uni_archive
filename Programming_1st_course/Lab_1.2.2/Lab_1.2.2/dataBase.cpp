#include "dataBase.h"
#include <queue>

bool cut(Tree cur_tree, characteristics character, unsigned value)
{
	return ((character == type && cur_tree.type == value) || (character == age && cur_tree.age == value) || (character == x_coordinate && cur_tree.i == value) || (character == y_coordinate && cur_tree.j == value));
}


DataBase::DataBase(char file_name[])
{
	stream = new Binstream(file_name);
}


DataBase::~DataBase()
{
	delete stream;
}

void DataBase::cut_trees(characteristics character, unsigned value)
{
	unsigned offset = 4 * sizeof(unsigned);
	unsigned size = stream->size() / offset;
	std::queue<Tree> saved;
	Tree cur_tree;
	stream->goto_start();
	for (int tree = 0; tree < size; ++tree)
	{
		cur_tree.type = stream->read<unsigned>();
		cur_tree.age = stream->read<unsigned>();
		cur_tree.i = stream->read<unsigned>();
		cur_tree.j = stream->read<unsigned>();
		if (! cut(cur_tree, character, value))
		{
			saved.push(cur_tree);
		}
	}
	stream->clear();
	while (!saved.empty())
	{
		cur_tree = saved.front();
		saved.pop();
		stream->write(cur_tree.type);
		stream->write(cur_tree.age);
		stream->write(cur_tree.i);
		stream->write(cur_tree.j);
	}

	
}

void DataBase::plant_tree(unsigned type, unsigned i, unsigned j, unsigned age = 0)
{
	stream->goto_end();
	stream->write(type);
	stream->write(age);
	stream->write(i);
	stream->write(j);
}

double DataBase::avg_age(unsigned needed_type)
{
	double res = 0;
	double cnt = 0;
	unsigned offset = 4 * sizeof(unsigned);
	unsigned size = stream->size() / offset;
	stream->goto_start();
	for (int tree = 0; tree < size; ++tree)
	{
		unsigned type = stream->read<unsigned>();
		unsigned age = stream->read<unsigned>();
		unsigned i = stream->read<unsigned>();
		unsigned j = stream->read<unsigned>();
		if (type == needed_type)
		{
			res += age;
			++cnt;
		}
	}
	if (cnt == 0)
		return 0;
	else
	{
		res = res / cnt;
		return res;
	}
}

unsigned DataBase::size()
{
	unsigned offset = 4 * sizeof(unsigned);
	unsigned size = stream->size() / offset;
	return size;
}
