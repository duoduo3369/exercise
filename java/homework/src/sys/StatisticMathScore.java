package sys;

public class StatisticMathScore extends StatisticMajorScore {
	
	public StatisticMathScore(){
		super();
	}
	public void printStudent(){
		System.out.println("---数学成绩分析---");
		System.out.println("分析时间: " + statisedTime);
		super.printStudent();
	}
}
