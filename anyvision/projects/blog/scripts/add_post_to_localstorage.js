// TODO add event listener to replace inline in html

function addToLocalStorage () {
  const title = document.getElementById('new-form-titlefield').value;
  const content = document.getElementById('new-form-contentfield').value;
  window.localStorage.setItem(Date.now().toString(), JSON.stringify({ title, content }));
}
