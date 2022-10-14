import './App.css';
import './index.css'
import Sidebar from './Sidebar';
import MainWindow from './MainWindow';
import Form from './Components/Form';
import React, { useState, useEffect } from "react";

function App() {
    const [data, setdata] = useState({
      name: "",
      age: 0,
      date: "",
      programming: "",
    });

    const [articles, setArticles] = useState([]);
  // Using useEffect for single rendering
  useEffect(() => {
      // Using fetch to fetch the api from 
      // flask server it will be redirected to proxy
      fetch("/data").then((res) =>
          res.json().then((data) => {
              console.log("IN DATA")
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
            console.log("IN DATA")
        })
    );
  }, []);
  
  useEffect(()=>{
    fetch("/send-request",{
      'methods':'GET',
      headers : {
        'Content-Type':'application/json'
      }
    })
    .then(response => response.json())
    .then(response => setArticles(response))
    .catch(error => console.log(error))


  },[])

  // create a timetable array
  // 2d array: [course_id, course_name, course_type, section_id]
  // array is size 11 hours*5 days*2 semesters = 110 elements
  const [timetable, settimetable] = useState({
  }

  );
  let entire_timetable = {};
  console.log("here")
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
          
          let timetables = new Array(2);
          for(let i = 0; i < 2; i++){
            timetables[i] = new Array(66);
          }
          console.log("HEEEEE")
          console.log(timetable.length);
          for (let i = 0; i < timetable.length; i++) {
            console.log("length = "  + timetable.length + " i " + i);
            let obj = {};
            obj['classID'] = timetable[i][0];
            obj['classSection'] = timetable[i][1];
            obj['classType'] = timetable[i][2];
            obj['classColorIdx'] = i+1; 
            //arr.forEach(child_element => {
           //   obj[child_element] = timetable[element][child_element];
            //  console.log(obj);
            //});
            let sem = (i >= timetable.length/2 ? 1 : 0);
            let indx = (i < timetable.length/2 ? i : i - timetable.length/2);
            console.log("Sem" + sem);
            timetables[sem][indx] = obj;
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
          console.log(timetables);
        })
    );
  }, []);
  
  const insertedArticle = (article) =>{
    const new_articles = [...articles,article]
    setArticles(new_articles)
  }
  
  console.log("ALEX")
  console.log(timetable)
  return (
    <div className="App">
      <header className="App-header">
        <h1>Live Timetable Love</h1>
      </header>
      <Form action="{{ url_for('send-request') }}" method="post" insertedArticle={insertedArticle} />
      <div className='whole-webpage'>
        <MainWindow timetableData={timetable} className="main-window"/>
        <Sidebar className="sidebar"/>
      </div>
    </div>
  );
}

export default App;
