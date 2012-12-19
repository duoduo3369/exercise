package sys;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;

public class ReadStudentInfo {
	public static Object read() {
		try {
			FileInputStream fin = new FileInputStream("stdentinfo.ds");
			ObjectInputStream oin = new ObjectInputStream(fin);
			Object obj = null;
			while ((obj = oin.readObject()) != null) {
				if (obj instanceof Student) {
					Student s = (Student) obj;
					System.out.println(s);
					s.printMajorScores();
				}
			}
			oin.close();
			return obj;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (EOFException e) {
			//e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return null;
	}
}
