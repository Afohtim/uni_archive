#pragma once

enum color {Black, Red};

struct Node
{
	int val;
	Node* par;
	Node* left = nullptr;
	Node* right = nullptr;
	color col = Black;
	bool leaf = true;
};


class Tree
{
private:
	Node* root;
	void check_insert(Node* node);
	void check_erase(Node* node);
public:
	Tree();
	~Tree();

	void insert(int x);
	void erase(int x);
};

