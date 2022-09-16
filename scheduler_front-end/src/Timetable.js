import React from "react";
import Period from "./Period";

//TODO:
// Currently only printing for one semester. Need to do both semesters. 
// Decide how to view the 2 semesters
const Timetable = (props) =>{
    //make sidebar for seaching classes, adding and removing
    //const sidebar = new Array(2);
    //sidebar[0] = new Array(3).fill(null);
    //sidebar[1] = new Array(1).fill(null);

    const timetable = new Array(10); 
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(5).fill(null); 
    }

    return (
        <div> 
        {timetable.map((row)=>{
            return (
                <div>{
                    row.map(()=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
                }
                </div>
            )
        })}
        </div>

    )
}

export default Timetable;