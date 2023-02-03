// -- React --
import React, { useEffect, useState } from "react";
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';
import { AwesomeButton } from "react-awesome-button";
import "react-awesome-button/dist/styles.css";


// -- Windows --
import MainWindow from './MainWindow';
import Sidebar from './Sidebar';
import Options from './Options';
import HelpMenu from "./Components/HelpMenu";

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

  return (
    <div className="App">
      <head>
        <title>Live Timetable Love</title>
      </head>
      <header className="Website-Header">
        <h1 class="website-name">Live Timetable Love</h1>
        <HelpMenu/>
      </header>
      <div className="whole-webpage">
        <Options    timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
        <MainWindow timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
        <Sidebar    courses={courses} setCourses={setCourses} constraints={constraints} setConstraints={setConstraints}/>
        <Generate   courses={courses} constraints={constraints} setTimetables={setTimetables}/>
        <p class="dedication">Dedicated to Professor Hans Kunov</p>
        </div>
    </div>
  );
}

export default App;
