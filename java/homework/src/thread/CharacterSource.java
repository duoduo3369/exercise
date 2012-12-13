package thread;

public interface CharacterSource {
	public void addCharacterListener(CharacterListener clsner);
	public void removeCharacterListener(CharacterListener clsner);
	public void nextCharacter();

}
