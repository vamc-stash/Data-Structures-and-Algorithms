import java.util.Scanner;
import java.io.*;

class Node{
	
	int data;
	Node next;

	Node(int data){
		this.data = data;
		this.next = null;
	}
};

class LList{

	Node head;

	LList(){
		head = null;
	}

	public void insert(int data){
		Node newnode = new Node(data);
		if(head == null){
			head = newnode;
		}
		else{
			Node temp = head;
			while(temp.next != null){
				temp = temp.next;
			}
			temp.next = newnode;
		}	
	} 

	public void insert_at_head(int data){
		Node newnode = new Node(data);
		if(head == null){
			head = newnode;
		}
		else{
			newnode.next = head;
			head = newnode;
		}
	}

	public boolean search(int val){
		Node temp = head;
		while(temp != null){
			if(temp.data == val)
				return true;
			temp = temp.next;
		}
		return false;
	}

	public void remove(int val){
		Node temp = head;
		Node prev = null;
		while(temp != null){
			if(temp.data == val){
				break;
			}
			prev = temp;
			temp = temp.next;
		}
		if(temp != null){
			if(prev == null){
				head = temp.next;
				temp = null;
			}
			else{
				prev.next = temp.next;
				temp = null;
			}
		}
		this.display();
	}

	public void reverse(Node head){
		if(head.next == null){
			this.head = head;
			return;
		}
		reverse(head.next);
		(head.next).next = head;
		head.next = null;
	}

	public void display(){
		Node temp = head;
		while(temp != null){
			System.out.print(temp.data + " --> ");
			temp = temp.next;
		}
		System.out.println("null");
	}

	public void displayReverse(Node head){
		if(head == null){
			return;
		}
		displayReverse(head.next);
		System.out.print(head.data + " ");
	}

	private Node[] split(Node head){
		if(head == null || head.next == null){
			Node[] halves = new Node[2];
			halves[0] = head;
			halves[1] = null;
			return halves;
		}
		Node slowptr = head;
		Node fastptr = head.next;
		while(fastptr != null){
			fastptr = fastptr.next;
			if(fastptr != null){
				slowptr = slowptr.next;
				fastptr = fastptr.next;
			}
		}

		Node[] halves = new Node[2];
		halves[0] = head;
		halves[1] = slowptr.next;
		slowptr.next = null;
		return halves;
	}
	private Node merge(Node a, Node b){
		if(a == null)
			return b;
		if(b == null)
			return a;
		Node temp = null;
		if(a.data <= b.data){
			temp = a;
			temp.next = merge(a.next, b);
		}
		else{
			temp = b;
			temp.next = merge(a, b.next);
		}
		return temp;
	}
	public Node mergeSort(Node head){
		if(head == null || head.next == null)
			return head;
		
		Node[] halves = split(head);
		Node fHalf = halves[0];
		Node sHalf = halves[1];
		fHalf = mergeSort(fHalf);
		sHalf = mergeSort(sHalf);
		return merge(fHalf, sHalf);
	}
}

public class LinkedList{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt"; 

	public static void main(String args[]){

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
		
		int[] arr = new int[n];
		for(int i=0; i<n; i++){
			arr[i] = scanner.nextInt();
		}
		
		// insertion
		System.out.println("Insertion at tail");
		LList list = new LList();
		for(int i=0; i<n; i++){
			list.insert(arr[i]);
		}
		list.display();

		System.out.println("Insertion at head");
		LList list2 = new LList();
		for(int i=0; i<n; i++){
			list2.insert_at_head(arr[i]);
		}
		list2.display();

		// search
		int searchVal = scanner.nextInt();
		boolean isAvailable = list.search(searchVal);
		if(isAvailable)
			System.out.println(searchVal + " is found");
		else
			System.out.println(searchVal + " is not found");

		// delete
		int delVal = scanner.nextInt();
		System.out.println("After deletion of node " + delVal);
		list.remove(delVal);
		
		// reverse
		System.out.println("Reversing list");
		list.reverse(list.head);
		list.display();
	
		// traverse reverse
		list.displayReverse(list.head);

		//merge sort
		System.out.println("\nSorted List");
		list.head = list.mergeSort(list.head);
		list.display();
	}
}