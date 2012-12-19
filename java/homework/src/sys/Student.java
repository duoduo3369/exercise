package sys;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Iterator;

public class Student implements Serializable{
	private String no;
	private String name;
	private HashSet<MajorScore> grades;
	public Student(String no, String name) {
		super();
		this.no = no;
		this.name = name;
		this.grades = new HashSet<MajorScore>();
	}
	public void addMajorScore(MajorScore ms){
		this.grades.add(ms);
	}
	public void printMajorScores(){
		Iterator<MajorScore> iterator = grades.iterator();
		while(iterator.hasNext()){
			System.out.println(iterator.next());
		}
	}
	public int hashCode(){
		if(no == null){
			return super.hashCode();
		}
		int length = no.length();
		char ch;
		int result = 0;
		for(int i = 0; i < length; i++){
			result += no.charAt(i);
		}
		return result;
	}
	public String getNo() {
		return no;
	}
	public String getName() {
		return name;
	}
	public String toString() {
		return "Ñ§ºÅ:" + no + " ÐÕÃû:" + name;
	}
	public boolean equals(Object obj){
		if(obj instanceof Student){
			Student s = (Student)obj;
			return s.no.equals(this.no);
		}
		return false;
	}
}
