package experiment._6;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;


public class Lottery {
	private static final int SIZE = 30; 
	private static final int DIGITNUMBERS = 7;
	private final int FISRT = 7;
	private final int SECOND = 6;
	private final int THIRD = 5;
	private static ArrayList<Integer> randomArray =new ArrayList<Integer>();
	static
	{
		for(int i = 1; i <= SIZE; i++){
			randomArray.add(i);
		}
	}
	//*/
	public Lottery(){
		this.lottery();
	}
	public void lottery(){
		Collections.shuffle(randomArray);
	}
	public String toString(){
		StringBuffer out = new StringBuffer("�˴�ҡ������Ϊ��");
		for(int i = 0; i < DIGITNUMBERS; i++){
			out.append(randomArray.get(i) + " ");
		}
		return out.toString();
	}
	public void wonWhitch(int[] lottery){
		int lucky = equalsBitNumbers(lottery);
		switch(lucky){
		case FISRT:
		{
			System.out.println("��ϲ�㣺����һ�Ƚ�");
			break;
		}
		case SECOND:
		{
			System.out.println("��ϲ�㣺���˶��Ƚ�");
			break;
		}
		case THIRD:
		{
			System.out.println("��ϲ�㣺�������Ƚ�");
			break;
		}
		default:
		{
			System.out.println("��Ʒ��̫�ã����û�н�������һ�Ű�");
		}
		}
		
	}
	private int equalsBitNumbers(int[] lottery){
		if(lottery.length != DIGITNUMBERS){
			System.out.println("����ˮ�����ף�Ӧ��7λ�Ŷ�");
			return 0;
		}
		int count = 0;
		for(int i = 0;i < DIGITNUMBERS; i++){
			for(int j:lottery){
				if(j == randomArray.get(i)){
					count++;
				}
			}
		}
		return count;
	}
	public static void main(String[] args) {
		Lottery money = new Lottery();
		System.out.println(money);
		int[] lottery = new int[7];
		Scanner s = new Scanner(System.in);
		while(true){
			money.lottery();
			for(int i = 0; i < 7 && s.hasNextInt(); i++){
				lottery[i] = s.nextInt();
			}
			money.wonWhitch(lottery);
			//money.lottery();
			System.out.println(money);
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
