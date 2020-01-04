const { LinkedList } = require('linked_list');

test('sanity test', ()=> {
  const llist = new LinkedList();
  expect(llist).not.toBeNull();
});

test('remove data from empty list', ()=> {
  const llist = new LinkedList();
});

test('add element', ()=> {
  const llist = new LinkedList();
  expect(llist.isEmpty()).toBeTruthy();
  llist.pushFront(5);
  expect(llist.isEmpty()).toBeFalsy();
});

test('remove element', ()=> {
  const llist = new LinkedList();
  expect(llist.isEmpty()).toBeTruthy();
  llist.pushFront(5);
  expect(llist.isEmpty()).toBeFalsy();
  llist.popFront();
  expect(llist.isEmpty()).toBeTruthy();
});

function initIntList(numElements){
  const llist = new LinkedList();
  for (let i = 0; i < numElements; ++i) {
    llist.pushFront(i);
  }

  return llist;
}

test('for of order', ()=> {
  const llistOfInts = initIntList(10);
  let i = 9;
  for (let element of llistOfInts) {
    expect(element).toBe(i);
    --i;
  }
});

test('pop front on empty list', ()=> {
  const llist = new LinkedList();
  expect(llist.popFront()).toBe(undefined);
});

test('strain test', ()=> {
  let numOfElements = 400000;
  const llistOfInts = initIntList(numOfElements);
  let i = numOfElements - 1;
  for (let element of llistOfInts) {
    expect(element).toBe(i);
    --i;
  }
});