package figure;

import static org.junit.Assert.*;
import junit.framework.TestCase;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class TestFigure extends TestCase{
	private Rectangle rectangle;
	private Circle circle;
	private Triangle triangle;
	public void setUp() throws Exception {
		rectangle = new Rectangle(20,40);
		circle = new Circle(10);
		triangle = new Triangle(3,4,5);
	}

	public void testGetPerimeter() {
		Assert.assertTrue(rectangle.getPerimeter() == 120);
		Assert.assertTrue(circle.getPerimeter() == Math.PI * 20);
		Assert.assertTrue(triangle.getPerimeter() == 12);
	}
	public void testGetArea(){
		Assert.assertTrue(rectangle.getArea() == 800);
		Assert.assertTrue(circle.getArea() == Math.PI * 100);
		Assert.assertTrue(triangle.getArea() == 6);
	}

}
