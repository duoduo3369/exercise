package sys;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;

public class StudentTest {

	public static void main(String[] args) {
		HashSet<Student> set = new HashSet<Student>();
		
		Student a = new Student("101","¿Óπ„");
		MathScore ms = new MathScore(80, a); 
		SoftWareScore ss = new SoftWareScore(79,a);
		a.addMajorScore(ms);
		a.addMajorScore(ss);
		
		Student b = new Student("102","œƒ∫Ó‘®");
		MathScore ms2 = new MathScore(212, b); 
		b.addMajorScore(ms2);
		
		Student c = new Student("103","’≈Ú¢");
		MathScore ms3 = new MathScore(90.1,c);
		c.addMajorScore(ms3);
		
		MathScore msa = new MathScore(800, a); 
		a.changeMajorScore(msa);
		set.add(a);
		set.add(b);
		set.add(c);
		SaveStudentInfo.save(set);
		set = ReadStudentInfo.read();
		Iterator<Student> iterator = set.iterator();
		while(iterator.hasNext()){
			Student studentInSet = iterator.next(); 
			System.out.println("!!" + studentInSet);
			studentInSet.printMajorScores();
		}
		
		/*
		Statistic statistic = new Statistic();
		statistic.statistic(set);
		statistic.statisticMathScore.printStudent();
		*/
		
	}
}
