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

// class RedBlackTree implements the operations in Red Black Tree
class RedBlackTree {
private:
	Structptr root;
	Structptr tnil;
public:
    RedBlackTree() {
		tnil = new Node;
		tnil->color = 0;
		tnil->left = nullptr;
		tnil->right = nullptr;
		root = tnil;
	}

    void insert(int key) {
		// Ordinary Binary Search Insertion
		Structptr node = new Node;
        Structptr x = this->root;
        Structptr y = nullptr;

		node->parent = nullptr;
		node->building_num = key;
		node->color = 1; // new node must be red
            
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
        node->left = tnil;
		node->right = tnil;
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
		stabilizeTree(node);
	}

    void flipColors(Structptr node,Structptr uncle){
        uncle->color = 0;   
        node->parent->color = 0;
        node->parent->parent->color = 1;
    }
    //After inserting new node, Making the tree red-black again
    void stabilizeTree(Structptr node){
		Structptr uncle;
		while (node->parent->color == 1) {
			if (node->parent == node->parent->parent->right) {
				uncle = node->parent->parent->left; // uncle
				if (uncle->color == 1) {
					flipColors(node,uncle);
					node = node->parent->parent;
				} else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotation(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					leftRotation(node->parent->parent);
				}
			} else {
				uncle = node->parent->parent->right; 

				if (uncle->color == 1) {
					flipColors(node,uncle);
					node = node->parent->parent;	
				} else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotation(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					rightRotation(node->parent->parent);
				}
			}
			if (node == root) {
				break;
			}
		}
		root->color = 0;
	}

    //function to execute right rotation
    void rightRotation(Structptr node){
        Structptr temp = node->left;
        node->left = temp->right;
        if(temp->right != tnil){
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if(node->parent == nullptr){
            this->root = temp;
        } else if(node == node->parent->right){
            node->parent->right = temp;
        }else{
            node->parent->left = temp;
        }
        temp->right = node;
        node->parent = temp;
    }

    //function to perform left rotation
    void leftRotation(Structptr gp){
        Structptr temp = gp->right;
        gp->right = temp->left;
        if(temp->left != tnil){
           temp->left->parent = gp; 
        }
        temp->parent = gp->parent;
        if(gp->parent == nullptr){
            this->root = temp;
        }else if (gp = gp->parent->left){
            gp->parent->left = temp;
        }else{
            gp->parent->right = temp;
        }
        temp->left = gp;
        gp->parent = temp;

    }

    void transplantSub(Structptr x, Structptr y){
        if(x->parent == nullptr){
            root = y;
        }else if(x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
        y->parent = x->parent;
    }

    Structptr findBuilding(Structptr node, int key){
        if(node->building_num == key || node == tnil){
            return node;
        }

        if(key<node->building_num){
            return findBuilding(node->left,key);
        }else{
            return findBuilding(node->right,key);
        }
        
    }

    void deleteNode(int key){
        Structptr del = findBuilding(root, key);
        if(del == tnil){
            cout<<"building not in the complex";
            return;
        }
        Structptr temp = del;
        int del_color = temp->color;
        if(del->left == tnil){
            Structptr temp_right = del->right;
            transplantSub(del,temp_right)
        } else if(del->right == tnil){
            Structptr temp_left = del->left;
            transplantSub(del,temp_left);
        }else{
            
        }

    }

    Structptr getRoot(){
        return this->root;
    }
    void printInorder(Structptr root) {
            if(root == tnil){
                return;
            }
            printInorder(root->left);
            cout<<root->building_num<<"; ";
            cout<<root->color<<"; \n";
            printInorder(root->right);
            return;
	    }

};

int main() {
	RedBlackTree bst;
	bst.insert(8);
    cout<<"first print";
    bst.printInorder(bst.getRoot());
	bst.insert(18);
	bst.insert(5);
    cout<<"second";
    bst.printInorder(bst.getRoot());
	bst.insert(15);
    cout<<"\n third";
    bst.printInorder(bst.getRoot());
    cout<<" fourth\n";
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.printInorder(bst.getRoot());
    bst.deleteNode(50);
	return 0;
}