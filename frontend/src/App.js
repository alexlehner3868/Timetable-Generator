// -- React --
import React, { useEffect, useState } from "react";
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';
import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';

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

  const removeAll = (constraint) => {
    if (document.getElementById("morning_priorities")) {
      document.getElementById("morning_priorities").value = 0;
    } if (document.getElementById("afternoon_priorities")) {
      document.getElementById("afternoon_priorities").value = 0;
    } if (document.getElementById("evening_priorities")) {
      document.getElementById("evening_priorities").value = 0;
    } if (document.getElementById("minimize_priorities")) {
      document.getElementById("minimize_priorities").value = 0;
    } if (document.getElementById("async_priorities")) {
      document.getElementById("async_priorities").value = 0;
    } if (document.getElementById("sync_priorities")) {
      document.getElementById("sync_priorities").value = 0;
    } if (document.getElementById("lunch_priorities")) {
      document.getElementById("lunch_priorities").value = 0;
    } if (document.getElementById("dinner_priorities")) {
      document.getElementById("dinner_priorities").value = 0;
    } if (document.getElementById("before_priorities")) {
      document.getElementById("before_priorities").value = 0;
    } if (document.getElementById("before_value")) {
      document.getElementById("before_value").value = "";
    } if (document.getElementById("after_priorities")) {
      document.getElementById("after_priorities").value = 0;
    } if (document.getElementById("after_value")) {
      document.getElementById("after_value").value = "";
    } if (document.getElementById("max_class_priorities")) {
      document.getElementById("max_class_priorities").value = 0;
    } if (document.getElementById("max_class_value")) {
      document.getElementById("max_class_value").value = "";
    } if (document.getElementById("max_break_priorities")) {
      document.getElementById("max_break_priorities").value = 0;
    } if (document.getElementById("max_break_value")) {
      document.getElementById("max_break_value").value = "";
    }
    setConstraints(prev => new Set())
    setCourses(prev => new Set())
  };

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
        <Options    timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
        <MainWindow timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex} constraints={constraints} setConstraints={setConstraints}/>
        <Sidebar    courses={courses} setCourses={setCourses} constraints={constraints} setConstraints={setConstraints}/>
        
        <Generate   courses={courses} constraints={constraints} setTimetables={setTimetables} setTtbIndex={setTtbIndex}/>
        <p class="dedication">Dedicated to Professor Hans Kunov</p>
        <p></p>
        <AwesomeButton className="clear-button" onPress={event => removeAll()}>Clear Courses & Constraints</AwesomeButton>
        </div>
    </div>
  );
}

export default App;
