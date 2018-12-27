
#define _LAZYBST_H_

class LazyBST {
private:
	class node {
	public:
		int height;
		int size;
		int data;
		node *leftNode;
		node *rightNode;
		node(int key);

	};
	node* root;
	int insertRec(node *&nodePtr, node *&newNode);
	void inorderRec(node*& tempNode);
	void rebalance(node*& nodePtr);
	void fillArray(node*& nodePtr, int *tempArray, int &next);
	int findMax(node*& tempNode);
	void removeNode(int key, node*& tempNode);
	node* arrayMakeTree(int* tempArray, int start, int end);
	int getHeight(node *tempNode);
	int getSize(node *tempNode);
	void destroyTree(node* tempNode);
	bool locateRec(const char *position, int& key, node*& tempNode, int index);
	//void copyRec(node*& newNode, node* const &tempNode);

public:
	LazyBST();
	LazyBST(const LazyBST& other);
	~LazyBST();
	const LazyBST& operator=(const LazyBST& rhs);
	void insert(int key);
	bool remove(int key);
	bool find(int key);
	void inorder();
	bool locate(const char *position, int& key);

};

