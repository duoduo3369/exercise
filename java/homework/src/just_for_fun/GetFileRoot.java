package just_for_fun;

import java.io.File;

public class GetFileRoot {

	 public static void main(String[] args) {   
		 File[] roots = File.listRoots();    
		 for (int i=0; i<roots.length; i++) { 
			 System.out.println(roots[i]);   
		 }
	}
}
