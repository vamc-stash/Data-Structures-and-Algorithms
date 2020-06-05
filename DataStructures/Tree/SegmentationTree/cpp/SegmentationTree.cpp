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

void updateUtil(int* st, int s, int e, int i, int diff, int si){
	if(i < s || i > e)
		return;
	st[si] += diff;
	if(s != e){
		int mid = s + ((e - s) / 2);
		updateUtil(st, s, mid, i, diff, 2*si + 1);
		updateUtil(st, mid+1, e, i, diff, 2*si + 2);
	}
}
void update(int* st, int a[], int n, int index, int newValue){
	if(index < 0 || index > n-1){
		cout<<"Invalid input"<<endl;
		return;
	}
	int diff = newValue - a[index];
	a[index] = newValue;

	updateUtil(st, 0, n-1, index, diff, 0);
}

int getSumUtil(int* st, int s, int e, int l, int r, int si){
	if(s > e || l > e || r < s)
		return 0;
	if(s >= l && e <= r)
		return st[si];
	int mid = s + ((e - s) / 2);
	return getSumUtil(st, s, mid, l, r, 2*si + 1) + getSumUtil(st, mid + 1, e, l, r, 2*si + 2);
}
int getSum(int* st, int n, int l, int r){
	if(l < 0 || r > n-1 || l > r){
		cout<<"Invalid input: ";
		return -1;
	}

	cout<<"sum in the range ("<<l<<", "<<r<<") is ";
	return getSumUtil(st, 0, n-1, l, r, 0);
}

int buildSTutil(int* st, int a[], int s, int e, int si){
	if(s == e){
		st[si] = a[s];
		return a[s];
	}
	int mid = s + ((e - s) / 2);

	st[si] = buildSTutil(st, a, s, mid, 2*si+1) + buildSTutil(st, a, mid+1, e, 2*si+2);
	return st[si];
}
int* buildST(int* st, int a[], int n){
	int height = (int)(ceil(log2(n)));
	int maxSize = 2*(int)(pow(2, height)) - 1;

	st = new int[maxSize];
	buildSTutil(st, a, 0, n-1, 0);

	return st;
}

int main(){

	fast_io;

	FILE *fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int n, a[n];
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];

	int *st;
	st = buildST(st, a, n);

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

			int sum = getSum(st, n, l, r);
			cout<<sum<<endl; 
		}
		else if(opt == "update"){
			int index, value;
			cin>>index>>value;
			
			update(st, a, n, index, value); 
		}
	}
	fclose(fp);
}