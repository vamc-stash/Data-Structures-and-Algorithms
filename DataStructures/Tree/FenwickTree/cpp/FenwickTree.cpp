// Sum of Given range Implementation

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

using namespace std;

int getSum(int *f,int index){

	int prefixSum = 0;
	while(index > 0){
		prefixSum += f[index];
		index -= (index & (-index));
	}
	return prefixSum;
}
void update(int* f,int n,int index,int val){
	while(index <= n){
		f[index] += val;
		index += (index & (-index));
	}
}
int* build(int a[],int n){
	int size = n+1;
	int* fenwick = new int[size];
	for(int i=1;i<=n;i++)
		fenwick[i]=0;
	for(int i=0;i<n;i++)
		update(fenwick,n,i+1,a[i]);
	return fenwick; 
}

int main(){

	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n, a[n];
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];

	int *fenwick = build(a, n);

	int t = 100000; // max input size
	while(t--){
		string opt;
		cin>>opt;
		if(opt == ""){
			break;  // eof
		}

		if(opt == "sum"){
			int l,r;
			cin>>l>>r;	

			if(l < 0 || r > n-1 || l > r){
				cout<<"Invalid Input"<<endl;
			}
			else{
				int sum = getSum(fenwick, r+1) - getSum(fenwick,l);
				cout<<"sum in the range ("<<l<<", "<<r<<") is "<<sum<<endl; 
			}
			
		}
		else if(opt == "update"){
			int index, newval;
			cin>>index>>newval;

			if(index < 0 || index > n-1){
				cout<<"Invalid Input"<<endl;
			}
			else{
				int diff = newval-a[index];
				a[index] = newval;
				update(fenwick,n,index+1,diff);
			}
			
		}
	}
	fclose(fp);
}