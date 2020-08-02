#include<iostream>

struct Node
{
	int value = 0;
	Node* parent;
	Node* left = nullptr, *right = nullptr;
};

class Tree
{
private:
	Node* root;
public:
	Tree()
	{
		root = new Node;
	}
	void insert(int x)
	{
		Node* node = root;
		while (true)
		{
			if (node->value > x)
			{
				if (node->right == nullptr)
				{
					node->right = new Node;
					node->right->value = x;
					return;
				}
			}
			else
			{
				if (node->left == nullptr)
				{
					node->left = new Node;
					node->left->value = x;
					return;
				}
			}
			if (root->left == nullptr) 
			{
				root = root->right;
				continue;
			}
			if (root->right == nullptr)
			{
				root = root->left;
				continue;
			}
			if (rand() % 2)
			{
				root = root->left;
			}
			else
			{
				root = root->right;
			}


		}
		
	}
};

int main()
{

}