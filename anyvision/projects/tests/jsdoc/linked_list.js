/**
 * Represents a Linked List.
 */
class LinkedList {
  listSize;

  /**
   * Creates a Linked List.
   * @constructor
   */
  LinkedList() {
    this.listSize = 0;
  }

  isEmpty() {
    return this.listSize === 0;
  }

  /**
   * Size of the list.
   * @returns {number} size of list.
   */
  size() {
    return this.listSize;
  }

  popFront(){}

  popBack(){}

  /**
   * Find data.
   * @param data - data to find.
   * @param {function} cmpFunc - compare function for the comparator.
   */
  find(data, cmpFunc){}

  getIterator(){}
}