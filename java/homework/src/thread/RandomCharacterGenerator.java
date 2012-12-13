package thread;
import java.util.*;
public class RandomCharacterGenerator extends Thread 
implements CharacterSource {

	static char[] chars;
	static String charArray = "abcdefghijklmnopqrstuvwxyz0123456789";
	static {
		chars = charArray.toCharArray();
	}
	Random random;
	CharacterEventHandler handler;
	public RandomCharacterGenerator(){
		random = new Random();
		handler = new CharacterEventHandler();
	}
	public int getPauseTime(){
		return (int)(Math.max(1000, 5000*random.nextDouble()));
	}
	@Override
	public void addCharacterListener(CharacterListener clsner) {
		handler.addCharacterListener(clsner);
	}

	@Override
	public void removeCharacterListener(CharacterListener clsner) {
		handler.removeCharacterListener(clsner);
	}

	@Override
	public void nextCharacter() {
		handler.fireNewCharacter(this, 
				(int)chars[random.nextInt(chars.length)]);
		
	}
	public void run(){
		for(;;){
			this.nextCharacter();
			try{
				Thread.sleep(this.getPauseTime());
			}catch(InterruptedException ie){
				return ;
			}
		}
	}
}
