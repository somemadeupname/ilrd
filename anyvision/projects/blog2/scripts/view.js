export default class View {
  constructor () {
    // TODO split into smaller functions
    this.app = this.getElement('root');
    // Create search bar
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
    // Create posts section
    this.contentSection = this.createElement('div', '', 'content-section');
    this.postsSection = this.createElement('section', 'posts', 'posts-id');
    this.contentSection.append(this.postsSection);
    // Create add/edit post form
    this.newPostForm = this.createElement('div', '', 'new-post-form');
    this.newPostFormForm = this.createElement('form');
    this.newPostFormFormForm = this.createElement('form');
    this.newPostFormFormForm.action = '#';
    this.formTitleField = this.createElement('div', 'mdl-textfield');
    this.formTitleField.classList.add('mdl-js-textfield');
    this.formTitleField.classList.add('mdl-textfield--floating-label');
    this.formTitleField.classList.add('new-form-content-titlefield');
    this.titleFieldInput = this.createElement('input', 'mdl-textfield__input', 'new-form-titlefield');
    this.titleFieldInput.type = 'text';
    this.titleFieldLabel = this.createElement('label', 'mdl-textfield__label');
    this.titleFieldLabel.for = 'new-form-titlefield';
    this.titleFieldLabel.textContent = 'Title'; // TODO i18n
    this.formTitleField.append(this.titleFieldInput);
    this.formTitleField.append(this.titleFieldLabel);
    this.newPostFormFormForm.append(this.formTitleField);
    this.formContentField = this.createElement('div', 'mdl-textfield');
    this.formContentField.classList.add('mdl-js-textfield');
    this.formContentField.classList.add('new-form-content-textfield');
    this.contentFieldTextArea = this.createElement('textarea', 'mdl-textfield__input', 'new-form-contentfield');
    // this.contentFieldTextArea.type = 'text';
    this.contentFieldTextArea.rows = '7'; // TODO rethink this
    this.contentFieldLabel = this.createElement('mdl-textfield__label');
    this.contentFieldLabel.for = 'new-form-contentfield';
    this.formContentField.append(this.contentFieldTextArea);
    this.formContentField.append(this.contentFieldLabel);
    this.newPostFormFormForm.append(this.formContentField);
    this.newFormCloseButton = this.createElement('button', 'mdl-button', 'new-form-close-button');
    this.newFormCloseButton.classList.add('mdl-js-button');
    this.newFormCloseButton.classList.add('mdl-button--raised');
    this.newFormCloseButton.classList.add('mdl-js-ripple-effect');
    this.newFormCloseButton.textContent = 'Close'; // TODO i18n
    this.newFormPublishButton = this.createElement('button', 'mdl-button', 'new-form-publish-button');
    this.newFormPublishButton.classList.add('mdl-js-button');
    this.newFormPublishButton.classList.add('mdl-button--raised');
    this.newFormPublishButton.classList.add('mdl-js-ripple-effect');
    this.newFormPublishButton.textContent = 'Publish'; // TODO i18n
    this.newPostFormForm.append(this.newPostFormFormForm);
    this.newPostFormForm.append(this.newFormCloseButton);
    this.newPostFormForm.append(this.newFormPublishButton);
    this.newPostForm.append(this.newPostFormForm);
    this.contentSection.append(this.newPostForm);
    this.app.append(this.contentSection);
    // Create add post button
    this.addPostButton = this.createElement('button', 'mdl-button', 'add-post-button');
    this.addPostButton.classList.add('mdl-js-button');
    this.addPostButton.classList.add('mdl-button--fab');
    this.addPostButton.classList.add('mdl-js-ripple-effect');
    this.addPostButtonSign = this.createElement('i', 'add-icon');
    this.addPostButtonSign.classList.add('material-icons');
    this.addPostButtonSign.textContent = 'add';
    this.addPostButton.append(this.addPostButtonSign);
    this.app.append(this.addPostButton);
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

  getElement (selector) {
    const element = document.querySelector(selector);
    return element;
  }

  bindAddPost (handler) {
    this.newFormPublishButton.addEventListener('click', (event) => {
      event.preventDefault();

      if (this._postContent && this._postTitle) {
        handler(this._postTitle, this._postContent);
        this._resetFormInput();
      }
    });
  }

  displayAllPosts (posts) {
    this.clearPosts();
    posts.forEach((post) => this.displayPost(post));
  }

  get _postTitle () {
    return this.titleFieldInput.value;
  }

  get _postContent () {
    return this.contentFieldTextArea.value;
  }

  _resetFormInput () {
    this.titleFieldInput.value = '';
    this.contentFieldTextArea.value = '';
  }

  displayPost (post) {
    const articleElement = this.createElement('article');
    articleElement.className = 'post mdl-shadow--4dp';
    const h3Element = this.createElement('h3');
    h3Element.textContent = post.title;
    const pElement = this.createElement('p');
    pElement.textContent = post.content;
    const shareButtonElement = this.createElement('button');
    shareButtonElement.className = 'share-post-button mdl-button mdl-js-button mdl-button--fab mdl-js-ripple-effect';
    const materialIconElement = this.createElement('i');
    materialIconElement.className = 'material-icons';
    materialIconElement.textContent = 'share';
    shareButtonElement.append(materialIconElement);

    articleElement.append(h3Element);
    articleElement.append(pElement);
    // TODO add share key
    // articleElement.appendChild(shareButtonElement);

    this.postsSection.append(articleElement);
  }

  clearPosts () {
    this.postsSection.innerHTML = '';
  }
}
