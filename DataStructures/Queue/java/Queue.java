import java.util.Scanner;
import java.io.*;

class Queu{
	int[] arr;
	int rear, front, capacity;

	Queu(int capacity){
		arr = new int[capacity];
		front = rear = -1;
		this.capacity = capacity; 
	} 

	private boolean isEmpty(){
		return (this.rear == -1 && this.front == -1);
	} 
	private Boolean isFull(){
		return ((this.rear + 1)%(this.capacity) == this.front);
	}

	public void enqueue(int val){
		if(this.isFull()){
			System.out.println("Insufficient queue capacity, so " + val + " is not enqueued");
			return;
		}
		if(this.front == -1)
			(this.front)++;
		this.rear = (this.rear+1)%this.capacity;
		this.arr[this.rear] = val;
	}
	public void dequeue(){
		if(this.isEmpty()){
			System.out.println("queue is empty, cant perform dequeue()");
			return;
		}
		if(this.rear == this.front){
			this.rear = this.front = -1;
		}
		else
			this.front = (this.front + 1)%this.capacity;
	}
	public int peek(){
		if(this.isEmpty()){
			System.out.print("stack is Empty, cant retrieve top() : ");
			return 403;
		}
		return this.arr[this.front];
	}
}

public class Queue{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	private static int size = 5;

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

		Queu q = new Queu(size);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "enqueue".length() && opt.substring(0,"enqueue".length()).equals("enqueue")){
				String[] ch = opt.split(" "); 
				int val = Integer.parseInt(ch[1]);
				q.enqueue(val);
			}
			else if(opt.equals("dequeue")){
				q.dequeue();
			}
			else if(opt.equals("peek")){
				System.out.println(q.peek());
			}
		}
	}
}