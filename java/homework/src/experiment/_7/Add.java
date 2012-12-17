package experiment._7;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Add {
	/**
	 * 使用缓冲区从键盘上读入内容
	 * */
	public static void main(String[] args) {
		BufferedReader buf = new BufferedReader(
				new InputStreamReader(System.in));
		String str = null;
		double a = 0,b = 0;
		
		try {
			System.out.print("请输入a:");		
			str = buf.readLine();
			a = Double.parseDouble(str);
			System.out.print("请输入b:");		
			str = buf.readLine();
			b = Double.parseDouble(str);
			buf.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("结果为：" + (a+b));
	}
}
