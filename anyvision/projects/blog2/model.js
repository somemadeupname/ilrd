/**
 * Model to create, read, update and delete via db
 */
class Model {
  constructor () {
    this.db = window.localStorage;
  }

  /**
   * Add post
   * @param postContent - stingified title and content of a post.
   */
  addPost (postContent) {
    this.db.setItem(Date.now().toString(), JSON.stringify(postContent));
  }

  editPost (id, updatedContent) {
    const postToEdit = this.db.getItem(id);
    if (postToEdit === null) {
      throw Error('Couldn\'t edit post. ID couldn\'t be found');
    }
    this.db.setItem(id, JSON.stringify(updatedContent));
  }

  deletePost (id) {
    if (this.db.getItem(id) === null) {
      throw Error('Couldn\'t delete post. ID couldn\'t be found');
    }
    this.db.removeItem(id);
  }
}
