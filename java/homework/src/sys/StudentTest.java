package sys;

public class StudentTest {

	public static void main(String[] args) {
		Student a = new Student("101","abc");
		Student b = new Student("101","bbb");
		System.out.println(a.equals(b));
		MathScore ms = new MathScore(80, a); 
		MathScore ms2 = new MathScore(212, a); 
		System.out.println(ms.equals(ms2));
		a.addMajorScore(ms);
		a.addMajorScore(ms2);
		///*
		SoftWareScore ss = new SoftWareScore(79,a);
		a.addMajorScore(ss);
		//*/
		a.printMajorScores();
		SaveStudentInfo s = new SaveStudentInfo();
		s.save(a);
		s.save(b);
		//System.out.println("========");
		
		ReadStudentInfo r = new ReadStudentInfo();
		r.read();
	}
}
