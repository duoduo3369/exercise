package experiment._2;

public class Node {
	/**
	 * ����ͷ��㣬�Ҳ巨
	 * 
	 * */
	private Node next;
	private Object value;
	public Node(){
		this.value = null;
		this.next = null;		
	}
	public Node(Object value){
		this.value = value;
		this.next = null;		
	}
	public Node(Object value,Node next){
		this.value = value;
		this.next = next;		
	}
	public String toString(){
		return "ֵΪ: " + value + " ��һ���ڵ�: " + next;
	}
	
	public static void main(String[] args) {
		Node head = new Node("");
		
		System.out.println(head);

	}

}
