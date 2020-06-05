#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
	int data;
	struct Node *left, *right;
};

struct Node *newnode(int key){
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
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
struct Node *delete(struct Node *root, int data){
	if(root == NULL)
		return root;
	if(data < root->data )
		root -> left = delete(root->left, data);
	else if(data > root->data)
		root -> right = delete(root->right, data);
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
		root -> right = delete(root->right, temp -> data);
	}
	return root;
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