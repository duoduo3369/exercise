package sys;

public class MathScore extends MajorScore {
	private static final String courseName = "ÊýÑ§³É¼¨";
	public MathScore(double score,Student student) {
		super(score, student);
	}
	public boolean equals(Object obj){
		if(obj instanceof MathScore){
			MathScore ms = (MathScore)obj;
			return ms.student.equals(this.student);
		}
		return false;
	}
	public String toString(){
		return courseName + ": " + score;
	}
}
