import React from 'react';
import profile_image from './coffee.png';

class TopSectionImage extends React.Component {
  render () {
    return (
        <img className='top-section-image' src={profile_image} alt='top-section'></img>
    )
  }
}

export default TopSectionImage;