const { LinkedList } = require('linked_list');

test('sanity test', ()=> {
  const llist = new LinkedList();
  expect(llist).not.toBeNull();
});

// test('sanity test2 should fail', ()=> {
//   const llist2 = new LinkedList();
//   expect(llist2).toBeNull();
// });

test('remove data from empty list', ()=> {
  const llist = new LinkedList();

});