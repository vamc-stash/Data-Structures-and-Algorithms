import java.util.Scanner;

class HelloWorld{
	public static void main(String args[]){
		System.out.println("Hello World");

		//create a Scanner object
		Scanner sObj = new Scanner(System.in);
		String name = sObj.nextLine(); // read String
		int age = sObj.nextInt();	// read int
		double weight = sObj.nextDouble(); // read double

		System.out.println("username : " + name + " , age : " + age + " , weight : " + weight);
	}
}