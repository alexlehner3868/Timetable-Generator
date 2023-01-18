// -- React --
import React from "react";
import NextButton from "./Components/NonEssentialComponents/NextButton";
import BackButton from "./Components/NonEssentialComponents/BackButton";
import DownloadButton from "./Components/DownloadButton";

// -- Module --
const Options = ({timetables, ttbIndex, setTtbIndex}) => {
  return (
    <div className="control-bar">
      <BackButton  nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <p className="current-timetable-number">{ttbIndex+1} / {timetables.length}</p>
      <NextButton nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <DownloadButton  timetables={timetables} ttbIndex={ttbIndex}/>
    </div>
  )
}

// -- Exports --
export default Options;
