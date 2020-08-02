#pragma once

enum colors { None,  Black, White };

struct Node
{
	Node* bot_rt = nullptr;
	Node* bot_lt = nullptr;
	Node* up_rt = nullptr;
	Node* up_lt = nullptr;
	bool checker = false;
	int color = None;
};

class Board
{
public:
	Board(unsigned board_size);

	void place_checker(int i, int j, int color);
	int max_beat(int i, int j, colors color);

private:
	Node* bottom_left;
	unsigned size;
	Node* goto_pos(int i, int j);

	
};

