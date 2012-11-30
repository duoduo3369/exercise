package just_for_fun;

import java.util.*;

class Cat {
	private int catNumber;

	Cat(int i) {
		catNumber = i;
	}

	void print() {
		System.out.println("Cat #" + catNumber);
	}
}

class Dog {
	private int dogNumber;

	Dog(int i) {
		dogNumber = i;
	}

	void print() {
		System.out.println("Dog #" + dogNumber);
	}
}

public class CatsAndDogs {
	public static void main(String[] args) {
		Vector cats = new Vector();
		for (int i = 0; i < 7; i++)
			cats.addElement(new Cat(i));

		cats.addElement(new Dog(7));
		
		Enumeration e = cats.elements();
		while(e.hasMoreElements()){
			((Cat)e.nextElement()).print();
		}


	}
}
