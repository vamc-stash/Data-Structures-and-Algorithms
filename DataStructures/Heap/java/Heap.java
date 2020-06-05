// Max Heap Implementation
import java.util.Scanner;
import java.io.*;

class PriorityQueue{
	int[] arr;
	int size, capacity;

	PriorityQueue(int capacity){
		arr = new int[capacity];
		size = 0;
		this.capacity = capacity; 
	} 

	private void heapify_down(int[] arr, int size, int i){
		int largest = i;
		int left = 2*i + 1; // left child
		int right = 2*i + 2; // right child
		if(left < size && arr[left] > arr[largest])
			largest = left;
		if(right < size && arr[right] > arr[largest])
			largest = right;
		if(largest != i){
			int temp = arr[i];
			arr[i] = arr[largest];
			arr[largest] = temp;
			this.heapify_down(arr, size, largest);
		}
	}

	private void heapify_up(int[] arr, int i){
		int p = (i-1)/2; // parent
		if(i != 0 && arr[p] < arr[i]){
			int temp = arr[i];
			arr[i] = arr[p];
			arr[p] = temp;
			heapify_up(arr, p);
		}
	}

	public void insert(int data){
		if(this.size == this.capacity){
			System.out.println("overflow: could not insert " + data);
			return;
		}
		(this.arr)[this.size] = data;
		(this.size)++;

		this.heapify_up(this.arr, (this.size)-1);
	}
	public void dequeue(){
		if(this.size == 0){
			System.out.println("empty heap: could not remove priority element");
			return;
		}
		(this.arr)[0] = (this.arr)[this.size - 1];
		(this.size)--;

		this.heapify_down(this.arr, this.size, 0);
	}
	public int peek(){
		if(this.size == 0){
			System.out.println("empty heap: could not retreive priority element: ");
			return 403;
		}
		return (this.arr)[0];
	}
	public void display(){
		for(int i=0; i<this.size; i++){
			System.out.print((this.arr)[i] + " ");
		}
		System.out.println();
	}
}

public class Heap{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	private static int size = 20;

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

		PriorityQueue pq = new PriorityQueue(size);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() > "insert".length() && opt.substring(0,"insert".length()).equals("insert")){
				String[] ch = opt.split(" "); 
				int val = Integer.parseInt(ch[1]);
				pq.insert(val);
			}
			else if(opt.equals("dequeue")){
				pq.dequeue(); // Remove priority element (max value element in this case)
			}
			else if(opt.equals("peek")){
				System.out.println(pq.peek()); // priority element of the heap
			}
			else if(opt.equals("display")){
				pq.display(); // display heap
			}
		}
	}
}