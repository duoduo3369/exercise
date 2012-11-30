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
		Assert.assertTrue((int)stack.getTop() == 2);
		System.out.println("第1次弹栈：" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == false);
		System.out.println("第2次弹栈：" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == true);
		System.out.println("第3次弹栈：" + stack.pop());
		Assert.assertTrue(stack.isEmpty() == true);
		stack.push(5);
		System.out.println("第1次压栈");
		stack.push(6);
		System.out.println("第2次压栈");
		stack.push(5);
		System.out.println("第3次压栈");
		stack.push(7);
		System.out.println("第4次压栈");
		stack.push(8);
		System.out.println("第5次压栈");
		stack.push(9);
		System.out.println("第6次压栈");
	}

}
