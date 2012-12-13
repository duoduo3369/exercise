package experiment._4;

import static org.junit.Assert.*;
import junit.framework.TestCase;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class StackTest extends TestCase {

	Stack stack;
	@Before
	public void setUp() throws Exception {
		stack = new Stack(5);
		
	}

	@Test
	public void testStack() {	
		stack.push(3);
		stack.push(2);
		Assert.assertTrue(stack.isEmpty() == false);
		Assert.assertTrue(((Integer)stack.getTop()) == 2);
		System.out.println("��1�ε�ջ��" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == false);
		System.out.println("��2�ε�ջ��" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == true);
		System.out.println("��3�ε�ջ��" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == true);
		stack.push(5);
		System.out.println("��1��ѹջ");
		stack.push(6);
		System.out.println("��2��ѹջ");
		stack.push(5);
		System.out.println("��3��ѹջ");
		stack.push(7);
		System.out.println("��4��ѹջ");
		stack.push(8);
		System.out.println("��5��ѹջ");
		stack.push(9);
		System.out.println("��6��ѹջ");
	}

}
