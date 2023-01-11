// -- React --
import React from "react";
import NextButton from "./Components/NonEssentialComponents/NextButton";
import BackButton from "./Components/NonEssentialComponents/BackButton";
import DownloadButton from "./Components/DownloadButton";

// -- Module --
const Options = ({timetables, ttbIndex, setTtbIndex}) => {
  return (
    <div className="control-bar">
      <h3>Bar :)</h3>
      <BackButton nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <NextButton nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <DownloadButton timetables={timetables} ttbIndex={ttbIndex}/>
    </div>
  )
}

// -- Exports --
export default Options;
