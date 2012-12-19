package sys;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class SaveStudentInfo {

	public static void save(Student student){
		try {
			String filename = "stdentinfo.ds";
			File f = new File(filename); 
			FileOutputStream fout = new FileOutputStream(f,true);
			MyObjectOutputStream moos = MyObjectOutputStream.newInstance(f, fout);
			moos.writeObject(student);
			moos.flush();
			moos.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
