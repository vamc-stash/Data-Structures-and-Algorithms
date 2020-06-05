#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

using namespace std;

struct Node{
	int data;
	struct Node *left, *right;
	int height;
};

struct Node *newnode(int key){
	struct Node *node = new Node;
	node -> data = key;
	node -> left = node -> right = NULL;
	node -> height = 1;
	return node;
}

//
int height(struct Node *node){
	if(node == NULL)
		return 0;
	return (node -> height);
} 
int getBalance(struct Node *node){
	if(node == NULL)
		return 0;
	return height(node->left) - height(node->right); 
}
struct Node* rightRotate(struct Node* a){
	struct Node *b = a -> left;
	struct Node *t = b -> right;

	b -> right = a;
	a -> left = t;

	a -> height = max(height(a->left), height(a->right)) + 1;
	b -> height = max(height(b->left), height(b->right)) + 1;

	return b;
}
struct Node* leftRotate(struct Node* a){
	struct Node *b = a -> right;
	struct Node *t = b -> left;

	b -> left = a;
	a -> right = t;

	a -> height = max(height(a->left), height(a->right)) + 1;
	b -> height = max(height(b->left), height(b->right)) + 1;

	return b;
}
struct Node *balancedTree(struct Node *node, int data){

	node -> height = 1 + max(height(node->left), height(node->right));
	int bal = getBalance(node);

	// Left Left case 
	if (bal> 1 && data < node->left->data) 
        return rightRotate(node); 

    // Right Right Case 
    if (bal < -1 && data > node->right->data) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (bal > 1 && data > node->left->data) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (bal < -1 && data < node->right->data) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    }

	return node;
}
//

struct Node *insert(struct Node *node, int data){
	if(node == NULL)
		return newnode(data);
	if(data < node->data)
		node -> left = insert(node->left, data);
	else if(data > node->data)
		node -> right = insert(node->right, data);
	return balancedTree(node, data);
}

bool search(struct Node *root, int data){
	if(root == NULL)
		return false;
	if(root->data == data)
		return true;
	else if(root->data < data)
		return search(root->right, data);
	else
		return search(root->left, data);
	return false;
}

struct Node *getInorderSuccessor(struct Node *temp){
	while(temp && temp->left != NULL)
		temp = temp -> left;
	return temp;
}
struct Node *delete_(struct Node *node, int data){
	if(node == NULL)
		return node;
	if(data < node->data )
		node -> left = delete_(node->left, data);
	else if(data > node->data)
		node -> right = delete_(node->right, data);
	else{
		//Node with one child or no child 
		if(node -> left == NULL){
			struct Node *temp = node -> right;
			free(node);
			return temp;
		}
		else if(node -> right == NULL){
			struct Node *temp = node -> left;
			free(node);
			return temp;
		}
		//Node with two child
		struct Node *temp = getInorderSuccessor(node->right);
		node -> data = temp -> data;
		node -> right = delete_(node->right, temp -> data);
	}
	return balancedTree(node, data);
}

void preorder(struct Node* root){
	if(root){
		cout<<root -> data<<" ";
		preorder(root -> left);
		preorder(root -> right);
	}
}
void inorder(struct Node* root){
	if(root){
		inorder(root -> left);
		cout<<root -> data<<" ";
		inorder(root -> right);
	}
}
void postorder(struct Node* root){
	if(root){
		postorder(root -> left);
		postorder(root -> right);
		cout<<root -> data<<" ";
	}
}

int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n, a[n];
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];

	struct Node *root = NULL;

	for(int i=0; i<n; i++){
		root = insert(root, a[i]);
	}

	int t = 100000; //max input size
	while(t--){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "search"){
			int key;
			cin>>key;

			bool isFound = search(root,key); 
			if(isFound)
				cout<<key<<" is found."<<endl;
			else
				cout<<key<<" is not found"<<endl;
		}
		else if(opt == "delete"){
			int key;
			cin>>key;
			
			root = delete_(root, key);
		}
		else if(opt == "inorder"){
			cout<<"Inorder Traversal: "<<endl;
			inorder(root);
			cout<<endl;
		}
		else if(opt == "preorder"){
			cout<<"Preorder Traversal: "<<endl;
			preorder(root);
			cout<<endl;
		}
		else if(opt == "postorder"){
			cout<<"Postorder Traversal: "<<endl;
			inorder(root);
			cout<<endl;
		}
	}
	fclose(fp);
}