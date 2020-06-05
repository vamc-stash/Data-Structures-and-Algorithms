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
	struct Node *prev, *next;
};

class LList{

	private:
		void split(struct Node *head, struct Node** fh, struct Node** sh){
			if((head) == NULL || (head) -> next == NULL){
				*fh = head;
				*sh = NULL;
				return; 
			}
			struct Node* slowptr = head;
			struct Node* fastptr = (head) -> next;
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
			struct Node *head = NULL;
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

	public:
		struct Node *head, *tail;

		LList(){
			this -> head = NULL;
		}

		void insert_at_tail(int data){
			struct Node* newnode = new Node;
			newnode -> data = data;
			newnode -> prev = newnode -> next = NULL;
			this -> tail = newnode;
			if(this -> head == NULL){
				this -> head = newnode;
				return;
			}
			struct Node* temp = this -> head;
			while(temp->next != NULL){
				temp = temp -> next;
			}
			temp -> next = newnode;
			newnode -> prev = temp;
			return;
		}

		void insert_at_head(int data){
			struct Node* newnode = new Node;
			newnode -> data = data;
			newnode -> prev = NULL;
			newnode -> next = this -> head;
			if(this -> head)
				(this -> head) -> prev = newnode;
			else
				this -> tail = newnode;
			this -> head = newnode;
			return ;
		}

		bool search(int val){
			struct Node* temp = this -> head;
			while(temp != NULL){
				if(temp -> data == val){
					return true;
				}
				temp = temp -> next;
			}
			return false;
		}

		void remove(int val){
			struct Node* temp = this -> head;
			while(temp != NULL){
				if(temp -> data == val){
					break;
				}
				temp = temp -> next;
			}
			if(temp != NULL){
				if(temp -> prev == NULL){
					struct Node* delnode = temp;
					this -> head = temp -> next;
					if(this -> head)
						(this->head) -> prev = NULL;
					else
						this -> tail = NULL;
					free(delnode);
				}
				else{
					struct Node* delnode = temp;
					temp -> prev -> next = temp -> next;
					if(temp -> next)
						temp -> next -> prev = temp -> prev;
					else
						this -> tail = temp -> prev;
					free(delnode);
				}
			}
			this -> display();
			this -> displayReverse();
			return ;
		}

		void reverse(struct Node* head){
			if(head -> next == NULL){
				this -> head = head;
				return;
			}
			reverse(head -> next);
			head -> next -> next = head;
			head-> next = NULL;

		}

		void mergeSort(struct Node **head, struct Node **tail){
			if((*head) == NULL || (*head) -> next == NULL)
				return;
			struct Node *fHalf, *sHalf;
			split(*head, &fHalf, &sHalf);
			mergeSort(&fHalf, tail);
			mergeSort(&sHalf, tail);
			*head = merge(fHalf, sHalf, tail);
		}

		void display(){
			cout<<"null";
			struct Node* temp = this -> head;
			while(temp){
				cout<<" <-- "<<temp->data<<"--> ";
				temp = temp -> next;
			}
			cout<<"null"<<endl;
		}

		void displayReverse(){
			cout<<"null";
			struct Node* temp = this -> tail;
			while(temp){
				cout<<" <-- "<<temp->data<<" --> ";
				temp = temp -> prev;
			}
			cout<<"null"<<endl;
		}
			
};

int main(){

	fast_io;

	freopen("../input.txt","r",stdin);
	freopen("../output.txt","w",stdout);

	int n,i;
	cin>>n;
	int a[n];
	for(i=0; i<n; i++)
		cin>>a[i];

	LList slist;

	//Insertion 
	cout<<"insertion at tail"<<endl;
	for(int i=0; i<n; i++){
		slist.insert_at_tail(a[i]);
	}
	slist.display();
	slist.displayReverse();

	LList slist2;
	cout<<"insertion at head"<<endl;
	for(int i=0; i<n; i++){
		slist2.insert_at_head(a[i]);
	}
	slist2.display();
	slist2.displayReverse();

	//Search
	int searchVal;
	cin>>searchVal;
	bool isAvailable = slist.search(searchVal);
	if(isAvailable)
		cout<<searchVal<<" is found."<<endl;
	else
		cout<<searchVal<<" is not found."<<endl;

	//Delete
	int delVal;
	cin>>delVal;
	cout<<"After deletion of node "<<delVal<<endl;
	slist.remove(delVal);

	// Merge Sort
	slist.mergeSort(&slist.head, &slist.tail);
	cout<<"Sorted List"<<endl;
	slist.display();
	cout<<"Traversing Sorted List in descending order"<<endl;
	slist.displayReverse();
}