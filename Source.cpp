#include<iostream>
#include"BinarySearchTree.h"

template<typename K, typename V>
int BST<K,V>::calculateheight(Node* node)//function to calculate height of BST
{
	if (node == NULL)
		return -1;
	else
	{
		int leftsubheight = calculateheight(node->left);
		int rightsubheight = calculateheight(node->right);

		if (leftsubheight > rightsubheight)
			return leftsubheight + 1;
		else
			return rightsubheight + 1;
	}
}

template<typename K, typename V>
bool BST<K,V>::isBalanced(Node* node)
{
	if (node == NULL)//base case: when tree is empty or when we reached the bottom of tree
		return true;

	//calculating height of left and right subtrees
	int leftsubheight = calculateheight(node->left);
	int rightsubheight = calculateheight(node->right);

	/*
	checking if height difference of left and right subtree is less than
	or equal to one and that is the case for left
	and right subtrees or not, if not then return false.
	*/
	if (abs(leftsubheight - rightsubheight) <= 1 && isBalanced(node->left)
		&& isBalanced(node->right))
	{
		return true;
	}
	return false;
}

int main()
{
	BST<int, string> bst;

	for (int i = 0; i < 7; i++)
		bst.Insert(i + 1, "A");

	BST<int, string>::InorderIterator it;

	for (it = bst.begin(); !it.end(); it++)
		cout << (*it).first << "  " << (*it).second << endl;

	cout << endl << bst.isBalanced(bst.begin()) << endl;//checking if bst is balanced or not
}