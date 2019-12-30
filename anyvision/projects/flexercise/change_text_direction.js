let rtlButton = document.getElementById('right-to-left');
let ltrButton = document.getElementById('left-to-right');

rtlButton.addEventListener('click', changeTextDirection('left'));
ltrButton.addEventListener('click', changeTextDirection('right'));

function changeTextDirection(direction) {
  console.log(`logged ${direction}`);
}

