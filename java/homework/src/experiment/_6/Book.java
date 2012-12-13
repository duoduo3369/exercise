package experiment._6;

public class Book {
	private int id;
	private String name;
	private double money;
	private static int idBase = 100;
	public Book(String name, double money) {
		super();
		this.id = idBase++;
		this.name = name;
		this.money = money;
	}
	public boolean equals(Object o){
		if(o instanceof Book){
			Book book = (Book)o;
			if(book.id == this.id){
				return true;
			}
		}
		return false;
	}
	
	public int hashCode(){
		int result = 71;
		result = result * 69 + id;
		result = result * 21 + id * 3;
		return result;
	}
	public String toString(){
		return "书名： "+name + " 单价：" + money;
	}
	public double getMoney() {
		return money;
	}
}
