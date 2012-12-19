package sys;

import java.util.HashSet;
import java.util.Iterator;

public class StudentTest {

	public static void main(String[] args) {
		Student a = new Student("101","abc");
		Student b = new Student("101","bbb");
		HashSet<Student> set = new HashSet<Student>();
		
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
		//a.printMajorScores();
		set.add(a);
		set.add(b);
		SaveStudentInfo.save(set);
		System.out.println("========");
		
		set = ReadStudentInfo.read();
		Iterator<Student> iterator = set.iterator();
		while(iterator.hasNext()){
			Student studentInSet = iterator.next(); 
			System.out.println("!!" + studentInSet);
			studentInSet.printMajorScores();
		}
	}
}
