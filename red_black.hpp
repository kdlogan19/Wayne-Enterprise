#include <iostream>
// node structure
struct Node {
	int building_num; // building_num
    int executionTime;
    int totalTime;
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node* Structptr;
std::ofstream fout("output.txt");
// class RedBlackTree implements the operations in Red Black Tree
class RedBlackTree {
private:
    Structptr root;
    Structptr tnil;
public:

    //constructor of Red-Black Tree`
    RedBlackTree() {
		tnil = new Node;
		tnil->color = 0; //initializing all external nodes as black nodes
		tnil->left = tnil;
		tnil->right = tnil;
		root = tnil;
	}

    //initialization of struct node
    Structptr initializeNode(int num,int time){
        Structptr newNode = new Node;
        newNode->parent = tnil;
		newNode->building_num = num;
        newNode->totalTime = time;
        newNode->executionTime = 0;
		newNode->color = 1; // new node must be red
        newNode->left = tnil;
		newNode->right = tnil;
        return newNode;
    }

    //Inserting a new node whenever a new building construction begins
    void insert(Structptr node) {
		// Ordinary Binary Search Insertion
		//Structptr node = initializeNode(buildingNum,totalTime);
        Structptr x = root;
        Structptr y = tnil;            
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
		if (y == tnil) {
			root = node;
		} else if (node->building_num < y->building_num) {
			y->left = node;
		} else {
			y->right = node;
		}
		// if new node is a root node, simply return
		if (node->parent == tnil){
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == tnil) {
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
                    // When uncle is red
                    flipColors(node,uncle);
                    node = node->parent->parent;	
                } else {
                    if (node == node->parent->right) {
                        //When node is right child, first we perform left rotation
                        node = node->parent;
                        leftRotation(node);
                    }
                    //we perform right rotation
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotation(node->parent->parent);
                }
            }
            //When new node is in the right subtree of grandparant  
            else {
                uncle = node->parent->parent->left; // uncle being left subtree of gp
                if (uncle->color == 1) {
                    // When uncle is red
                    flipColors(node,uncle);
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        // When node is left child or right tree(RL)
                        node = node->parent;
                        rightRotation(node);
                    }
                    // We perform a left rotation
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
        if(node->parent == tnil){
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
        if(gp->parent == tnil){
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
        if(x->parent == tnil){
            root = y;
        }else if(x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
        if(y != tnil){
            y->parent = x->parent;
        }
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
        while(node->left != tnil){
            node = node->left;
        }
        return node;
    }

    void deleteNode(int key){
        Structptr del = findBuilding(root, key);
        if(del == tnil){
            std::cout<<"building not in the complex";
            return;
        }
        Structptr y = del;
        Structptr temp;
        int del_color = y->color;
        if(del->left == tnil){
            temp = del->right;
            transplantSub(del,del->right);
        } else if (del->right == tnil){
            temp = del->left;
            transplantSub(del,del->left);
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

    Structptr getTNIL(){
        return tnil;
    }

    Structptr getRoot(){
        return this->root;
    }

   void printInorder(Structptr node,int val1,int val2,std::string& temp){
           
            if(node == tnil){
                return;
            }
            
            printInorder(node->left, val1,val2, temp);
            if(val1 <= node->building_num<=val2){
                temp = temp + "(" + std::to_string(node->building_num) + "," + std::to_string(node->executionTime) + "," + std::to_string(node->totalTime) + "),";
            }
            printInorder(node->right,val1,val2, temp);
            return;
	    }

};


