#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct DataBlock{
	int key,value;
};
struct DataBlock* hashmap[SIZE];

int hashCode(int key){
	return key % SIZE;
}
void insert(int key, int value){
	struct DataBlock* item = (struct DataBlock*)malloc(sizeof(struct DataBlock));
	item -> key = key;
	item -> value = value;

	int hashIndex = hashCode(key);

	//search for empty block
	int temp = hashIndex;
	while(hashmap[hashIndex] != NULL){
		hashIndex++;
		hashIndex %= SIZE;
		if(hashIndex == temp){
			printf("Hashmap size is full, so previous data item with key %d is overwritten.\n", key);
			break;
		}
	}

	hashmap[hashIndex] = item;
}

struct DataBlock* search(int key){

	int hashIndex = hashCode(key);

	int temp = hashIndex;
	while(hashmap[hashIndex] != NULL){
		if(hashmap[hashIndex] -> key == key)
			return hashmap[hashIndex];
		hashIndex++;
		hashIndex %= SIZE;
		if(hashIndex == temp){
			break;
		}
	}
	return NULL;
}

void delete(int key){
	int hashIndex = hashCode(key);

	int temp = hashIndex;
	while(hashmap[hashIndex] != NULL){
		if(hashmap[hashIndex] -> key == key){
			hashmap[hashIndex] = NULL;
			return;
		}
		hashIndex++;
		hashIndex %= SIZE;
		if(hashIndex == temp){
			printf("data item with key %d is not found to delete.\n", key);
			break;
		}
	}
	return;
}

void display(){
	int i;
	for(i=0; i<SIZE; i++){
		if(hashmap[i] != NULL)
			printf("(%d, %d) ", hashmap[i]->key, hashmap[i]->value);
		else
			printf("~~ ");
	}
	printf("\n");
}

int main(){

	FILE* fp = freopen("../input.txt","r",stdin);
	freopen("../output.txt","w",stdout);
	
	while(!feof(fp)){

		char opt[30];
		fgets(opt, 30, fp);

		if(!strncmp(opt, "insert", strlen("insert"))){
			char choice[10];
			int key,value;
			sscanf(opt, "%s %d %d", choice, &key, &value);

			insert(key, value);
		}
		else if(!strncmp(opt, "search", strlen("search"))){
			char choice[10];
			int key;
			sscanf(opt, "%s %d", choice, &key);

			struct DataBlock* item = search(key);
			if(item != NULL)
				printf("(%d,%d) is found.\n", item->key, item->value);
			else
				printf("%d is not found\n", key);
		}
		else if(!strncmp(opt, "delete", strlen("delete"))){
			char choice[10];
			int key;
			sscanf(opt, "%s %d", choice, &key);

			delete(key);
		}
		else if(!strncmp(opt, "display", strlen("display"))){
			display();
		}
	}
}

