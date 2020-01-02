/**
 * Represents a Linked List.
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

  isEmpty() {
    return this._size === 0;
  }

  /**
   * Size of the list.
   * @returns {number} size of list.
   */
  size() {
    return this._size;
  }

  popFront() {
    if (this._head === null) {
      return undefined;
    }

    let removedData = this._head.data;
    this.head = this._head.next;
    --this._size;
  }

  pushFront(data) {
    this._head = new Node(data, this._head);
  }

  /**
   * Find data.
   * @param data - data to find.
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
          const data = cur.data;
          cur = cur.next;
          return { value: data, done: false };
        }

        return { value: undefined, done: true };
      },
    };
  }
}

class Node {
  constructor(data, next) {
    this.data = data;
    this.next = null;
  }
}

module.exports = { LinkedList };
