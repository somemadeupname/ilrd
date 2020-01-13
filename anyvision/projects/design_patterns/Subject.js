// const { Observer } = require('Observer.js');

class Subject {
  constructor () {
    this.observers = [];
    this.color = null;
  }

  // add the ability to subscribe to a new object / DOM element
  // update all subscribed objects / DOM elements

  // essentially, add something to the observers array
  subscribe (f) {
    this.observers.push(f);
  }

  // and pass some data to each of them
  notifyAll () {
    const generateColor = function () {
      // The available hex options
      const hex = ['a', 'b', 'c', 'd', 'e', 'f', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
      let color = '#';

      // Create a six-digit hex color
      for (let i = 0; i < 6; i += 1) {
        // Append first hex value to the string
        color += hex[Math.floor(Math.random() * Math.floor(hex.length))];
      }
      // Return the color string
      return color;
    };

    this.color = generateColor();
    for (const observer of this.observers) {
      observer.update(this.color);
    }
  }
}

class Observer {
  constructor (elementIndex) {
    this.element = document.getElementById('obs' + elementIndex);
  }

  update (color) {
    this.element.style.background = color;
  }
}

const observer1 = new Observer(1);
const observer2 = new Observer(2);
const observer3 = new Observer(3);

// instantiate new Observer class
const mainObserver = new Subject();

// subscribe to some observers
mainObserver.subscribe(observer1);
mainObserver.subscribe(observer2);
mainObserver.subscribe(observer3);

document.getElementById('button_obs').addEventListener('click', (e) => {
  mainObserver.notifyAll();
});
