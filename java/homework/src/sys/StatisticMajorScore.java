package sys;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.TreeSet;

public abstract class StatisticMajorScore {
	public String statisedTime;
	protected int excellentNumber;
	protected int wellNumber;
	protected int passNumber;
	protected int failNumber;
	protected int totalNumber;
	protected TreeSet<MajorScore> majorSet;
	public StatisticMajorScore(){
		excellentNumber = 0;
		wellNumber = 0;
		passNumber = 0;
		failNumber = 0;
		totalNumber = 0;
		majorSet = new TreeSet<MajorScore>();
	}
	public void add(MajorScore ms) {
		majorSet.add(ms);
	}
	public void setStatisedTime(){
		statisedTime = getCurrentDatetime();
	}
	public String getCurrentDatetime() {
		  Date currentTime = new Date();
		  DateFormat df = DateFormat.getDateTimeInstance(DateFormat.LONG,DateFormat.LONG);
		  String dateString = df.format(currentTime);
		  return dateString;
		 } 
	public void printStudent(){
		Iterator<MajorScore> iterator = majorSet.iterator();
		while(iterator.hasNext()){
			MajorScore ms = (MajorScore)(iterator.next());
			System.out.print(ms.getStudent());
			System.out.println(": " + ms.getScore());
		}
	}
}
