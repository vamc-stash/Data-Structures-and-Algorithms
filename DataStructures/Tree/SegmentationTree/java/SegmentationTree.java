// Sum of given implementation

import java.util.Scanner;
import java.io.*;
import java.lang.Math;

public class SegmentationTree{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";


	int st[];

	SegmentationTree(int[] a, int n){
		int height = (int)(Math.ceil(Math.log(n)/Math.log(2)));
		int maxSize = 2*(int)(Math.pow(2, height)) - 1;

		st = new int[maxSize];
		buildSTutil(a, 0, n-1, 0);
	}

	void updateUtil(int s, int e, int i, int diff, int si){
		if(i < s || i > e)
			return;
		st[si] += diff;
		if(s != e){
			int mid = s + ((e - s) / 2);
			updateUtil(s, mid, i, diff, 2*si + 1);
			updateUtil(mid+1, e, i, diff, 2*si + 2);
		}
	}
	void update(int a[], int n, int index, int newValue){
		if(index < 0 || index > n-1){
			System.out.println("Invalid input");
			return;
		}
		int diff = newValue - a[index];
		a[index] = newValue;

		updateUtil(0, n-1, index, diff, 0);
	}

	int getSumUtil(int s, int e, int l, int r, int si){
		if(s > e || l > e || r < s)
			return 0;
		if(s >= l && e <= r)
			return st[si];
		int mid = s + ((e - s) / 2);
		return getSumUtil(s, mid, l, r, 2*si + 1) + getSumUtil(mid + 1, e, l, r, 2*si + 2);
	}
	int getSum(int n, int l, int r){
		if(l < 0 || r > n-1 || l > r){
			System.out.print("Invalid input: ");
			return -1;
		}

		System.out.print("sum in the range (" + l + ", " + r + ") is ");
		return getSumUtil(0, n-1, l, r, 0);
	}

	int buildSTutil(int a[], int s, int e, int si){
		if(s == e){
			st[si] = a[s];
			return a[s];
		}
		int mid = s + ((e - s) / 2);

		st[si] = buildSTutil(a, s, mid, 2*si+1) + buildSTutil(a, mid+1, e, 2*si+2);
		return st[si];
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

		SegmentationTree st = new SegmentationTree(a, n);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "sum".length() && opt.substring(0,"sum".length()).equals("sum")){
				String[] ch = opt.split(" "); 
				int l = Integer.parseInt(ch[1]);
				int r = Integer.parseInt(ch[2]);

				int sum = st.getSum(n, l, r);
				System.out.println(sum);
				
			}
			else if(opt.length() >= "update".length() && opt.substring(0,"update".length()).equals("update")){
				String[] ch = opt.split(" "); 
				int index = Integer.parseInt(ch[1]);
				int value = Integer.parseInt(ch[2]);

				st.update(a, n, index, value);	
			}
		}
	}
}