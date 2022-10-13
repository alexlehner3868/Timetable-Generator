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
    const num_days  = 6;
    const num_hours = 11;
    const timetable = new Array(num_hours); 
    let count = 0;
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(num_days).fill(null); 
        
    }
    if(props.courses !== undefined){
        for(let i = 0; i < num_hours; i++){
            for(let j = 0; j < num_days; j++){
                timetable[i][j] = (props.courses[count] !== undefined ? props.courses[count] : {
                    classID: "",
                    classSection: "",
                    classColorIdx: "",
                    classType: "",
                });
                console.log("tdata at" + count);
                console.log(timetable[i][j]);
                count++;
            }
        }
    }else{
        for(let i = 0; i < num_hours; i++){
            for(let j = 0; j < num_days; j++){
                timetable[i][j] = {
                    classID: "",
                    classSection: "",
                    classColorIdx: "",
                    classType: "",
                };
                count++;
            }
        }
    }
    console.log("props in timetable")
    console.log(props.courses);

  
    return (
        <div className="timetable"> 
        {timetable.map((row)=>{
            return (
                <div>
                {    
                    row.map((col)=> <Period  ClassID={col.classID} classSection={col.classSection} classColorIdx={col.classColorIdx} classType={col.classType}/>)
                }
                </div>
                
            )

        })}
        </div>

    )
    
}

export default Timetable;
