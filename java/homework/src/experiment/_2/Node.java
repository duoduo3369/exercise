package experiment._2;

public class Node {
	/**
	 * 加入头结点，右插法
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
		return "值为: " + value + " 下一个节点: " + next;
	}
	
	public static void main(String[] args) {
		Node head = new Node("");
		
		System.out.println(head);

	}

}
