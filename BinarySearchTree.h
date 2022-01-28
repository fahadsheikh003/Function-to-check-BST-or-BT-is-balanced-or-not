#pragma once
#include<queue>

using namespace std;

template<typename K, typename V>
class BST
{
	struct Node
	{
		K key;
		V value;
		Node* left, * right;

		Node() : key(K()), value(V()), left(NULL), right(NULL) {};

		Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {};
	};

	Node* Insert(Node* node, K key, V value)
	{
		if (node == NULL)
			return new Node(key, value);
		else if (node->key > key)
			node->left = Insert(node->left, key, value);
		else if (node->key < key)
			node->right = Insert(node->right, key, value);
		return node;
	}

	Node* Remove(Node * node, K key, V value = V())
	{
		if (node == NULL)
			return NULL;
		else if (node->key > key)
			node->left = Remove(node->left, key, value);
		else if (node->key < key)
			node->right = Remove(node->right, key, value);
		else if (node->key == key)
		{
			if (node->left == NULL)
			{
				Node* temp = node->right;
				free(node);
				return temp;
			}
			else if (node->right == NULL)
			{
				Node* temp = node->left;
				free(node);
				return temp;
			}
			else
			{
				Node* temp = node->right;
				while (temp->left)
				{
					temp = temp->left;
				}

				node->key = temp->key;
				node->value = temp->value;

				node->right = Remove(node->right, temp->key, temp->value);
			}
		}
		return node;
	}

	class Iterator
	{
	protected:
		queue<Node*> Q;

	public:
		Iterator() {};

		Iterator(Node* node) {
			operator=(node);
		};

		virtual void operator=(Node* node) = 0;

		pair<K, V> operator*()
		{
			Node* node = Q.front();
			pair<K, V> P;
			P.first = node->key;
			P.second = node->value;
			return P;
		}

		void operator++()
		{
			Q.pop();
		}

		void operator++(int)
		{
			++(*this);
		}

		bool end()
		{
			return Q.empty();
		}
	};

	void clear(Node * node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			free(node);
		}
	}

	Node* root;
public:
	BST() : root(NULL) {};

	BST(const BST<K, V> & obj) : root(NULL)
	{
		if (obj.root)
		{
			PreorderIterator it;

			for (it = obj.root; !it.end(); it++)
				Insert((*it).first, (*it).second);
		}
	}

	BST<K, V>& operator=(const BST<K, V> & obj)
	{
		this->clear();
		if (obj.root)
		{
			PreorderIterator it;

			for (it = obj.root; !it.end(); it++)
				Insert((*it).first, (*it).second);
		}
		return *this;
	}

	void Insert(K key, V value)
	{
		root = Insert(root, key, value);
	}

	void Remove(K key, V value = V())
	{
		root = Remove(root, key, value);
	}

	Node* begin()
	{
		return root;
	}

	class InorderIterator : public Iterator
	{
		void inorder(Node* node)
		{
			if (node)
			{
				inorder(node->left);
				Iterator::Q.push(node);
				inorder(node->right);
			}
		}

	public:
		void operator=(Node* node)
		{
			while (!Iterator::Q.empty())
				Iterator::Q.pop();
			inorder(node);
		}
	};

	class PreorderIterator : public Iterator
	{
		void preorder(Node* node)
		{
			if (node)
			{
				Iterator::Q.push(node);
				preorder(node->left);
				preorder(node->right);
			}
		}

	public:
		void operator=(Node* node)
		{
			while (!Iterator::Q.empty())
				Iterator::Q.pop();
			preorder(node);
		}
	};

	class PostorderIterator : public Iterator
	{
		void postorder(Node* node)
		{
			if (node)
			{
				postorder(node->left);
				postorder(node->right);
				Iterator::Q.push(node);
			}
		}

	public:
		void operator=(Node* node)
		{
			while (!Iterator::Q.empty())
				Iterator::Q.pop();
			postorder(node);
		}
	};

	int calculateheight(Node* node);

	bool isBalanced(Node* node);

	void clear()
	{
		clear(root);
		root = NULL;
	}

	~BST()
	{
		clear();
	}
};