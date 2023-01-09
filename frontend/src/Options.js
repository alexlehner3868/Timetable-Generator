// -- React --
import React from "react";
import NextButton from "./Components/NonEssentialComponents/NextButton";
import BackButton from "./Components/NonEssentialComponents/BackButton";

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
