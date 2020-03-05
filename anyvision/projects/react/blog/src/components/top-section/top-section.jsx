import React from 'react';
import Header from "../header/header";
import TopSectionImage from '../top-section-image/top-section-image';
import LinksNavBar from '../links-nav-bar/links-nav-bar'
import './top-section.css'

class TopSection extends React.Component {
  render () {
    return (
        <div className='top-section'>
          <TopSectionImage/>
          <Header/>
          <LinksNavBar/>
        </div>
  )
  }
}

export default TopSection;