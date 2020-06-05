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

class Stack{
	private:
		int top_, capacity;
		int* arr;

		bool isEmpty(){
			return (this->top_ == -1);
		}
		bool isFull(){
			return (this->top_ == (this->capacity)-1);
		}

	public:
		Stack(int maxCapacity){
			arr = new int[maxCapacity];
			top_ = -1;
			capacity = maxCapacity;
		}

		void push(int val){
			if(this->isFull()){
				cout<<"Insufficient stack capacity, so "<<val<<" is not pushed"<<endl;
				return;
			}
			this->arr[++(this->top_)] = val;
		}
		void pop(){
			if(this->isEmpty()){
				cout<<"Stack is Empty, cant perform pop()"<<endl;
				return;
			}
			(this->top_)--;
		}
		int top(){
			if(this->isEmpty()){
				cout<<"stack is empty, cant retrieve top() : ";
				return 403;
			}
			return this->arr[this->top_];
		}
};

int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	Stack s(SIZE);

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "push"){
			int val;
			cin>>val;
			s.push(val);
		}
		else if(opt == "pop"){
			s.pop();
		}
		else if(opt == "top"){
			cout<<s.top()<<endl;
		}
	}
	fclose(fp);

}