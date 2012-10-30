package experiment._1;
import java.math.BigInteger;


public class Factor {
	long factor(long number){
		long result = 1;
		for(long i = 2; i <= number; ++i){
			result *= i;
		}
		return result;
	}
	BigInteger big_factor(long number){
		BigInteger result = new BigInteger("1");
		
		for(long i = 2; i <= number; ++i){
			
			result = result.multiply(new BigInteger(i+""));
		}
		return result;
	}
	public static void main(String args[]){
		Factor factor = new Factor();
		int n = 20;
		long sum = 0;
		for(int i = 1; i <= n; ++i){
			sum += factor.factor(i);
		}
		System.out.println(factor.factor(1000));
		System.out.println(factor.factor(20));
		System.out.println(sum);
		//溢出 
		//TODO: 解决溢出
		
		
		BigInteger big_sum = new BigInteger("0");
		for(long i = 1; i <= 20L; ++i){
			big_sum = big_sum.add(factor.big_factor(i));
		}
		System.out.println(factor.big_factor(1000));
		System.out.println(factor.big_factor(20));
		System.out.println(big_sum);
		
	}
	
}
