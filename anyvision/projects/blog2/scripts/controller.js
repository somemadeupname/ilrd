export default class Controller {
  constructor (model, view) {
    this.model = model;
    this.view = view;

    this.displayPostsOnLoad(this.model.getPosts());
  }

  handleAddPost = (postContent) => {
    this.model.addPost(postContent)
  };

  handleEditPost = (id, postContent) => {
    this.model.editPost(id, postContent);
  };

  handleDeletePost = (id) => {
    this.model.deletePost(id);
  };

  displayPostsOnLoad (posts) {
    this.view.displayAllPosts(posts);
  }
}
