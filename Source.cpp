#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "worldcup23a1.h"

using namespace std;

void printTree(Node<int>* root, int space = 0)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += 10;

	// Process right child first
	printTree(root->right, space);

	// Print current node after space
	// count
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << *(root->data) << "\n";

	// Process left child
	printTree(root->left , space);
}

int main()
{
	AVLTree<int> tree;
	int arr[5] = { 1,2,0,8,7 };
	for (int i = 0; i < 5; i++)
	{
		tree.insert(arr[i]);
	}

	int min = 1, max = 6;
	int index = 0;
	int* const output = new int[6];
	tree.inOrderMinToMax(tree.getRoot(), &min, &max, output, index);

	/*world_cup_t wc;
	wc.add_team(123, 5);
	wc.add_player(45, 123, 4, 5, 6, true);*/
	return 0;
}

///*
// * testAVLTree.cpp
// *
// *  Created on: 19 ���� 2013
// *      Author: shirel
// */
//
//#include "avl_tree.h"
//#include <vector>
//#include <ostream>
//#include <random>
//#include <chrono>
//#include <algorithm>
//#include <iostream>
//
//
//using namespace std;
//
//int main() {
//	AVLTree<int> tree;
//	AVLTree<int> tree2;
//
//	//Specific Cases
//
//	/*correct output for the four next cases
//	1 BF: 0 Height: 0
//	2 BF: 0 Height: 1
//	3 BF: 0 Height: 0 */
//
//	//basic LL root change
//
//	int arr[9] = { 13, 10, 15, 5, 11, 16, 4, 6, 7};
//	
//	tree.insert(tree.getRoot(), &arr[0]);
//	tree.insert(tree.getRoot(), &arr[1]);
//	tree.insert(tree.getRoot(), &arr[2]);
//	tree.insert(tree.getRoot(), &arr[3]);
//	tree.insert(tree.getRoot(), &arr[4]);
//	tree.insert(tree.getRoot(), &arr[5]);
//	tree.insert(tree.getRoot(), &arr[6]);
//	tree.insert(tree.getRoot(), &arr[7]);
//	tree.insert(tree.getRoot(), &arr[8]);
//	
//	int min = 5;
//	int max = 14;
//	int size = tree.getNodesNumberBetweenMinMax(tree.getRoot(), &min, &max);
//	int** arr33 = new int * [size];
//	tree.InorderMinMax(arr33, &min, &max);
//	for(int i =0; i<size; i++){
//		printf("%d ", *arr33[i]);
//	}
//
//	//int** arr23 = new int* [4];
//	//tree.fillArrayMaxToMinInTree(arr23);
//
//	/*
//	int arr2345[4] = { 0 };
//	for (int i = 0; i < 4; i++) {
//		arr2345[i] = *arr23[i];
//	}
//
//	*/
//	/*
//	tree.insert(tree.getRoot(), &arr[4]);
//	tree.insert(tree.getRoot(), &arr[5]);
//	tree.insert(tree.getRoot(), &arr[6]);
//	tree.insert(tree.getRoot(), &arr[7]);
//	*/
//	//tree.printTree();
//	//tree.remove(tree.getRoot(), &arr[0]);
//
//	//tree.remove(0);
//	//tree.remove(1);
//	
//	//tree.insert(tree.getRoot(), &arr[8]);
//	/*
//	tree2.insert(tree2.getRoot(), &arr[4]);
//	tree2.insert(tree2.getRoot(), &arr[5]);
//	tree2.insert(tree2.getRoot(), &arr[6]);
//	tree2.insert(tree2.getRoot(), &arr[7]);
//
//	int** array1 = new int*[4];
//	int** array2 = new int*[4];
//	int** newArray = new int*[8];
//	tree.fillArray(array1);
//	tree2.fillArray(array2);
//
//	tree.mergeTree(array1, 4, array2, 4, newArray);
//
//	cout << endl;
//	
//
//
//
//	////basic LR root change
//	//tree.insert(3, 3);
//	//tree.insert(1, 1);
//	//tree.insert(2, 2);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////basic RR root change
//	//tree.insert(1, 1);
//	//tree.insert(2, 2);
//	//tree.insert(3, 3);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////basic RL root change
//	//tree.insert(1, 1);
//	//tree.insert(3, 3);
//	//tree.insert(2, 2);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////basic LR not root change
//	///*correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 0 Height: 1
//	//3 BF: 0 Height: 0
//	//4 BF: 1 Height: 2
//	//5 BF: 0 Height: 0
//	//6 BF: 1 Height: 3
//	//7 BF: 0 Height: 0
//	//8 BF: 1 Height: 1 */
//	//tree.insert(6, 6);
//	//tree.insert(4, 4);
//	//tree.insert(8, 8);
//	//tree.insert(3, 3);
//	//tree.insert(5, 5);
//	//tree.insert(7, 7);
//	//tree.insert(1, 1);
//	//tree.insert(2, 2);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	///*basic LL not root change
//	//correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 0 Height: 1
//	//3 BF: 0 Height: 0
//	//4 BF: 1 Height: 2
//	//5 BF: 0 Height: 0
//	//6 BF: 1 Height: 3
//	//7 BF: 0 Height: 0
//	//8 BF: 1 Height: 1 */
//	//tree.insert(6, 6);
//	//tree.insert(4, 4);
//	//tree.insert(8, 8);
//	//tree.insert(3, 3);
//	//tree.insert(5, 5);
//	//tree.insert(7, 7);
//	//tree.insert(2, 2);
//	//tree.insert(1, 1);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////basic RR not root change
//	///*correct output
//	// * 1 BF: 0 Height: 0
//	//2 BF: 0 Height: 1
//	//3 BF: 0 Height: 0
//	//5 BF: 1 Height: 2
//	//7 BF: 0 Height: 0*/
//	//tree.insert(5, 5);
//	//tree.insert(7, 7);
//	//tree.insert(1, 1);
//	//tree.insert(2, 2);
//	//tree.insert(3, 3);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////basic RL not root change
//	///*correct output
//	// * 1 BF: 0 Height: 0
//	//2 BF: 0 Height: 1
//	//3 BF: 0 Height: 0
//	//5 BF: 1 Height: 2
//	//7 BF: 0 Height: 0*/
//	//tree.insert(5, 5);
//	//tree.insert(7, 7);
//	//tree.insert(1, 1);
//	//tree.insert(3, 3);
//	//tree.insert(2, 2);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////root deletion no roll successor is a neighbour
//	///*correct output
//	//2 BF: 0 Height: 0
//	//3 BF: 1 Height: 1
//	//5 BF: 1 Height: 2
//	//6 BF: 0 Height: 0*/
//	//tree.insert(4, 4);
//	//tree.insert(5, 5);
//	//tree.insert(3, 3);
//	//tree.insert(2, 2);
//	//tree.insert(6, 6);
//	//tree.AVLRemove(4);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////root deletion no roll successor is not a neighbour
//	///*correct output
//	//2 BF: 0 Height: 0
//	//3 BF: 1 Height: 1
//	//5 BF: 0 Height: 2
//	//6 BF: 0 Height: 0
//	//7 BF: 0 Height: 1
//	//8 BF: 0 Height: 0 */
//	//tree.insert(4, 4);
//	//tree.insert(3, 3);
//	//tree.insert(7, 7);
//	//tree.insert(2, 2);
//	//tree.insert(5, 5);
//	//tree.insert(8, 8);
//	//tree.insert(6, 6);
//	//tree.AVLRemove(4);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion no roll successor is a neighbour case7
//	///*correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 1 Height: 1
//	//4 BF: 1 Height: 2
//	//5 BF: 0 Height: 0
//	//7 BF: 1 Height: 3
//	//8 BF: -1 Height: 1
//	//9 BF: 0 Height: 0*/
//	//tree.insert(7, 7);
//	//tree.insert(3, 3);
//	//tree.insert(8, 8);
//	//tree.insert(2, 2);
//	//tree.insert(4, 4);
//	//tree.insert(9, 9);
//	//tree.insert(5, 5);
//	//tree.insert(1, 1);
//	//tree.AVLRemove(3);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion no roll successor is not a neighbour case8
//	///*correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 1 Height: 1
//	//5 BF: 0 Height: 2
//	//6 BF: 0 Height: 0
//	//7 BF: 0 Height: 1
//	//8 BF: 0 Height: 0
//	//9 BF: 0 Height: 3
//	//10 BF: 0 Height: 0
//	//12 BF: -1 Height: 2
//	//13 BF: -1 Height: 1
//	//14 BF: 0 Height: 0*/
//	//tree.insert(9, 9);
//	//tree.insert(3, 3);
//	//tree.insert(12, 12);
//	//tree.insert(2, 2);
//	//tree.insert(7, 7);
//	//tree.insert(10, 10);
//	//tree.insert(13, 13);
//	//tree.insert(1, 1);
//	//tree.insert(5, 5);
//	//tree.insert(8, 8);
//	//tree.insert(14, 14);
//	//tree.insert(6, 6);
//	//tree.AVLRemove(3);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion causing LR case9
//	///*correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 0 Height: 1
//	//3 BF: 0 Height: 0
//	//4 BF: 0 Height: 2
//	//7 BF: -1 Height: 1
//	//8 BF: 0 Height: 0*/
//	//tree.insert(7, 7);
//	//tree.insert(2, 2);
//	//tree.insert(8, 8);
//	//tree.insert(1, 1);
//	//tree.insert(4, 4);
//	//tree.insert(9, 9);
//	//tree.insert(3, 3);
//	//tree.AVLRemove(9);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion causing LL case10
//	///*correct output
//	//1 BF: 0 Height: 0
//	//2 BF: 1 Height: 1
//	//3 BF: 0 Height: 2
//	//4 BF: 0 Height: 0
//	//7 BF: 0 Height: 1
//	//8 BF: 0 Height: 0*/
//	//tree.insert(7, 7);
//	//tree.insert(3, 3);
//	//tree.insert(8, 8);
//	//tree.insert(2, 2);
//	//tree.insert(4, 4);
//	//tree.insert(9, 9);
//	//tree.insert(1, 1);
//	//tree.AVLRemove(9);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion causing RR case11
//	///*correct output
//	//2 BF: 0 Height: 0
//	//3 BF: 0 Height: 1
//	//7 BF: 0 Height: 0
//	//8 BF: 0 Height: 2
//	//9 BF: -1 Height: 1
//	//10 BF: 0 Height: 0*/
//	//tree.insert(3, 3);
//	//tree.insert(2, 2);
//	//tree.insert(8, 8);
//	//tree.insert(7, 7);
//	//tree.insert(1, 1);
//	//tree.insert(9, 9);
//	//tree.insert(10, 10);
//	//tree.AVLRemove(1);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////node deletion causing RL case12
//	///*correct output
//	//* 2 BF: 0 Height: 0
//	//3 BF: 1 Height: 1
//	//7 BF: 0 Height: 2
//	//10 BF: 0 Height: 0
//	//13 BF: 0 Height: 1
//	//14 BF: 0 Height: 0*/
//	//tree.insert(3, 3);
//	//tree.insert(2, 2);
//	//tree.insert(13, 13);
//	//tree.insert(7, 7);
//	//tree.insert(1, 1);
//	//tree.insert(14, 14);
//	//tree.insert(10, 10);
//	//tree.AVLRemove(1);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////double rotations RL and RR case 13
//	///*correct output
//	//3 BF: 0 Height: 0
//	//5 BF: 0 Height: 1
//	//7 BF: 0 Height: 0
//	//9 BF: 0 Height: 2
//	//11 BF: 0 Height: 0
//	//13 BF: 1 Height: 1
//	//15 BF: 0 Height: 3
//	//17 BF: 0 Height: 0
//	//19 BF: -1 Height: 2
//	//21 BF: -1 Height: 1
//	//23 BF: 0 Height: 0*/
//	//tree.insert(9, 9);
//	//tree.insert(3, 3);
//	//tree.insert(15, 15);
//	//tree.insert(1, 1);
//	//tree.insert(7, 7);
//	//tree.insert(13, 13);
//	//tree.insert(19, 19);
//	//tree.insert(5, 5);
//	//tree.insert(11, 11);
//	//tree.insert(17, 17);
//	//tree.insert(21, 21);
//	//tree.insert(23, 23);
//	//tree.AVLRemove(1);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////double rotations RR and RR case 14
//	///*correct output
//	//3 BF: 0 Height: 0
//	//7 BF: 0 Height: 1
//	//8 BF: 0 Height: 0
//	//9 BF: 0 Height: 2
//	//11 BF: 0 Height: 0
//	//13 BF: 1 Height: 1
//	//15 BF: 0 Height: 3
//	//17 BF: 0 Height: 0
//	//19 BF: -1 Height: 2
//	//21 BF: -1 Height: 1
//	//23 BF: 0 Height: 0*/
//	//tree.insert(9, 9);
//	//tree.insert(3, 3);
//	//tree.insert(15, 15);
//	//tree.insert(1, 1);
//	//tree.insert(7, 7);
//	//tree.insert(13, 13);
//	//tree.insert(19, 19);
//	//tree.insert(8, 8);
//	//tree.insert(11, 11);
//	//tree.insert(17, 17);
//	//tree.insert(21, 21);
//	//tree.insert(23, 23);
//	//tree.AVLRemove(1);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////double rotations RL and LL case 15
//	///*correct output
//	//6 BF: 0 Height: 0
//	//7 BF: 1 Height: 1
//	//8 BF: 1 Height: 2
//	//9 BF: 0 Height: 0
//	//10 BF: 0 Height: 3
//	//11 BF: -1 Height: 1
//	//12 BF: 0 Height: 0
//	//15 BF: 0 Height: 2
//	//17 BF: 0 Height: 0
//	//18 BF: 0 Height: 1
//	//20 BF: 0 Height: 0
//	// */
//	//tree.insert(15, 15);
//	//tree.insert(10, 10);
//	//tree.insert(20, 20);
//	//tree.insert(8, 8);
//	//tree.insert(11, 11);
//	//tree.insert(17, 17);
//	//tree.insert(21, 21);
//	//tree.insert(7, 7);
//	//tree.insert(9, 9);
//	//tree.insert(12, 12);
//	//tree.insert(18, 18);
//	//tree.insert(6, 6);
//	//tree.AVLRemove(21);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////double rotations LR and LL case 16
//	///*correct output
//	//6 BF: 0 Height: 0
//	//7 BF: 1 Height: 1
//	//8 BF: 1 Height: 2
//	//9 BF: 0 Height: 0
//	//10 BF: 0 Height: 3
//	//11 BF: -1 Height: 1
//	//12 BF: 0 Height: 0
//	//15 BF: 0 Height: 2
//	//20 BF: 0 Height: 0
//	//21 BF: 0 Height: 1
//	//22 BF: 0 Height: 0 */
//	//tree.insert(15, 15);
//	//tree.insert(10, 10);
//	//tree.insert(20, 20);
//	//tree.insert(8, 8);
//	//tree.insert(11, 11);
//	//tree.insert(17, 17);
//	//tree.insert(22, 22);
//	//tree.insert(7, 7);
//	//tree.insert(9, 9);
//	//tree.insert(12, 12);
//	//tree.insert(21, 21);
//	//tree.insert(6, 6);
//	//tree.AVLRemove(17);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////delete node cause LR
//	///*correct output
//	// * 2 BF: 0 Height: 0
//	//3 BF: -1 Height: 2
//	//4 BF: 0 Height: 0
//	//6 BF: 1 Height: 1*/
//
//	//tree.insert(5, 5);
//	//tree.insert(3, 3);
//	//tree.insert(6, 6);
//	//tree.insert(2, 2);
//	//tree.insert(4, 4);
//	//tree.AVLRemove(5);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	////delete node cause LR
//	///*correct output
//	// * 2 BF: 0 Height: 0
//	//3 BF: 0 Height: 1
//	//6 BF: 0 Height: 0*/
//	//tree.insert(5, 5);
//	//tree.insert(3, 3);
//	//tree.insert(6, 6);
//	//tree.insert(2, 2);
//	//tree.AVLRemove(5);
//	//tree.printTree();
//	//tree.TestsRemove(tree.GetRoot());
//
//	//cout << endl;
//
//	//std::vector<int> vector;
//	//for (int i = 1; i <= 100; i++) vector.push_back(i);
//
//	////Randomly insert and removes nodes
//	//for (int k = 0; k < 20; ++k) {
//	//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//	//	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));
//	//	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
//	//		tree.insert(*it, *it);
//
//	//	}
//	//	tree.printTree();
//	//	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));
//	//	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
//	//		tree.AVLRemove(*it);
//	//		tree.printTree();
//
//	//	}
//	//	tree.TestsRemove(tree.GetRoot());
//	//	tree.printTree();
//	//	cout << '\n';
//	//}
//
//	return 0;
//}