package experiment._7;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Add {
	/**
	 * ʹ�û������Ӽ����϶�������
	 * */
	public static void main(String[] args) {
		BufferedReader buf = new BufferedReader(
				new InputStreamReader(System.in));
		String str = null;
		double a = 0,b = 0;
		
		try {
			System.out.print("������a:");		
			str = buf.readLine();
			a = Double.parseDouble(str);
			System.out.print("������b:");		
			str = buf.readLine();
			b = Double.parseDouble(str);
			buf.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("���Ϊ��" + (a+b));
	}
}
