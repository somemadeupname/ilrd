package il.co.ilrd.linked_list;

public interface Iterator {

    /**
     * Check if there is a next element.
     *
     * @return true if next element is valid, otherwise false.
     */
    boolean hasNext();

    /**
     * @return Data of current element.
     */
    Object next();
}