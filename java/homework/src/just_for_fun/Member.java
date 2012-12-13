package just_for_fun;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
public class Member extends Observable implements Observer{
	private String name;
	private String state;
	public Member(String name){
		this.name = name;
	}
	public void stateChanged(){
		setChanged();
		notifyObservers();
	}
	public void setState(String state){
		this.state = state;
		stateChanged();
	}
	@Override
	public void update(Observable o, Object arg) {
		if(o instanceof Member){
			Member m = (Member)o;
			this.state = m.state;
			String outS = "----------------------";
			System.out.println(outS);
			System.out.println(name + " got it! " + "\nState is " + state);	
		}
			
		
	}
	public static void main(String args[]){
		Member duoduo = new Member("duoduo");
		Member sun = new Member("sun");
		Member li = new Member("li");
		duoduo.addObserver(sun);
		duoduo.setState("!加上sun!");
		duoduo.addObserver(li);
		duoduo.setState("!!!加上li!!!");
		duoduo.deleteObserver(sun);
		duoduo.setState("!删掉sun!");
		
	}

}
