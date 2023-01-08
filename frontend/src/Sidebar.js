// -- React --
import React from "react";
import {useState} from "react";

// -- Components --
import EditCourse from './Components/EditCourse';

// -- Data --
import Data from "./data/courses.json";

// -- Module --
const Sidebar = ({courses, setCourses}) => {
  const [query, setQuery]  = useState("");

  return (
    <div className="sidebar">
      <div className="search-bar">
      <input
        type="text"
        placeholder="Search For Class"
        className="search-bar"
        onChange={event => setQuery(event.target.value)}
      />
      <i className="fa fa-magnifying-glass fa-lg"></i>
      </div>

      <div className="search-results-box">
        {
          Data.filter(class_result => {
            if (query === "") {
              //nothing in the search bar, don't show anything
              return class_result;
            } else if (class_result.ACAD_ACT_CD.toLowerCase().includes(query.toLowerCase())) {
              //returns array with all matches
              return class_result;
            } // TODO: add searching by class name here once we add class-Name to the database
            return false;
          }).map((class_result, index) => (
            <div className="search-results" key={index}>
              <div className="add-course-square" id="add-course-square" >
                <h1 className="course-code"> {class_result.ACAD_ACT_CD} </h1>
                <EditCourse
                  action="{{ url_for('send-request') }}"
                  method="post"
                  course={class_result.ACAD_ACT_CD}
                  setCourses={setCourses}
                />
              </div>
            </div>
          ))
        }
      </div>
    </div>
  )
}

// -- Exports --
export default Sidebar;
