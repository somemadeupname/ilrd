/**
 * Represents a Singly Linked List.
 * @Author: Ran Shieber
 * @version: 1.0
 * @Reviewer: Vladimir Kraykin
 */
class LinkedListECMA6 {
  /**
   * Creates a Linked List.
   * @constructor
   */
  constructor () {
    this._size = 0;
    this._head = null;
  }

  /**
   * Checks if list is empty.
   * @returns {boolean} True if the list is empty, false otherwise.
   */
  isEmpty () {
    return this._size === 0;
  }

  /**
   * Size of the list.
   * @returns {number} The number of elements in the list.
   */
  size () {
    return this._size;
  }

  /**
   * Removes the last element added to the list.
   * @returns {data | undefined} - Data of the removed element. undefined if list is empty.
   */
  popFront () {
    if (this._head === null) {
      throw 'Cannot perform pop an empty List';
    }
    const removedData = this._head._data;
    this._head = this._head._next;
    this._size -= 1;
    return removedData;
  }

  /**
   * Insert data into the list.
   * @param {*} data - Data to be inserted into the list.
   */
  pushFront (data) {
    this._head = new Node(data, this._head);
    this._size += 1;
  }

  /**
   * Find element key in Linked List.
   * @param {*} key - key to find.
   * @param {function} cmpFunc - compare function for the comparator.
   * @return {*|undefined} Value of matched element. undefined if element isn't found.
   */
  find (key, cmpFunc) {
    for (const value of this) {
      if (cmpFunc(key, value)) {
        return value;
      }
    }

    return undefined;
  }

  [Symbol.iterator] () {
    let cur = this._head;
    return {
      next: function () {
        if (cur !== null) {
          const data = cur._data;
          cur = cur._next;
          return { value: data, done: false };
        }

        return { value: undefined, done: true };
      },
    };
  }
}

class Node {
  constructor (data, next) {
    this._data = data;
    this._next = next;
  }
}

module.exports = { LinkedList: LinkedListECMA6 };
