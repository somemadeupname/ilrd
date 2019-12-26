function search(event) {
  // const ENTER = 'Enter';
  // if (event.key === 'Enter') {
    let searchQuery = document.getElementById('search_box').value;
    showSearchResults(searchQuery);
  // }
}

function showSearchResults(searchQuery) {

  // clear currently visible posts
  document.getElementById('posts-id').innerHTML = '';

  let searchRegex = new RegExp(searchQuery, 'i');

  Object.keys(localStorage).forEach(function (key) {
    if (searchRegex.test(key) || searchRegex.test(localStorage.getItem(key))) {
      showPostNode(key, localStorage.getItem(key));
    }
  });
}

