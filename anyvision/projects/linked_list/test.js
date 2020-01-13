const { LinkedList } = require('./linked_list_ecma6.js');
// const { LinkedList } = require('/home/student/Downloads/linkedList'); ADI'S FILE

test('sanity test', () => {
  const llist = new LinkedList();
  expect(llist).not.toBeNull();
});
