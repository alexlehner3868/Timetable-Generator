// -- React --
import React from "react";
import NextButton from "./Components/NonEssentialComponents/NextButton";
import BackButton from "./Components/NonEssentialComponents/BackButton";
import DownloadButton from "./Components/DownloadButton";

// -- Module --
const Options = ({timetables, ttbIndex, setTtbIndex}) => {
  let timetable_index_str;
  if(timetables.length === 0 || ttbIndex == NaN){
   // timetable_index_str = "";
   timetable_index_str = "No timetables";
  }else{
    timetable_index_str = (ttbIndex+1).toString(); 
    timetable_index_str += "/";
    timetable_index_str +=(timetables.length).toString();
  }
  return (
    <div className="control-bar">
  
      <BackButton  nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <p className="current-timetable-number">{timetable_index_str}</p>
      <NextButton nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
  
      <DownloadButton  timetables={timetables} ttbIndex={ttbIndex}/>
    </div>
  )
}

// -- Exports --
export default Options;
