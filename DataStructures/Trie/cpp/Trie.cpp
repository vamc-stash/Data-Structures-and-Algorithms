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

class Trie{

	bool isLeaf;
	unordered_map<char, Trie*> map;

	public:

		Trie(){
			this -> isLeaf = false;
		}
		void insert(string);
		bool search(string);
		bool delete_(Trie* &, string);
		bool haveChildren(Trie const*);
};

void Trie:: insert(string str){
	Trie* curr = this;
	for(int i=0; i < str.length(); i++){
		if(curr -> map[str[i]] == NULL)
			curr -> map[str[i]] = new Trie();

		curr = curr -> map[str[i]];
	}
	curr -> isLeaf = true;
} 
bool Trie:: search(string str){
	struct Trie* curr = this;
	if(curr == NULL)
		return 0;
	for(int i=0; i < str.length(); i++){
		curr = curr -> map[str[i]];
		if(curr == NULL)
			return 0;
	}
	return curr -> isLeaf;
}

bool Trie:: haveChildren(Trie const* curr){
	for(auto it:curr->map)
        if(it.second)
           return true;
     return false;
}
bool Trie:: delete_(Trie*  &curr, string str){
	if(curr == NULL)
		return 0;
	if(str.length()){
		if(curr != NULL && (curr) -> map[str[0]] != NULL && delete_((curr) -> map[str[0]], str.substr(1)) && curr -> isLeaf == false){
			if(!haveChildren(curr)){
				delete curr;
				curr = NULL;
				return 1;
			}
			else
				return 0;
		}
	}
	if(str.length() == 0 && curr -> isLeaf == true){
		if(!haveChildren(curr)){
			delete curr;
			curr = NULL;
			return 1;
		}
		else{
			curr -> isLeaf = false;
			return 0;
		}
	}
	return 0;
}
int main(){
	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	Trie* head = new Trie();

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "insert"){
			string word;
			cin>>word;
			
			head -> insert(word);
		}
		else if(opt == "search"){
			string word;
			cin>>word;

			bool isFound = head -> search(word); 
			if(isFound)
				cout<<word<<" is found."<<endl;
			else
				cout<<word<<" is not found"<<endl;
		}
		else if(opt == "delete"){
			string word;
			cin>>word;
			
			head -> delete_(head,word);
		}
	}

	fclose(fp);
}