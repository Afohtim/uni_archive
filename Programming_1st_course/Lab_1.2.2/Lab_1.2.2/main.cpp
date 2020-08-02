#include "dataBase.h"
#include<iostream>

int main()
{
	DataBase db("DataBase.db");
	db.plant_tree(0, 1, 1, 5);
	db.plant_tree(0, 1, 2, 4);
	db.plant_tree(1, 1, 3, 6);
	db.plant_tree(1, 2, 4, 9);
	db.plant_tree(0, 2, 5, 2);
	std::cout << db.avg_age(0) << ' ' << db.size() << '\n';
	std::cin.get();

}