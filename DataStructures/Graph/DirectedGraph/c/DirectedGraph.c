#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
	int data;
	struct Node *next;
};
struct Graph{
	int v;
	struct Node** adjList;
};
struct Node* getNewNode(int data){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node -> data = data;
	node -> next = NULL;
	return node;
}
struct Graph* createGraph(int v){
	struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
	g -> v = v;
	g -> adjList = (struct Node**)malloc(sizeof(struct Node*) * v);

	return g;
}
void addEdge(struct Graph* g, int u, int v){
	struct Node* newnode = getNewNode(v);
	newnode -> next = g -> adjList[u];
	g -> adjList[u] = newnode;
}
void print(struct Graph* g){
	int i,j;
	for(i=0; i<g->v; i++){
		printf("%d : ", i);
		struct Node* temp = g -> adjList[i];
		while(temp != NULL){
			printf("%d -> ", temp -> data);
			temp = temp -> next;
		}
		printf("null\n");
	}
}
int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int v;
	scanf("%d",&v);

	struct Graph* g = createGraph(v);

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"addEdge",strlen("addEdge"))){ 
			char choice[10];
			int u,v;
			sscanf(opt, "%s %d %d" , choice, &u, &v);

			// u -> v
			addEdge(g, u, v);
		}
	}

	print(g);

	fclose(fp); 

}