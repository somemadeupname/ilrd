class View {
  constructor () {
    this.app = this.getElement('root');

    this.searchBarSection = this.createElement('section', 'search-bar-section');
    this.searchForm = this.createElement('form', '', 'search-bar');
    this.searchDiv = this.createElement('div', 'mdl-textfield');
    this.searchDiv.classList.add('mdl-js-textfield');
    this.searchInput = this.createElement('input', 'mdl-textfield__input', 'search_box');
    this.searchInput.type = 'text';
    this.searchInput.autocomplete = 'off';
    this.searchInput.placeholder = 'Search..'; // TODO i18n

    this.searchDiv.append(this.searchInput);
    this.searchForm.append(this.searchDiv);
    this.searchBarSection.append(this.searchForm);
    this.app.append(this.searchBarSection);

    this.contentSection = this.createElement('div', '', 'content-section');
    this.postsSection = this.createElement('section', 'posts', 'posts-id');

    this.contentSection.append(this.postsSection);
    this.app.append(this.postsSection);




  }

  /**
   * Create HTML element.
   * @param {string} tag - element tag
   * @param {string} [className]
   * @param {string} [id]
   * @returns {Element}
   */
  createElement (tag, className, id) {
    const element = document.createElement(tag);
    if (className) {
      element.classList.add(className);
    }
    if (id) {
      element.id = id;
    }
    return element;
  }

  getElement(selector) {
    const element = document.querySelector(selector);
    return element;
  }

}

let view = new View();