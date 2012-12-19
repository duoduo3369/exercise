package sys;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.HashSet;

public class ReadStudentInfo {
	public static HashSet<Student> read() {
		HashSet<Student> studentSet = new HashSet<Student>();
		try {
			FileInputStream fin = new FileInputStream("stdentinfo.ds");
			ObjectInputStream oin = new ObjectInputStream(fin);
			Object obj = null;
			while ((obj = oin.readObject()) != null) {
				if (obj instanceof Student) {
					Student s = (Student) obj;
					studentSet.add(s);
				}
			}
			oin.close();
			return studentSet;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (EOFException e) {
			//e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return studentSet;
	}
}
