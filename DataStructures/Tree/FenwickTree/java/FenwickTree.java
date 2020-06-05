// Sum of given implementation

import java.util.Scanner;
import java.io.*;
import java.lang.Math;

public class FenwickTree{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";


	int f[];

	FenwickTree(int n){
		f = new int[n+1];
		for(int i=1;i<=n;i++)
			f[i]=0;
	}

	int getSum(int index){

		int prefixSum = 0;
		while(index > 0){
			prefixSum += this.f[index];
			index -= (index & (-index));
		}
		return prefixSum;
	}
	void update(int n,int index,int val){
		while(index <= n){
			this.f[index] += val;
			index += (index & (-index));
		}
	}
	void build(int a[], int n){
		
		for(int i=0;i<n;i++)
			update(n,i+1,a[i]);
	}

	public static void main(String[] args){

		FileInputStream instream = null;
		PrintStream outstream = null;

		try{
			instream = new FileInputStream(ipfile);
			outstream = new PrintStream(new FileOutputStream(opfile));
			System.setIn(instream);
			System.setOut(outstream);
		} catch(Exception e){
			System.err.println("Error occured");
		}

		Scanner scanner = new Scanner(System.in);

		int n = scanner.nextInt();
		int[] a = new int[n];
		for(int i=0; i<n; i++){
			a[i] = scanner.nextInt();
		}

		FenwickTree f = new FenwickTree(n);
		f.build(a,n);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "sum".length() && opt.substring(0,"sum".length()).equals("sum")){
				String[] ch = opt.split(" "); 
				int l = Integer.parseInt(ch[1]);
				int r = Integer.parseInt(ch[2]);

				if(l < 0 || r > n-1 || l > r){
					System.out.println("Invalid Input");
				}
				else{
					int sum = f.getSum(r+1) - f.getSum(l);
					System.out.println("sum in the range (" + l + ", " + r + ") is " + sum);				
				}
				
			}
			else if(opt.length() >= "update".length() && opt.substring(0,"update".length()).equals("update")){
				String[] ch = opt.split(" "); 
				int index = Integer.parseInt(ch[1]);
				int newval = Integer.parseInt(ch[2]);


				if(index < 0 || index > n-1){
					System.out.println("Invalid Input");
				}
				else{
					int diff = newval-a[index];
					a[index] = newval;
					f.update(n,index+1,diff);
				}
			}
		}
	}
}