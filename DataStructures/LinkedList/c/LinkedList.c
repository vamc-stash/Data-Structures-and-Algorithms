#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
	int data;
	struct node* next;
};

struct node* insert_at_tail(struct node* head, int data){
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	if(newnode == NULL){
		printf("Memory is not allocated");
		exit(1); 
	}
	newnode -> data = data;
	newnode -> next = NULL;
	if(head == NULL){
		head = newnode;
		return head;
	}
	struct node* temp = head;
	while(temp->next != NULL){
		temp = temp -> next;
	}
	temp -> next = newnode;
	return head;
}

struct node* insert_at_head(struct node* head, int data){
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	if(newnode == NULL){
		printf("Memory is not allocated");
		exit(1); 
	}
	newnode -> data = data;
	newnode -> next = head;
	head = newnode;
	return head;
}

bool search(struct node* head, int val){
	struct node* temp = head;
	while(temp != NULL){
		if(temp -> data == val){
			return true;
		}
		temp = temp -> next;
	}
	return false;
}

struct node* _remove(struct node* head, int val){
	struct node* temp = head;
	struct node* prev = NULL;
	while(temp != NULL){
		if(temp -> data == val){
			break;
		}
		prev = temp;
		temp = temp -> next;
	}
	if(temp != NULL){
		if(prev == NULL){
			struct node* delnode = temp;
			head = temp -> next;
			free(delnode);
		}
		else{
			struct node* delnode = temp;
			prev -> next = temp -> next;
			free(delnode);
		}
	}
	return head;
}

struct node* reverseList(struct node* head){
	if(head -> next == NULL){
		return head;
	}
	struct node* h = reverseList(head -> next);
	head -> next -> next = head;
	head -> next = NULL;
	return h;
}

void split(struct node* head, struct node** fh, struct node** sh){
	if(head == NULL || head->next == NULL){
		*fh = head;
		*sh = NULL;
		return; 
	}
	struct node* slowptr = head;
	struct node* fastptr = head -> next;
	while(fastptr != NULL){
		fastptr = fastptr -> next;
		if(fastptr != NULL){
			slowptr = slowptr -> next;
			fastptr = fastptr -> next;
		}
	}
	*fh = head;
	*sh = slowptr -> next;
	slowptr -> next = NULL;
	return;

}
struct node* merge(struct node* fh, struct node* sh){
	if(fh == NULL){
		return sh;
	}
	if(sh == NULL){
		return fh;
	}
	struct node* temp = NULL;
	if(fh->data <= sh->data){
		temp = fh;
		temp -> next = merge(fh->next, sh);
	}
	else{
		temp = sh;
		temp -> next = merge(fh, sh->next);
	}
	return temp;
}
void mergeSort(struct node **head){
	if((*head) == NULL || (*head)->next == NULL)
		return;
	struct node *fHalf, *sHalf;
	split(*head, &fHalf, &sHalf);
	mergeSort(&fHalf);
	mergeSort(&sHalf);
	*head = merge(fHalf, sHalf);
}

void display(struct node* head){
	while(head != NULL){
		printf("%d --> ", head->data);
		head = head -> next;
	}
	printf("null\n");
}

void displayReverse(struct node* head){
	if(head == NULL)
		return;
	displayReverse(head -> next);
	printf("%d ", head -> data);
}

int main(){

	freopen("../input.txt","r",stdin);
	freopen("../output.txt","w",stdout);

	int n,i;
	scanf("%d",&n);
	int a[n];
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	//Insertion 
	printf("insertion at tail\n");
	struct node* head = NULL;
	for(i=0; i<n; i++){
		head = insert_at_tail(head,a[i]);
	}
	display(head); // Traversing list
 
	printf("insertion at head\n");
	head = NULL;
	for(i=0; i<n; i++){
		head = insert_at_head(head,a[i]);
	}
	display(head);

	//Search
	int searchVal;
	scanf("%d", &searchVal);
	bool isAvailable = search(head,searchVal);
	if(isAvailable)
		printf("%d is found.\n", searchVal);
	else
		printf("%d is not found.\n", searchVal);

	//Delete
	int delVal;
	scanf("%d", &delVal);
	head = _remove(head, delVal);
	printf("After deletion of node %d\n", delVal);
	display(head);

	//Reverse
	head = reverseList(head);
	printf("Reversing list\n");
	display(head);

	//Traverse reverse
	displayReverse(head);

	//Merge Sort
	mergeSort(&head);
	printf("Sorted List\n");
	display(head);
}