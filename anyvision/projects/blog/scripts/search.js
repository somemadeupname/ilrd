function search() {
  // TODO use event listener
  let searchQuery = document.getElementById('search_box').value;
  showSearchResults(searchQuery);
}

function showSearchResults(searchQuery) {

  // clear currently visible posts
  document.getElementById('posts-id').innerHTML = '';
  // TODO use safe regex
  let searchRegex = new RegExp(searchQuery, 'i');

  Object.keys(localStorage).forEach(function (key) {
    if (searchRegex.test(key) || searchRegex.test(localStorage.getItem(key))) {
      createPostNode(key, localStorage.getItem(key));
    }
  });
}

