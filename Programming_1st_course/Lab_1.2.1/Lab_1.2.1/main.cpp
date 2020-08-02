#include "List.h"
#include<iostream>

int main()
{
	Board board = Board(8);
	//out of board
	/*
	board.place_checker(3, 3, Black);
	board.place_checker(5, 5, Black);
	board.place_checker(7, 7, Black);
	std::cout << board.max_beat(2, 2, White) << '\n';
	*/
	//combo
	board.place_checker(2, 2, Black);
	board.place_checker(4, 4, Black);
	board.place_checker(4, 6, White);
	board.place_checker(2, 6, Black);
	board.place_checker(2, 4, Black);
	std::cout << board.max_beat(1, 1, White) << '\n';
	std::cin.get();
	
}