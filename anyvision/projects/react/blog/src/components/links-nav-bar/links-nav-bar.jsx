import React from 'react';
import './links-nav-bar.css'
import facebook_logo from './facebook.svg';
import twitter_logo from './twitter.svg';
import linkedin_logo from './linkedin.svg';
import instagram_logo from './instagram.svg';

class LinksNavBar extends React.Component {
  render () {
    return (
        <nav className='links-nav-bar'>
          <a className="nav-link" href="https://www.facebook.com/" target="_blank" rel="noopener noreferrer">
            <img src={facebook_logo} alt="fb_icon" width="32" height="32"/></a>
          <a className="nav-link" href="https://www.twitter.com/" target="_blank" rel="noopener noreferrer">
            <img src={twitter_logo} alt="tw_icon" width="32" height="32"/></a>
          <a className="nav-link" href="https://www.linkedin.com/" target="_blank" rel="noopener noreferrer">
            <img src={linkedin_logo} alt="li_icon" width="32" height="32"/></a>
          <a className="nav-link" href="https://www.instagram.com/" target="_blank" rel="noopener noreferrer">
            <img src={instagram_logo} alt="ig_icon" width="32" height="32"/></a>
        </nav>
    )
  }
}

export default LinksNavBar;