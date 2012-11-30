package experiment;

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
		 * ����ͷ��㣬�����Ҳ巨
		 * index ֵӦ>=0
		 * ����ڵ�ͬ���飬���磬�ڵ�һ��λ�ò�����insert(0��value)
		 * ��index��������ڵ�ĸ���ʱ���嵽β�ڵ㡣 
		 * ����ɹ�������true��
		 * */
		if(index < 0){
			System.out.println("�����쳣�������±겻��Ϊ��ֵ");
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
		 * ����ͷ��㣬������ɾ����
		 * index ֵӦ>=0����index<=size()
		 * ɾ���ڵ�ͬ���飬���磬�ڵ�һ��λ��ɾ����delete(0)
		 * ���һ���ڵ�delete(size())
		 * ��index��������ڵ�ĸ���ʱ������false�� 
		 * */
		if(!isIndexOutOfRange(index)){
			System.out.println("ɾ���쳣����ɾ�ڵ��±�Խ���ԭ����Ϊ��");
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
			System.out.println("ɾ���쳣������Ϊ�գ�����ɾ��");
			return false;
		}
		return true;
	}
	public Object getDate(int index){
		if(!isIndexOutOfRange(index)){
			System.out.println("�����쳣���ڵ��±�Խ���ԭ����Ϊ��");
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
	protected class Node {
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
			return "--> " + value + " " + next;
		}
	}

	public static void main(String[] args) {
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
		a.insert(7,5);
		System.out.println(a.head);
		System.out.println(a.size());
		a.delete(6);
		a.getDate(6);
		System.out.println(a.head);
		System.out.println(a.size());
		System.out.println(a.getDate(5));
		
	}

}
