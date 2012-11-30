package experiment._4;

public class Stack {
	
	public Stack() {
		super();
		this.length = 0;
		this.top = -1;
	}
	public Stack(int length) {
		super();
		this.length = length;
		this.stack = new Object[length];
		this.top = -1;
	}
	boolean isEmpty(){
		return top == -1;
	}
	void push(Object obj){
		if(this.isFull()){
			System.out.println("栈已经满了");
			return ;
		}
		this.stack[++top] = obj;
	}
	Object pop(){
		if(this.isEmpty()){
			System.out.println("栈已经空了");
			return null;
		}
		return this.stack[top--];
	}
	Object getTop(){
		if(this.isEmpty()){
			return null;
		}
		return this.stack[top];		
		
	}
	private boolean isFull(){
		return length == top+1;
	}
	static public void IntToBinary(int number){
		int length = (int)Math.ceil(Math.log(number)/Math.log(2))+1;
		Stack stack = new Stack(length);
		while(number != 0){
			stack.push(number % 2);
			number /= 2;
		}
		while(!stack.isEmpty()){
			System.out.print(stack.pop());
		}
		System.out.println();
		
	}
	private int top;
	private int length;
	private Object[] stack;
	public static void main(String args[]){
		Stack.IntToBinary(7);
		Stack.IntToBinary(8);
		Stack.IntToBinary(9);
		Stack.IntToBinary(2);
	}
	
}
