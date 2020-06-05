import java.util.Scanner;
import java.io.*;

public class DisjointSet{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	int n;
	int[] rank;
	int[] parent;

	DisjointSet(int n){
		this.n = n;
		rank = new int[n];
		parent = new int[n];
		for(int i=0; i<n; i++)
			parent[i] = i;
	}
	int find(int x){
		if(parent[x] != x)
			parent[x] = find(parent[x]);
		return parent[x];
	}
	void _union(int u, int v){
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

		DisjointSet ds = new DisjointSet(n);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "union".length() && opt.substring(0,"union".length()).equals("union")){
				String[] ch = opt.split(" "); 
				int a = Integer.parseInt(ch[1]);
				int b = Integer.parseInt(ch[2]);

				ds._union(a, b);
			}
			else if(opt.length() >= "find".length() && opt.substring(0,"find".length()).equals("find")){
				String[] ch = opt.split(" "); 
				int a = Integer.parseInt(ch[1]);
				int b = Integer.parseInt(ch[2]);

				if(ds.find(a) == ds.find(b))
					System.out.println(a+", "+b+" belongs to same set.");
				else
					System.out.println(a+", "+b+" belongs to different sets.");
			}
		}
	}
}