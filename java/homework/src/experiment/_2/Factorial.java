package experiment._2;

public class Factorial {
	static long factorial(int number){
		long result = 1;
		for(int i = 1; i <= number; ++i){
			result *= i;
		}
		return result;
	}
	static long factorialRecursion(int number){
		if(number == 1){
			return 1;
		}
		return (long)number * factorialRecursion(number - 1);
	}
	public static void main(String[] args) {
		int number = 20;
		System.out.println(factorial(number));
		System.out.println(factorial(number) == factorialRecursion(number));

	}

}
