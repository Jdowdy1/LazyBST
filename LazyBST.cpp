#include "LazyBST.h"
#include <iostream>
#include <cmath>
#include <minmax.h>
using namespace std;
LazyBST::LazyBST() {

	root = NULL;

}
LazyBST::~LazyBST() {
	destroyTree(root);
}
void LazyBST::destroyTree(node *tempNode)
{
	if (tempNode != NULL)
	{
		destroyTree(tempNode->leftNode);
		destroyTree(tempNode->rightNode);
		delete tempNode;
		tempNode = NULL;
	}
}
/*
LazyBST::LazyBST(const LazyBST& other){
copyRec(this->root, other.root);
}
void LazyBST::copyRec(node*& newNode, node* const &tempNode){
if (tempNode == NULL){
newNode = NULL;
}
newNode = new node(tempNode->data);
newNode->size = tempNode->size;
newNode->height = tempNode->height;

copyRec(newNode->leftNode, tempNode->leftNode);
copyRec(newNode->rightNode, tempNode->rightNode);
}*/
LazyBST::node::node(int key) {
	data = key;
	leftNode = NULL;
	rightNode = NULL;
	height = 0;
	size = 1;
}
//const LazyBST& LazyBST::operator=(const LazyBST& rhs){

//}
bool LazyBST::remove(int key) {
	if (find(key) == true) {
		removeNode(key, root);
		return true;
	}
	else
		return false;
}
void LazyBST::removeNode(int key, node*& tempNode)
{
	if (tempNode != NULL && tempNode->height > 3)
	{

		if (tempNode->leftNode->size >= tempNode->rightNode->size * 2)
			rebalance(tempNode);
		else if (tempNode->rightNode->size >= tempNode->leftNode->size * 2)
			rebalance(tempNode);
	}

	if (tempNode == NULL) {
		return;
	}
	// item not found; do nothing
	// continue to traverse until we find the element
	if (key < tempNode->data)
	{
		removeNode(key, tempNode->leftNode);
	}
	else if (tempNode->data < key) {
		removeNode(key, tempNode->rightNode);
	}
	else if (tempNode->leftNode != NULL && tempNode->rightNode != NULL)
		// two children
	{
		// find right�s lowest value
		tempNode->data = findMax(tempNode->leftNode);
		// now delete that found value
		removeNode(tempNode->data, tempNode->rightNode);
	}
	else
		// zero or one child
	{
		node* oldNode = tempNode;
		// ternary operator
		tempNode = (tempNode->leftNode != NULL) ? tempNode->leftNode : tempNode->rightNode;
		delete oldNode;
	}
	getSize(tempNode);
	getHeight(tempNode);
}
int LazyBST::findMax(node*& tempNode) {
	if (tempNode == NULL)
		return NULL;
	else if (tempNode->rightNode == NULL) {
		return tempNode->data;
	}
	else {
		return findMax(tempNode->rightNode);
	}
}
bool LazyBST::find(int key) {
	node *nodePtr = root;
	while (nodePtr)
	{
		if (nodePtr->data == key)
			return true;
		else if (key < nodePtr->data)
			nodePtr = nodePtr->leftNode;
		else
			nodePtr = nodePtr->rightNode;
	}
	return false;
}
void LazyBST::inorder() {
	inorderRec(root);

}
void LazyBST::inorderRec(node*& tempNode) {
	if (tempNode == NULL)
		return;

	cout << "(";
	inorderRec(tempNode->leftNode);

	cout << tempNode->data << ":" << tempNode->height << ":" << tempNode->size;

	inorderRec(tempNode->rightNode);

	cout << ")";
}
int LazyBST::insertRec(node *&nodePtr, node *&newNode)
{

	if (nodePtr != NULL && nodePtr->height > 3)
	{

		if (nodePtr->leftNode->size >= nodePtr->rightNode->size * 2)
			rebalance(nodePtr);
		else if (nodePtr->rightNode->size >= nodePtr->leftNode->size * 2)
			rebalance(nodePtr);
	}



	int temp = 0;
	if (nodePtr != NULL && newNode->data == nodePtr->data)
	{
		return -1;
	}

	if (nodePtr == NULL)
	{
		nodePtr = newNode; // Insert the node.
		return 0;
	}
	else if (newNode->data < nodePtr->data)
	{
		temp = insertRec(nodePtr->leftNode, newNode); // Search the left branch.

	}
	else
	{
		temp = insertRec(nodePtr->rightNode, newNode); // Search the right branch.

	}
	if (temp != -1) {
		nodePtr->height = getHeight(nodePtr);
		nodePtr->size = getSize(nodePtr);
	}
	return temp;

}
void LazyBST::insert(int key)
{
	node *newNode = NULL; // Pointer to a new node.
						  // Create a new node and store num in it.
	newNode = new node(key);

	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		insertRec(root, newNode);

	}

}
void LazyBST::rebalance(node*& nodePtr) {
	int a = 0;
	int n = nodePtr->size;
	int *tempArray = new int[nodePtr->size];

	fillArray(nodePtr, tempArray, a);
	delete nodePtr;
	nodePtr = NULL;

	nodePtr = arrayMakeTree(tempArray, 0, n - 1);
	delete[] tempArray;
}
void LazyBST::fillArray(node*& nodePtr, int *tempArray, int &next) {
	if (nodePtr == NULL) {
		return;
	}
	fillArray(nodePtr->leftNode, tempArray, next);

	tempArray[next] = nodePtr->data;
	next++;

	fillArray(nodePtr->rightNode, tempArray, next);
	delete nodePtr->leftNode;
	delete nodePtr->rightNode;
	nodePtr->leftNode = NULL;
	nodePtr->rightNode = NULL;



}
LazyBST::node* LazyBST::arrayMakeTree(int *tempArray, int start, int end)
{
	/* Base Case */

	if (start > end)
		return NULL;

	/* Get the middle element and make it root */
	int mid = (start + end) / 2;

	node *tempNode = new node(tempArray[mid]);


	/* Recursively construct the left subtree and make it
	left child of root */
	tempNode->leftNode = arrayMakeTree(tempArray, start, mid - 1);

	/* Recursively construct the right subtree and make it
	right child of root */
	tempNode->rightNode = arrayMakeTree(tempArray, mid + 1, end);

	tempNode->height = getHeight(tempNode);
	tempNode->size = getSize(tempNode);
	return tempNode;
}
bool LazyBST::locate(const char *position, int& key) {
	bool check;
	check = locateRec(position, key, root, 0);
	return check;
}
bool LazyBST::locateRec(const char *position, int& key, node*& tempNode, int index) {
	bool check = false;
	if (tempNode == NULL) {
		check = false;
		return check;
	}


	if (position[index] == 'L') {
		check = locateRec(position, key, tempNode->leftNode, index + 1);
	}
	else if (position[index] == 'R') {
		check = locateRec(position, key, tempNode->rightNode, index + 1);
	}
	else {
		key = tempNode->data;
		check = true;
		return check;
	}
	return check;
}
int LazyBST::getHeight(node *tempNode) {
	int left = -1;
	int right = -1;
	if (tempNode == NULL) {
		return -1;
	}
	else {
		if (tempNode->leftNode != NULL) {
			left = tempNode->leftNode->height;
		}
		if (tempNode->rightNode != NULL) {
			right = tempNode->rightNode->height;
		}
		return tempNode->height = max(left, right) + 1;
	}

}
int LazyBST::getSize(node *tempNode) {
	int left = 0;
	int right = 0;
	if (tempNode == NULL) {
		return 0;
	}

	else {
		if (tempNode->leftNode != NULL) {
			left = tempNode->leftNode->size;
		}
		if (tempNode->rightNode != NULL) {
			right = tempNode->rightNode->size;
		}
		return tempNode->size = (left + right) + 1;
	}
}

