import './App.css';
import './index.css'
import Sidebar from './Sidebar';
import MainWindow from './MainWindow';
import Form from './Components/Form';
import React, { useState, useEffect } from "react";
import ShowScheduleButton from './Components/ShowScheduleButton';
import RemoveCourseButton from './Components/RemoveCourseButton';
import AddConstraintButton from './Components/AddConstraintButton';

let counter = 0;

function App() {
  
  counter++;

  const [classes, setClasses] = useState([]);

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
        'Content-Type':'text/plain'
      }
    })
    .then(response => response.json())
    .then(response => setClasses(response))
    .catch(error => console.log(error))


  },[]);

  useEffect(()=>{
    fetch("/remove-class",{
      'methods':'GET',
      headers : {
        'Content-Type':'text/plain'
      }
    })
    .then(response => response.json())
    .then(response => setClasses(response))
    .catch(error => console.log(error))


  },[]);
  
  const [constraints, setConstraints] = useState([]);
  useEffect(()=>{
    fetch("/add-constraint",{
      'methods':'GET',
      headers : {
        'Content-Type':'text/plain'
      }
    })
    .then(response => response.json())
    .then(response => setConstraints(response))
    .catch(error => console.log(error))


  },[]);

  const insertedConstraint = (constraint) =>{
    setConstraints(constraint)
  }

  // create a timetable array
  // 2d array: [course_id, course_name, course_type, section_id]
  // array is size 11 hours*5 days*2 semesters = 110 elements
  const [timetable, settimetable] = useState({});
  const [result_message, setResultMessage] = useState("");
  let entire_timetable = {};
  // third page
  useEffect(() => {
    // Using fetch to fetch the api from 
    // flask server it will be redirected to proxy
    fetch("/basic-schedule").then((res) =>
        res.json().then((props) => {
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
          let timetable = props[1]
          let message  = props[0]
          // Save the error message (if there is one)
          setResultMessage(message)
          console.log("save emss", message)
          if (counter > 15) {
            console.log(counter)
            const arr = ['classID', 'classSection', 'classNum'];
            
            let timetables = new Array(2);
            for(let i = 0; i < 2; i++){
              timetables[i] = new Array(66);
            }
            console.log("HEEEEE")
            console.log(timetable.length);
            for (let i = 0; i < timetable.length; i++) {
              //console.log("length = "  + timetable.length + " i " + i);
              let obj = {};
              obj['classID'] = timetable[i][0];
              obj['classSection'] = timetable[i][1];
              obj['classType'] = timetable[i][2];
              obj['classColorIdx'] = timetable[i][3]; 
              obj['className'] = timetable[i][4];
              
              //arr.forEach(child_element => {
            //   obj[child_element] = timetable[element][child_element];
              //  console.log(obj);
              //});
              let sem = (i >= timetable.length/2 ? 1 : 0);
              let indx = (i < timetable.length/2 ? i : i - timetable.length/2);
              //console.log("Sem" + sem);

              timetables[sem][indx] = obj;
              //console.log("T: "+ timetables);
              //console.log("O"+ obj);
            }
            // obj = {classID: '', classSection = '', classNum =''}
            

            settimetable(
              // code to accept each timetable grid item and set array properly
              // row.map((col)=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
              // entire_timetable = timetable
            // entire_timetable = timetables
            timetables = timetable

            );
            console.log("Entire Timetale");
            console.log(timetables);
          }
        })
    );
  }, [classes]);
  
  
  const insertedClass = (class_) =>{
    const new_classes = [...classes,class_]
    setClasses(new_classes)
  }
  const removedClass = (class_) =>{
    setClasses(class_)
  }
  const addedConstraint = (constraint) =>{
    setConstraints(constraint)
  }

  

  return (
    <div class="App">
      <header class="App-header">
        <h1>Live Timetable Love</h1>
      </header>
      <Form action="{{ url_for('send-request') }}" method="post" insertedClass={insertedClass} />
      <RemoveCourseButton action="{{ url_for('remove-class') }}" method="post" removedClass={removedClass} />
      <AddConstraintButton action="{{ url_for('add-constraint') }}" method="post" addedConstraint={addedConstraint} />
      <ShowScheduleButton action="{{ url_for('basic-schedule') }}" method="post"  />
      <div className='whole-webpage'>
        <MainWindow timetableData={timetable} resultMessage ={result_message} class="main-window"/>
        <Sidebar class="sidebar"/>
      </div>
    </div>
  );
}

export default App;
