import java.util.Scanner;
import java.io.*;

public class Bst{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	class Node{
		int data;
		Node left, right;

		public Node(int data){
			this.data = data;
			this.left = this.right = null;
		}
	}

	Node root;

	Bst(){
		root = null;
	}

	void insert(int data){
		root = insertHelper(root, data);
	}
	Node insertHelper(Node root, int data){
		if(root == null){
			root = new Node(data);
			return root;
		}
		if(data < root.data)
			root.left = insertHelper(root.left, data);
		else if(data > root.data)
			root.right = insertHelper(root.right, data);
		return root;
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
	Node deleteHelper(Node root, int data){
		if(root == null)
			return root;
		if(data < root.data )
			root.left = deleteHelper(root.left, data);
		else if(data > root.data)
			root.right = deleteHelper(root.right, data);
		else{
			//Node with one child or no child 
			if(root.left == null){
				Node temp = root.right;
				root = null;
				return temp;
			}
			else if(root.right == null){
				Node temp = root.left;
				root = null;
				return temp;
			}
			//Node with two child
			Node temp = getInorderSuccessor(root.right);
			root.data = temp.data;
			root.right = deleteHelper(root.right, temp.data);
		}
		return root;
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

		Bst bst = new Bst();
		for(int i=0; i<n; i++){
			int key = scanner.nextInt();
			bst.insert(key);
		}

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "search".length() && opt.substring(0,"search".length()).equals("search")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);

				boolean isFound = bst.search(bst.root, key);
				if(isFound)
					System.out.println(key + " is found.");
				else
					System.out.println(key + " is not found.");
				
			}
			else if(opt.length() >= "delete".length() && opt.substring(0,"delete".length()).equals("delete")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);

				bst.delete(key);	
			}
			else if(opt.equals("inorder")){
				System.out.println("Inorder traversal: ");
				bst.inorder(bst.root);
				System.out.println();
			}
			else if(opt.equals("preorder")){
				System.out.println("Preorder traversal: ");
				bst.preorder(bst.root);
				System.out.println();
			}
			else if(opt.equals("postorder")){
				System.out.println("Postorder traversal: ");
				bst.postorder(bst.root);
				System.out.println();
			}


		}
	}
}