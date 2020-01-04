/**
 * Represents a Singly linked list.
 */
class LinkedList {
  /**
   * Creates a Linked List.
   * @constructor
   */
  constructor() {
    this._size = 0;
    this._head = null;
  }

  /**
   * Checks if list is empty.
   * @returns {boolean} true if list is empty, false otherwise.
   */
  isEmpty() {
    return this._size === 0;
  }

  /**
   * Size of the list.
   * @returns {number} number of elements in the list.
   */
  size() {
    return this._size;
  }

  /**
   * Removes the last element added to the list.
   * @returns {undefined|data} - undefined if list is empty. | data of the removed element.
   */
  popFront() {
    if (this._head === null) {
      return undefined;
    }

    let removedData = this._head.data;
    this._head = this._head._next;
    --this._size;
    return removedData
  }

  /**
   * Insert data into the list.
   * @param {*} data - data to be inserted into the list.
   */
  pushFront(data) {
    this._head = new Node(data, this._head);
    ++this._size;
  }

  /**
   * Find data.
   * @param {*} data - data to find.
   * @param {function} cmpFunc - compare function for the comparator.
   */
  find(data, cmpFunc) {
    for (let node of this) {
      if (cmpFunc(node, data)) {
        return node;
      }
    }

    return undefined;
  }

  [Symbol.iterator]() {
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
  constructor(data, next) {
    this._data = data;
    this._next = null;
  }
}

module.exports = { LinkedList };

