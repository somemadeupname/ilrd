const sum = require('./sum');

describe('testing simple sum', tests);

function tests() {
  test('adds 1 + 2 to equal 3', () => {
    expect(sum(1, 2)).toBe(3);
  });

  test('adds 1 + 1 to equal 3', () => {
    expect(sum(1, 1)).toBe(3);
  });
}

