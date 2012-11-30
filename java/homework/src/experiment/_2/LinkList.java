package experiment._2;

public class LinkList {
	public Node head = new Node();
	private int many = 0;
	public int size(){
		return many;
	}
	public boolean isEmpty(){
		return many == 0;
	}
	public boolean insert(int index,Object value){
		/**
		 * 引入头结点，采用右插法
		 * index 值应>=0
		 * 插入节点同数组，例如，在第一个位置插入则insert(0，value)
		 * 当index大于链表节点的个数时，插到尾节点。 
		 * 插入成功，返回true。
		 * */
		if(index < 0){
			System.out.println("插入异常：插入下标不能为负值");
			return false;
		}
		Node node = new Node(value);
		Node p = head;
		int i = 0;
		while(p.next != null && i < index){
			p = p.next;
			++i;
		}
		node.next = p.next;
		p.next = node;
		++many;
		return true;
	}
	private boolean isIndexOutOfRange(int index){
		if(isEmpty()){			
			return false;
		}
		if(index >= size()){			
			return false;
		}
		return true;
	}
	public boolean delete(int index){
		/**
		 * 引入头结点，采用右删除法
		 * index 值应>=0，且index<=size()
		 * 删除节点同数组，例如，在第一个位置删除则delete(0)
		 * 最后一个节点delete(size())
		 * 当index大于链表节点的个数时，返回false。 
		 * */
		if(!isIndexOutOfRange(index)){
			System.out.println("删除异常：待删节点下标越界或原链表为空");
			return false;
		}
		Node p = head;
		int i = 0;
		while(p.next != null && i < index){
			p = p.next;
			++i;
		}
		p.next = p.next.next;
		--many;
		return true;
	}
	public boolean delete(Object x){
		if(isEmpty()){
			System.out.println("删除异常：链表为空");
			return false;
		}
		Node p = head,search_p = p.next;
		while(p.next != null){
			if(search_p.value == x){
				p.next = search_p.next;
				--many;
				return true;
			}
			p = p.next;
			search_p = p.next;
		}
		return false;
	}
	public Object getDate(int index){
		if(!isIndexOutOfRange(index)){
			System.out.println("坐标异常：节点下标越界或原链表为空");
			return null;
		}
		Node p = head;
		int i = 0;
		while(p.next != null && i < index){
			p = p.next;
			++i;
		}
		return p.next.value;
	}
	public void traverse(){
		Node p = head.next;
		while(p != null){
			System.out.print(p.value+" ");
			p = p.next;
		}
		System.out.println();
	}
	protected class Node {
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
			return "--> " + value + " " + next;
		}
	}
	
	public static void test(){
		LinkList a = new LinkList();
		a.delete(1);
		a.insert(-1,-1);
		System.out.println(a.head);
		System.out.println(a.size());
		a.insert(0,0);
		a.insert(1,1);
		a.insert(2,2);
		a.insert(3,3);
		a.insert(4,4);
		a.insert(5,5);
		a.insert(6,3);
		a.insert(7,2);
		System.out.println(a.head);
		System.out.println(a.size());
		a.delete(6);
		a.getDate(6);
		System.out.println(a.head);
		System.out.println(a.size());
		System.out.println(a.getDate(5));
		a.delete((Object)2);
		System.out.println(a.head);
		a.delete((Object)2);
		System.out.println(a.head);
		a.delete((Object)8);
		System.out.println(a.head);
		a.traverse();
	}

	public static void main(String[] args) {
		test();
	}

}
