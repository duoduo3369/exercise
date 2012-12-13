package experiment._6;

import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;

public class ShoppingCart {
	HashMap shoplist;

	public ShoppingCart() {
		shoplist = new HashMap();
	}

	public void add(Book book, int many) {
		if (shoplist.containsKey(book)) {
			shoplist.put(book, (Integer) (shoplist.get(book)) + many);
			return;
		}
		shoplist.put(book, many);
	}

	public String toString() {
		Collection keyset = shoplist.keySet();
		Iterator iterator = keyset.iterator();
		StringBuffer outString = new StringBuffer();
		while (iterator.hasNext()) {
			Book book = (Book) iterator.next();

			outString.append(book.toString());
			outString.append(" ����:" + shoplist.get(book) + "��\n");
		}
		return outString.toString();
	}

	public double getSum() {
		double sum = 0;
		Collection keyset = shoplist.keySet();
		Iterator iterator = keyset.iterator();
		while (iterator.hasNext()) {
			Book book = (Book) iterator.next();
			sum += book.getMoney() * (Integer) (shoplist.get(book));
		}
		return sum;
	}

	public static void main(String args[]) {
		ShoppingCart shoppingCart = new ShoppingCart();
		Book xiyou = new Book("���μ�", 49.99);
		Book sanguo = new Book("��������", 59.99);
		Book suanfa = new Book("�㷨����", 112.99);
		Book shejimoshi = new Book("Head first ���ģʽ", 99.99);
		shoppingCart.add(xiyou, 2);
		shoppingCart.add(sanguo, 5);
		shoppingCart.add(xiyou, 2);
		shoppingCart.add(suanfa, 1);
		shoppingCart.add(shejimoshi, 1);

		System.out.println(shoppingCart.toString());
		System.out.println("�ܼƣ�" + shoppingCart.getSum() + "Ԫ");
		Scanner s = new Scanner(System.in);
		do {
			System.out.println("���������������ۡ��͹����Ǳ��飬Ctrl+Z��������");
			if (s.hasNext()) {
				String name = s.next();
				if (s.hasNextDouble()) {
					double price = s.nextDouble();
					Book book = new Book(name, price);
					if (s.hasNextInt()) {
						int many = s.nextInt();
						shoppingCart.add(book, many);
					} else {
						break;
					}
				} else {
					break;
				}
			}
		} while (s.hasNext());
		System.out.println(shoppingCart.toString());
		System.out.println("�ܼƣ�" + shoppingCart.getSum() + "Ԫ");
	}
}
