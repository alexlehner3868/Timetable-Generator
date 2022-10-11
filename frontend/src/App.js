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
  // second page
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
  
  // create a timetable array
  // 2d array: [course_id, course_name, course_type, section_id]
  // array is size 11 hours*5 days*2 semesters = 110 elements
  const [timetable, settimetable] = useState([[]]);
  const entire_timetable = [];
  // third page
  useEffect(() => {
    // Using fetch to fetch the api from 
    // flask server it will be redirected to proxy
    fetch("/").then((res) =>
        res.json().then((timetable) => {
            settimetable(
              // code to accept each timetable grid item and set array properly
              // row.map((col)=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
              entire_timetable = timetable
            );
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
        <button type="button" onclick="window.location.href='{{ url_for( 'move_forward') }}';">Forward</button>
      </div>
    </div>
  );
}

export default App;
