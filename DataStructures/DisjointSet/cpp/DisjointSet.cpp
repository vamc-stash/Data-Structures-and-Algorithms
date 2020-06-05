#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_map>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

using namespace std;

class DisjointSet{
	private:
		int n;
		int *rank;
		int *parent;
	public:
		DisjointSet(int n){
			this -> n = n;
			rank = new int[n];
			parent = new int[n];
			for(int i=0; i<n; i++){
				parent[i] = i;
			}
		}
		void _union(int, int);
		int find(int);
};
int DisjointSet:: find(int x){
	if(parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}
void DisjointSet:: _union(int u, int v){
	int uset = find(u);
	int vset = find(v);

	if(uset == vset)
		return;

	if(rank[uset] < rank[vset])
		parent[uset] = vset;
	else if(rank[uset] > rank[vset])
		parent[vset] = uset;
	else{
		parent[vset] = uset;
		rank[uset] += 1;
	}
}
int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n;
	cin>>n;

	DisjointSet ds(n);

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "union"){
			int u,v;
			cin>>u>>v;
			
			ds._union(u, v);
		}
		else if(opt == "find"){
			int u,v;
			cin>>u>>v;
			
			if(ds.find(u) == ds.find(v)){
				cout<<u<<", "<<v<<" belongs to same set"<<endl;
			}
			else{
				cout<<u<<", "<<v<<" belongs to different sets"<<endl;
			}
		}
	}

	fclose(fp);
}