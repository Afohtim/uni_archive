#pragma once
#include "binstream.h"

enum characteristics {type, age, x_coordinate, y_coordinate};

struct Tree
{
	unsigned type = 0;
	unsigned age = 0;
	unsigned i = 0;
	unsigned j = 0;
};

class DataBase
{
public:
	DataBase(char file_name[]);
	~DataBase();

	void cut_trees(characteristics character, unsigned value);
	void plant_tree(unsigned type, unsigned i, unsigned j, unsigned age);
	double avg_age(unsigned type);
	unsigned size();
private:
	Binstream* stream = nullptr;
};

