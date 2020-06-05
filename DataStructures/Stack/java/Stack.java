import java.util.Scanner;
import java.io.*;

class Stac{
	int[] arr;
	int top_, capacity;

	Stac(int capacity){
		arr = new int[capacity];
		top_ = -1;
		this.capacity = capacity; 
	} 

	private boolean isEmpty(){
		return (this.top_ == -1);
	} 
	private Boolean isFull(){
		return (this.top_ == (this.capacity)-1);
	}

	public void push(int val){
		if(this.isFull()){
			System.out.println("Insufficient stack capacity, so " + val + " is not pushed");
			return;
		}
		this.arr[++(this.top_)] = val;
	}
	public void pop(){
		if(this.isEmpty()){
			System.out.println("Stack is Empty, cant perform pop()");
			return;
		}
		(this.top_)--;
	}
	public int top(){
		if(this.isEmpty()){
			System.out.print("stack is Empty, cant retrieve top() : ");
			return 403;
		}
		return this.arr[this.top_];
	}
}
public class Stack{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

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

		Stac s = new Stac(100);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() > 3 && opt.substring(0,4).equals("push")){
				String[] ch = opt.split(" "); 
				int val = Integer.parseInt(ch[1]);
				s.push(val);
			}
			else if(opt.equals("pop")){
				s.pop();
			}
			else if(opt.equals("top")){
				System.out.println(s.top());
			}
		}
	}
}