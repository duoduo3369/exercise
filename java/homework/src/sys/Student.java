package sys;

import java.io.Serializable;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

public class Student implements Serializable {
	private String no;
	private String name;
	private HashMap<String, MajorScore> grades;

	public Student(String no, String name) {
		super();
		this.no = no;
		this.name = name;
		// this.grades = new HashSet<MajorScore>();
		this.grades = new HashMap<String, MajorScore>();
	}

	public void addMajorScore(MajorScore ms) {
		// this.grades.add(ms);
		this.grades.put(ms.getClass().getName(), ms);
	}

	public boolean changeMajorScore(MajorScore ms) {
		if (deleteMajorScore(ms)) {
			addMajorScore(ms);
			return true;
		}
		return false;
	}

	public boolean deleteMajorScore(MajorScore ms) {
		// if(grades.contains(ms)){
		if (grades.containsKey(ms)) {
			grades.remove(ms);
			return true;
		}
		return false;
	}

	// public HashSet<MajorScore> getMajorScoreSet(){
	public HashMap<String, MajorScore> getMajorScoreMap() {
		return grades;
	}

	public void printMajorScores() {
		Set<Entry<String, MajorScore>> set = grades.entrySet();
		Iterator<Entry<String, MajorScore>> iterator = set.iterator();
		while (iterator.hasNext()) {
			Entry<String, MajorScore> entry = iterator.next();
			System.out.println(entry.getValue());
		}
	}

	public int hashCode() {
		if (no == null) {
			return super.hashCode();
		}
		int length = no.length();
		char ch;
		int result = 0;
		for (int i = 0; i < length; i++) {
			result += no.charAt(i);
		}
		return result;
	}

	public String getNo() {
		return no;
	}

	public String getName() {
		return name;
	}

	public String toString() {
		return "Ñ§ºÅ:" + no + " ÐÕÃû:" + name;
	}

	public boolean equals(Object obj) {
		if (obj instanceof Student) {
			Student s = (Student) obj;
			return s.no.equals(this.no);
		}
		return false;
	}
}
