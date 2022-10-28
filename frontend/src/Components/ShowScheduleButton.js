import { useState } from 'react';
import ShowScheduleService from './AddCourseService'

const ShowScheduleButton = (props) => {
    
    function ShowSchedule(){
        var out = fetch(`http://localhost:5000/basic-schedule`,{
            'method':'POST',
             headers : {
            'Content-Type':'text/plain'
      }
    })
        return out;
    }
    const handleSubmit=(event)=>{
      console.log("trying to display the schedule")
      event.preventDefault()
    }

  return (
       <div>
            <button onClick={() => ShowSchedule()} className="btn btn-primary mt-2"> Show Schedule </button>
       </div>
  )}

export default ShowScheduleButton;
