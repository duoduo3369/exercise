package figure;

public class Triangle extends Shape{

	public Triangle() {
		super();
	}

	public Triangle(double side_1, double side_2, double side_3) {
		super();
		this.side_1 = side_1;
		this.side_2 = side_2;
		this.side_3 = side_3;
	}

	@Override
	double getArea() {
		//º£Â×¹«Ê½
		double p = (side_1 + side_2 + side_3) / 2;
		return Math.sqrt(p*(p-side_1)*(p-side_2)*(p-side_3));
	}

	@Override
	double getPerimeter() {
		return side_1 + side_2 + side_3;
	}
	private double side_1,side_2,side_3;
	public double getSide_1() {
		return side_1;
	}

	public void setSide_1(double side_1) {
		this.side_1 = side_1;
	}

	public double getSide_2() {
		return side_2;
	}

	public void setSide_2(double side_2) {
		this.side_2 = side_2;
	}

	public double getSide_3() {
		return side_3;
	}

	public void setSide_3(double side_3) {
		this.side_3 = side_3;
	}

}
