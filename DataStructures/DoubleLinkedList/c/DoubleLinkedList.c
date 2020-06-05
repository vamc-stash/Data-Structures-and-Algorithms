#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
	int data;
	struct Node *prev, *next;
};

struct Node* insert_at_tail(struct Node *head, struct Node **tail, int data){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	if(newnode == NULL){
		printf("Memory is not allocated");
		exit(1); 
	}
	newnode -> data = data;
	newnode -> prev = newnode -> next = NULL;
	*tail = newnode;

	if(head == NULL){
		head = newnode;
		return head;
	}
	struct Node* temp = head;
	while(temp -> next){
		temp = temp -> next;
	}
	temp -> next = newnode;
	newnode -> prev = temp;

	return head;
}

struct Node* insert_at_head(struct Node* head, struct Node **tail, int data){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	if(newnode == NULL){
		printf("Memory is not allocated");
		exit(1); 
	}
	newnode -> data = data;
	newnode -> prev = NULL;
	newnode -> next = head;
	if(head){
		head -> prev = newnode;
	}
	else{
		*tail = newnode;
	}
	head = newnode;
	return head;
}

bool search(struct Node* head, int val){
	struct Node* temp = head;
	while(temp != NULL){
		if(temp -> data == val){
			return true;
		}
		temp = temp -> next;
	}
	return false;
}

struct Node* _remove(struct Node* head, struct Node **tail, int val){
	struct Node* temp = head;
	while(temp != NULL){
		if(temp -> data == val){
			break;
		}
		temp = temp -> next;
	}
	if(temp != NULL){
		if(temp -> prev == NULL){
			struct Node* delnode = temp;
			head = temp -> next;
			if(head){
				head -> prev = NULL;
			}
			else{
				*tail = NULL;
			}
			free(delnode);
		}
		else{
			struct Node* delnode = temp;
			temp -> prev -> next = temp -> next;
			if(temp -> next)
				temp -> next -> prev = temp -> prev;
			else
				*tail = temp -> prev;
			free(delnode);
		}
	}
	return head;
}

void split(struct Node* head, struct Node** fh, struct Node** sh){
	if(head == NULL || head->next == NULL){
		*fh = head;
		*sh = NULL;
		return; 
	}
	struct Node* slowptr = head;
	struct Node* fastptr = head -> next;
	while(fastptr != NULL){
		fastptr = fastptr -> next;
		if(fastptr != NULL){
			slowptr = slowptr -> next;
			fastptr = fastptr -> next;
		}
	}
	*fh = head;
	*sh = slowptr -> next;
	slowptr -> next -> prev = NULL;
	slowptr -> next = NULL;
	return;

}
struct Node* merge(struct Node* fh, struct Node* sh, struct Node **tail){
	struct Node* head = NULL;
	while(fh != NULL && sh != NULL){
		if(fh->data <= sh->data){
			if(head == NULL)
				head = fh;

			struct Node *t = fh -> next;
			fh -> next = sh;
			if(sh -> prev){
				sh -> prev ->next = fh;
			}
			sh -> prev = fh;
			fh = t;
		}
		else{
			if(head == NULL)
				head = sh;

			struct Node *t = sh -> next;
			sh -> next = fh;
			if(fh -> prev){
				fh -> prev ->next = sh;
			}
			fh -> prev = sh;
			sh = t;
		}
	}
	if(fh != NULL){
		while(fh -> next != NULL){
			fh = fh -> next;
		}
		*tail = fh;
	}
	else if(sh != NULL){
		while(sh -> next != NULL){
			sh = sh -> next;
		}
		*tail = sh;
	}
	
	return head;
}
void mergeSort(struct Node **head, struct Node **tail){
	if((*head) == NULL || (*head)->next == NULL)
		return;
	struct Node *fHalf, *sHalf;
	split(*head, &fHalf, &sHalf);
	mergeSort(&fHalf, tail);
	mergeSort(&sHalf, tail);
	*head = merge(fHalf, sHalf, tail);
}

void display(struct Node* head){
	printf("null");
	while(head){
		printf(" <-- %d --> ",head -> data);
		head = head -> next;
	}
	printf("null\n");
}

void displayReverse(struct Node* tail){
	printf("null");
	while(tail){
		printf(" <-- %d --> ",tail -> data);
		tail = tail -> prev;
	}
	printf("null\n");
}

int main(){
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n,i;
	scanf("%d",&n);
	int a[n];
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	//Insertion 
	printf("insertion at tail\n");
	struct Node* head = NULL;
	struct Node* tail;
	for(i=0; i<n; i++){
		head = insert_at_tail(head,&tail,a[i]);
	}
	display(head); // Traversing list
	displayReverse(tail); // Traversing Reverse
 
	printf("insertion at head\n");
	head = NULL;
	for(i=0; i<n; i++){
		head = insert_at_head(head,&tail,a[i]);
	}
	display(head);
	displayReverse(tail);

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
	head = _remove(head, &tail, delVal);
	printf("After deletion of node %d\n", delVal);
	display(head);
	displayReverse(tail);

	//Merge Sort
	mergeSort(&head, &tail);
	printf("Sorted List\n");
	display(head);
	printf("Traversing Sorted List in descending order\n");
	displayReverse(tail);


}