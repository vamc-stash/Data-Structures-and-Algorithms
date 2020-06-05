import java.util.Scanner;
import java.util.ArrayList;
import java.io.*;

public class UndirectedGraph{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	int v;
	ArrayList<ArrayList<Integer>> adjList;

	UndirectedGraph(int v){
		this.v = v;
		adjList = new ArrayList<ArrayList<Integer>>(v);
		for(int i=0; i<v; i++)
			adjList.add(new ArrayList<Integer>());
	}
	void addEdge(int a, int b){
		adjList.get(a).add(b);
		if(a != b)
			adjList.get(b).add(a);
	}
	void print(){
		for(int i=0; i<v; i++){
			System.out.print(i + " : ");
			for(int j=0; j<adjList.get(i).size(); j++){
				System.out.print(adjList.get(i).get(j) + " -> ");
			}
			System.out.println("null");
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

		int v = scanner.nextInt();

		UndirectedGraph g = new UndirectedGraph(v);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "addEdge".length() && opt.substring(0,"addEdge".length()).equals("addEdge")){
				String[] ch = opt.split(" "); 
				int a = Integer.parseInt(ch[1]);
				int b = Integer.parseInt(ch[2]);

				// a <-> b
				g.addEdge(a, b);
			}
		}

		g.print();
	}
}