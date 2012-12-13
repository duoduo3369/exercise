package experiment._4;

public class Problem_3 {

	public static void main(String[] args) {
		int N = 5;
		int[][] matric = new int[N][];
		for(int i = 1; i < N; i++){
			matric[i] = new int[i];
			for(int j = 0; j < i; j++){
				matric[i][j] = i * j;
			}
		}
		System.out.println("< >");
		for(int i = 1; i < N; i++){
			System.out.print("< ");
			for(int j = 0; j < matric[i].length; j++){
				System.out.print(matric[i][j] + " ");
			}
			System.out.println(">");
		}
	}

}
