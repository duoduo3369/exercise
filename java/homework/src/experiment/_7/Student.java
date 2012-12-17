package experiment._7;

public class Student {
	private int no;
	private String name;
	private int grade;
	public Student(int no, String name, int grade) {
		super();
		this.no = no;
		this.name = name;
		this.grade = grade;
	}
	public int getGrade() {
		return grade;
	}
	public void setGrade(int grade) {
		this.grade = grade;
	}
	public int getNo() {
		return no;
	}
	public String getName() {
		return name;
	}
	public String toString() {
		return "学号:" + no + " 姓名:" + name + " 分数:" + grade;
	}
}
