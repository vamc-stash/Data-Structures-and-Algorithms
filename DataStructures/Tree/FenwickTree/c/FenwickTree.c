// Sum of Given range Implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int getSum(int f[],int index){

	int prefixSum = 0;
	while(index > 0){
		prefixSum += f[index];
		index -= (index & (-index));
	}
	return prefixSum;
}
void update(int f[],int n,int index,int val){
	while(index <= n){
		f[index] += val;
		index += (index & (-index));
	}
}
void build(int fenwick[], int a[],int n){

	for(int i=1;i<=n;i++)
		fenwick[i]=0;
	for(int i=0;i<n;i++)
		update(fenwick,n,i+1,a[i]);
}

int main(){

	FILE* fp = freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);

	int i,n, a[n];
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);

	int fenwick[n+1];
	build(fenwick, a, n);

	while(!feof(fp)){

		char opt[20]; 
		fgets(opt, 20, fp); // it reads string from a file, one line at a time

		if(!strncmp(opt,"sum",strlen("sum"))){ 
			char choice[10];
			int l,r;
			sscanf(opt, "%s %d %d" , choice, &l, &r); //sscanf reads formatted input from string

			if(l < 0 || r > n-1 || l > r){
				printf("Invalid Input\n");
			}
			else{
				int sum = getSum(fenwick, r+1) - getSum(fenwick, l);
				printf("sum in the range (%d, %d) is %d\n",l,r,sum);
			}
		}
		else if(!strncmp(opt,"update",strlen("update"))){
			char choice[10];
			int index, newval;
			sscanf(opt, "%s %d %d" , choice, &index, &newval);

			int diff = newval-a[index];
			a[index] = newval;
			update(fenwick,n,index+1,diff); 
		}
	}
	fclose(fp); 
}