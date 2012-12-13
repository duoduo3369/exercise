package thread;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SwingTypeTester extends JFrame implements CharacterSource {

	protected RandomCharacterGenerator producer;
	private CharacterDisplayCanvas displayCanvas;
	private CharacterDisplayCanvas feedbackCanvas;
	private JButton quitButton;
	private JButton startButton;
	private CharacterEventHandler handler;
	public SwingTypeTester(){
		initComponents();
	}
	
	@SuppressWarnings("deprecation")
	private void initComponents() {
		handler = new CharacterEventHandler();
		displayCanvas = new CharacterDisplayCanvas();
		feedbackCanvas = new CharacterDisplayCanvas(this);
		quitButton = new JButton();
		startButton = new JButton();
		add(displayCanvas,BorderLayout.NORTH);
		add(feedbackCanvas,BorderLayout.CENTER);
		JPanel p = new JPanel();
		startButton.setLabel("开始");
		quitButton.setLabel("推出");
		p.add(startButton);
		p.add(quitButton);
		
		
		add(p,BorderLayout.SOUTH);
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent evt){
				quit();
			}
		});
		
		
		feedbackCanvas.addKeyListener(new KeyAdapter(){
			public void keyPressed(KeyEvent ke){
				char c = ke.getKeyChar();
				if(c != KeyEvent.CHAR_UNDEFINED){
					newCharacter((int)c);
				}
			}
		});
		startButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent evt) {
				producer = new RandomCharacterGenerator();
				displayCanvas.setCharacterSource(producer);
				producer.start();
				startButton.setEnabled(false);
				feedbackCanvas.setEnabled(true);
				feedbackCanvas.requestFocus();
			}
			
		});
		quitButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				quit();
				
			}
			
		});
	}
	public void newCharacter(int c) {
		handler.fireNewCharacter(this, c);
		
	}

	private void quit() {
		System.exit(0);
		
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
		throw new IllegalStateException("我们不需要制造");

	}
	public static void main(String args[]){
		new SwingTypeTester().show();
	}

}
