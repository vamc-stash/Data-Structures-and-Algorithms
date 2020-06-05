import java.util.Scanner;
import java.util.HashMap;
import java.util.Set;
import java.io.*;

public class Trie{

	private static final String ipfile = "../input.txt";
	private static final String opfile = "../output.txt";

	private boolean isLeaf;
	private HashMap<Character, Trie> map;

	Trie(){
		this.isLeaf = false;
		map = new HashMap<Character, Trie>();
	}

	public void insert(String str){
		Trie curr = this;
		for(int i=0; i < str.length(); i++){
			
			curr.map.putIfAbsent(str.charAt(i), new Trie());

			curr = curr.map.get(str.charAt(i));
		}
		curr.isLeaf = true;
	} 
	public boolean search(String str){
		Trie curr = this;
		if(curr == null)
			return false;
		for(int i=0; i < str.length(); i++){
			curr = curr.map.get(str.charAt(i));
			if(curr == null)
				return false;
		}
		return curr.isLeaf;
	}

	public boolean haveChildren(Trie curr){

		Set< HashMap.Entry<Character, Trie>> set = map.entrySet();
		for(HashMap.Entry<Character, Trie> it: set){
			if(it.getValue().map != null)
				return true;
		}
		return false;
	}
	public boolean delete(Trie curr, String str){
		if(curr == null)
			return false;
		if(str.length() > 0){
			if(curr != null && curr.map.get(str.charAt(0)) != null && delete(curr.map.get(str.charAt(0)), str.substring(1)) && curr.isLeaf == false){
				if(!haveChildren(curr)){
					curr = null;
					return true;
				}
				else
					return false;
			}
		}
		if(str.length() == 0 && curr.isLeaf == true){
			if(!haveChildren(curr)){
				curr = null;
				return true;
			}
			else{
				curr.isLeaf = false;
				return false;
			}
		}
		return false;
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

		Trie head = new Trie();

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "insert".length() && opt.substring(0,"insert".length()).equals("insert")){
				String[] ch = opt.split(" "); 
				String word = ch[1];

				head.insert(word);	
			}
			if(opt.length() >= "search".length() && opt.substring(0,"search".length()).equals("search")){
				String[] ch = opt.split(" "); 
				String word = ch[1];

				boolean isFound = head.search(word);
				if(isFound)
					System.out.println(word + " is found.");
				else
					System.out.println(word + " is not found.");
				
			}
			else if(opt.length() >= "delete".length() && opt.substring(0,"delete".length()).equals("delete")){
				String[] ch = opt.split(" "); 
				String word = ch[1];

				head.delete(head, word);	
			}
		}
	}
}