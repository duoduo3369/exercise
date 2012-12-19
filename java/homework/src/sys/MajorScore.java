package sys;

import java.io.Serializable;

public abstract class MajorScore implements Serializable{
	
	public MajorScore(double score,Student student) {
		super();
		this.score = score;
		this.student = student;
	}

	protected double score;
	protected Student student;
	public int hashCode(){
		return this.student.hashCode();
	}
	public double getScore() {
		return score;
	}

	public void setScore(double score) {
		this.score = score;
	}
}
