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

    Structptr initializeNode(int key){
        Structptr newNode = new Node;
        newNode->parent = nullptr;
		newNode->building_num = key;
		newNode->color = 1; // new node must be red
        newNode->left = tnil;
		newNode->right = tnil;
        return newNode;
    }

    void insert(int key) {
		// Ordinary Binary Search Insertion
		Structptr node = initializeNode(key);
        Structptr x = this->root;
        Structptr y = nullptr;            
		while (x != tnil) {
			y = x;
			if (node->building_num < x->building_num) {
				x = x->left;
			} else {
				x = x->right;
			}
            //cout<<"\n \n **parent of new node"<<y->building_num<<"  "<<node->building_num;
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
            //When new node is in the left subtree of grandparant
            if (node->parent == node->parent->parent->left){
                uncle = node->parent->parent->right; // uncle

                if (uncle->color == 1) {
                    // mirror case 3.1
                    flipColors(node,uncle);
                    node = node->parent->parent;	
                } else {
                    if (node == node->parent->right) {
                        // mirror case 3.2.2
                        node = node->parent;
                        leftRotation(node);
                    }
                    // mirror case 3.2.1
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotation(node->parent->parent);
                }
            }
            //When new node is in the right subtree of grandparant  
            else {
                uncle = node->parent->parent->left; // uncle
                if (uncle->color == 1) {
                    // case 3.1
                    flipColors(node,uncle);
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        // case 3.2.2
                        node = node->parent;
                        rightRotation(node);
                    }
                    // case 3.2.1
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    leftRotation(node->parent->parent);
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
        }else if (gp == gp->parent->left){
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

    Structptr treeMinimum(Structptr node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    void deleteNode(int key){
        Structptr del = findBuilding(root, key);
        if(del == tnil){
            cout<<"building not in the complex";
            return;
        }
        Structptr y = del;
        Structptr temp;
        int del_color = y->color;
        if(del->left == tnil){
            temp = del->right;
            transplantSub(del,temp);
        } else if (del->right == tnil){
            temp = del->left;
            transplantSub(del,temp);
        } else {
            y = treeMinimum(del->right);
            del_color = y->color;
            temp = y->right;
            if (y->parent == del){
                temp->parent = y;
            } else {
                transplantSub(y,y->right);
                y->right = del->right;
                y->right->parent = y;
            }
            transplantSub(del,y);
            y->left = del->left;
            y->left->parent = y;
            y->color = del-> color;
            }
        delete del;
        if(del_color == 0){
            fixDeletion(temp);
        }

    }

    void fixDeletion(Structptr node){
        Structptr temp;             //
        while(node != root && node->color == 0){
            if(node == node->parent->left){
                temp = node->parent->right;
                //case 1
                if(temp->color == 1){
                    temp->color = 0;
                    node->parent->color = 1;
                    leftRotation(node->parent);
                    temp = node->parent->right;
                }
                //case 2
                if(temp->left->color == 0 && temp->right->color == 0){
                    temp -> color = 1;
                    node = node->parent;
                }
                //case 3 
                else {
                    if (temp->right->color == 0){
                        temp->left->color = 0;
                        temp->color = 1;
                        rightRotation(temp);
                        temp = node->parent->right;
                    }
                    temp->color = node->parent->color;
                    node->parent->color  = 0;
                    temp->right->color = 0;
                    leftRotation(node->parent);
                    node = root;
                }
            }else {
                temp = node->parent->left;
                if (temp->color == 1) {
                    temp->color = 0;
                    node->parent->color = 1;
                    rightRotation(node->parent);
                    temp = node->parent->left;
                }
                if (temp->left->color == 0 && temp->right->color == 0) {
                    temp->color = 1;
                    node = node->parent;
                }
                else {
                    if (temp->left->color == 0) {
                        temp->right->color = 0;
                        temp->color = 1;
                        leftRotation(temp);
                        temp = node->parent->left;
                    }
                    temp->color = node->parent->color;
                    node->parent->color = 0;
                    temp->left->color = 0;
                    rightRotation(node->parent);
                    node = root;
                }
            }
        }
        node->color = 0;
    }

    Structptr getRoot(){
        return this->root;
    }
    void printInorder(Structptr node) {
            if(node == tnil){
                return;
            }
        
                printInorder(node->left);
                if(node != this->root){
                    cout<<node->building_num<<"; ";
                    cout<<node->parent->building_num<<";";
                    cout<<node->color<<"; \n";
                }
                printInorder(node->right);
                return;
	    }

};

int main() {

	RedBlackTree bst;
    int x;
    for (int i = 0; i<5;++i){
        cin>>x;
        bst.insert(x);
    }

    cout<<bst.getRoot()->building_num<<"\n";
    bst.printInorder(bst.getRoot());
	return 0;
}