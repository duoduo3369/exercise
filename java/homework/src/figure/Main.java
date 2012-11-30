package figure;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Rectangle rectangle = new Rectangle(10,100);
		Circle circle = new Circle(50);
		Shape s = (Shape)rectangle;
		s.getArea();
		s.getPerimeter();
		s = (Shape)circle;
		s.getArea();
		s.getPerimeter();
	}

}
