package sys;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map.Entry;
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
			HashMap<String, MajorScore> majorMap = student.getMajorScoreMap();
			Iterator<Entry<String, MajorScore>> iteratorMajorSet = majorMap.entrySet().iterator();
			//Iterator<MajorScore> iteratorMajorSet = majorSet.iterator();
			while(iteratorMajorSet.hasNext()){
				Entry<String, MajorScore> entry = iteratorMajorSet.next();
				MajorScore ms = entry.getValue();
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
