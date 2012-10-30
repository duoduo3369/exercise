package figure;

public class Circle {
	private double radius;
	public double getRadius(){
		return this.radius;
	}
	public void setRadius(double radius){
		this.radius = radius;
	}
	public double getArea(){
		return Math.PI * this.radius * this.radius;
	}
}
