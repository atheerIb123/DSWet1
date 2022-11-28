#ifndef GENERIC_AVL_TREE_H_
#define GENERIC_AVL_TREE_H_

#include <iostream>

template<class T>
class Node
{
public:
	Node(T& data) : data(new T(data)),left(nullptr), right(nullptr) {}
	Node(const Node& other);
	Node& operator=(const Node& other);
	~Node();

	Node* right;
	Node* left;
	T* data;
};

template<class T>
class AVLTree
{
private:
	Node<T>* root;
	int numOfNodes;

	int max(int val1, int val2) const;
	static Node<T>* findMinNode(Node<T>* root);
	Node<T>* insertNode(Node<T>* root, T& data);
	Node<T>* removeNode(Node<T>*, T& data);
	Node<T>* copyNodes(Node<T>* node);
public:
	AVLTree() : root(nullptr), numOfNodes(0) {}
	AVLTree(const AVLTree& other);
	AVLTree<T>& operator=(const AVLTree<T>& other);
	~AVLTree();
	void deleteTree(Node<T>* root);

	int calcHeight(Node<T>* node);
	Node<T>* rightRotation(Node<T>* root);
	Node<T>* leftRotation(Node<T>* root);
	Node<T>* balanceTree(Node<T>* root); //a helper method for rotations
	int getBalance(Node<T>* node);
	int getNodesNum() const;
	Node<T>* insert(T& data);
	Node<T>* find(Node<T>* root, const T& data);
	Node<T>* remove(T& data);
	Node<T>* getRoot() const;
	void inOrder(Node<T>* root, T* const output, int& index) const;
	void inOrderMinToMax(Node<T>* node, T* min, T* max, T* const output, int& index) const;
	void mergeTrees();

};

template<class T>
Node<T>::Node<T>(const Node<T>& other)
{
	data = new T(*(other.data));

	if (other.left)
	{
		left = new Node<T>(*(other.left));
	}
	else 
	{
		left = nullptr;
	}

	if (other.right) {
		right = new Node<T>(*(other.right));
	}
	else
	{
		right = nullptr;
	}
}

template<class T>
Node<T>& Node<T>::operator=(const Node<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	data = new T(*(other.data));

	if (other.left) {
		left = new Node<T>(*(other.left));
	}
	else {
		left = nullptr;
	}

	if (other.right) {
		right = new Node<T>(*(other.right));
	}
	else 
	{
		right = nullptr;
	}

	return *this;
}

template<class T>
Node<T>::~Node<T>()
{
	delete data;
}


template<class T>
inline AVLTree<T>::AVLTree(const AVLTree& other)
{
	this->root = copyNodes(other.getRoot());
	this->numOfNodes = other.numOfNodes;
}

template<class T>
inline AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	deleteTree(this->root);
	this->root = copyNodes(other.root);
	this->numOfNodes = other.numOfNodes;

	return *this;
}

template<class T>
inline AVLTree<T>::~AVLTree()
{
	deleteTree(this->root);
}

template<class T>
inline void AVLTree<T>::deleteTree(Node<T>* node)
{
	if (node == NULL)
	{
		return;
	}

	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

template<class T>
int AVLTree<T>::calcHeight(Node<T>* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	int leftHeight = calcHeight(node->left);
	int rightHeight = calcHeight(node->right);

	return 1 + max(leftHeight, rightHeight);
}

template<class T>
inline Node<T>* AVLTree<T>::rightRotation(Node<T>* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	Node<T>* newParent = root->left;

	root->left = newParent->right;
	newParent->right = root;

	return newParent;
}

template<class T>
inline Node<T>* AVLTree<T>::leftRotation(Node<T>* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	
	Node<T>* newParent = root->right;
	root->right = newParent->left;
	newParent->left = root;
	
	return newParent;
}

template<class T>
inline Node<T>* AVLTree<T>::balanceTree(Node<T>* root)
{
	if (root != nullptr)
	{
		if (getBalance(root) == 2)
		{
			if (getBalance(root->left) >= 0)
			{
				return rightRotation(root);
			}
			else if (getBalance(root->left) == -1)
			{
				root->left = leftRotation(root->left);
				return rightRotation(root);
			}
		}
		else if (getBalance(root) == -2)
		{
			if (getBalance(root->right) <= 0)
			{
				return leftRotation(root);
			}
			else if (getBalance(root->right) == 1)
			{
				root->right = rightRotation(root->right);
				return leftRotation(root);
			}
		}
	}

	return root;
}

template<class T>
inline int AVLTree<T>::max(int val1, int val2) const
{
	return val1 < val2 ? val2 : val1;
}

//Could've been implemented non-recursively 
template<class T>
inline Node<T>* AVLTree<T>::findMinNode(Node<T>* root)
{
	if (root == nullptr)
	{
		return root;
	}

	if (root->left == nullptr)
	{
		return root;
	}

	return findMinNode(root->left);
}



template<class T>
inline int AVLTree<T>::getBalance(Node<T>* node)
{
	if(node)
	{
		return (calcHeight(node->left) - calcHeight(node->right));
	}
}

template<class T>
inline int AVLTree<T>::getNodesNum() const
{
	return this->numOfNodes;
}

template<class T>
inline Node<T>* AVLTree<T>::insertNode(Node<T>* node, T& data)
{
	if (node == nullptr)
	{
		Node<T>* newNode = new Node<T>(data);
		
		if (this->root == nullptr)
		{
			this->root = newNode;
		}

		this->numOfNodes++;
		return newNode;
	}

	if (data < *(node->data))
	{
		node->left = insertNode(node->left, data);
	}
	else
	{
		node->right = insertNode(node->right, data);
	}

	node = balanceTree(node);
	this->root = node;

	return root;
}

template<class T>
inline Node<T>* AVLTree<T>::insert(T& data)
{
	if (find(this->root, data))
	{
		return nullptr;
	}

	return insertNode(this->root, data);
}

template<class T>
inline Node<T>* AVLTree<T>::find(Node<T>* node, const T& data)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (*(node->data) == data)
	{
		return node;
	}

	if (*(node->data) < data)
	{
		return find(node->right, data);
	}
	else if (*(node->data) > data)
	{
		return find(node->left, data);
	}

	return nullptr;
}

template<class T>
inline Node<T>* AVLTree<T>::remove(T& data)
{
	if (!find(this->root, data))
	{
		return nullptr;
	}

	return removeNode(this->root, data);
}

template<class T>
inline Node<T>* AVLTree<T>::getRoot() const
{
	return this->root;
}

template<class T>
inline Node<T>* AVLTree<T>::removeNode(Node<T>* node, T& data)
{
	if (node == nullptr)
	{
		return node;
	}

	if (data < *(node->data)) //search in the left sub-tree
	{
		node->left = removeNode(node->left, data);
	}
	else if (data > *(node->data)) //search in the right sub-tree
	{
		node->right = removeNode(node->right, data);
	}
	else //We found the actual node
	{
		Node<T>* toDelete = nullptr;
		if (node->right == nullptr || node->left == nullptr)
		{
			if (node->right == nullptr && node->left == nullptr) //has no children (in case of having a leaf)
			{
				toDelete = node;
				node = nullptr;
				this->root = node;
			}
			else
			{
				toDelete = node->left ? node->left : node->right;
				*(node) = *(toDelete);
			}

			this->numOfNodes--;
			delete toDelete;
			toDelete = nullptr;
		}
		else //in case the wanted node for deletion has two children
		{
			Node<T>* temp = findMinNode(node->right);
			*(node->data) = *(temp->data);
			node->right = removeNode(node->right, *(temp->data));
		}
	}

	if (node == nullptr)
	{
		return node;
	}

	node = balanceTree(node);
	this->root = node;

	return this->root;
}

template<class T>
inline Node<T>* AVLTree<T>::copyNodes(Node<T>* node)
{
	if (node != nullptr)
	{
		Node<T>* newNode = new Node<T>(*(node->data));
		newNode->left = copyNodes(node->left);
		newNode->right = copyNodes(node->right);
		return newNode;
	}

	return nullptr;
}

template<class T>
inline void AVLTree<T>::inOrder(Node<T>* node ,T* const output, int& index) const
{
	if (node == nullptr)
	{
		return;
	}

	inOrder(node->left, output, index);
	output[index++] = *(node->data);
	inOrder(node->right, output, index);
	
}

template<class T>
inline void AVLTree<T>::inOrderMinToMax(Node<T>* node, T* min, T* max, T* const output, int& index) const
{
	if (node == nullptr)
	{
		return;
	}

	if (*(min) == *(node->data) && *(max) == *(node->data))
	{
		output[index++] = *(node->data);
	}

	if ((*(node->data) < *(max) || *(node->data) == *(max)) && (*(node->data) > *(min) || *(node->data) == *(min)))
	{
		inOrderMinToMax(node->left, min, max, output, index);
		output[index++] = *(node->data);
		inOrderMinToMax(node->right, min, max, output, index);
	}
	else if (*(node->data) < *(min))
	{
		inOrderMinToMax(node->right, min, max, output, index);
	}
	else
	{
		inOrderMinToMax(node->left, min, max, output, index);
	}
}

#endif


