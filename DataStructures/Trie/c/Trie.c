#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CHAR_SIZE 26

struct Trie{
	bool isLeaf;
	struct Trie* map[CHAR_SIZE];
};

struct Trie* getNewNode(){
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node -> isLeaf = false;

	int i;
	for(i=0; i<CHAR_SIZE; i++)
		node -> map[i] = NULL;
	return node;
}

void insert(struct Trie* head, char* str){
	struct Trie* curr = head;
	while(*str){
		if(curr -> map[*str - 'a'] == NULL)
			curr -> map[*str - 'a'] = getNewNode();

		curr = curr -> map[*str - 'a'];
		str++;
	}
	curr -> isLeaf = true;
}

bool search(struct Trie* head, char* str){
	if(head == NULL)
		return 0;
	struct Trie* curr = head;
	while(*str){
		curr = curr -> map[*str - 'a'];
		if(curr == NULL)
			return 0;
		str++;
	}
	return curr -> isLeaf;
}

bool haveChildren(struct Trie* curr){
	int i;
	for(i=0; i<CHAR_SIZE; i++){
		if(curr -> map[i])
			return 1;
	}
	return 0;
}
bool delete(struct Trie** curr, char* str){
	if(*curr == NULL)
		return 0;
	if(*str){
		if(*curr != NULL && (*curr) -> map[*str - 'a'] != NULL && delete(&((*curr) -> map[*str - 'a']), str+1) && (*curr) -> isLeaf == false){
			if(!haveChildren(*curr)){
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else
				return 0;
		}
	}
	if(*str == '\0' && (*curr) -> isLeaf == true){
		if(!haveChildren(*curr)){
			free(*curr);
			(*curr) = NULL;
			return 1;
		}
		else{
			(*curr) -> isLeaf = false;
			return 0;
		}
	}
	return 0;
}
int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	struct Trie* head = getNewNode();

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"insert",strlen("insert"))){
			char choice[10];
			char word[40];
			sscanf(opt, "%s %s" , choice, word);

			insert(head, word); 
		}
		else if(!strncmp(opt,"search",strlen("search"))){ 
			char choice[10];
			char word[40];
			sscanf(opt, "%s %s" , choice, word);

			bool isFound = search(head, word); 
			if(isFound)
				printf("%s is found.\n", word);
			else
				printf("%s is not found\n", word);
		}
		else if(!strncmp(opt,"delete",strlen("delete"))){
			char choice[10];
			char word[40];
			sscanf(opt, "%s %s" , choice, word);

			delete(&head, word); 
		}
	}
	fclose(fp); 

}