// Sum of Given range Implementation

// run: gcc Segmentation.c -lm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void updateUtil(int st[], int s, int e, int i, int diff, int si){
	if(i < s || i > e)
		return;
	st[si]  += diff;
	if(s != e){
		int mid = s + ((e - s) / 2);
		updateUtil(st, s, mid, i, diff, 2*si + 1);
		updateUtil(st, mid+1, e, i, diff, 2*si + 2);
	}
}
void update(int st[], int a[], int n, int index, int newValue){
	if(index < 0 || index > n-1){
		printf("Invalid input\n");
		return;
	}
	int diff = newValue - a[index];
	a[index] = newValue;

	updateUtil(st, 0, n-1, index, diff, 0);
}

int getSumUtil(int st[], int s, int e, int l, int r, int si){
	if(s > e || l > e || r < s)
		return 0;
	if(s >= l && e <= r)
		return st[si];
	int mid = s + ((e - s) / 2);
	return getSumUtil(st, s, mid, l, r, 2*si + 1) + getSumUtil(st, mid + 1, e, l, r, 2*si + 2);
}
int getSum(int st[], int n, int l, int r){
	if(l < 0 || r > n-1 || l > r){
		printf("Invalid input: ");
		return -1;
	}

	printf("sum in the range (%d, %d) is ", l, r);
	return getSumUtil(st, 0, n-1, l, r, 0);
}

int buildSTutil(int st[], int a[], int s, int e, int si){
	if(s == e){
		st[si] = a[s];
		return a[s];
	}
	int mid = s + ((e - s) / 2);

	st[si] = buildSTutil(st, a, s, mid, 2*si+1) + buildSTutil(st, a, mid+1, e, 2*si+2);
	return st[si];
}

int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int i,n, a[n];
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);

	int height = (int)(ceil(log(n)/log(2)));

	int maxSize = 2*(int)(pow(2, height)) - 1;

	int st[maxSize];
	int ret = buildSTutil(st, a, 0, n-1, 0);

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"sum",strlen("sum"))){ 
			char choice[10];
			int l,r;
			sscanf(opt, "%s %d %d" , choice, &l, &r); //sscanf reads formatted input from string

			int sum = getSum(st, n, l, r);
			printf("%d\n", sum); 
		}
		else if(!strncmp(opt,"update",strlen("update"))){
			char choice[10];
			int index, value;
			sscanf(opt, "%s %d %d" , choice, &index, &value);

			update(st, a, n, index, value); 
		}
	}
	fclose(fp); 
}