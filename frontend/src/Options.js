// -- React --
import React from "react";
import NextButton from "./Components/NextButton";

// -- Module --
const Options = ({timetables, setTimetables}) => {
  return (
    <div className="control-bar">
      <h3>Bar :)</h3>
      <NextButton timetables={timetables} setTimetables={setTimetables}/>
    </div>
  )
}

// -- Exports --
export default Options;
