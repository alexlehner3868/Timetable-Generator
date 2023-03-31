// -- React --
import React, { useEffect, useState } from "react";
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';
import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';
import ControlButtons from "./Components/NonEssentialComponents/ControlButtons";
// -- Windows --
import MainWindow from './MainWindow';
import Sidebar from './Sidebar';
import Options from './Options';
import HelpMenu from "./Components/HelpMenu";
import Message from "./Components/NonEssentialComponents/Message";
// -- Components --
import Generate from './Components/Generate';

// -- Styles --
import './index.css'
import './tabs.css'

// -- Module --
function App() {
  // -- Set document title (tab) dynamically based on visability
  document.addEventListener("visibilitychange", () => {
    if (document.visibilityState === 'visible') {
     document.title = "Live Timetable Love"
    } else {
      document.title = "WE MISS YOU! ❤️"
    }
  });
  // -- State --
  // Set of courses to consider
  const [courses,   setCourses]   = useState(new Set());
  useEffect(() => { // save when updated
    if (courses && courses.size) {
      localStorage.setItem("courses", JSON.stringify(Array.from(courses)));
      console.log("saved courses", JSON.parse(localStorage.getItem("courses")));
    }
  }, [courses]);
  useEffect(() => { // restore on first render
    const courses = new Set(JSON.parse(localStorage.getItem("courses")));
    if (courses && courses.size) {
      setCourses(courses);
      console.log("restored courses", courses);
    }
  }, []);

  // Message to the user
  const [message,   setMessage]   = useState("");
  useEffect(() => { // save when updated
    if (message && message.length) {
      localStorage.setItem("message", JSON.stringify(message));
      console.log("saved message", JSON.parse(localStorage.getItem("message")));
    }
  }, [message]);
  useEffect(() => { // restore on first render
    const message = JSON.parse(localStorage.getItem("message"));
    if (message && message.length) {
      setMessage(message);
      console.log("restored message", message);
    }
  }, []);

  
  // Timetable(s) generated
  const [ttbIndex,   setTtbIndex]   = useState(0);
  const [timetables, setTimetables] = useState([]);
  useEffect(() => { // save when updated
    if (timetables && timetables.length) {
      localStorage.setItem("timetables", JSON.stringify(timetables));
      localStorage.setItem("ttbIndex", JSON.stringify(ttbIndex));
      console.log("saved timetables", JSON.parse(localStorage.getItem("timetables")));
    }
  }, [timetables, ttbIndex]);
  useEffect(() => { // restore on first render
    const timetables = JSON.parse(localStorage.getItem("timetables"));
    const ttbIndex   = JSON.parse(localStorage.getItem("ttbIndex"));
    if (timetables && timetables.length) {
      setTimetables(timetables);
      setTtbIndex(ttbIndex);
      console.log("restored timetable", timetables);
    }
  }, []);

  // Constraints supplied by the user
  const [constraints, setConstraints] = useState(new Set());
  useEffect(() => { // save when updated
    if (constraints && constraints.size) {
      localStorage.setItem("constraints", JSON.stringify(Array.from(constraints)));
      console.log("saved constraints", JSON.parse(localStorage.getItem("constraints")));
    }
  }, [constraints]);
  useEffect(() => { // restore on first render
    const constraints = new Set(JSON.parse(localStorage.getItem("constraints")));
    if (constraints && constraints.size) {
      setConstraints(constraints);
      console.log("restored constraints", constraints);
    }
  }, []);

  const [num_timetables, setNumTimetables] = useState();
  useEffect(() => { // save when updated
    if (num_timetables && num_timetables > 0 && num_timetables < 41) {
      localStorage.setItem("num_time", JSON.stringify(num_timetables));
      console.log("saved number of timetables", JSON.parse(localStorage.getItem("num_time")));
    }
  }, [num_timetables]);
  useEffect(() => { // restore on first render
    const num_timetables = JSON.parse(localStorage.getItem("num_time"));
    if (num_timetables && num_timetables > 0 && num_timetables < 41) {
      setNumTimetables(num_timetables);
      console.log("restored num_timetables", num_timetables);
    }
  }, []);

  // Used to store the tabIndex of the timetable (ie F vs W)
  const [tabIndex, setTabIndex] = useState(0);


  return (
    <div className="App">
      <head>
        <title>Live Timetable Love</title>
        <link rel="preconnect" href="https://fonts.googleapis.com"/> 
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin/> 
        <link href="https://fonts.googleapis.com/css2?family=Roboto+Mono:ital,wght@0,300;0,400;0,600;1,300&family=Rubik:wght@600;700&display=swap" rel="stylesheet"/>      </head>
      <header className="Website-Header">
        <h1 class="website-name">Live Timetable Love</h1>
        <HelpMenu/>
      </header>
      <div className="whole-webpage">
        <Options    timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex} num_timetables={num_timetables} setNumTimetables={setNumTimetables} setTabIndex={setTabIndex}/>
        <MainWindow message={message} timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex} constraints={constraints} setConstraints={setConstraints} tabIndex={tabIndex} setTabIndex={setTabIndex}/>
        <Sidebar    setMessage={setMessage} courses={courses} setCourses={setCourses} constraints={constraints} setConstraints={setConstraints} setTimetables={setTimetables} setTtbIndex={setTtbIndex} num_timetables={num_timetables} setNumTimetables={setNumTimetables}/>
        <Message message={message}/>
        <p className="dedication">Dedicated to Professor Hans Kunov</p>
        <p></p>
        </div>
    </div>
  );
}

export default App;
