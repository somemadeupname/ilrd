const { LinkedList } = require('./linked_list_ecma5.js');
// const { LinkedList } = require('/home/student/Downloads/linkedList'); ADI'S FILE

test('sanity test', () => {
  const llist = new LinkedList();
  expect(llist).not.toBeNull();
});

test('add element', () => {
  const llist = new LinkedList();
  expect(llist.isEmpty()).toBeTruthy();
  llist.pushFront(5);
  expect(llist.isEmpty()).toBeFalsy();
});

test('confirm popFront throws exception', () => {
  const llist = new LinkedList();
  expect(() => { llist.popFront(); }).toThrowError();
});

test('remove element', () => {
  const llist = new LinkedList();
  expect(llist.isEmpty()).toBeTruthy();
  llist.pushFront(5);
  expect(llist.isEmpty()).toBeFalsy();
  llist.popFront();
  expect(llist.isEmpty()).toBeTruthy();
});

function initIntList(numElements) {
  const llist = new LinkedList();
  for (let i = 0; i < numElements; i += 1) {
    llist.pushFront(i);
  }

  return llist;
}

test('for of order', () => {
  const llistOfInts = initIntList(10);
  let i = 9;
  for (let element of llistOfInts) {
    expect(element).toBe(i);
    i -= 1;
  }
});

test('strain test', () => {
  const numOfElements = 4000;
  const llistOfInts = initIntList(numOfElements);
  let i = numOfElements - 1;
  for (let element of llistOfInts) {
    expect(element).toBe(i);
    i -= 1;
  }
  console.log(llistOfInts.toString());
});

function intCompareFunc(number1, number2) {
  return number2 - number1 === 0;
}

test('find data', () => {
  const numOfElements = 400000;
  const llistOfInts = initIntList(numOfElements);
  let i = numOfElements - 1;

  expect(llistOfInts.find(19, intCompareFunc)).not.toBe(undefined);
});

test('Try to find data not in list', () => {
  const numOfElements = 4000;
  const llistOfInts = initIntList(numOfElements);
  let i = numOfElements - 1;

  expect(llistOfInts.find(numOfElements + 5, intCompareFunc)).toBe(undefined);
});

function initStudentObjectList() {
  const studentList = new LinkedList();
  studentList.pushFront({ name: 'Dani', age: 13 });
  studentList.pushFront({ name: 'Vova', age: 26 });
  return studentList;
}

function studentCmp(student1, student2) {
  return (student1.name === student2.name) && (student1.age === student2.age);
}

test('test size when adding and removing', () => {
  const llist = new LinkedList();
  for (let i = 0; i < 20; i += 1) {
    llist.pushFront(5);
    expect(llist.size()).toBe(i+1);
  }
  for (let i = 19; i > 0; i -= 1) {
    llist.popFront(5);
    expect(llist.size()).toBe(i);
  }
  // expect(llist.isEmpty()).toBeTruthy();
});
