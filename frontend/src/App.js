// -- React --
import React, { useEffect, useState } from "react";

// -- Windows --
import MainWindow from './MainWindow';
import Sidebar from './Sidebar';
import Options from './Options';

// -- Components --
import Generate from './Components/Generate';

// -- Styles --
import './index.css'
import './tabs.css'

// -- Module --
function App() {
  // -- State --
  // Set of courses to consider
  const [courses,   setCourses]   = useState(new Set());
  useEffect(() => { // save when updated
    if (courses.size) {
      localStorage.setItem("courses", JSON.stringify(Array.from(courses)));
      console.log("saved courses", JSON.parse(localStorage.getItem("courses")));
    }
  }, [courses]);
  useEffect(() => { // restore on first render
    const courses = new Set(JSON.parse(localStorage.getItem("courses")));
    if (courses.size) {
      setCourses(courses);
      console.log("restored courses", courses);
    }
  }, []);

  // Message to the user
  const [message,   setMessage]   = useState("");
  useEffect(() => { // save when updated
    if (message.length) {
      localStorage.setItem("message", JSON.stringify(message));
      console.log("saved message", JSON.parse(localStorage.getItem("message")));
    }
  }, [message]);
  useEffect(() => { // restore on first render
    const message = JSON.parse(localStorage.getItem("message"));
    if (message.length) {
      setMessage(message);
      console.log("restored message", message);
    }
  }, []);

  // Timetable(s) generated
  const [timetable, setTimetable] = useState([]);
  useEffect(() => { // save when updated
    if (timetable.length) {
      localStorage.setItem("timetable", JSON.stringify(timetable));
      console.log("saved timetable", JSON.parse(localStorage.getItem("timetable")));
    }
  }, [timetable]);
  useEffect(() => { // restore on first render
    const timetable = JSON.parse(localStorage.getItem("timetable"));
    if (timetable.length) {
      setTimetable(timetable);
      console.log("restored timetable", timetable);
    }
  }, []);

  return (
    <div className="App">
      <header className="Website-Header">
        <h1>Live Timetable Love</h1>
      </header>
      <div className="whole-webpage">
        <Options/>
        <MainWindow timetable={timetable}/>
        <Sidebar    courses={courses} setCourses={setCourses}/>
        <Generate   courses={courses} setTimetable={setTimetable}/>
        <h1 className="message">
          <p>
            Courses: {[...courses].join(", ")}
          </p>
          <p>
            Message: {message}
          </p>
        </h1>
      </div>
    </div>
  );
}

export default App;
