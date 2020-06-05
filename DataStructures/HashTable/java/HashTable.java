import java.util.Scanner;
import java.io.*;

class DataBlock{
	int key, value;
}
class HashMap{
	DataBlock[] hashmap;
	int size;

	HashMap(int size){
		hashmap = new DataBlock[size];
		this.size = size;
	}

	private int hashCode(int key){
		return key % (this.size);
	}

	public void insert(int key, int value){
		DataBlock item = new DataBlock();
		item.key = key;
		item.value = value;

		int hashIndex = this.hashCode(key);

		//search for empty block
		int temp = hashIndex;
		while(hashmap[hashIndex] != null){
			hashIndex++;
			hashIndex %= (this.size);
			if(hashIndex == temp){
				System.out.println("Hashmap size is full, so previous data item with key " + key + " is overwritten");
				break;
			}
		}
		
		hashmap[hashIndex] = item;
	}

	public DataBlock search(int key){
		int hashIndex = this.hashCode(key);

		int temp = hashIndex;
		while(hashmap[hashIndex] != null){
			if(hashmap[hashIndex].key == key)
				return hashmap[hashIndex];
			hashIndex++;
			hashIndex %= (this.size);
			if(hashIndex == temp){
				break;
			}
		}
		return null;
	}

	public void delete(int key){
		int hashIndex = this.hashCode(key);

		int temp = hashIndex;
		while(hashmap[hashIndex] != null){
			if(hashmap[hashIndex].key == key){
				hashmap[hashIndex] = null;
				return;
			}
			hashIndex++;
			hashIndex %= (this.size);
			if(hashIndex == temp){
				System.out.println("data item with key " + key + " is not found to delete");
				break;
			}
		}
		return;
	}

	public void display(){

		for(int i=0; i<this.size; i++){
			if(hashmap[i] != null)
				System.out.print("(" + hashmap[i].key + ", " + hashmap[i].value + ") ");
			else
				System.out.print("~~ ");
		}
		System.out.println();
	}
}
public class HashTable{

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

		HashMap h = new HashMap(size);

		while(scanner.hasNext()){
			String opt = scanner.nextLine();

			if(opt.length() >= "insert".length() && opt.substring(0,"insert".length()).equals("insert")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);
				int value = Integer.parseInt(ch[2]);
				h.insert(key, value);
			}
			else if(opt.length() >= "search".length() && opt.substring(0,"search".length()).equals("search")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);
				DataBlock item = h.search(key);
				if(item != null)
					System.out.println("(" + item.key + ", " + item.value + ") is found");
				else
					System.out.println(key + " is not found");
			}
			else if(opt.length() >= "delete".length() && opt.substring(0,"delete".length()).equals("delete")){
				String[] ch = opt.split(" "); 
				int key = Integer.parseInt(ch[1]);
				h.delete(key);
			}
			else if(opt.equals("display")){
				h.display();
			}
		}
	}
}