function showPostNode(title, content) {
  let articleElement = document.createElement('article');
  articleElement.className = 'post mdl-shadow--4dp';
  let h3Element = document.createElement('h3');
  h3Element.textContent = title;
  let pElement = document.createElement('p');
  pElement.textContent = content;

  articleElement.appendChild(h3Element);
  articleElement.appendChild(pElement);



  document.getElementById('posts-id').appendChild(articleElement);

  //TODO add button
}

function showPostNodes() {
  Object.keys(localStorage).forEach(function (key) {
    showPostNode(key, localStorage.getItem(key));
  });
}

showPostNodes();
