// TODO make post box move with scroll, dim background around window
function clearForm() {
  document.getElementById('new-form-titlefield').value = '';
  document.getElementById('new-form-contentfield').value = '';
}

let newPostForm = document.querySelector('#new-post-form');
let showFormButton = document.querySelector('#add-post-button');
showFormButton.addEventListener('click', function () {
  newPostForm.style.display = 'block';
  clearForm();
});

let closeFormButton = document.getElementById('new-form-close-button');
closeFormButton.addEventListener('click', function () {
  newPostForm.style.display = 'none';
  clearForm();
});

let publishFormButton = document.getElementById('new-form-publish-button');
publishFormButton.addEventListener('click', function () {
  newPostForm.style.display = 'none';
  clearForm();
  location.reload();
});

