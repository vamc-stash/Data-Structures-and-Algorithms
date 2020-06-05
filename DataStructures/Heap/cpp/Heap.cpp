// Max heap implementation

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

#define SIZE 10

using namespace std;

class PriorityQueue{
	private:
		int *arr;
		int size, capacity;

		void heapify_down(int* arr, int size, int i){
			int largest = i;
			int left = 2*i + 1; // left child
			int right = 2*i + 2; // right child
			if(left < size && arr[left] > arr[largest])
				largest = left;
			if(right < size && arr[right] > arr[largest])
				largest = right;
			if(largest != i){
				swap(arr[i], arr[largest]);
				heapify_down(arr, size, largest);
			}
		}

		void heapify_up(int* arr, int i){
			int p = (i-1)/2; // parent
			if(i && arr[p] < arr[i]){
				swap(arr[i], arr[p]);
				heapify_up(arr, p);
			}
		}

	public:
		PriorityQueue(int maxCapacity){
			arr = new int[maxCapacity];
			size = 0;
			capacity = maxCapacity;
		}

		void insert(int data){
			if(this -> size == this -> capacity){
				cout<<"overflow: could not insert "<<data<<endl;
				return;
			}
			(this -> arr)[this->size] = data;
			(this -> size)++;

			heapify_up(this->arr, (this->size)-1);
		}
		void dequeue(){
			if(this -> size == 0){
				cout<<"empty heap: could not remove priority element"<<endl;
				return;
			}
			(this->arr)[0] = (this->arr)[this->size - 1];
			(this->size)--;

			heapify_down(this->arr, this->size, 0);
		}
		int peek(){
			if(this -> size == 0){
				cout<<"empty heap: could not retreive priority element: ";
				return 403;
			}
			return (this->arr)[0];
		}
		void display(){
			for(int i=0; i<this->size; i++){
				cout<<(this->arr)[i]<<" ";
			}
			cout<<endl;
		}
};

int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	PriorityQueue pq(SIZE);

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "insert"){
			int val;
			cin>>val;
			pq.insert(val);
		}
		else if(opt == "dequeue"){
			pq.dequeue(); // Remove priority element (max value element in this case)
		}
		else if(opt == "peek"){
			cout<<pq.peek()<<endl;  // priority element of the heap
		}
		else if(opt == "display"){
			pq.display(); // display heap
		}
	}
	fclose(fp);
}