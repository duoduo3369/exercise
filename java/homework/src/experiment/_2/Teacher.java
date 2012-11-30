package experiment._2;

import java.util.Arrays;

public class Teacher implements Comparable{
	private int no;
	private String name;
	private int age;
	private String seminary;
	public Teacher(){
		
	}
	public Teacher(int no,String name,int age,String seminary){
		this.no = no;
		this.name = name;
		this.age = age;
		this.seminary = seminary;
	}
	public void setNo(int no){
		this.no = no;
	}
	public String getNO(){
		return Integer.toString(this.no);
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
	public int compareTo(Object other) {
		Teacher otherTeacher = (Teacher)other;
		if(this.no == otherTeacher.no){
			return 0;
		}
		else if(this.no < otherTeacher.no){
			return -1;
		}
		else{
			return 1;
		}
		
	}
	public static void main(String args[]){
		Teacher li = new Teacher(1001,"������",20,"��ϢѧԺ");
		Teacher zhang = new Teacher(1002,"�Ź���",20,"��ϢѧԺ");
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
		Teacher[] array = new Teacher[2]; 
		array[0] = zhang;
		array[1] = li;
		System.out.println("����ǰ");
		for(int i = 0; i < array.length; i++){
			System.out.println(array[i]);
		}
		Arrays.sort(array);
		System.out.println("�����");
		for(int i = 0; i < array.length; i++){
			System.out.println(array[i]);
		}
	}
	
}
