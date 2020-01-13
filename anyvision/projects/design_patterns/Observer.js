class Observer {
  constructor (elementIndex) {
    this.element = document.getElementById('obs' + elementIndex);
  }

  update (color) {
    this.element.style.background = color;
  }
}

// module.exports = { Observer };
