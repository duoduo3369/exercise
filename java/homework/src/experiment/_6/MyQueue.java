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
		 * �����ջ���
		 * */
		stackLeft.push(o);
	}
	public Object deQueue(){
		/**
		 * ���ӷ����������
		 * 1���Ҷ�ջΪ��ʱ����Ϊ�����ջ��ӣ�����ʱӦ�����ջ�ĵ�
		 * һ��Ԫ���ȳ��ӣ�����Ӧ�����ջ��ջ�׵�Ԫ��ȫ��ѹ���ұ�ջ��
		 * Ȼ�󵯳����ջ��ջ��Ԫ�أ�
		 * 2���ұ�ջ��Ϊ��ʱ�����ε����ұ�ջ��Ԫ�ؼ���
		 * */
		if(stackRight.isEmpty()){
			if(stackLeft.isEmpty()){
				//TODO ����Ӧ���ø��쳣
				System.out.println("�쳣������Ϊ��!");
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
		Book xiyou = new Book("���μ�",49.99);
		Book sanguo = new Book("��������",59.99);
		Book suanfa = new Book("�㷨����",112.99);
		Book shejimoshi = new Book("Head first ���ģʽ",99.99);
		
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
