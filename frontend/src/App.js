import './App.css';
import './index.css'
import Sidebar from './Sidebar';
import MainWindow from './MainWindow';
import React, { useState, useEffect } from "react";

function App() {
    const [data, setdata] = useState({
      name: "",
      age: 0,
      date: "",
      programming: "",
  });

  // Using useEffect for single rendering
  useEffect(() => {
      // Using fetch to fetch the api from 
      // flask server it will be redirected to proxy
      fetch("/data").then((res) =>
          res.json().then((data) => {
              // Setting a data from api
              setdata({
                  name: data.Name,
                  age: data.Age,
                  date: data.Date,
                  programming: data.programming,
              });
          })
      );
  }, []);
  const tdata = ""
  // Using useEffect for single rendering
  useEffect(() => {
    // Using fetch to fetch the api from 
    // flask server it will be redirected to proxy
    fetch("/gen").then((res) =>
        res.json().then((data) => {
            // Setting a data from api
            tdata = data
        })
    );
}, []);

  return (
    <div className="App">
      <header className="App-header">
        <h1>Live Timetable Love</h1>
      </header>
      <div className='whole-webpage'>
        <MainWindow className="main-window"/>
        <Sidebar className="sidebar"/>
        <p>{tdata}</p>
      </div>
    </div>
  );
}

export default App;
