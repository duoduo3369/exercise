package experiment._5;

public class StringSpecial {

	private String string;
	private int upperCaseAlphabetLetterNumber;
	private int lowerCaseAlphabetLetterNumber;
	private int notAlphabetLetterNumber;
	public StringSpecial(String s){
		string = s;
		countCaseNumber();
	}
	private void countCaseNumber(){
		upperCaseAlphabetLetterNumber = 0;
		lowerCaseAlphabetLetterNumber = 0;
		notAlphabetLetterNumber = 0;
		int length = string.length();
		for(int i = 0 ; i < length; i++){
			if(string.charAt(i) >= 'A' && string.charAt(i) <= 'Z'){
				upperCaseAlphabetLetterNumber++;
			}
			else if(string.charAt(i) >= 'a' && string.charAt(i) <= 'z'){
				lowerCaseAlphabetLetterNumber++;
			}
			else{
				notAlphabetLetterNumber++;
			}
		}
	}
	public int getUpperCaseAlphabetLetterNumber() {
		return upperCaseAlphabetLetterNumber;
	}
	public int getLowerCaseAlphabetLetterNumber() {
		return lowerCaseAlphabetLetterNumber;
	}
	public int getNotAlphabetLetterNumber() {
		return notAlphabetLetterNumber;
	}
	public String toString() {
		return string;
	}
	public static void main(String[] args) {
		StringSpecial string = new StringSpecial("ABCabcdd1234");
		System.out.println(string);
		System.out.println("Сд��ĸ�� " + string.getLowerCaseAlphabetLetterNumber());
		System.out.println("��д��ĸ�� " + string.getUpperCaseAlphabetLetterNumber());
		System.out.println("��Ӣ����ĸ�� " + string.getNotAlphabetLetterNumber());
	}


}
