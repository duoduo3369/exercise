package figure;

public class Rectangle extends Shape{

	public Rectangle() {
		super();
	}
	public Rectangle(double height, double width) {
		super();
		this.height = height;
		this.width = width;
	}
	private double height;
	private double width;
	public double getArea() {
		return height * width;
	}
	public double getHeight() {
		return height;
	}
	public void setHeight(double height) {
		this.height = height;
	}
	public double getWidth() {
		return width;
	}
	public void setWidth(double width) {
		this.width = width;
	}
	@Override
	double getPerimeter() {
		return (width + height) * 2;
	}

}
