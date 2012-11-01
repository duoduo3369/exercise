package just_for_fun;
//: SystemProperty.java
import java.util.*;

public class SystemProperty {
	/** java编程思想里面的一个例子。
	* 显示着台机器上的系统信息.
	* @author Bruce Eckel
	* @author http://www.BruceEckel.com
	* @version 1.0
	*/
	public static void main(String[] args) {
		/** Sole entry point to class & application
		* @param args array of string arguments
		* @return No return value
		* @exception exceptions No exceptions thrown
		*/
		System.out.println(new Date());
		Properties p = System.getProperties();
		p.list(System.out);
		System.out.println("--- Memory Usage:");
		Runtime rt = Runtime.getRuntime();
		System.out.println("Total Memory = "
				+ rt.totalMemory()
				+ " Free Memory = "
				+ rt.freeMemory()
				+ " Used Memory = "
				+ (rt.totalMemory() - rt.freeMemory()));
		try {
			Thread.currentThread().sleep(5 * 1000);
		}
		catch(InterruptedException e){
		}
	}

}///:~
