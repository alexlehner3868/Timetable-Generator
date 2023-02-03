// -- React --
import React from "react";
import {useState} from "react";

// -- Components --
import EditCourse from './EditCourse';

// -- Data --
import Data from "../data/courses.json";

// -- Module --
const SearchBar = ({courses, setCourses}) => {
  const [query, setQuery]  = useState("");

  const showResults = (query) =>  {
    var x = document.getElementById("search-results-box-id");
    var y = document.getElementById("active-courses");
    if(query === "" || query.length === 0){
      x.style.display = "none";
      y.style.display = "block";
    }else{
      x.style.display = "block";
      y.style.display = "none";
    }
  }

  return (
    <div >
      <div className="search-bar-div">
        <form id="search-course-form">
          <input
            type="text"
            placeholder="Search For A Class..."
            className="search-bar"
            onChange={event => setQuery(event.target.value)}
            onInput={event => showResults(event.target.value)}
          />   
      </form>
      
      </div>

      <div className="search-results-box" id="search-results-box-id">
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
                  showResults={showResults}
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
export default SearchBar;
