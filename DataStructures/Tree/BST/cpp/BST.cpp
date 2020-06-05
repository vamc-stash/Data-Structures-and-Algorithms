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
};

struct Node *newnode(int key){
	struct Node *node = new Node;
	node -> data = key;
	node -> left = node -> right = NULL;
	return node;
}

struct Node *insert(struct Node *root, int data){
	if(root == NULL)
		return newnode(data);
	if(data < root->data)
		root -> left = insert(root->left, data);
	else if(data > root->data)
		root -> right = insert(root->right, data);
	return root;
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
struct Node *delete_(struct Node *root, int data){
	if(root == NULL)
		return root;
	if(data < root->data )
		root -> left = delete_(root->left, data);
	else if(data > root->data)
		root -> right = delete_(root->right, data);
	else{
		//Node with one child or no child 
		if(root -> left == NULL){
			struct Node *temp = root -> right;
			free(root);
			return temp;
		}
		else if(root -> right == NULL){
			struct Node *temp = root -> left;
			free(root);
			return temp;
		}
		//Node with two child
		struct Node *temp = getInorderSuccessor(root->right);
		root -> data = temp -> data;
		root -> right = delete_(root->right, temp -> data);
	}
	return root;
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

	int t = 100000; // max input size
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