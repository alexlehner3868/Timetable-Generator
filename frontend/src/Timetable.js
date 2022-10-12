import React from "react";
import Period from "./Period";

//TODO:
// Currently only printing for one semester. Need to do both semesters. 
// Decide how to view the 2 semesters
const Timetable = (props) =>{
     
    /*
    const timetable = new Array(11); 
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(6).fill(null); 
    }
*/
//Testing timetable
    const timetable = new Array(2); 
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(2).fill(null); 
    }
    console.log(props);
    return (
        <div className="timetable"> 
        {timetable.map((row)=>{
            return (
                <div>
                {    
                    row.map((col)=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
                }
                </div>
                
            )
        })}
        </div>

    )
}

export default Timetable;
