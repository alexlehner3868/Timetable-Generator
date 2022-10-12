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
  const [timetable, settimetable] = useState({

  }

  );
  let entire_timetable = {};
  
  // third page
  useEffect(() => {
    // Using fetch to fetch the api from 
    // flask server it will be redirected to proxy
    fetch("/basic-schedule").then((res) =>
        res.json().then((timetable) => {
          /*
          let new_timetable = new Array(timetable.length);
          for (let i = 0; i<timetable.length; i++) {
            new_timetable[i][0] = timetable[i][0];
            new_timetable[i][1] = timetable[i][1];
            new_timetable[i][2] = timetable[i][2];
            classID: new_timetable[i][0],
            classSection: new_timetable[i][1],
            classNum: new_timetable[i][2]
          }*/
          const arr = ['classID', 'classSection', 'classNum'];
          
          let timetables = {}
          console.log(timetable.length);
          for (let i = 0; i < timetable.length; i++) {
            let obj = {};
            obj['classID'] = timetable[i][0];
            obj['classSection'] = timetable[i][1];
            obj['classNum'] = i; // I fucked this up and forget type. classNum is for color
            //arr.forEach(child_element => {
           //   obj[child_element] = timetable[element][child_element];
            //  console.log(obj);
            //});
            timetables[i] = obj;
            console.log("T: "+ timetables);
            console.log("O"+ obj);
          }
          // obj = {classID: '', classSection = '', classNum =''}
          

          settimetable(
            // code to accept each timetable grid item and set array properly
            // row.map((col)=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
            // entire_timetable = timetable
           // entire_timetable = timetables
           timetables

          );
          console.log("Entire Timetale");
          console.log(entire_timetable);
        })
    );
  }, []);
  console.log("ALEX")
  console.log(timetable)
  return (
    <div className="App">
      <header className="App-header">
        <h1>Live Timetable Love</h1>
      </header>
      <div className='whole-webpage'>
        <MainWindow props={entire_timetable} className="main-window"/>
        <Sidebar className="sidebar"/>
        <button type="button" onclick="window.location.href='{{ url_for( 'move_forward') }}';">Forward</button>
      </div>
    </div>
  );
}

export default App;
