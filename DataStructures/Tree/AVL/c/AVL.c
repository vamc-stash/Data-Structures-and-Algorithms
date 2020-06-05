#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
	int data;
	struct Node *left, *right;
	int height;
};

struct Node *newnode(int key){
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	node -> data = key;
	node -> left = node -> right = NULL;
	node -> height = 1;
	return node;
}
//
int  max(int a, int b){
	return (a>b)? a:b;
}
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
	else
		return node; 

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
struct Node *delete(struct Node *node, int data){
	if(node == NULL)
		return node;
	if(data < node->data )
		node -> left = delete(node->left, data);
	else if(data > node->data)
		node -> right = delete(node->right, data);
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
		node -> right = delete(node->right, temp -> data);
	}
	return balancedTree(node, data);
}

void preorder(struct Node* root){
	if(root){
		printf("%d ", root -> data);
		preorder(root -> left);
		preorder(root -> right);
	}
}
void inorder(struct Node* root){
	if(root){
		inorder(root -> left);
		printf("%d ", root -> data);
		inorder(root -> right);
	}
}
void postorder(struct Node* root){
	if(root){
		postorder(root -> left);
		postorder(root -> right);
		printf("%d ", root -> data);
	}
}

int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int i,n, a[n];
	scanf("%d",&n);
	for(i=0; i<n; i++)
		scanf("%d" ,&a[i]);

	struct Node *root = NULL;
	for(i=0; i<n; i++){
		root = insert(root, a[i]);
	}

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"search",strlen("search"))){ 
			char choice[10];
			int key;
			sscanf(opt, "%s %d" , choice, &key); //sscanf reads formatted input from string

			bool isFound = search(root,key); 
			if(isFound)
				printf("%d is found.\n", key);
			else
				printf("%d is not found\n", key);
		}
		else if(!strncmp(opt,"delete",strlen("delete"))){
			char choice[10];
			int key;
			sscanf(opt, "%s %d" , choice, &key);

			root = delete(root,key); 
		}
		else if(!strncmp(opt,"inorder",strlen("inorder"))){
			printf("Inorder traversal: ");
			inorder(root);
			printf("\n");
		}
		else if(!strncmp(opt,"preorder",strlen("preorder"))){
			printf("Preorder traversal: ");
			preorder(root);
			printf("\n");
		}
		else if(!strncmp(opt,"postorder",strlen("postorder"))){
			printf("Postorder traversal: ");
			postorder(root);
			printf("\n");
		}
	}


	fclose(fp); 
}