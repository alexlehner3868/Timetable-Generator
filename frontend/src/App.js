// -- React --
import React, { useEffect, useState } from "react";

// -- Windows --
import MainWindow from './MainWindow';
import Sidebar from './Sidebar';
import Options from './Options';

// -- Components --
import Generate from './Components/Generate';
import AddConstraintButton from './Components/NonEssentialComponents/AddConstraintButton';

// -- Styles --
import './index.css'
import './tabs.css'

// -- Module --
function App() {
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

  // NOTE: likely temporary while we introduce constraints connections
  const addedConstraint = (constraint) =>{
    setConstraints(constraint)
  }

  return (
    <div className="App">
      <header className="Website-Header">
        <h1>Live Timetable Love</h1>
      </header>
      <div className="whole-webpage">
        <Options    timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
        <MainWindow timetables={timetables} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
        <Sidebar    courses={courses} setCourses={setCourses} addedConstraint={addedConstraint}/>
        <Generate   courses={courses} setTimetables={setTimetables}/>
        <h1 className="message">
          <p>
            Message: {message}
          </p>
        </h1>
      </div>
    </div>
  );
}

export default App;
