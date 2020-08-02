#include "List.h"

int max(int x, int y)
{
	return x > y ? x : y;
}

Board::Board(unsigned board_size)
{
	this->size = board_size;
	bottom_left = new Node;
	
	//generating first layer
	Node* current_node = bottom_left;

	for (int i = 0; i < size / 2 - 1; ++i)
	{
		current_node->up_rt = new Node;
		current_node->up_rt->bot_lt = current_node;

		current_node->up_rt->bot_rt = new Node;
		current_node->up_rt->bot_rt->up_lt = current_node->up_rt;

		current_node = current_node->up_rt->bot_rt;
	}
	if (board_size % 2 == 0)
	{
		current_node->up_rt = new Node;
		current_node->up_rt->bot_lt = current_node;
	}

	//generatng rest of the layers;
	Node* curr_bot_node = nullptr;
	for (int i = 0; i < size / 2 - 1; ++i)
	{
		curr_bot_node = bottom_left->up_rt;
		for (int j = 0; j < i; ++j)
		{
			curr_bot_node = curr_bot_node->up_lt->up_rt;
		}
		current_node = new Node;
		for (int j = 0; j < size / 2 - 1; ++j)
		{
			current_node->up_rt = new Node;
			current_node->up_rt->bot_lt = current_node;

			current_node->up_rt->bot_rt = new Node;
			current_node->up_rt->bot_rt->up_lt = current_node->up_rt;

			current_node->bot_rt = curr_bot_node;
			curr_bot_node->up_lt = current_node;
			if (curr_bot_node->bot_lt->up_lt != nullptr)
			{
				current_node->bot_lt = curr_bot_node->bot_lt->up_lt;
				current_node->bot_lt->up_rt = current_node;
			}

			curr_bot_node = curr_bot_node->bot_rt == nullptr ? nullptr : curr_bot_node->bot_rt->up_rt;

			current_node = current_node->up_rt->bot_rt;
			
		}
		if (board_size % 2 == 0)
		{
			current_node->up_rt = new Node;
			current_node->up_rt->bot_lt = current_node;
		}
		current_node->bot_rt = curr_bot_node;
		curr_bot_node->up_lt = current_node;
		current_node->bot_lt = curr_bot_node->bot_lt->up_lt;
		current_node->bot_lt->up_rt = current_node;
	}
	

}

void Board::place_checker(int i, int j, int color)
{
	if ((i + j) % 2 == 1)
	{
		return;
	}
	Node* current_node = goto_pos(i, j);
	
	current_node->checker = true;
	current_node->color = color;
}

int Board::max_beat(int i, int j, colors color)
{
	int res = 0;
	Node* current_node = goto_pos(i, j);

	if (current_node->bot_lt != nullptr && current_node->bot_lt->color != color  && current_node->bot_lt->bot_lt != nullptr && current_node->bot_lt->checker == true && current_node->bot_lt->bot_lt->checker == false)
	{
		current_node->bot_lt->checker = false;
		res = max(res, max_beat(i - 2, j - 2, color) + 1);
		current_node->bot_lt->checker = true;
	}

	if (current_node->bot_rt != nullptr && current_node->bot_rt->color != color && current_node->bot_rt->bot_rt != nullptr && current_node->bot_rt->checker == true && current_node->bot_rt->bot_rt->checker == false)
	{
		current_node->bot_rt->checker = false;
		res = max(res, max_beat(i - 2, j + 2, color) + 1);
		current_node->bot_rt->checker = true;
	}

	if (current_node->up_lt != nullptr && current_node->up_lt->color != color && current_node->up_lt->up_lt != nullptr && current_node->up_lt->checker == true && current_node->up_lt->up_lt->checker == false)
	{
		current_node->up_lt->checker = false;
		res = max(res, max_beat(i + 2, j - 2, color) + 1);
		current_node->up_lt->checker = true;
	}

	if (current_node->up_rt != nullptr && current_node->up_rt->color != color && current_node->up_rt->up_rt != nullptr && current_node->up_rt->checker == true && current_node->up_rt->up_rt->checker == false)
	{
		current_node->up_rt->checker = false;
		res = max(res, max_beat(i + 2, j + 2, color) + 1);
		current_node->up_rt->checker = true;
	}

	return res;
}

Node* Board::goto_pos(int i, int j)
{
	Node* current_node = bottom_left;
	while (i > 0 && j > 0)
	{
		current_node = current_node->up_rt;
		--i, --j;
	}
	if (i > 0)
	{
		while (i > 0)
		{
			current_node = current_node->up_rt->up_lt;
			i -= 2;
		}
	}
	else
	{
		while (j > 0)
		{
			current_node = current_node->up_rt->bot_rt;
			j -= 2;
		}
	}
	return current_node;
}
