package just_for_fun.fivechess;
import java.util.Arrays;
public class Board {
	private Object[][] board;
	public int size = 0;
	public Board(int size){
		board = new Object[size][size];
		this.size = size;
		for(int i = 0; i < board.length; i++){
			for(int j = 0; j < board[i].length; j++){
				board[i][j] = "+";
			}
		}
	}
	public void print(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				System.out.print(board[i][j]);
			}
			System.out.println();
		}
	}
	public static void main(String AAA[]){
		Board b = new Board(15);
		b.print();
	}

}
