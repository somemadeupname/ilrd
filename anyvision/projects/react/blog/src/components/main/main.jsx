import React from 'react';
import './main.css'
import AddPostButton from '../add_post_button/add_post_button';

const spanStyle = {color:'red'}; //TODO remove this

class Main extends React.Component {
  render(){
    return (
        <div>
          <h1>
            <span style={spanStyle}>remove this: </span>
              this is where the main section goes
          </h1>
          <AddPostButton/>
        </div>

    )
  }
}

export default Main;