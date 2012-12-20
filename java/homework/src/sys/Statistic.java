package sys;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Statistic {
	public StatisticMathScore statisticMathScore; 
	public Statistic(){
		statisticMathScore = new StatisticMathScore();
	}
	public void statistic(HashSet<Student> studentSet){
		Iterator<Student> iteratorStudent = studentSet.iterator();
		statisticMathScore.setStatisedTime();
		while(iteratorStudent.hasNext()){
			Student student = iteratorStudent.next();
			HashSet<MajorScore> majorSet = student.getMajorScoreSet();
			Iterator<MajorScore> iteratorMajorSet = majorSet.iterator();
			while(iteratorMajorSet.hasNext()){
				MajorScore ms = iteratorMajorSet.next();
				String className = ms.getClass().getName();
				switch(className){
				case "sys.MathScore":{
					statisticMathScore.add(ms);
					break;
				}
				}
			}
		}
	}
}
