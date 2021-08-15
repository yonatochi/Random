#include <iostream>
using namespace std;

enum Color {RED, BLACK};
struct Node{
	int data;
	Color color;
	Node *left, *right, *parent;
};

class RedBlackTree{
	private:
		Node* root;
	protected:
		void rotateLeft(Node *&x){
			Node* y = x->right;
			x->right = y->left;
			if(y->left!=NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if(x->parent==NULL)
				root = y;
			else if(x==x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void rotateRight(Node *&x){
			Node* y = x->left;
			x->left = y->right;
			if(y->right!=NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if(x->parent==NULL)
				root = y;
			else if(x==x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
	public:		
		RedBlackTree(){
			root = NULL;
		}
		void insertRB(int val){
			Node* z;
			z->data = val;
			Node* y = NULL;
			Node* x = root;
			while(x!=NULL){
				y = x;
				if(z->data<x->data)
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if(y==NULL)
				root = z;
			else if(z->data<y->data)
				y->left = z;
			else
				y->right = z;
			z->left = NULL;
			z->right = NULL;
			z->color = RED;
			insertRBfixup(z);
		}
		void insertRBfixup(Node *&z){
			while(z->parent->color==RED){
				if(z->parent==z->parent->parent->left){
					Node* y = z->parent->parent->right;
					if(y->color==RED){ // Case 1
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else if(z==z->parent->right){ // Case 2
						z = z->parent;
						rotateLeft(z);
					}
					// Case 3
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateRight(z->parent->parent);
				}
				else{
					Node* y = z->parent->parent->left;
					if(y->color==RED){ // Case 1
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else if(z==z->parent->left){ // Case 2
						z = z->parent;
						rotateRight(z);
					}
					// Case 3
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateLeft(z->parent->parent);
				}
			}
			root->color = BLACK;
		}
};

int main(){
	RedBlackTree T;
	T.insertRB(2);
	T.insertRB(7);
	T.insertRB(9);
	T.insertRB(3);
	T.insertRB(1);
	T.insertRB(4);
	return 0;
}
