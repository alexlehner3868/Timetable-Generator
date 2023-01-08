// -- React --
import React from "react";
import NextButton from "./Components/NextButton";
import BackButton from "./Components/BackButton";

// -- Module --
const Options = ({timetables, setTimetables}) => {
  return (
    <div className="control-bar">
      <h3>Bar :)</h3>
      <BackButton timetables={timetables} setTimetables={setTimetables}/>
      <NextButton timetables={timetables} setTimetables={setTimetables}/>
    </div>
  )
}

// -- Exports --
export default Options;
