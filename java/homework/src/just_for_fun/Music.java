package just_for_fun;

class Note {
	private int value;

	private Note(int val) {
		value = val;
	}

	public static final Note middleC = new Note(0), cSharp = new Note(1),
			cFlat = new Note(2);
} // Etc.

class Instrument {
	public void play(Note n) {
		System.out.println("Instrument.play()");
	}
}

class Wind extends Instrument {
	public void play(Note n) {
		System.out.println("Wind.play()");
	}

}

public class Music {
	public static void tune(Instrument i) {
		i.play(Note.middleC);
	}

	public static void main(String[] args) {
		Instrument flute = new Instrument();
		tune(flute); // Upcasting
	}
}