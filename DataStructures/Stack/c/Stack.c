#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

struct Stack{
	int *arr, top, capacity;
};

struct Stack* createStack(int maxCapacity){
	struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
	s -> arr = (int*)malloc(sizeof(int) * maxCapacity);
	s -> top = -1;
	s -> capacity = maxCapacity;
	return s;
}

bool isFull(struct Stack* s){
	return (s->top == (s->capacity-1));
}
bool isEmpty(struct Stack* s){
	return (s->top == -1);
}
void push(struct Stack* s, int val){
	if(isFull(s)){
		printf("Insufficient stack capacity, so %d is not pushed.\n", val);
		return;
	}
	s->arr[++(s->top)] = val;
}
void pop(struct Stack* s){
	if(isEmpty(s)){
		printf("stack is empty, cant perform pop()\n");
		return;
	}
	(s->top)--;
}
int top(struct Stack* s){
	if(isEmpty(s)){
		printf("stack is empty, cant retrieve top() : ");
		return 403;
	}
	return s->arr[s->top];
}
int main(){

	FILE* fp = freopen("../input.txt","r",stdin);
	freopen("../output.txt","w",stdout);

	struct Stack *s = createStack(SIZE);
	
	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time
		
		if(!strncmp(opt,"push", strlen("push"))){ 
			char choice[10];
			int val;
			sscanf(opt, "%s %d" , choice, &val); //sscanf reads formatted input from string
			push(s,val); // push 
		}
		else if(!strncmp(opt,"pop", strlen("pop"))){
			pop(s); // pop
		}
		else if(!strncmp(opt,"top", strlen("top"))){
			printf("%d\n",top(s)); // top element of the stack
		}
	}
	fclose(fp);
}