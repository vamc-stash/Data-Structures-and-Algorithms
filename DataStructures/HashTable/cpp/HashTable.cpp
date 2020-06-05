#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

#define SIZE 20

using namespace std;

struct DataBlock{
	int key,value;
};

class HashMap{
	private:
		DataBlock **hashmap;

		int hashCode(int key){
			return key % SIZE;
		}
		
	public:
		HashMap(){
			hashmap =  new DataBlock*[SIZE];
			for(int i=0; i<SIZE; i++)
				hashmap[i] = NULL;
		}

		void insert(int key, int value){
			DataBlock *item = new DataBlock;
			item -> key = key;
			item -> value = value;

			int hashIndex = hashCode(key);

			//search for empty block
			int temp = hashIndex;
			while(hashmap[hashIndex] != NULL){
				hashIndex++;
				hashIndex %= SIZE;
				if(hashIndex == temp){
					cout<<"Hashmap size is full, so previous data item with key "<<key<<" is overwritten"<<endl;
					break;
				}
			}
			
			hashmap[hashIndex] = item;
		}

		DataBlock* search(int key){
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

		void delete_(int key){
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
					cout<<"data item with key "<<key<<" is not found to delete"<<endl;
					break;
				}
			}
			return;
		}

		void display(){

			for(int i=0; i<SIZE; i++){
				if(hashmap[i] != NULL)
					cout<<"("<<hashmap[i]->key<<", "<<hashmap[i]->value<<") ";
				else
					cout<<"~~ ";
			}
			cout<<endl;
		}
};

int main(){

	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	HashMap h;

	while(1){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "insert"){
			int key, value;
			cin>>key>>value;
			h.insert(key, value);
		}
		else if(opt == "search"){
			int key;
			cin>>key;
			DataBlock* item = h.search(key);
			if(item != NULL)
				cout<<"("<<item->key<<", "<<item->value<<") is found"<<endl;
			else
				cout<<key<<" is not found"<<endl;
		}
		else if(opt == "delete"){
			int key;
			cin>>key;
			h.delete_(key);
		}
		else if(opt == "display"){
			h.display();
		}
	}
	fclose(fp);
}
