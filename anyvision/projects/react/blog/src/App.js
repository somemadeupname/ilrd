import React from 'react';
import logo from './logo.svg';
import './App.css';
import TopSection from './components/top-section/top-section';
import Footer from './components/footer/footer';
import Main from './components/main/main';

function App() {
  return (
    <div>
      <TopSection className='top-section'></TopSection>
      <Main className='main'></Main>
      <Footer className='footer'></Footer>
    </div>
  )
}

export default App;