// TODO add event listener to replace inline in html

function addToLocalStorage() {
  let title = document.getElementById('new-form-titlefield').value;
  let content = document.getElementById('new-form-contentfield').value;
  window.localStorage.setItem(title, content);
}

