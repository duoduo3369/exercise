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
		return "编号为" + this.no + "、姓名为" + this.name +"、年龄为" + this.age + "的" + this.seminary + "学院老师";
	}
	
	public static void main(String args[]){
		Teacher li = new Teacher("李晓峰","1001",20,"信息学院");
		Teacher zhang = new Teacher("张国庆","1002",20,"信息学院");
//		li.setAge(20);
//		li.setName("李晓峰");
//		li.setNo("1001");
//		li.setSeminary("信息学院");
//		zhang.setSeminary("信息学院");
//		zhang.setNo("1002");
//		zhang.setName("张国庆");
//		zhang.setAge(20);
		System.out.println(li.equals(zhang));
		System.out.println(li);
		System.out.println(zhang);
	}
}
