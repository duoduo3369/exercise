package sys;

public class StatisticMathScore extends StatisticMajorScore {
	
	public StatisticMathScore(){
		super();
	}
	public void printStudent(){
		System.out.println("---��ѧ�ɼ�����---");
		System.out.println("����ʱ��: " + statisedTime);
		super.printStudent();
	}
}
