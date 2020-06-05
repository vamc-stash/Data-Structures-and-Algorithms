#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

struct Queue{
	int *arr;
	int front, rear, capacity; 
};

struct Queue *createQueue(int maxCapacity){
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
	q->arr = (int*)malloc(sizeof(int) * maxCapacity);
	q->front = q->rear = -1;
	q->capacity = maxCapacity;
	return q;
}

bool isFull(struct Queue* q){
	return ((q->rear+1)%q->capacity == q->front);
}
bool isEmpty(struct Queue* q){
	return (q->rear == -1 && q->front == -1);
}
void enqueue(struct Queue* q, int val){
	if(isFull(q)){
		printf("Insufficient queue capacity, so %d is not enqueued.\n", val);
		return;
	}
	if(q->front == -1)
		(q->front)++;
	q -> rear = (q->rear+1)%q->capacity;
	q->arr[q->rear] = val;
}
void dequeue(struct Queue* q){
	if(isEmpty(q)){
		printf("queue is empty, cant perform dequeue()\n");
		return;
	}
	if(q->rear == q->front){
		q->rear = q->front = -1;
	}
	else
		q->front = (q->front + 1)%q->capacity;
}
int peek(struct Queue* q){
	if(isEmpty(q)){
		printf("queue is empty , cant retrieve front element : ");
		return 403;
	}
	return q->arr[q->front];
}

int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	struct Queue *q = createQueue(SIZE); 

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"enqueue",strlen("enqueue"))){ 
			char choice[10];
			int val;
			sscanf(opt, "%s %d" , choice, &val); //sscanf reads formatted input from string
			enqueue(q,val); // Enqueue 
		}
		else if(!strncmp(opt,"dequeue",strlen("dequeue"))){
			dequeue(q); // Dequeue
		}
		else if(!strncmp(opt,"peek",strlen("peek"))){
			printf("%d\n",peek(q)); // front element of the queue
		}
	}
	fclose(fp); 
}