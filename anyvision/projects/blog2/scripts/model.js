/**
 * Model to create, read, update and delete via db
 */
export default class Model {
  constructor () {
    this.db = window.localStorage;
    this.posts = [];
  }

  getPosts () {
    const posts = [];
    Object.keys(this.db).forEach((key) => {
      const post = JSON.parse(this.db.getItem(key));
      posts.push(post);
    });
    return posts;
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
    // TODO put errors elsewhere?
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
