package experiment._5;

public class Problem_2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		final int TestSize = 20;
		int[] ramdomTest = new int[TestSize+1];
		for(int i = 0; i < 1000; i++){
			ramdomTest[(int) (Math.random()*20+0.5)]++;
		}
		for(int i = 0; i <= TestSize; i++){
			System.out.println(i + ": " + ramdomTest[i] +" ");
		}
		int TestCountSum = 0;
		for(int number:ramdomTest){
			TestCountSum += number;
		}
		System.out.println(TestCountSum);
	}

}
