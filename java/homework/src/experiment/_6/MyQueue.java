package experiment._6;

import java.util.Stack;

public class MyQueue {

	private Stack stackLeft;
	private Stack stackRight;
	public MyQueue(){
		stackLeft = new Stack();
		stackRight = new Stack();
	}
	public void enQueue(Object o){
		/**
		 * 从左边栈入队
		 * */
		stackLeft.push(o);
	}
	public Object deQueue(){
		/**
		 * 出队分两种情况：
		 * 1、右端栈为空时：因为从左端栈入队，出队时应将左端栈的第
		 * 一个元素先出队，首先应将左端栈除栈底的元素全部压入右边栈，
		 * 然后弹出左边栈的栈底元素；
		 * 2、右边栈不为空时，依次弹出右边栈顶元素即可
		 * */
		if(stackRight.isEmpty()){
			if(stackLeft.isEmpty()){
				//TODO 这里应该用个异常
				System.out.println("异常：队列为空!");
				return null;
			}
			while(stackLeft.size() > 1){
				stackRight.push(stackLeft.pop());
			}
			return stackLeft.pop();
		}
		return stackRight.pop();
	}
	public static void main(String[] args) {
		MyQueue queue = new MyQueue();
		queue.enQueue(3);
		queue.enQueue(4);
		System.out.println(queue.deQueue());
		System.out.println(queue.deQueue());
		System.out.println(queue.deQueue());
		Book xiyou = new Book("西游记",49.99);
		Book sanguo = new Book("三国演义",59.99);
		Book suanfa = new Book("算法导论",112.99);
		Book shejimoshi = new Book("Head first 设计模式",99.99);
		
		queue.enQueue(xiyou);
		queue.enQueue(sanguo);
		System.out.println(queue.deQueue());
		queue.enQueue(suanfa);
		queue.enQueue(shejimoshi);		
		System.out.println(queue.deQueue());
		System.out.println(queue.deQueue());
		System.out.println(queue.deQueue());

	}

}
