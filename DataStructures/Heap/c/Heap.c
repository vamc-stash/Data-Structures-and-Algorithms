
// Max Heap Implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct PriorityQueue{
	int *arr;
	int size, capacity;
};

struct PriorityQueue *create(int maxCapacity){
	struct PriorityQueue *q = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
	q->arr = (int*)malloc(sizeof(int) * maxCapacity);
	q->size = 0;
	q->capacity = maxCapacity;
	return q;
}

void swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void heapify_down(int* arr, int size, int i){
	int largest = i;
	int left = 2*i + 1; // left child
	int right = 2*i + 2; // right child
	if(left < size && arr[left] > arr[largest])
		largest = left;
	if(right < size && arr[right] > arr[largest])
		largest = right;
	if(largest != i){
		swap(&arr[i], &arr[largest]);
		heapify_down(arr, size, largest);
	}
}

void heapify_up(int* arr, int i){
	int p = (i-1)/2; // parent
	if(i && arr[p] < arr[i]){
		swap(&arr[i], &arr[p]);
		heapify_up(arr, p);
	}
}

void insert(struct PriorityQueue* pq, int data){
	if(pq -> size == pq -> capacity){
		printf("overflow: could not insert %d\n", data);
		return;
	}
	(pq -> arr)[pq->size] = data;
	(pq -> size)++;

	heapify_up(pq->arr, (pq->size)-1);
}
void dequeue(struct PriorityQueue* pq){
	if(pq -> size == 0){
		printf("empty heap: could not remove priority element\n");
		return;
	}
	(pq->arr)[0] = (pq->arr)[pq->size - 1];
	(pq->size)--;

	heapify_down(pq->arr, pq->size, 0);
}
int peek(struct PriorityQueue* pq){
	if(pq -> size == 0){
		printf("empty heap: could not retreive priority element: ");
		return 403;
	}
	return (pq->arr)[0];
}
void display(struct PriorityQueue* pq){
	int i;
	for(i=0; i<pq->size; i++){
		printf("%d ", (pq->arr)[i]);
	}
	printf("\n");
}
int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	struct PriorityQueue *q = create(SIZE); 

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"insert",strlen("insert"))){ 
			char choice[10];
			int val;
			sscanf(opt, "%s %d" , choice, &val); //sscanf reads formatted input from string
			insert(q,val); // Push
		}
		else if(!strncmp(opt,"dequeue",strlen("dequeue"))){
			dequeue(q); // Remove priority element (max value element in this case)
		}
		else if(!strncmp(opt,"peek",strlen("peek"))){
			printf("%d\n",peek(q)); // priority element of the heap
		}
		else if(!strncmp(opt,"display",strlen("display"))){
			display(q); // display heap
		}
	}
	fclose(fp); 
}