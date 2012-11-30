package experiment._1;

public class hw26 {

	static void draw(int n){
		int half = n / 2;
		//…œ∞Î∂Œ ––
		for(int i  = 1;i <= half;i++){
			//ø’∏Ò
			for(int blank = 0; blank <= half - i;blank++){
				System.out.print(" ");
			}
			//–«–«
			for(int star = 1; star <= 2*i-1; star++){
				System.out.print("*");
			}
			System.out.println();
		}
		//œ¬∞Î∂Œ ––
		for(int i = 0; i <= half; i++){
			//ø’∏Ò
			for(int blank = 0; blank < i;blank++){
				System.out.print(" ");
			}
			//–«–«
			for(int star = 1; star <= 2*(half-i)+1; star++){
				System.out.print("*");
			}
			System.out.println();
		}
	}
	public static void main(String[] args) {
		draw(7);
		draw(11);
	}

}
