#ifndef GENERIC_AVL_TREE_H_
#define GENERIC_AVL_TREE_H_

#include <iostream>

template<class T>
class Node
{
public:
	Node(T& data) : data(new T(data)),left(nullptr), right(nullptr), next(nullptr), previous(nullptr) {}
	Node(const Node& other);
	Node& operator=(const Node& other);
	~Node();

	Node* right;
	Node* left;
	Node* previous;
	Node* next;
	//Node* parent;
	T* data;
};

template<class T>
class LinkedListNode
{	
public:
	LinkedListNode() : head(nullptr){}
	Node<T>* head;
	Node<T>* currentRoot;
};

template<class T>
class AVLTree
{
private:
	Node<T>* root;
	int numOfNodes;

	int max(int val1, int val2) const;
	static Node<T>* findMinNode(Node<T>* root);
	Node<T>* insertNode(Node<T>* root, T& data, Node<T>* nodeOfList);
	Node<T>* removeNode(Node<T>*, T& data);
	Node<T>* copyNodes(Node<T>* node);
	void mergeArrays(T* const arr1, int size1, T* const arr2, int size2, T* const newArr);
	Node<T>* mergeTreesRecu(int left, int right, Node<T>* root, T* const newArr);


public:
	AVLTree() : root(nullptr), numOfNodes(0), listOfNodes() {}
	AVLTree(const AVLTree& other);
	AVLTree<T>& operator=(const AVLTree<T>& other);
	~AVLTree();
	void deleteTree(Node<T>* root);

	T* findMax(Node<T>* root);
	int calcHeight(Node<T>* node);
	Node<T>* rightRotation(Node<T>* root);
	Node<T>* leftRotation(Node<T>* root);
	Node<T>* balanceTree(Node<T>* root); //a helper method for rotations
	int getBalance(Node<T>* node);
	int getNodesNum() const;
	Node<T>* insert(T* data);
	Node<T>* find(Node<T>* root, const T& data);
	Node<T>* remove(T* data);
	Node<T>* getRoot() const;
	void inOrder(Node<T>* root, T* const output, int& index) const;
	void inOrderMinToMax(Node<T>* node, T* min, T* max, T* const output, int& index) const;
	void mergeTrees(T* const arr1, int size1, T* const arr2, int size2, T* const newArr);
	LinkedListNode<T> listOfNodes;
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

	if (other.next)
	{
		next = new Node<T>(*(other.next));
	}
	else
	{
		next = nullptr;
	}

	if (other.previous)
	{
		previous = new Node<T>(*(other.previous));
	}
	else
	{
		previous = nullptr;
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

	if (other.next)
	{
		next = new Node<T>(*(other.next));
	}
	else
	{
		next = nullptr;
	}

	if (other.previous)
	{
		previous = new Node<T>(*(other.previous));
	}
	else
	{
		previous = nullptr;
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
inline T* AVLTree<T>::findMax(Node<T>* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (root->right == nullptr)
	{
		return root->data;
	}

	return findMax(root->right);
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
inline Node<T>* AVLTree<T>::insertNode(Node<T>* node, T& data, Node<T>* nodeOfList)
{
	if (node == nullptr)
	{
		Node<T>* newNode = new Node<T>(data);
		
		
		if (this->root == nullptr)
		{
			this->root = newNode;
			this->listOfNodes.head = newNode;
		}
		else if (nodeOfList->previous == nullptr && data < *nodeOfList->data)
		{
			newNode->next = nodeOfList;
			nodeOfList->previous = newNode;
			this->listOfNodes.head = newNode;
		}
		else if (nodeOfList->next == nullptr && data > *nodeOfList->data)
		{
			newNode->previous = nodeOfList;
			nodeOfList->next = newNode;
		}
		else if (nodeOfList->next != nullptr && nodeOfList->previous != nullptr) /*&& data > *nodeOfList->data*/
		{
			/*Node<T>* temp = nodeOfList->previous;
			nodeOfList->previous = newNode;
			newNode->next = nodeOfList;
			newNode->previous = temp;
			temp->next = newNode;*/
			Node<T>* temp = nodeOfList->next;
			nodeOfList->next = newNode;
			newNode->next = temp;
			newNode->previous = nodeOfList;
		}
		/*else if (nodeOfList->next != nullptr && nodeOfList->previous != nullptr && data < *(nodeOfList)->data)
		{

		}*/

		this->numOfNodes++;
		return newNode;
	}

	if (data < *(node->data) && data < *(nodeOfList->data))
	{
		if (nodeOfList->previous == nullptr)
		{
			node->left = insertNode(node->left, data, nodeOfList);
		}
		else
		{
			node->left = insertNode(node->left, data, nodeOfList->previous);
		}
	}
	else if(data < *(node->data) && data > *(nodeOfList->data))
	{
		node->left = insertNode(node->left, data, nodeOfList);
	}
	else if (data > *(node->data) && data > *(nodeOfList->data))
	{
		if (nodeOfList->next == nullptr)
		{
			node->right = insertNode(node->right, data, nodeOfList);
		}
		else
		{
			node->right = insertNode(node->right, data, nodeOfList->next);
		}
	}
	else if (data > *(node->data) && data < *(nodeOfList->data))
	{
		node->right = insertNode(node->right, data, nodeOfList);
	}

	node = balanceTree(node);     
	this->root = node;

	return root;
}

template<class T>
inline Node<T>* AVLTree<T>::insert(T* data)
{
	if (find(this->root,* data))
	{
		return nullptr;
	}
	
	listOfNodes.currentRoot = this->root;

	return insertNode(this->root, *data, listOfNodes.currentRoot);
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

//template<class T>
//void AVLTree<T>::removeMinNode(Node<T>* node)
//{
//
//}

template<class T>
inline Node<T>* AVLTree<T>::remove(T* data)
{
	if (!find(this->root, *data))
	{
		return nullptr;
	}

	Node<T>* tempNode = find(this->root, *data);

	//if (tempNode->right != nullptr && tempNode->left != nullptr)
	//{
	//	Node<T>* temp = findMinNode(tempNode->right);
	//	*(tempNode->data) = *(temp->data);
	//	//removeMinNode(temp);
	//}
	
	//Node<T>* next(tempNode->next);

	//if (tempNode->previous == nullptr)
	//{
	//	listOfNodes.head = tempNode->next;
	//	tempNode->next->previous = nullptr;
	//}
	//else if (tempNode->next != nullptr && tempNode->previous != nullptr)
	//{
	//	Node<T>* temp = tempNode->previous;
	//	temp->next = tempNode->next;
	//	tempNode->next->previous = temp;
	//}
	//else if (tempNode->next == nullptr)
	//{
	//	Node<T>* temp = tempNode->previous;
	//	temp->next = nullptr;
	//}
	
	listOfNodes.currentRoot = this->root;
	Node<T>* head = removeNode(root, *data);
	
	return head;
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
			/*if (nodeOfList->previous == nullptr)
			{
				listOfNodes.head = nodeOfList->next;
				nodeOfList->next->previous = nullptr;
			}
			else if (nodeOfList->next != nullptr && nodeOfList->previous != nullptr)
			{
				Node<T>* temp = nodeOfList->previous;
				temp->next = nodeOfList->next;
				nodeOfList->next->previous = temp;
			}
			else if (nodeOfList->next == nullptr)
			{
				Node<T>* temp = nodeOfList->previous;
				temp->next = nullptr;
			}*/

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

			if (toDelete->next == nullptr && toDelete->previous)
			{
				toDelete->previous->next = nullptr;
			}
			else if (toDelete->previous == nullptr && toDelete->next != nullptr)
			{
				listOfNodes.head = toDelete->next;
				toDelete->next->previous = nullptr;
			}
			else if (toDelete->previous != nullptr && toDelete->next != nullptr)
			{
				Node<T>* temp = toDelete->previous;
				temp->next = toDelete->next;
				toDelete->next->previous = temp;
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
	this->listOfNodes.currentRoot = this->root;

	return this->root;
	/*
	if (head == nullptr)
		return nullptr;
	if (data < *head->data)
	{
		head->left = removeNode(head->left, data);
	}
	else if (data > *head->data)
	{
		head->right = removeNode(head->right, data);
	}
	else
	{
		Node<T>* r = head->right;
		if (head->right == nullptr) {
			Node<T>* l = head->left;
			delete(head);
			head = l;
		}
		else if (head->left == nullptr) {
			delete(head);
			head = r;
		}
		else {
			while (r->left != nullptr)
				r = r->left;
			*head->data = *r->data;
			head->right = removeNode(head->right, *r->data);
		}
	}
	
	head = balanceTree(head);
	this->root = head;
	this->listOfNodes.currentRoot = this->root;*/
	
	//return root;
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
inline void AVLTree<T>::mergeArrays(T* const arr1, int size1, T* const arr2, int size2, T* const newArr)
{
	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2)
	{
		if (arr1[i] < arr2[j])
		{
			newArr[k] = arr1[i++];
		}
		else
		{
			newArr[k] = arr2[j++];
		}
		k++;
	}

	while (i < size1)
	{
		newArr[k++] = arr1[i++];
	}
	
	while(j < size2)
	{
		newArr[k++] = arr2[j++];
	}
}

template<class T>
inline Node<T>* AVLTree<T>::mergeTreesRecu(int left, int right, Node<T>* root, T* const newArr)
{
	if (right < left)
	{
		return nullptr;
	}

	int mid = (left + right) / 2;
	root = new Node<T>(newArr[mid]);
	root->left = mergeTreesRecu(left, mid - 1, root->left, newArr);
	root->right = mergeTreesRecu(mid + 1, right, root->right, newArr);

	return root;
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

template<class T>
inline void AVLTree<T>::mergeTrees(T* const arr1, int size1, T* const arr2, int size2, T* const newArr)
{
	mergeArrays(arr1, size1, arr2, size2, newArr);

	Node<T>* root = nullptr;
	Node<T>* newRoot = mergeTreesRecu(0, size1 + size2 - 1, root, newArr);
	this->numOfNodes = size1 + size2;
	this->root = newRoot;
}

#endif


