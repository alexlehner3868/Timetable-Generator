// -- React --
import React from "react";
import NextButton from "./Components/NonEssentialComponents/NextButton";
import BackButton from "./Components/NonEssentialComponents/BackButton";
import DownloadButton from "./Components/DownloadButton";

// -- Module --
const Options = ({timetables, ttbIndex, setTtbIndex, num_timetables, setNumTimetables}) => {
  let timetable_index_str;
  if (timetables.length === 0 || ttbIndex == NaN) {
   // timetable_index_str = "";
   timetable_index_str = "No timetables";
  } else{
    timetable_index_str = (ttbIndex+1).toString(); 
    timetable_index_str += "/";
    timetable_index_str +=(timetables.length).toString();
  }

  function handleSubmitNumTimetables (event) {
    event.preventDefault();
    const num_timetables_val = document.getElementById("num_timetables").value;
    if (num_timetables_val && num_timetables_val > 0 && num_timetables_val < 41) {
      setNumTimetables(num_timetables_val);
      //console.log("printing the new num timetables", num_timetables_val)
    }
  } 
  console.log(num_timetables)

  return (
    <div className="control-bar">
      
      <p className="current-timetable-number">Timetables to Show</p>
      
      <input type="number" defaultValue={num_timetables} id="num_timetables" min="1" max="40" onChange = {handleSubmitNumTimetables} ></input>

      <BackButton  nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
      <p className="current-timetable-number">{timetable_index_str}</p>
      <NextButton nTimetables={timetables.length} ttbIndex={ttbIndex} setTtbIndex={setTtbIndex}/>
  
      <DownloadButton  timetables={timetables} ttbIndex={ttbIndex}/>
    </div>
  )
}

// -- Exports --
export default Options;
