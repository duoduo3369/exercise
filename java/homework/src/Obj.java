
public class Obj {
	private String name;
	public Obj(String name){
		this.name = name;
	}
	public void generaName(){
		name = name + " changed!";
	}
	public String toString(){
		return name + " ";
		
	}

}
