#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

#define SIZE 5

using namespace std;

class Queue{
	private:
		int *arr;
		int front, rear, capacity;

		bool isEmpty(){
			return (this->rear == -1 && this->front == -1);
		}
		bool isFull(){
			return ((this->rear + 1)%(this->capacity) == this->front);
		}
	public:
		Queue(int maxCapacity){
			arr = new int[maxCapacity];
			front = -1;
			rear = -1;
			capacity = maxCapacity;
		}

		void enqueue(int val){
			if(this->isFull()){
				cout<<"Insufficient queue capacity, so "<<val<<" is not enqueued"<<endl;
				return;
			}
			if(this->front == -1)
				(this->front)++;
			this->rear = (this->rear+1)%this->capacity;
			this->arr[this->rear] = val;
		}
		void dequeue(){
			if(this->isEmpty()){
				cout<<"queue is empty, cant perform dequeue()"<<endl;
				return;
			}
			if(this->rear == this->front){
				this->rear = this->front = -1;
			}
			else
				this->front = (this->front + 1)%this->capacity;
		}
		int peek(){
			if(this->isEmpty()){
				cout<<"queue is empty , cant retrieve front element : ";
				return 403;
			}
			return this->arr[this->front];
		}
};

int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	Queue q(SIZE);

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "enqueue"){
			int val;
			cin>>val;
			q.enqueue(val);
		}
		else if(opt == "dequeue"){
			q.dequeue();
		}
		else if(opt == "peek"){
			cout<<q.peek()<<endl;
		}
	}
	fclose(fp);
}