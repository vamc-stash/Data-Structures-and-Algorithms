#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct DisjSet{
	int *rank;
	int *parent;
	int n;
};

struct DisjSet* create(int n){
	struct DisjSet* ds = (struct DisjSet*)malloc(sizeof(struct DisjSet));
	ds -> n = n;
	ds -> rank = (int*)calloc(n, sizeof(int));
	ds -> parent = (int*)malloc(sizeof(int) * n);

	int i;
	for(i=0; i<n; i++){
		ds->parent[i] = i;
	}
	return ds;
}
int find(struct DisjSet* ds, int x){
	if(ds->parent[x] != x){
		ds->parent[x] = find(ds, ds->parent[x]);
	}
	return ds->parent[x];
}
void _union(struct DisjSet* ds, int u, int v){
	int uset = find(ds, u);
	int vset = find(ds, v);

	if(uset == vset)
		return;

	if(ds->rank[uset] < ds->rank[vset])
		ds->parent[uset] = vset;
	else if(ds->rank[uset] > ds->rank[vset])
		ds->parent[vset] = uset;
	else{
		ds->parent[vset] = uset;
		ds->rank[uset] += 1;
	}
}
int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n;
	scanf("%d",&n);

	struct DisjSet* ds = create(n);

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"union",strlen("union"))){ 
			char choice[10];
			int u, v;
			sscanf(opt, "%s %d %d" , choice, &u, &v);

			// u -> v
			_union(ds, u, v);
		}
		else if(!strncmp(opt,"find",strlen("find"))){ 
			char choice[10];
			int u, v;
			sscanf(opt, "%s %d %d" , choice, &u, &v);

			// u -> v
			if(find(ds, u) == find(ds, v)){
				printf("%d, %d belongs to same set\n",u,v);
			}
			else{
				printf("%d, %d belongs to different sets\n",u,v);
			}
		}
	}

	fclose(fp); 

}