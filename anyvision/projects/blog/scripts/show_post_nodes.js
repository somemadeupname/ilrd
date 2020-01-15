function createPostNode (title, content) {
  const articleElement = document.createElement('article');
  articleElement.className = 'post mdl-shadow--4dp';
  const h3Element = document.createElement('h3');
  h3Element.textContent = title;
  const pElement = document.createElement('p');
  pElement.textContent = content;
  // console.log(content.replace('\n', '<br>'));
  const shareButtonElement = document.createElement('button');
  shareButtonElement.className = 'share-post-button mdl-button mdl-js-button mdl-button--fab mdl-js-ripple-effect';
  const materialIconElement = document.createElement('i');
  materialIconElement.className = 'material-icons';
  materialIconElement.textContent = 'share';
  shareButtonElement.appendChild(materialIconElement);

  articleElement.appendChild(h3Element);
  articleElement.appendChild(pElement);
  // TODO add share key
  // articleElement.appendChild(shareButtonElement);

  document.getElementById('posts-id').appendChild(articleElement);
}

(function showPostNodes () {
  Object.keys(localStorage).forEach(function (key) {
    const post = JSON.parse(localStorage.getItem(key));
    createPostNode(post.title, post.content);
  });
})();