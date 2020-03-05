import React from 'react';
import IconButton from '@material-ui/core/IconButton';
import './add_post_button.css';

class AddPostButton extends React.Component {
  render(){
    return (
        <IconButton aria-label='add' id='add-post-button'>
        </IconButton>
    )
  }
}

export default AddPostButton;