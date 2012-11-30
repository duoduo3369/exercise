package figure;

public class Circle extends Shape{
	
	public Circle() {
		super();
	}
	public Circle(double radius) {
		super();
		this.radius = radius;
	}
	
	public double getRadius(){
		return this.radius;
	}
	public void setRadius(double radius){
		this.radius = radius;
	}
	public double getArea(){
		return Math.PI * radius * radius;
	}
	
	double getPerimeter() {
		return 2 * Math.PI * radius;
	}
	private double radius;
}
