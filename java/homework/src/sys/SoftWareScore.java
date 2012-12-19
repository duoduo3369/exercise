package sys;

public class SoftWareScore extends MajorScore {
	private static final String courseName = "������̳ɼ�";
	public SoftWareScore(double score, Student student) {
		super(score, student);
	}

	public boolean equals(Object obj){
		if(obj instanceof SoftWareScore){
			SoftWareScore ms = (SoftWareScore)obj;
			return ms.student.equals(this.student);
		}
		return false;
	}
	public String toString(){
		return courseName + ": " + score;
	}
}
