package experiment._1;

public class PrimeNumber {

	boolean isPrime(int number){
		//double sqr = Math.floor(Math.sqrt(number));
		int i;
		for(i = 2; i < number; i++){
			if(number % i == 0){
				return false;			
			}
		}
		return true;
	}
	public static void main(String[] args) {
		PrimeNumber pnumber = new PrimeNumber();
		int i,n = 100;
		for(i = 2; i < n; ++i){
			if(pnumber.isPrime(i)){
				System.out.print(i+" ");
			}
		}

	}

}
