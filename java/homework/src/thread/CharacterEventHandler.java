package thread;

import java.util.*;

public class CharacterEventHandler {
	private Vector listeners = new Vector();
	public void addCharacterListener(CharacterListener clsner){
		listeners.add(clsner);
	}
	public void removeCharacterListener(CharacterListener clsner){
		listeners.remove(clsner);
	}
	public void fireNewCharacter(CharacterSource cs,int c){
		CharacterEvent ce = new CharacterEvent(cs,c);
		CharacterListener[] cl = (CharacterListener[])
				listeners.toArray(new CharacterListener[0]);
		for(int i = 0; i < cl.length; i++){
			cl[i].newCharacter(ce);
		}
	}
}
