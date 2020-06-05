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
	struct Node* next;
};

class LList{

	private:
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
			slowptr -> next = NULL;
			return;

		}
		struct Node* merge(struct Node* fh, struct Node* sh){
			if(fh == NULL){
				return sh;
			}
			if(sh == NULL){
				return fh;
			}
			struct Node* temp = NULL;
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

	public:
		struct Node* head;

		LList(){
			this -> head = NULL;
		}

		void insert_at_tail(int data){
			struct Node* newnode = new Node;
			newnode -> data = data;
			newnode -> next = NULL;
			if(this -> head == NULL){
				this -> head = newnode;
				return;
			}
			struct Node* temp = this -> head;
			while(temp->next != NULL){
				temp = temp -> next;
			}
			temp -> next = newnode;
			return;
		}

		void insert_at_head(int data){
			struct Node* newnode = new Node;
			newnode -> data = data;
			newnode -> next = this -> head;
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
			struct Node* prev = NULL;
			while(temp != NULL){
				if(temp -> data == val){
					break;
				}
				prev = temp;
				temp = temp -> next;
			}
			if(temp != NULL){
				if(prev == NULL){
					struct Node* delnode = temp;
					head = temp -> next;
					free(delnode);
				}
				else{
					struct Node* delnode = temp;
					prev -> next = temp -> next;
					free(delnode);
				}
			}
			this -> display();
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

		void mergeSort(struct Node **head){
			if((*head) == NULL || (*head)->next == NULL)
				return;
			struct Node *fHalf, *sHalf;
			split(*head, &fHalf, &sHalf);
			mergeSort(&fHalf);
			mergeSort(&sHalf);
			*head = merge(fHalf, sHalf);
		}

		void display(){
			struct Node* temp = this -> head;
			while(temp != NULL){
				cout<<temp->data<<" --> ";
				temp = temp -> next;
			}
			cout<<"null"<<endl;
		}

		void displayReverse(struct Node* head){
			if(head == NULL)
				return;
			displayReverse(head -> next);
			cout<<head -> data<<" ";
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

	LList slist2;
	cout<<"insertion at head"<<endl;
	for(int i=0; i<n; i++){
		slist2.insert_at_head(a[i]);
	}
	slist2.display();

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
	

	//Reverse
	slist.reverse(slist.head);
	cout<<"Reversing list"<<endl;
	slist.display();

	//Traverse reverse
	slist.displayReverse(slist.head);

	//Sort
	cout<<endl<<"Sorted List"<<endl;
	slist.mergeSort(&slist.head);
	slist.display();
}