package experiment._4;

public class Matrix {
	public Matrix(int rows, int cols) {
		super();
		this.rows = rows;
		this.cols = cols;
		matrix = new double[rows][cols];
	}
	private int rows,cols;
	private double[][] matrix;
	public int height() {
		return rows;
	}
	public int width() {
		return cols;
	}
	public void set(int row, int col, double value){
		if(row >= rows || row < 0 || col < 0 || col >= cols){
			System.out.println("越界！");
			return ;
		}
		matrix[row][col] = value;
	}
	public double get(int row, int col){
		if(row >= rows || row < 0 || col < 0 || col >= cols){
			System.out.println("越界！");
			return 0.0;
		}
		return matrix[row][col];
	}
	public void print(){
		for(double[] row: matrix){
			for(double col :row){
				System.out.print (col + " ");
			}
			System.out.println();
		}
	}
	public void add(Matrix b){
		if(this.height() != b.height() || this.width() != b.width()){
			System.out.println("矩阵行列不相同，不能相加！");
			return ;
		}
		for(int i = 0; i < this.rows;i++){
			for(int j = 0; j < this.cols; j++){
				matrix[i][j] += b.get(i, j);
			}
		}
	}
	public Matrix multiply(Matrix b){
		if(this.cols != b.height()){
			System.out.println("矩阵不符合相乘条件！");
			return null;
		}
		Matrix result = new Matrix(rows,b.width());
		for(int row = 0; row < this.rows;row++){
			for(int col = 0; col < b.width();col++){
				double value = 0;
				for(int k = 0; k < this.cols; k++){
					value += matrix[row][k]*b.get(k, col);
				}
				result.set(row, col, value); 
			}
		}
		return result;
		
	}
	public static void main(String[] args) {
		Matrix a = new Matrix(2,2);
		a.set(0,0,1);
		a.set(0,1,1);
		a.set(1,1,1);
		a.print();
		Matrix b = new Matrix(2,2);
		b.set(0,0,1);
		b.set(0,1,2);
		b.set(1,0,3);
		b.set(1,1,4);
		b.print();
		
		Matrix c = a.multiply(b);
		c.print();
		a.add(b);
		a.print();
	
	}
}
