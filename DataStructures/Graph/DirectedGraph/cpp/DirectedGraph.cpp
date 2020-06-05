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

class Graph{
	private:
		int v;
		vector<int> *adjList;
	public:
		Graph(int v){
			this -> v = v;
			adjList = new vector<int>[v];
		}
		void addEdge(int, int);
		void print();
};
void Graph:: addEdge(int u, int v){
	adjList[u].push_back(v);
}
void Graph:: print(){
	for(int i=0; i<v; i++){
		cout<<i<<" : ";
		for(int j=0; j<adjList[i].size(); j++){
			cout<<adjList[i][j]<<" -> ";
		}
		cout<<"null"<<endl;
	}
}
int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int v;
	cin>>v;

	Graph g(v);

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "addEdge"){
			int u,v;
			cin>>u>>v;
			
			// u -> v
			g.addEdge(u, v);
		}
	}

	g.print();

	fclose(fp);
}