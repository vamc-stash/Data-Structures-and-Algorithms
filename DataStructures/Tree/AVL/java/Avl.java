import java.util.Scanner;
import java.io.*;

public class Avl{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	class Node{
		int data, height;
		Node left, right;

		public Node(int data){
			this.data = data;
			this.left = this.right = null;
			this.height = 1;
		}
	}

	Node root;

	Avl(){
		root = null;
	}

	int max(int a, int b){
		return (a>b)?a:b;
	}
	int height(Node node){
		if(node == null)
			return 0;
		return (node.height);
	}
	int getBalance(Node node){
		if(node == null)
			return 0;
		return height(node.left) - height(node.right); 
	}
	Node rightRotate(Node a){
		Node b = a.left;
		Node t = b.right;

		b.right = a;
		a.left = t;

		a.height = max(height(a.left), height(a.right)) + 1;
		b.height = max(height(b.left), height(b.right)) + 1;

		return b;
	}
	Node leftRotate(Node a){
		Node b = a.right;
		Node t = b.left;

		b.left = a;
		a.right = t;

		a.height = max(height(a.left), height(a.right)) + 1;
		b.height = max(height(b.left), height(b.right)) + 1;

		return b;
	}
	Node balancedTree(Node node, int data){

		node.height = 1 + max(height(node.left), height(node.right));
		int bal = getBalance(node);

		// Left Left case 
		if (bal> 1 && data < node.left.data) 
	        return rightRotate(node); 

	    // Right Right Case 
	    if (bal < -1 && data > node.right.data) 
	        return leftRotate(node); 
	  
	    // Left Right Case 
	    if (bal > 1 && data > node.left.data) 
	    { 
	        node.left =  leftRotate(node.left); 
	        return rightRotate(node); 
	    } 
	  
	    // Right Left Case 
	    if (bal < -1 && data < node.right.data) 
	    { 
	        node.right = rightRotate(node.right); 
	        return leftRotate(node); 
	    }

		return node;
	}

	void insert(int data){
		root = insertHelper(root, data);
	}
	Node insertHelper(Node node, int data){
		if(node == null){
			node = new Node(data);
			return node;
		}
		if(data < node.data)
			node.left = insertHelper(node.left, data);
		else if(data > node.data)
			node.right = insertHelper(node.right, data);
		return balancedTree(node, data);
	}

	boolean search(Node root, int data){
		if(root == null)
			return false;
		if(root.data == data)
			return true;
		else if(root.data < data){
			return search(root.right, data);
		}
		return search(root.left, data);
	}

	void delete(int data){
		root = deleteHelper(root, data);
	}
	Node deleteHelper(Node node, int data){
		if(node == null)
			return node;
		if(data < node.data )
			node.left = deleteHelper(node.left, data);
		else if(data > node.data)
			node.right = deleteHelper(node.right, data);
		else{
			//Node with one child or no child 
			if(node.left == null){
				Node temp = node.right;
				node = null;
				return temp;
			}
			else if(node.right == null){
				Node temp = node.left;
				node = null;
				return temp;
			}
			//Node with two child
			Node temp = getInorderSuccessor(node.right);
			node.data = temp.data;
			node.right = deleteHelper(node.right, temp.data);
		}
		return balancedTree(node, data);
	}
	Node getInorderSuccessor(Node temp){
		while(temp != null && temp.left != null)
			temp = temp.left;
		return temp;
	}

	void preorder(Node node){
		if(node != null){
			System.out.print(node.data + " ");
			preorder(node.left);
			preorder(node.right);
		}
	}
	void inorder(Node node){
		if(node != null){
			inorder(node.left);
			System.out.print(node.data + " ");
			inorder(node.right);
		}
	}
	void postorder(Node node){
		if(node != null){
			postorder(node.left);
			postorder(node.right);
			System.out.print(node.data + " ");
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

		Avl avl = new Avl();
		for(int i=0; i<n; i++){
			int key = scanner.nextInt();
			avl.insert(key);
		}

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "search".length() && opt.substring(0,"search".length()).equals("search")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);

				boolean isFound = avl.search(avl.root, key);
				if(isFound)
					System.out.println(key + " is found.");
				else
					System.out.println(key + " is not found.");
				
			}
			if(opt.length() >= "delete".length() && opt.substring(0,"delete".length()).equals("delete")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);

				avl.delete(key);	
			}
			else if(opt.equals("inorder")){
				System.out.println("Inorder traversal: ");
				avl.inorder(avl.root);
				System.out.println();
			}
			else if(opt.equals("preorder")){
				System.out.println("Preorder traversal: ");
				avl.preorder(avl.root);
				System.out.println();
			}
			else if(opt.equals("postorder")){
				System.out.println("Postorder traversal: ");
				avl.postorder(avl.root);
				System.out.println();
			}


		}
	}
}