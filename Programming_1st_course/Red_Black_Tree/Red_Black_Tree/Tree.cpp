#include "Tree.h"



Tree::Tree()
{
	root = new Node;
}


Tree::~Tree()
{
}

void Tree::insert(int x)
{
	if (root = nullptr)
	{
		root = new Node;
		root->val = x;
		root->col = Black;
		return;
	}
	Node* node = root;
	while (true)
	{
		if (x < node->val)
		{
			if (node->left->leaf == true)
			{
				break;
			}
			else
			{
				node = node->left;
				continue;
			}
		}
		else
		{
			if (node->right->leaf == true)
			{
				break;
			}
			else
			{
				node = node->right;
			}
		}

	}
	if (x < node->val)
	{
		node->left->leaf = false;
		node->left->left = new Node;
		node->left->par = node->left;
		node->left->right = new Node;
		node->left->par = node->left;
		node->left->col = Red;

		check_insert(node->left);
	}
	else
	{
		node->right = new Node;
		node->right->par = node;
		check_insert(node->right);
	}
}

void Tree::erase(int x)
{

}
