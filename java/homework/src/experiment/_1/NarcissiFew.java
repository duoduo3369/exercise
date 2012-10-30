package experiment._1;

public class NarcissiFew {

	
	boolean isNarcissiFew(int number){
		int hundred,ten,one;
		hundred = number / 100;
		ten = number / 10 % 10;
		one = number % 10;
		if(Math.pow(hundred,3)+Math.pow(ten,3)+Math.pow(one,3) == number){
			return true;
		}
		else{
			return false;
		}
	}
	
	public static void main(String[] args) {
		NarcissiFew narcissifew = new NarcissiFew();
		int n = 1000;
		int i;
		for(i = 100; i < n; i++){
			if(narcissifew.isNarcissiFew(i))
			{
				System.out.println(i);
			}
			
		}
	}
}
