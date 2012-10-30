package experiment._2;

public class Teacher {
	private String no;
	private String name;
	private int age;
	private String seminary;
	public Teacher(){
		
	}
	public Teacher(String no,String name,int age,String seminary){
		this.no = no;
		this.name = name;
		this.age = age;
		this.seminary = seminary;
	}
	public void setNo(String no){
		this.no = no;
	}
	public String getNO(){
		return this.no;
	}
	public void setName(String name){
		this.name = name;
	}
	public String getName(){
		return this.name;
	}
	public void setAge(int age){
		this.age = age;
	}
	public int getAge(){
		return this.age;
	}
	public void setSeminary(String seminary){
		this.seminary = seminary;
	}
	public String getSeminary(){
		return this.seminary;
	}
	public boolean equals(Object teacher){
		if(teacher == null){
			return false;
		}
		if(teacher instanceof Teacher)
		{
			Teacher t = (Teacher)teacher;
			return this.no == t.no;
		}
		return false;
	}
	public String toString(){
		return "���Ϊ" + this.no + "������Ϊ" + this.name +"������Ϊ" + this.age + "��" + this.seminary + "ѧԺ��ʦ";
	}
	
	public static void main(String args[]){
		Teacher li = new Teacher("������","1001",20,"��ϢѧԺ");
		Teacher zhang = new Teacher("�Ź���","1002",20,"��ϢѧԺ");
//		li.setAge(20);
//		li.setName("������");
//		li.setNo("1001");
//		li.setSeminary("��ϢѧԺ");
//		zhang.setSeminary("��ϢѧԺ");
//		zhang.setNo("1002");
//		zhang.setName("�Ź���");
//		zhang.setAge(20);
		System.out.println(li.equals(zhang));
		System.out.println(li);
		System.out.println(zhang);
	}
}
