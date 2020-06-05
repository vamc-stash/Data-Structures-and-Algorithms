import java.util.Scanner;
import java.io.*;

class Node{
	int data;
	Node prev, next;

	Node(int data){
		this.data = data;
		this.prev = this.next = null;
	}
};

class DLList{
	Node head, tail;

	DLList(){
		head = tail = null;
	}

	public void insert_at_tail(int data){
		Node newnode = new Node(data);
		tail = newnode;
		if(head == null){
			head = newnode;
			return;
		}
		Node temp = head;
		while(temp.next != null){
			temp = temp.next;
		}
		temp.next = newnode;
		newnode.prev = temp;
		return;
	}

	public void insert_at_head(int data){
		Node newnode = new Node(data);
		newnode.next = head;
		if(head != null)
			head.prev = newnode;
		else
			tail = newnode;
		head = newnode;
		return ;
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
		while(temp != null){
			if(temp.data == val){
				break;
			}
			temp = temp.next;
		}
		if(temp != null){
			if(temp.prev == null){
				head = temp.next;
				if(head != null)
					head.prev = null;
				else
					tail = null;
				temp = null;
			}
			else{
				temp.prev.next = temp.next;
				if(temp.next != null)
					temp.next.prev = temp.prev;
				else
					tail = temp.prev;
				temp = null;
			}
		}
		this.display();
		this.displayReverse();
	}

	public void display(){
		System.out.print("null");
		Node temp = head;
		while(temp != null){
			System.out.print(" <-- " + temp.data + " --> ");
			temp = temp.next;
		}
		System.out.println("null");
	}

	public void displayReverse(){
		System.out.print("null");
		Node temp = tail;
		while(temp != null){
			System.out.print(" <-- " + temp.data + " --> ");
			temp = temp.prev;
		}
		System.out.println("null");
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
		slowptr.next.prev = null;
		slowptr.next = null;
		return halves;
	}
	private Node merge(Node a, Node b){
		Node temp = null;
		while(a != null && b != null){
			if(a.data <= b.data){
				if(temp == null)
					temp = a;

				Node t = a.next;
				a.next = b;
				if(b.prev != null){
					b.prev.next = a;
				}
				b.prev = a;
				a = t;
			}
			else{
				if(temp == null)
					temp = b;

				Node t = b.next;
				b.next = a;
				if(a.prev != null){
					a.prev.next = b;
				}
				a.prev = b;
				b = t;
			}
		}
		if(a != null){
			while(a.next != null){
				a = a.next;
			}
			tail = a;
		}
		else if(b != null){
			while(b.next != null){
				b = b.next;
			}
			tail = b;
		}
		
		return temp;
	}
	public Node mergeSort(Node head){
		if(head == null || head.next == null){
			return head;
		}
		Node[] halves = split(head);
		Node fHalf = mergeSort(halves[0]);
		Node sHalf = mergeSort(halves[1]);
		return merge(fHalf, sHalf);
	}
}
public class DoubleLinkedList{

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
		int n = scanner.nextInt();
		
		int[] arr = new int[n];
		for(int i=0; i<n; i++){
			arr[i] = scanner.nextInt();
		}
		
		// insertion
		System.out.println("Insertion at tail");
		DLList list = new DLList(); 
		for(int i=0; i<n; i++){
			list.insert_at_tail(arr[i]);
		}
		list.display();
		list.displayReverse();

		System.out.println("Insertion at head");
		DLList list2 = new DLList();
		for(int i=0; i<n; i++){
			list2.insert_at_head(arr[i]);
		}
		list2.display();
		list2.displayReverse();

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
		
		// merge sort
 		list.head = list.mergeSort(list.head);
		System.out.println("Sorted List");
		list.display();
		System.out.println("Traversing Sorted List in descending order");
		list.displayReverse();
	}
}