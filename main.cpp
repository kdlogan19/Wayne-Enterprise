#include <iostream>

using namespace std;

// building_num structure that represents a node in the tree
struct Node {
	int building_num; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *Structptr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
	Structptr root;
	Structptr tnil;
public:
    RBTree() {
		tnil = new Node;
		tnil->color = 0;
		tnil->left = nullptr;
		tnil->right = nullptr;
		root = tnil;
	}

    void insert(int key) {
		// Ordinary Binary Search Insertion
		Structptr node = new Node;
		node->parent = nullptr;
		node->building_num = key;
		node->left = tnil;
		node->right = tnil;
		node->color = 1; // new node must be red

		Structptr y = nullptr;
		Structptr x = this->root;

		while (x != tnil) {
			y = x;
			if (node->building_num < x->building_num) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->building_num < y->building_num) {
			y->left = node;
		} else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		//fixInsert(node);
	}

    void prettyPrint() {
        
            if (root != tnil) {
                cout<<root->building_num<<" ";
                root = root->left;
            }else{
                cout<<"root null";
            }
	    }

};

int main() {
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	//bst.deleteNode(25);
	bst.prettyPrint();
	return 0;
}