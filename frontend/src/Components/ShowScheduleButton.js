import { useState } from 'react';
import ShowScheduleService from './AddCourseService'

const ShowScheduleButton = (props) => {
    function ShowSchedule(){
        
      console.log("trying to display the schedule")
        var out = fetch(`http://localhost:5000/basic-schedule`,{
            'method':'POST',
             headers : {
            'Content-Type':'text/plain'
      }
    })
        
    return out;
    }

  return (
       <div>
            <button onClick={() => ShowSchedule()} className="btn btn-primary mt-2"> Show Schedule </button>
       </div>
  )}

export default ShowScheduleButton;
