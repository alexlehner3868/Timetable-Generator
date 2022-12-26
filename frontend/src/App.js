// -- React --
import React, { useState } from "react";

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
  const [courses,   setCourses]   = useState(new Set());
  const [message,   setMessage]   = useState("");
  const [timetable, setTimetable] = useState([]);

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
