function LinkedListECMA5 () {
  this._head = null;

  this._Node = function (data, next) {
    this._data = data;
    this._next = next;
  };
}

/**
 * Checks if list is empty.
 * @returns {boolean} True if the list is empty, false otherwise.
 */
LinkedListECMA5.prototype.isEmpty = function () {
  return this._head === null;
};

/**
 * Size of the list.
 * @returns {number} The number of elements in the list.
 */
LinkedListECMA5.prototype.size = function () {
  let size = 0;
  for (const value of this) {
    size += 1;
  }
  return size;
};

/**
 * Removes the last element added to the list.
 * @returns {*} - Data of the removed element.
 */
LinkedListECMA5.prototype.popFront = function () {
  if (this._head === null) {
    throw new Error('Cannot perform pop an empty List');
  }

  const removedData = this._head._data;
  this._head = this._head._next;
  return removedData;
};

/**
 * Insert data into the list.
 * @param {*} data - Data to be inserted into the list.
 */
LinkedListECMA5.prototype.pushFront = function (data) {
  this._head = new this._Node(data, this._head);
}

/**
 * Find element key in Linked List.
 * @param {*} key - key to find.
 * @param {function} cmpFunc - compare function for the comparator.
 * @return {*|undefined} Value of matched element. undefined if element isn't found.
 */
LinkedListECMA5.prototype.find = function (key, cmpFunc) {
  for (const value of this) {
    if (cmpFunc(key, value)) {
      return value;
    }
  }

  return undefined;
}

LinkedListECMA5.prototype[Symbol.iterator] = function () {
  let cur = this._head;
  return {
    next () {
      if (cur !== null) {
        const data = cur._data;
        cur = cur._next;
        return { value: data, done: false };
      }

      return { value: undefined, done: true };
    }
  };
};

module.exports = { LinkedList: LinkedListECMA5 };
