package il.co.ilrd.linked_list;

public class TestLinkedList {

	public static void main(String[] args) {
		LinkedList linkedList = new LinkedList();
		System.out.println(linkedList.size());
		linkedList.pushFront(1);
		System.out.println(linkedList.size());
		linkedList.pushFront(2);
		System.out.println(linkedList.size());
		linkedList.pushFront(3);
		System.out.println(linkedList.size());
		
		System.out.println(linkedList.find(0));
		System.out.println(linkedList.find(2));
		System.out.println(linkedList.popFront());
		System.out.println(linkedList.popFront());
		System.out.println(linkedList.popFront());
		System.out.println(linkedList.popFront());
		System.out.println(linkedList.popFront());
		System.out.println(linkedList.popFront());
		linkedList.pushFront(3);
		linkedList.pushFront(2);
		linkedList.pushFront(1);
		System.out.println(linkedList.find(2).next());
		System.out.println(linkedList.find(0));
		linkedList.pushFront(2);
		System.out.println(linkedList.find(2).next());




	}

}
