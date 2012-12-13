package experiment._5;

public class Problem_3 {

	public static double[][] getTwoDimensionalArray(String string){
		//按；分行
		String[] splitStringWithSemicolon = string.split(";");
		double[][] array = new double[splitStringWithSemicolon.length][];
		for(int i = 0 ; i < array.length; i++){
			String[] splitStringWithComma = splitStringWithSemicolon[i].split(",");
			double[] rows = new double[splitStringWithComma.length];
			//按，分行
			array[i] = rows;
			for(int j = 0; j < splitStringWithComma.length; j++){
				array[i][j] = Double.parseDouble(splitStringWithComma[j]); 
			}			
		}		
		
		return array;
	}
	public static void printTwoDimensionalArray(double[][] array){
		for(double[] row :array){
			for(double d :row){
				System.out.print(d + " ");
			}
			System.out.println();
		}
	}
	public static void main(String[] args) {

		double[][] array = getTwoDimensionalArray("1,2;3,4,5;6,7,8");
		printTwoDimensionalArray(array);
	}

}
