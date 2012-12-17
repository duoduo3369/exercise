package experiment._7;

import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;

public class StudentTest {

	public static void main(String[] args) {
		String fileContent = "";
		ArrayList<Student> studentList = new ArrayList<Student>();
		try {
			File f = new File("data/data.txt");
			InputStreamReader read = new InputStreamReader(new FileInputStream(
					f), "UTF-8");
			BufferedReader reader = new BufferedReader(read);
			String line;
			int lineNumber = 100;
			while ((line = reader.readLine()) != null) {
				String[] lineDate = line.split(" ");
				studentList.add(new Student(lineNumber, lineDate[0], Integer
						.parseInt(lineDate[1])));
				lineNumber++;
			}
			read.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		Iterator i = studentList.iterator();
		double sum = 0;
		while (i.hasNext()) {
			Student s = (Student)i.next();
			sum += s.getGrade();
			System.out.println(s);
		}
		System.out.println("Æ½¾ù·Ö: " + sum / studentList.size());
	}
}
