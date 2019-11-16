package il.co.ilrd.linked_list;

/*
 * Author: Shieber
 * Reviewer: Hila
 */

public class LinkedList {
    private Node head;
    
    public LinkedList() {
		this.head = new Node(null, null);
	}

    /**
     * Pushes element at the front of list.
     *
     * @param data Data to push into list.
     */
    public void pushFront(Object data) {
    	
    	Node newNode = new Node(null, data);
    	
    	if (this.isEmpty()) {
    		this.head.next = newNode;
    	}
    	else {
    		newNode.next = head.next;
    		head.next = newNode;
    	}
    }

    /**
     * Removes and returns the first element of this list.
     *
     * @return The element at the front of this list, if list is empty null is returned.
     */
    public Object popFront() {
        
    	if (!this.isEmpty())
    	{
    		Object dataToRemove = this.head.next.data;
    		this.head.next = this.head.next.next;
    		return dataToRemove;
    		
    	}
    	return null;
    }

    /**
     * Checks if list is empty.
     *
     * @return true if empty, otherwise false.
     */
    public boolean isEmpty() {
        return (null == this.head.next);
    }

    /**
     * Get number of elements in the list.
     *
     * @return Number of elements in the list.
     */
    public int size() {
    	
    	int numOfNodes = 0;
    	Iterator iter = this.begin();
        
        while (iter.hasNext())
        {
        	iter.next();
        	++numOfNodes;
        }
        
    	return numOfNodes;
    }

    /**
     * Finds data in Linked List.
     *
     * @param data Data to find.
     * @return Iterator with found data, otherwise null.
     */
    public Iterator find(Object data) {
        Object curData = null;
        Iterator iter = this.begin();
        Iterator prevIter = this.begin();

        
        while (iter.hasNext())
        {
        	curData = iter.next();
        	if (data.equals(curData)) {
        		return prevIter;
        	}
        	else
        	{
        		if (prevIter.hasNext()) {
        			prevIter.next();        			
        		}
        	}
        }
    	return null;
    }

    /**
     * @return Iterator to the first element
     */
    public Iterator begin() {
        return (new ListIterator(this.head));
    }

    private class ListIterator implements Iterator {
        private Node curr;
        
        public ListIterator(Node node) {
			this.curr = node;
		}

        @Override
        public boolean hasNext() {
            return (null != this.curr.next);
        }

        @Override
        public Object next() {
            Object data = this.curr.data;
            this.curr = this.curr.next;
        	return data;
        }
    }

    private class Node {
        private Object data;
        private Node next;

        private Node(Node next, Object data) {
            this.data = data;
            this.next = next;
        }
    }
}